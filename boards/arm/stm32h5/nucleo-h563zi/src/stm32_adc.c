/****************************************************************************
 * boards/arm/stm32h5/nucleo-h563zi/src/stm32_adc.c
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

#include <stdbool.h>
#include <errno.h>
#include <debug.h>

#include <arch/board/board.h>

#include <nuttx/analog/adc.h>

#include "stm32.h"
#include "stm32_tim.h"

#if defined(CONFIG_ADC)
#if defined(CONFIG_STM32H5_ADC1) || defined(CONFIG_STM32H5_ADC2)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

/* The number of ADC channels in the conversion list */

//#define ADC1_NCHANNELS 2
#define ADC1_NCHANNELS 1
#define ADC2_NCHANNELS 0

/* Dependent on NCHANNELS and Differential/Single-Ended Mode
 * ADCx_NCHANNELS <= ADCx_NPINS <= 2 * ADCx_NCHANNELS
 */

//#define ADC1_NPINS     2
#define ADC1_NPINS     1
#define ADC2_NPINS     0

/* Map AWD index to ETRSEL per RM0481 tim_etr table: 1→3, 2→4, 3→5 */

#ifndef STM32H5_ETRSEL_FROM_AWD
#  define STM32H5_ETRSEL_FROM_AWD(awd) ((uint8_t)(2u + (uint8_t)(awd)))
#endif

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Identifying number of each ADC channel (even if NCHANNELS is less ) */

#ifdef CONFIG_STM32H5_ADC1

static const uint8_t g_chanlist1[ADC1_NCHANNELS] =
{
  3
  //10
};

static uint32_t g_pinlist1[ADC1_NPINS] =
{
  GPIO_ADC1_INP3 /* Channel  3 - Positive */
  //GPIO_ADC1_INP10 /* Channel 10 - Positive */
};

struct stm32_tim_dev_s *t1;
struct stm32_tim_dev_s *t8;
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/
static int tim1_trg_latch_isr(int irq, void *ctx, void *arg)
{
  
  /* 1) Ack TRG event */

  STM32_TIM_ACKINT(t1, ATIM_SR_TIF);

  /* 2) Latch outputs OFF — Only kill CH1 output: */

  //modifyreg32(STM32_TIM1_BASE + STM32_ATIM_CCER_OFFSET, ATIM_CCER_CC1E, 0);
  //modifyreg32(STM32_TIM1_BASE + STM32_ATIM_BDTR_OFFSET, ATIM_BDTR_MOE, 0);

  /* 3) Stop further TRG interrupts (we’ve latched) */

    if (t1)
      {
        STM32_TIM_DISABLEINT(t1, ATIM_DIER_TIE);
      }

  /* Optionally: set a flag, wake user code, etc. */

  return OK;
}

static void board_link_adc_awd_to_tim(int adc_index,
                                      uint8_t awd,   /* 1..3 */
                                      uint8_t ch,    /* 1..4: TIM channel to clear */
                                      uint8_t etf,   /* 0..15 ETR filter */
                                      bool etp)      /* invert ETR? */
{
  /* TIM1 pairs with ADC1; TIM8 pairs with ADC2 on H5 */

  struct stm32_tim_dev_s *t;
  if (adc_index == 1)
    {
      t1 = stm32_tim_init(1);
      t = t1;
    }
  else if (adc_index == 8)
    {
      t8 = stm32_tim_init(8);
      t = t8;
    }
  else
    {
      // return error
    }

  if (!t) return;

  STM32_TIM_ENABLE(t);
  STM32_TIM_SETMODE(t, STM32_TIM_MODE_UP);

  const uint8_t etrsel = STM32H5_ETRSEL_FROM_AWD(awd);  /* 3/4/5 */
  
  /* Make CH1 drive something: PWM or forced level */

  (void)STM32_TIM_OCREFCLR_FROM_ETR(t, ch, etrsel, etf, etp);

  uint32_t ccmr1 = getreg32(STM32_TIM1_BASE + STM32_ATIM_CCMR1_OFFSET);
  ccmr1 &= ~ATIM_CCMR1_OC1M_MASK;
  ccmr1 |=  (ATIM_CCMR_MODE_OCREFHI << ATIM_CCMR1_OC1M_SHIFT) | ATIM_CCMR1_OC1CE; /* OC1CE should already be set, keep it */
  putreg32(ccmr1, STM32_TIM1_BASE + STM32_ATIM_CCMR1_OFFSET);

  /* 4) Enable the CH1 output driver */

  modifyreg32(STM32_TIM1_BASE + STM32_ATIM_CCER_OFFSET, 0, ATIM_CCER_CC1E);

  /* TRGI = ETRF so AWD pulses create a TRG event (TIF) */

  uint32_t smcr = getreg32(STM32_TIM1_BASE + STM32_ATIM_SMCR_OFFSET);
  smcr &= ~ATIM_SMCR_TS_MASK;
  smcr |=  ATIM_SMCR_ETRF;            // TRGI source = ETRF

  /* Put TIM1 in a slave mode so TEV is generated on TRGI edges */

  smcr &= ~ATIM_SMCR_SMS_MASK;
  smcr |=  ATIM_SMCR_RESET;  /* or _GATED / _TRIGGER — all have side-effects */

  putreg32(smcr, STM32_TIM1_BASE + STM32_ATIM_SMCR_OFFSET);

  /* Attach a timer ISR and enable the TRG interrupt */
  irq_attach(STM32_IRQ_TIM1_TRG_COM, tim1_trg_latch_isr, 0);    // arg optional
  up_enable_irq(STM32_IRQ_TIM1_TRG_COM);
  STM32_TIM_ENABLEINT(t, ATIM_DIER_TIE);               // enable TRG interrupt
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_adc_setup
 *
 * Description:
 *   Initialize ADC and register the ADC driver.
 *
 ****************************************************************************/

int stm32_adc_setup(void)
{
  static bool initialized = false;
#ifdef CONFIG_STM32H5_ADC1
  struct adc_dev_s *adc1;
#endif
#ifdef CONFIG_STM32H5_ADC2
  struct adc_dev_s *adc2;
#endif
  int ret;
  int i;
  uint8_t ch;
  uint8_t etf;
  bool etp;

  /* Check if we have already initialized */

  if (!initialized)
    {
      /* Configure the pins as analog inputs for the selected channels */

#ifdef CONFIG_STM32H5_ADC1
      for (i = 0; i < ADC1_NCHANNELS; i++)
        {
          stm32_configgpio(g_pinlist1[i]);
        }

      adc1 = stm32h5_adc_initialize(1, g_chanlist1, ADC1_NCHANNELS);
      if (adc1 == NULL)
        {
          aerr("ERROR: Failed to get ADC interface 1\n");
          return -ENODEV;
        }

      /* Register the ADC driver at "/dev/adc0" */

      ret = adc_register("/dev/adc0", adc1);
      if (ret < 0)
        {
          aerr("ERROR: adc_register /dev/adc0 failed: %d\n", ret);
          return ret;
        }

#  ifdef CONFIG_STM32H5_TIM1_WDG1_HWLINK
      ch = CONFIG_STM32H5_TIM1_WDG1_CH;
      etf = CONFIG_STM32H5_TIM1_WDG1_ETF;
#    ifdef CONFIG_STM32H5_TIM1_WDG1_ETP
      etp = true;
#    else
      etp = false;
#    endif
      board_link_adc_awd_to_tim(1, 1, ch, etf, etp);
#    if defined(GPIO_TIM1_CH1OUT)
      stm32_configgpio(GPIO_TIM1_CH1OUT);
#    elif defined(GPIO_TIM1_CH2OUT)
      stm32_configgpio(GPIO_TIM1_CH2OUT);
#    elif defined(GPIO_TIM1_CH3OUT)
      stm32_configgpio(GPIO_TIM1_CH3OUT);
#    elif defined(GPIO_TIM1_CH4OUT)
      stm32_configgpio(GPIO_TIM1_CH4OUT);
#    endif
#  endif
#endif

#ifdef CONFIG_STM32H5_ADC2
      for (i = 0; i < ADC2_NCHANNELS; i++)
        {
          stm32_configgpio(g_pinlist2[i]);
        }

      adc2 = stm32h5_adc_initialize(2, g_chanlist2, ADC2_NCHANNELS);
      if (adc2 == NULL)
        {
          aerr("ERROR: Failed to get ADC interface 1\n");
          return -ENODEV;
        }

      /* Register the ADC driver at "/dev/adc0" */

      ret = adc_register("/dev/adc1", adc2);
      if (ret < 0)
        {
          aerr("ERROR: adc_register /dev/adc1 failed: %d\n", ret);
          return ret;
        }

#  ifdef CONFIG_STM32H5_TIM8_WDG1_HWLINK
      ch = CONFIG_STM32H5_TIM8_WDG1_CH;
      etf = CONFIG_STM32H5_TIM8_WDG1_ETF;
#    ifdef CONFIG_STM32H5_TIM1_WDG1_ETP
      etp = true;
#    else
      etp = false;
#    endif
      board_link_adc_awd_to_tim(2, 1, ch, etf, etp);
#    if defined(GPIO_TIM8_CH1OUT)
      stm32_configgpio(GPIO_TIM8_CH1OUT);
#    elif defined(GPIO_TIM8_CH2OUT)
      stm32_configgpio(GPIO_TIM8_CH2OUT);
#    elif defined(GPIO_TIM8_CH3OUT)
      stm32_configgpio(GPIO_TIM8_CH3OUT);
#    elif defined(GPIO_TIM8_CH4OUT)
      stm32_configgpio(GPIO_TIM8_CH4OUT);
#    endif
#  endif
#endif
      initialized = true;
    }
  return OK;
}

#endif /* CONFIG_STM32H5_ADC1 || CONFIG_STM32H5_ADC2 */
#endif /* CONFIG_ADC */
