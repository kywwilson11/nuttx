/****************************************************************************
 * fs/mqueue/mq_open.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/stat.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <sched.h>
#include <mqueue.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>

#include <nuttx/mqueue.h>
#include <nuttx/fs/fs.h>

#include "inode/inode.h"
#include "mqueue/mqueue.h"
#include "vfs/vfs.h"

/****************************************************************************
 * Private Functions Prototypes
 ****************************************************************************/

static int nxmq_file_close(FAR struct file *filep);
static int nxmq_file_poll(FAR struct file *filep,
                          FAR struct pollfd *fds, bool setup);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct file_operations g_nxmq_fileops =
{
  NULL,             /* open */
  nxmq_file_close,  /* close */
  NULL,             /* read */
  NULL,             /* write */
  NULL,             /* seek */
  NULL,             /* ioctl */
  NULL,             /* mmap */
  NULL,             /* truncate */
  nxmq_file_poll    /* poll */
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int nxmq_file_close(FAR struct file *filep)
{
  FAR struct inode *inode = filep->f_inode;

  if (atomic_read(&inode->i_crefs) <= 0)
    {
      FAR struct mqueue_inode_s *msgq = inode->i_private;

      if (msgq)
        {
          nxmq_free_msgq(msgq);
          inode->i_private = NULL;
        }
    }

  return 0;
}

static int nxmq_file_poll(FAR struct file *filep,
                          FAR struct pollfd *fds, bool setup)
{
  FAR struct inode *inode = filep->f_inode;
  FAR struct mqueue_inode_s *msgq = inode->i_private;
  pollevent_t eventset = 0;
  irqstate_t flags;
  int ret = 0;
  int i;

  flags = enter_critical_section();

  if (setup)
    {
      for (i = 0; i < CONFIG_FS_MQUEUE_NPOLLWAITERS; i++)
        {
          /* Find an available slot */

          if (msgq->fds[i] == NULL)
            {
              /* Bind the poll structure and this slot */

              msgq->fds[i] = fds;
              fds->priv    = &msgq->fds[i];
              break;
            }
        }

      if (i >= CONFIG_FS_MQUEUE_NPOLLWAITERS)
        {
          fds->priv = NULL;
          ret       = -EBUSY;
          goto errout;
        }

      /* Immediately notify on any of the requested events */

      if (msgq->nmsgs < msgq->maxmsgs)
        {
          eventset |= POLLOUT;
        }

      if (msgq->nmsgs > 0)
        {
          eventset |= POLLIN;
        }

      poll_notify(&fds, 1, eventset);
    }
  else if (fds->priv != NULL)
    {
      for (i = 0; i < CONFIG_FS_MQUEUE_NPOLLWAITERS; i++)
        {
          if (fds == msgq->fds[i])
            {
              msgq->fds[i] = NULL;
              fds->priv = NULL;
              break;
            }
        }
    }

errout:
  leave_critical_section(flags);
  return ret;
}

static int file_mq_vopen(FAR struct file *mq, FAR const char *mq_name,
                         int oflags, mode_t umask, va_list ap,
                         FAR int *created)
{
  FAR struct inode *inode;
  FAR struct mqueue_inode_s *msgq;
  FAR struct mq_attr *attr = NULL;
  struct inode_search_s desc;
  char fullpath[MAX_MQUEUE_PATH];
  irqstate_t flags;
  mode_t mode = 0;
  int ret;

  /* Make sure that a non-NULL name is supplied */

  if (!mq || !mq_name || *mq_name == '\0')
    {
      ret = -EINVAL;
      goto errout;
    }

  if (sizeof(CONFIG_FS_MQUEUE_VFS_PATH) + 1 + strlen(mq_name)
      >= MAX_MQUEUE_PATH)
    {
      ret = -ENAMETOOLONG;
      goto errout;
    }

  /* Were we asked to create it? */

  if ((oflags & O_CREAT) != 0)
    {
      /* We have to extract the additional
       * parameters from the variable argument list.
       */

      mode = va_arg(ap, mode_t);
      attr = va_arg(ap, FAR struct mq_attr *);
      if (attr != NULL)
        {
          if (attr->mq_maxmsg <= 0 || attr->mq_msgsize <= 0)
            {
              ret = -EINVAL;
              goto errout;
            }
        }
    }

  mode &= ~umask;

  /* Skip over any leading '/'.  All message queue paths are relative to
   * CONFIG_FS_MQUEUE_VFS_PATH.
   */

  while (*mq_name == '/')
    {
      mq_name++;
    }

  /* Get the full path to the message queue */

  snprintf(fullpath, MAX_MQUEUE_PATH,
           CONFIG_FS_MQUEUE_VFS_PATH "/%s", mq_name);

  /* Make sure that the check for the existence of the message queue
   * and the creation of the message queue are atomic with respect to
   * other processes executing mq_open().  A simple sched_lock() would
   * be sufficient for non-SMP case but critical section is needed for
   * SMP case.
   */

  flags = enter_critical_section();

  /* Get the inode for this mqueue.  This should succeed if the message
   * queue has already been created.  In this case, inode_find() will
   * have incremented the reference count on the inode.
   */

  SETUP_SEARCH(&desc, fullpath, false);

  ret = inode_find(&desc);
  if (ret >= 0)
    {
      /* Something exists at this path.  Get the search results */

      inode = desc.node;

      /* Verify that the inode is a message queue */

      if (!INODE_IS_MQUEUE(inode))
        {
          ret = -ENXIO;
          goto errout_with_inode;
        }

      /* It exists and is a message queue.  Check if the caller wanted to
       * create a new mqueue with this name.
       */

      if ((oflags & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))
        {
          ret = -EEXIST;
          goto errout_with_inode;
        }

      /* Associate the inode with a file structure */

      mq->f_oflags = oflags;
      mq->f_inode  = inode;

      if (created)
        {
          *created = 1;
        }
    }
  else
    {
      /* The mqueue does not exists.  Were we asked to create it? */

      if ((oflags & O_CREAT) == 0)
        {
          /* The mqueue does not exist and O_CREAT is not set */

          ret = -ENOENT;
          goto errout_with_lock;
        }

      /* Create an inode in the pseudo-filesystem at this path */

      inode_lock();
      ret = inode_reserve(fullpath, mode, &inode);
      inode_unlock();

      if (ret < 0)
        {
          goto errout_with_lock;
        }

      /* Allocate memory for the new message queue.  The new inode will
       * be created with a reference count of zero.
       */

      ret = nxmq_alloc_msgq(attr, &msgq);
      if (ret < 0)
        {
          goto errout_with_inode;
        }

      /* Associate the inode with a file structure */

      mq->f_oflags = oflags;
      mq->f_inode  = inode;

      INODE_SET_MQUEUE(inode);
      inode->u.i_ops    = &g_nxmq_fileops;
      inode->i_private  = msgq;
      msgq->inode       = inode;

      /* Set the initial reference count on this inode to one */

      atomic_fetch_add(&inode->i_crefs, 1);

      if (created)
        {
          *created = 0;
        }
    }

  RELEASE_SEARCH(&desc);
  leave_critical_section(flags);
#ifdef CONFIG_FS_NOTIFY
  notify_open(fullpath, oflags);
#endif
  return OK;

errout_with_inode:
  inode_release(inode);

errout_with_lock:
  RELEASE_SEARCH(&desc);
  leave_critical_section(flags);

errout:
  return ret;
}

static mqd_t nxmq_vopen(FAR const char *mq_name, int oflags, va_list ap)
{
  FAR struct file *mq;
  int created;
  int ret;
  int fd;

  fd = file_allocate(oflags, 0, &mq);
  if (fd < 0)
    {
      return fd;
    }

  ret = file_mq_vopen(mq, mq_name, oflags, getumask(), ap, &created);
  file_put(mq);
  if (ret < 0)
    {
      nx_close(fd);
      return ret;
    }

  return fd;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: file_mq_open
 *
 * Description:
 *   This function establish a connection between a named message queue and
 *   the calling task. This is an internal OS interface.  It is functionally
 *   equivalent to mq_open() except that:
 *
 *   - It is not a cancellation point, and
 *   - It does not modify the errno value.
 *
 *  See comments with mq_open() for a more complete description of the
 *  behavior of this function
 *
 * Input Parameters:
 *   mq - address of to-be-initialized struct file instance.
 *   mq_name - Name of the queue to open
 *   oflags - open flags
 *   Optional parameters.  When the O_CREAT flag is specified, two optional
 *   parameters are expected:
 *
 *     1. mode_t mode, and
 *     2. struct mq_attr *attr.  The mq_maxmsg attribute
 *        is used at the time that the message queue is
 *        created to determine the maximum number of
 *        messages that may be placed in the message queue.
 *
 * Returned Value:
 *   This is an internal OS interface and should not be used by applications.
 *   It follows the NuttX internal error return policy:  Zero (OK) is
 *   returned on success, instance pointed by mq is also initialized.
 *   A negated errno value is returned on failure.
 *
 ****************************************************************************/

int file_mq_open(FAR struct file *mq,
                 FAR const char *mq_name, int oflags, ...)
{
  va_list ap;
  int ret;

  memset(mq, 0, sizeof(*mq));

  va_start(ap, oflags);
  ret = file_mq_vopen(mq, mq_name, oflags, 0, ap, NULL);
  va_end(ap);

  return ret;
}

/****************************************************************************
 * Name: nxmq_open
 *
 * Description:
 *   This function establish a connection between a named message queue and
 *   the calling task. This is an internal OS interface.  It is functionally
 *   equivalent to mq_open() except that:
 *
 *   - It is not a cancellation point, and
 *   - It does not modify the errno value.
 *
 *  See comments with mq_open() for a more complete description of the
 *  behavior of this function
 *
 * Input Parameters:
 *   mq_name - Name of the queue to open
 *   oflags - open flags
 *   Optional parameters.  When the O_CREAT flag is specified, two optional
 *   parameters are expected:
 *
 *     1. mode_t mode, and
 *     2. struct mq_attr *attr.  The mq_maxmsg attribute
 *        is used at the time that the message queue is
 *        created to determine the maximum number of
 *        messages that may be placed in the message queue.
 *
 * Returned Value:
 *   This is an internal OS interface and should not be used by applications.
 *   It follows the NuttX internal error return policy:  Zero (OK) is
 *   returned on success, mqdes point to the new message queue descriptor.
 *   A negated errno value is returned on failure.
 *
 ****************************************************************************/

mqd_t nxmq_open(FAR const char *mq_name, int oflags, ...)
{
  va_list ap;
  mqd_t ret;

  va_start(ap, oflags);
  ret = nxmq_vopen(mq_name, oflags, ap);
  va_end(ap);

  return ret;
}

/****************************************************************************
 * Name: mq_open
 *
 * Description:
 *   This function establish a connection between a named message queue and
 *   the calling task.  After a successful call of mq_open(), the task can
 *   reference the message queue using the address returned by the call. The
 *   message queue remains usable until it is closed by a successful call to
 *   mq_close().
 *
 * Input Parameters:
 *   mq_name - Name of the queue to open
 *   oflags - open flags
 *   Optional parameters.  When the O_CREAT flag is specified, two optional
 *   parameters are expected:
 *
 *     1. mode_t mode, and
 *     2. struct mq_attr *attr.  The mq_maxmsg attribute
 *        is used at the time that the message queue is
 *        created to determine the maximum number of
 *        messages that may be placed in the message queue.
 *
 * Returned Value:
 *   A message queue descriptor or (mqd_t)-1 (ERROR)
 *
 * Assumptions:
 *
 ****************************************************************************/

mqd_t mq_open(FAR const char *mq_name, int oflags, ...)
{
  va_list ap;
  mqd_t ret;

  va_start(ap, oflags);
  ret = nxmq_vopen(mq_name, oflags, ap);
  va_end(ap);
  if (ret < 0)
    {
      set_errno(-ret);
      return ERROR;
    }

  return ret;
}
