/****************************************************************************
 * arch/arm/src/stm32h5/stm32h5_pwr.c
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
#include <nuttx/arch.h>

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include "arm_internal.h"
#include "stm32h5_pwr.h"
#include "stm32_rcc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define PWR_TIMEOUT (10 * CONFIG_BOARD_LOOPSPERMSEC)

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static inline uint16_t stm32h5_pwr_getreg(uint8_t offset)
{
  return (uint16_t)getreg32(STM32_PWR_BASE + (uint32_t)offset);
}

static inline void stm32h5_pwr_putreg(uint8_t offset, uint16_t value)
{
  putreg32((uint32_t)value, STM32_PWR_BASE + (uint32_t)offset);
}

static inline void stm32h5_pwr_modifyreg(uint8_t offset, uint16_t clearbits,
                                         uint16_t setbits)
{
  modifyreg32(STM32_PWR_BASE + (uint32_t)offset, (uint32_t)clearbits,
              (uint32_t)setbits);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32h5_pwr_enablebkp
 *
 * Description:
 *   Enables access to the backup domain (RTC registers, RTC backup data
 *   registers and backup SRAM).
 *
 * Input Parameters:
 *   writable  True: enable ability to write to backup domain registers
 *
 * Returned Value:
 *   True: The backup domain was previously writable.
 *
 ****************************************************************************/

bool stm32h5_pwr_enablebkp(bool writable)
{
  uint16_t regval;
  bool waswritable;

  /* Get the current state of the PWR disable Backup domain register */

  regval      = stm32h5_pwr_getreg(STM32_PWR_DBPCR_OFFSET);
  waswritable = ((regval & PWR_DBPCR_DBP) != 0);

  /* Enable or disable the ability to write */

  if (waswritable && !writable)
    {
      /* Disable backup domain access */

      regval &= ~PWR_DBPCR_DBP;
      stm32h5_pwr_putreg(STM32_PWR_DBPCR_OFFSET, regval);
    }
  else if (!waswritable && writable)
    {
      /* Enable backup domain access */

      regval |= PWR_DBPCR_DBP;
      stm32h5_pwr_putreg(STM32_PWR_DBPCR_OFFSET, regval);

      /* Enable does not happen right away */

      up_udelay(4);
    }

  return waswritable;
}

/****************************************************************************
 * Name stm32h5_pwr_adjustvcore
 *
 * Description:
 *   Adjusts the voltage used for digital peripherals (V_CORE) before
 *   raising or after decreasing the system clock frequency.  Compare
 *   [RM0456], section 10.5.4 Dynamic voltage scaling management.
 *
 * Input Parameters:
 *   sysclock - The frequency in Hertz the system clock will or has been set
 *              to.
 *
 ****************************************************************************/

void stm32h5_pwr_adjustvcore(unsigned sysclock)
{
  volatile int timeout;
  uint32_t vos_range;
  uint32_t vos_range_val;
  uint32_t vos_range_set;
  uint32_t actvos_val;

  /* Select the applicable V_CORE voltage range depending on the new system
   * clock frequency.
   */

  DEBUGASSERT(sysclock <= 250000000);

  if (sysclock > 200000000)
    {
      vos_range = PWR_VOSCR_VOS_RANGE0;
    }
  else if (sysclock > 150000000)
    {
      vos_range = PWR_VOSCR_VOS_RANGE1;
    }
  else if (sysclock > 100000000)
    {
      vos_range = PWR_VOSCR_VOS_RANGE2;
    }
  else
    {
      vos_range = PWR_VOSCR_VOS_RANGE3;
    }

  vos_range_val = vos_range >> PWR_VOSCR_VOS_SHIFT;

  actvos_val = ((getreg32(STM32H5_PWR_VOSSR) & PWR_VOSSR_ACTVOS_MASK) >> 
	     PWR_VOSSR_ACTVOS_SHIFT);


  if (vos_range_val > actvos_val)
    {
      for (i = actvos_val; i < vos_range_val; ++i)
        {
	  if (i == 0)
            {
              vos_range_set = PWR_VOSCR_VOS_RANGE2;
            }
          else if (i == 1)
            {
              vos_range_set = PWR_VOSCR_VOS_RANGE1;
            }
          else if (i == 2)
            {
              vos_range_set = PWR_VOSCR_VOS_RANGE0;
            }
  
          modreg32(vos_range_set, PWR_VOSCR_VOS_MASK, STM32_PWR_VOSCR);

          /* Wait until the new V_CORE voltage range has been applied. */

         for (timeout = PWR_TIMEOUT; timeout; timeout--)
            {
              if (getreg32(STM32_PWR_VOSSR) & PWR_VOSSR_VOSRDY)
                {
                  break;
                }
            }

         DEBUGASSERT(timeout > 0);

          /* Wait until the voltage level for the currently used VOS is ready. */
        
         for (timeout = PWR_TIMEOUT; timeout; timeout--)
            {
              if (getreg32(STM32_PWR_VOSSR) & PWR_VOSSR_ACTVOSRDY)
                {
                  break;
                }
            }
        
          DEBUGASSERT(timeout > 0);
	}
    }
  else if (vos_range_val < actvos_val)
    {
      for (i = actvos_val; i > vos_range_val; --i)
        {
	  if (i == 1)
            {
              vos_range_set = PWR_VOSCR_VOS_RANGE3;
            }
          else if (i == 2)
            {
              vos_range_set = PWR_VOSCR_VOS_RANGE2;
            }
          else if (i == 3)
            {
              vos_range_set = PWR_VOSCR_VOS_RANGE1;
            }
  
          modreg32(vos_range_set, PWR_VOSCR_VOS_MASK, STM32_PWR_VOSCR);

          /* Don't poll on VOSRDY when switching from high to low voltage */

          /* Wait until the voltage level for the currently used VOS is ready. */
        
          for (timeout = PWR_TIMEOUT; timeout; timeout--)
            {
              if (getreg32(STM32_PWR_VOSSR) & PWR_VOSSR_ACTVOSRDY)
                {
                  break;
                }
            }
        
          DEBUGASSERT(timeout > 0);
	}
    }
  else
    {
      /* actvos == new vos. Do nothing. */

      return;
    }

  DEBUGASSERT(timeout > 0);
}
