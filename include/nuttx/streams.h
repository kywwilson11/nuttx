/****************************************************************************
 * include/nuttx/streams.h
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

#ifndef __INCLUDE_NUTTX_STREAMS_H
#define __INCLUDE_NUTTX_STREAMS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/compiler.h>

#ifdef CONFIG_LIBC_LZF
#  include <lzf.h>
#endif
#include <stdio.h>
#ifndef CONFIG_DISABLE_MOUNTPOINT
#  include <nuttx/fs/fs.h>
#  ifdef CONFIG_MTD
#    include <nuttx/mtd/mtd.h>
#  endif
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define lib_stream_putc(stream, ch) \
        ((FAR struct lib_outstream_s *)(stream))->putc( \
        (FAR struct lib_outstream_s *)(stream), ch)
#define lib_stream_puts(stream, buf, len) \
        ((FAR struct lib_outstream_s *)(stream))->puts( \
        (FAR struct lib_outstream_s *)(stream), buf, len)
#define lib_stream_eof(c) ((c) <= 0)
#define lib_stream_getc(stream) \
        ((FAR struct lib_instream_s *)(stream))->getc( \
        (FAR struct lib_instream_s *)(stream))
#define lib_stream_gets(stream, buf, len) \
        ((FAR struct lib_instream_s *)(stream))->gets( \
        (FAR struct lib_instream_s *)(stream), buf, len)
#define lib_stream_flush(stream) \
        ((FAR struct lib_outstream_s *)(stream))->flush( \
        (FAR struct lib_outstream_s *)(stream))
#define lib_stream_seek(stream, offset, whence) \
        ((FAR struct lib_sostream_s *)(stream))->seek( \
        (FAR struct lib_sostream_s *)(stream), offset, whence)

#ifdef CONFIG_LIBC_LZF
#define LZF_STREAM_BLOCKSIZE  ((1 << CONFIG_STREAM_LZF_BLOG) - 1)
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* These are the generic representations of a streams used by the NuttX */

struct lib_instream_s;
typedef CODE int     (*lib_getc_t)(FAR struct lib_instream_s *self);
typedef CODE ssize_t (*lib_gets_t)(FAR struct lib_instream_s *self,
                                   FAR void *buf, size_t len);

struct lib_outstream_s;
typedef CODE void    (*lib_putc_t)(FAR struct lib_outstream_s *self, int ch);
typedef CODE ssize_t (*lib_puts_t)(FAR struct lib_outstream_s *self,
                                   FAR const void *buf, size_t len);
typedef CODE int     (*lib_flush_t)(FAR struct lib_outstream_s *self);

struct lib_instream_s
{
  off_t                  nget;    /* Total number of characters gotten.  Written
                                   * by get method, readable by user */
  lib_getc_t             getc;    /* Get one character from the instream */
  lib_gets_t             gets;    /* Get the string from the instream */
};

struct lib_outstream_s
{
  off_t                  nput;    /* Total number of characters put.  Written
                                   * by put method, readable by user */
  lib_putc_t             putc;    /* Put one character to the outstream */
  lib_puts_t             puts;    /* Writes the string to the outstream */
  lib_flush_t            flush;   /* Flush any buffered characters in the outstream */
};

/* Seek-able streams */

struct lib_sistream_s;
typedef CODE int     (*lib_sigetc_t)(FAR struct lib_sistream_s *self);
typedef CODE ssize_t (*lib_sigets_t)(FAR struct lib_sistream_s *self,
                                     FAR void *buf, size_t len);
typedef CODE off_t   (*lib_siseek_t)(FAR struct lib_sistream_s *self,
                                     off_t offset, int whence);

struct lib_sostream_s;
typedef CODE void    (*lib_soputc_t)(FAR struct lib_sostream_s *self,
                                     int ch);
typedef CODE ssize_t (*lib_soputs_t)(FAR struct lib_sostream_s *self,
                                     FAR const void *buf, size_t len);
typedef CODE int     (*lib_soflush_t)(FAR struct lib_sostream_s *self);
typedef CODE off_t   (*lib_soseek_t)(FAR struct lib_sostream_s *self,
                                     off_t offset, int whence);

struct lib_sistream_s
{
  off_t                  nget;    /* Total number of characters gotten.  Written
                                   * by get method, readable by user */
  lib_sigetc_t           getc;    /* Get one character from the instream */
  lib_gets_t             gets;    /* Get the string from the instream */
  lib_siseek_t           seek;    /* Seek to a position in the instream */
};

struct lib_sostream_s
{
  off_t                  nput;    /* Total number of characters put.  Written
                                   * by put method, readable by user */
  lib_soputc_t           putc;    /* Put one character to the outstream */
  lib_soputs_t           puts;    /* Writes the string to the outstream */
  lib_soflush_t          flush;   /* Flush any buffered characters in the outstream */
  lib_soseek_t           seek;    /* Seek a position in the output stream */
};

/* These are streams that operate on a fixed-sized block of memory */

struct lib_meminstream_s
{
  struct lib_instream_s  common;
  FAR const char        *buffer;  /* Address of first byte in the buffer */
  size_t                 buflen;  /* Size of the buffer in bytes */
};

struct lib_memoutstream_s
{
  struct lib_outstream_s common;
  FAR char              *buffer;  /* Address of first byte in the buffer */
  size_t                 buflen;  /* Size of the buffer in bytes */
};

struct lib_memsistream_s
{
  struct lib_sistream_s  common;
  FAR const char        *buffer;  /* Address of first byte in the buffer */
  off_t                  offset;  /* Current buffer offset in bytes */
  size_t                 buflen;  /* Size of the buffer in bytes */
};

struct lib_memsostream_s
{
  struct lib_sostream_s  common;
  FAR char              *buffer;  /* Address of first byte in the buffer */
  off_t                  offset;  /* Current buffer offset in bytes */
  size_t                 buflen;  /* Size of the buffer in bytes */
};

/* These are streams that operate on a FILE */

struct lib_stdinstream_s
{
  struct lib_instream_s  common;
  FAR FILE              *handle;
};

struct lib_stdoutstream_s
{
  struct lib_outstream_s common;
  FAR FILE              *handle;
};

struct lib_stdsistream_s
{
  struct lib_sistream_s  common;
  FAR FILE              *handle;
};

struct lib_stdsostream_s
{
  struct lib_sostream_s  common;
  FAR FILE              *handle;
};

/* These are streams that operate on a file descriptor */

struct lib_rawinstream_s
{
  struct lib_instream_s  common;
  int                    fd;
};

struct lib_rawoutstream_s
{
  struct lib_outstream_s common;
  int                    fd;
};

struct lib_fileinstream_s
{
  struct lib_instream_s  common;
  struct file            file;
};

struct lib_fileoutstream_s
{
  struct lib_outstream_s common;
  struct file            file;
};

struct lib_rawsistream_s
{
  struct lib_sistream_s  common;
  int                    fd;
};

struct lib_rawsostream_s
{
  struct lib_sostream_s  common;
  int                    fd;
};

struct lib_bufferedoutstream_s
{
  struct lib_outstream_s      common;
  FAR struct lib_outstream_s *backend;
  size_t                      pending;
  char                        buffer[CONFIG_STREAM_OUT_BUFFER_SIZE];
};

struct lib_hexdumpstream_s
{
  struct lib_outstream_s      common;
  FAR struct lib_outstream_s *backend;
  size_t                      pending;
  char                        buffer[CONFIG_STREAM_HEXDUMP_BUFFER_SIZE + 1];
};

struct lib_base64outstream_s
{
  struct lib_outstream_s      common;
  FAR struct lib_outstream_s *backend;
  size_t                      pending;
  unsigned char               bytes[3];
  size_t                      nbytes;
  char                        buffer[CONFIG_STREAM_BASE64_BUFFER_SIZE + 1];
};

/* This is a special stream that does buffered character I/O.  NOTE that is
 * CONFIG_SYSLOG_BUFFER is not defined, it is the same as struct
 * lib_outstream_s
 */

struct lib_syslogstream_s
{
  struct lib_outstream_s common;
  int priority;
};

struct lib_syslograwstream_s
{
  struct lib_outstream_s common;
#ifdef CONFIG_SYSLOG_BUFFER
  char buffer[CONFIG_SYSLOG_BUFSIZE];
  off_t offset;
#endif
  int last_ch;
};

/* LZF compressed stream pipeline */

#ifdef CONFIG_LIBC_LZF
struct lib_lzfoutstream_s
{
  struct lib_outstream_s      common;
  FAR struct lib_outstream_s *backend;
  lzf_state_t                 state;
  off_t                       offset;
  char                        in[LZF_STREAM_BLOCKSIZE];
  char                        out[LZF_MAX_HDR_SIZE + LZF_STREAM_BLOCKSIZE];
};
#endif

#ifndef CONFIG_DISABLE_MOUNTPOINT
struct lib_blkoutstream_s
{
  struct lib_sostream_s  common;
  FAR struct inode      *inode;
  struct geometry        geo;
  FAR unsigned char     *cache;
};
#endif

#if !defined(CONFIG_DISABLE_MOUNTPOINT) && defined(CONFIG_MTD)
struct lib_mtdoutstream_s
{
  struct lib_outstream_s common;
  FAR struct inode      *inode;
  struct mtd_geometry_s  geo;
  FAR unsigned char     *cache;
};

struct lib_mtdsostream_s
{
  struct lib_sostream_s  common;
  FAR struct inode      *inode;
  struct mtd_geometry_s  geo;
  FAR unsigned char     *cache;
};
#endif

struct va_format
{
  FAR const char *fmt;
  FAR va_list *va;
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#  define EXTERN extern "C"
extern "C"
{
#else
#  define EXTERN extern
#endif

extern struct lib_outstream_s g_lowoutstream;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: lib_meminstream, lib_memoutstream, lib_memsistream, lib_memsostream
 *
 * Description:
 *   Initializes a stream for use with a fixed-size memory buffer.
 *   Defined in lib/stdio/lib_meminstream.c and lib/stdio/lib_memoutstream.c.
 *   Seekable versions are defined in lib/stdio/lib_memsistream.c and
 *   lib/stdio/lib_memsostream.c.
 *
 * Input Parameters:
 *   stream    - User allocated, uninitialized instance of stream struct
 *               to be initialized.
 *   bufstart  - Address of the beginning of the fixed-size memory buffer
 *   buflen    - Size of the fixed-sized memory buffer in bytes
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

void lib_meminstream(FAR struct lib_meminstream_s *stream,
                     FAR const char *bufstart, size_t buflen);
void lib_memoutstream(FAR struct lib_memoutstream_s *stream,
                      FAR char *bufstart, size_t buflen);
void lib_memsistream(FAR struct lib_memsistream_s *stream,
                     FAR const char *bufstart, size_t buflen);
void lib_memsostream(FAR struct lib_memsostream_s *stream,
                     FAR char *bufstart, size_t buflen);

/****************************************************************************
 * Name: lib_stdinstream, lib_stdoutstream
 *
 * Description:
 *   Initializes a stream for use with a FILE instance.
 *   Defined in lib/stdio/lib_stdinstream.c and lib/stdio/lib_stdoutstream.c
 *
 * Input Parameters:
 *   stream  - User allocated, uninitialized instance of stream
 *             to be initialized
 *   handle  - User provided FILE instance (must have been opened for
 *             the correct access).
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

void lib_stdinstream(FAR struct lib_stdinstream_s *stream,
                     FAR FILE *handle);
void lib_stdoutstream(FAR struct lib_stdoutstream_s *stream,
                      FAR FILE *handle);
void lib_stdsistream(FAR struct lib_stdsistream_s *stream,
                     FAR FILE *handle);
void lib_stdsostream(FAR struct lib_stdsostream_s *stream,
                     FAR FILE *handle);

/****************************************************************************
 * Name: lib_fileinstream_open, lib_fileinstream_close,
 *       lib_fileoutstream_open, lib_fileoutstream_close
 *
 * Description:
 *   Initializes or release a file-based stream instance.
 *   Defined in lib_fileinstream.c and lib/lib_fileoutstream.c
 *
 * Input Parameters:
 *  For open:
 *    stream  - User allocated, uninitialized instance of stream struct
 *             to be initialized.
 *    path    - Path to the file to be opened.
 *    oflag   - File open flags.
 *    mode    - File access mode.
 *  For close:
 *    stream  - User allocated, initialized instance of stream struct
 * Returned Value:
 *  open: Zero on success; a negated errno value on failure.
 *  close: None (resource cleanup only).
 *
 ****************************************************************************/

int lib_fileinstream_open(FAR struct lib_fileinstream_s *stream,
                          FAR const char *path, int oflag, mode_t mode);
void lib_fileinstream_close(FAR struct lib_fileinstream_s *stream);
int lib_fileoutstream_open(FAR struct lib_fileoutstream_s *stream,
                           FAR const char *path, int oflag, mode_t mode);
void lib_fileoutstream_close(FAR struct lib_fileoutstream_s *stream);

/****************************************************************************
 * Name: lib_rawinstream, lib_rawoutstream, lib_rawsistream, and
 *       lib_rawsostream,
 *
 * Description:
 *   Initializes a stream for use with a file descriptor.
 *   Defined in lib/stdio/lib_rawinstream.c and lib/stdio/lib_rawoutstream.c.
 *   Seekable versions are defined in lib/stdio/lib_rawsistream.c and
 *   lib/stdio/lib_rawsostream.c
 *
 * Input Parameters:
 *   stream  - User allocated, uninitialized instance of stream struct
 *             to be initialized.
 *   fd      - User provided file/socket descriptor (must have been opened
 *             for the correct access).
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

void lib_rawinstream(FAR struct lib_rawinstream_s *stream, int fd);
void lib_rawoutstream(FAR struct lib_rawoutstream_s *stream, int fd);
void lib_rawsistream(FAR struct lib_rawsistream_s *stream, int fd);
void lib_rawsostream(FAR struct lib_rawsostream_s *stream, int fd);

/****************************************************************************
 * Name: lib_bufferedoutstream
 *
 * Description:
 *   Wrap a raw output stream to a buffered output stream.
 *
 * Input Parameters:
 *   stream  - User allocated, uninitialized instance of struct
 *             lib_bufferedoutstream_s to be initialized.
 *   backend - User allocated, initialized instance of struct
 *             lib_outstream_s to be buffered.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

void lib_bufferedoutstream(FAR struct lib_bufferedoutstream_s *stream,
                           FAR struct lib_outstream_s *backend);

/****************************************************************************
 * Name: lib_hexdumpstream
 *
 * Description:
 *   Convert binary stream to hex and redirect to syslog
 *
 * Input Parameters:
 *   stream    - User allocated, uninitialized instance of struct
 *               lib_bufferedoutstream_s to be initialized.
 *   backend   - Stream backend port.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

void lib_hexdumpstream(FAR struct lib_hexdumpstream_s *stream,
                       FAR struct lib_outstream_s *backend);

/****************************************************************************
 * Name: lib_base64stream
 *
 * Description:
 *   Convert binary stream to base64 and redirect to syslog
 *
 * Input Parameters:
 *   stream    - User allocated, uninitialized instance of struct
 *               lib_base64stream_s to be initialized.
 *   backend   - Stream backend port.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

void lib_base64outstream(FAR struct lib_base64outstream_s *stream,
                         FAR struct lib_outstream_s *backend);

/****************************************************************************
 * Name: lib_lowoutstream
 *
 * Description:
 *   Initializes a stream for use with low-level, architecture-specific
 *   output.
 *   Defined in ib/stdio/lib_lowoutstream.c
 *
 * Input Parameters:
 *   lowoutstream - User allocated, uninitialized instance of struct
 *                  lib_outstream_s to be initialized.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

#ifdef CONFIG_ARCH_LOWPUTC
void lib_lowoutstream(FAR struct lib_outstream_s *lowoutstream);
#endif

/****************************************************************************
 * Name: lib_zeroinstream, lib_nullinstream, lib_nulloutstream
 *
 * Description:
 *   Initializes NULL streams:
 *
 *   o The stream created by lib_zeroinstream will return an infinitely long
 *     stream of zeroes. Defined in lib/stdio/lib_zeroinstream.c
 *   o The stream created by lib_nullinstream will return only EOF.
 *     Defined in lib/stdio/lib_nullinstream.c
 *   o The stream created by lib_nulloutstream will write all data to the
 *     bit-bucket. Defined in lib/stdio/lib_nulloutstream.c
 *
 * Input Parameters:
 *   zeroinstream  - User allocated, uninitialized instance of struct
 *                   lib_instream_s to be initialized.
 *   nullinstream  - User allocated, uninitialized instance of struct
 *                   lib_instream_s to be initialized.
 *   nulloutstream - User allocated, uninitialized instance of struct
 *                   lib_outstream_s to be initialized.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

void lib_zeroinstream(FAR struct lib_instream_s *stream);
void lib_nullinstream(FAR struct lib_instream_s *stream);
void lib_nulloutstream(FAR struct lib_outstream_s *stream);

/****************************************************************************
 * Name: lib_syslogstream
 *
 * Description:
 *   Initializes syslog stream
 *
 * Input Parameters:
 *   stream   - User allocated, uninitialized instance of struct
 *              lib_syslogstream_s to be initialized.
 *   priority - log priority.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

void lib_syslogstream(FAR struct lib_syslogstream_s *stream, int priority);

/****************************************************************************
 * Name: lib_syslograwstream_open
 *
 * Description:
 *   Initializes a stream for use with the configured syslog interface.
 *   Only accessible from with the OS SYSLOG logic.
 *
 * Input Parameters:
 *   stream - User allocated, uninitialized instance of struct
 *            lib_syslograwstream_s to be initialized.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

void lib_syslograwstream_open(FAR struct lib_syslograwstream_s *stream);

/****************************************************************************
 * Name: lib_syslograwstream_close
 *
 * Description:
 *   Free resources held by the syslog stream.
 *
 * Input Parameters:
 *   stream - User allocated, uninitialized instance of struct
 *            lib_syslograwstream_s to be initialized.
 *
 * Returned Value:
 *   None (Resources freed).
 *
 ****************************************************************************/

#ifdef CONFIG_SYSLOG_BUFFER
void lib_syslograwstream_close(FAR struct lib_syslograwstream_s *stream);
#else
#  define lib_syslograwstream_close(s)
#endif

/****************************************************************************
 * Name: lib_lzfoutstream
 *
 * Description:
 *  LZF compressed pipeline stream
 *
 * Input Parameters:
 *   stream  - User allocated, uninitialized instance of struct
 *                lib_lzfoutstream_s to be initialized.
 *   backend - Stream backend port.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

#ifdef CONFIG_LIBC_LZF
void lib_lzfoutstream(FAR struct lib_lzfoutstream_s *stream,
                      FAR struct lib_outstream_s *backend);
#endif

/****************************************************************************
 * Name: lib_blkoutstream_open
 *
 * Description:
 *  open block driver stream backend
 *
 * Input Parameters:
 *   stream  - User allocated, uninitialized instance of struct
 *                lib_blkoutstream_s to be initialized.
 *   name    - The full path to the block driver to be opened.
 *
 * Returned Value:
 *   Returns zero on success or a negated errno on failure
 *
 ****************************************************************************/

#ifndef CONFIG_DISABLE_MOUNTPOINT
int lib_blkoutstream_open(FAR struct lib_blkoutstream_s *stream,
                          FAR const char *name);
#endif

/****************************************************************************
 * Name: lib_blkoutstream_close
 *
 * Description:
 *  close block driver stream backend
 *
 * Input Parameters:
 *   stream  - User allocated, uninitialized instance of struct
 *                lib_blkoutstream_s to be initialized.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

#ifndef CONFIG_DISABLE_MOUNTPOINT
void lib_blkoutstream_close(FAR struct lib_blkoutstream_s *stream);
#endif

/****************************************************************************
 * Name: lib_mtdoutstream_open
 *
 * Description:
 *  mtd driver stream backend
 *
 * Input Parameters:
 *   stream   - User allocated, uninitialized instance of struct
 *                lib_mtdoutstream_s to be initialized.
 *   name     - The full path of mtd device.
 *
 * Returned Value:
 *   Returns zero on success or a negated errno on failure
 *
 ****************************************************************************/

#if !defined(CONFIG_DISABLE_MOUNTPOINT) && defined(CONFIG_MTD)
int lib_mtdoutstream_open(FAR struct lib_mtdoutstream_s *stream,
                          FAR const char *name);
#endif

/****************************************************************************
 * Name: lib_mtdoutstream_close
 *
 * Description:
 *  close mtd driver stream backend
 *
 * Input Parameters:
 *   stream  - User allocated, uninitialized instance of struct
 *                lib_mtdoutstream_s to be initialized.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

#if !defined(CONFIG_DISABLE_MOUNTPOINT) && defined(CONFIG_MTD)
void lib_mtdoutstream_close(FAR struct lib_mtdoutstream_s *stream);
#endif

/****************************************************************************
 * Name: lib_mtdsostream_open
 *
 * Description:
 *  mtd driver seekable outstream backend
 *
 * Input Parameters:
 *   stream   - User allocated, uninitialized instance of struct
 *                lib_mtdsostream_s to be initialized.
 *   name     - The full path of mtd device.
 *
 * Returned Value:
 *   Returns zero on success or a negated errno on failure
 *
 ****************************************************************************/

#if !defined(CONFIG_DISABLE_MOUNTPOINT) && defined(CONFIG_MTD)
int lib_mtdsostream_open(FAR struct lib_mtdsostream_s *stream,
                         FAR const char *name);
#endif

/****************************************************************************
 * Name: lib_mtdsostream_close
 *
 * Description:
 *  close mtd driver seekable outstream backend
 *
 * Input Parameters:
 *   stream  - User allocated, uninitialized instance of struct
 *                lib_mtdsostream_s to be initialized.
 *
 * Returned Value:
 *   None (User allocated instance initialized).
 *
 ****************************************************************************/

#if !defined(CONFIG_DISABLE_MOUNTPOINT) && defined(CONFIG_MTD)
void lib_mtdsostream_close(FAR struct lib_mtdsostream_s *stream);
#endif

/****************************************************************************
 * Name: lib_noflush
 *
 * Description:
 *  lib_noflush() provides a common, dummy flush method for output streams
 *  that are not flushable.
 *
 * Returned Value:
 *  Always returns OK
 *
 ****************************************************************************/

int lib_noflush(FAR struct lib_outstream_s *self);

/****************************************************************************
 * Name: lib_snoflush
 *
 * Description:
 *  lib_snoflush() provides a common, dummy flush method for seekable output
 *  streams that are not flushable.
 *  is selected.
 *
 * Returned Value:
 *  Always returns OK
 *
 ****************************************************************************/

int lib_snoflush(FAR struct lib_sostream_s *self);

/****************************************************************************
 * Name: lib_sprintf
 *
 * Description:
 *  Stream-oriented implementation of sprintf.  Used only by the SYSLOG.
 *
 ****************************************************************************/

int lib_sprintf(FAR struct lib_outstream_s *stream,
                FAR const IPTR char *fmt, ...) printf_like(2, 3);

/****************************************************************************
 * Name: lib_bsprintf
 *
 * Description:
 *  Implementation of sprintf formatted output buffer data. Structure data
 *  types must be one-byte aligned.
 *
 ****************************************************************************/

int lib_bsprintf(FAR struct lib_outstream_s *s, FAR const IPTR char *fmt,
                 FAR const void *buf);

/****************************************************************************
 * Name: lib_sprintf_internal
 *
 * Description:
 *   This function does not take numbered arguments in printf.
 *   Equivalent to lib_sprintf when CONFIG_LIBC_NUMBERED_ARGS is not enabled
 *
 ****************************************************************************/

int lib_sprintf_internal(FAR struct lib_outstream_s *stream,
                         FAR const IPTR char *fmt, ...) printf_like(2, 3);

/****************************************************************************
 * Name: lib_vsprintf_internal
 *
 * Description:
 *   This function does not take numbered arguments in printf.
 *   Equivalent to lib_sprintf when CONFIG_LIBC_NUMBERED_ARGS is not enabled
 *
 ****************************************************************************/

int lib_vsprintf_internal(FAR struct lib_outstream_s *stream,
                          FAR const IPTR char *fmt, va_list ap)
                          printf_like(2, 0);

/****************************************************************************
 * Name: lib_vsprintf
 *
 * Description:
 *  Stream-oriented implementation that underlies printf family:  printf,
 *  fprint, sprint, etc.
 *
 ****************************************************************************/

int lib_vsprintf(FAR struct lib_outstream_s *stream,
                 FAR const IPTR char *src, va_list ap) printf_like(2, 0);

/****************************************************************************
 * Name: lib_scanf
 ****************************************************************************/

int lib_scanf(FAR struct lib_instream_s *stream, FAR int *lastc,
              FAR const IPTR char *fmt, ...) scanf_like(3, 4);

/****************************************************************************
 * Name: lib_vscanf
 *
 * Description:
 *  Stream-oriented implementation that underlies scanf family:  scanf,
 *  fscanf, vfscanf, sscanf, and vsscanf
 *
 ****************************************************************************/

int lib_vscanf(FAR struct lib_instream_s *stream, FAR int *lastc,
               FAR const IPTR char *fmt, va_list ap) scanf_like(3, 0);

/****************************************************************************
 * Name: lib_bscanf
 *
 * Description:
 *  Convert data into a structure according to standard formatting protocols.
 *  For string arrays, please use "%{length}s" or "%{length}c" to specify
 *  the length.
 *
 ****************************************************************************/

int lib_bscanf(FAR struct lib_instream_s *stream, FAR int *lastc,
               FAR const IPTR char *fmt, FAR void *data);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __INCLUDE_NUTTX_STREAMS_H */
