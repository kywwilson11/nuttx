/****************************************************************************
 * boards/arm/stm32h5/nucleo-h563zi/src/stm32_awd_pwm_latch.c
 *
 * Hardware-only latch OFF using PWM2 with CEN=0 and slave RESET on ETRF.
 * On AWD edge: CNT→0 => OCREF=0 (LOW) and stays LOW until software re-arms.
 *
 * Built only when CONFIG_NUCLEO_H563ZI_AWD_PWM_LATCH=y
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_NUCLEO_H563ZI_AWD_PWM_LATCH

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include "chip.h"
#include "arm_internal.h"
#include "hardware/stm32_tim.h"
#include "nucleo-h563zi.h"                 /* board-private prototypes */
#include "stm32_pwm.h" /* use PWM LL ops as requested */

/* Map TIM id to base (advanced timers only) */
static inline uintptr_t tim_base(int tim)
{
  switch (tim)
    {
      case 1:  return STM32_TIM1_BASE;
      case 8:  return STM32_TIM8_BASE;
      default: return 0;
    }
}

/* Channel → PWM output mask */
static inline uint16_t out_mask(uint8_t ch)
{
  static const uint16_t m[4] =
    { STM32_PWM_OUT1, STM32_PWM_OUT2, STM32_PWM_OUT3, STM32_PWM_OUT4 };
  return (ch >= 1 && ch <= 4) ? m[ch - 1] : 0;
}

/* ETRSEL encoding helper: AWD1/2/3 -> 3/4/5 on H5 */
#ifndef STM32H5_ETRSEL_FROM_AWD
#  define STM32H5_ETRSEL_FROM_AWD(awd) ((uint8_t)(2u + (uint8_t)(awd)))
#endif

/* State */
static struct stm32_pwm_dev_s *g_dev;
static uintptr_t g_base;
static int       g_tim;
static uint8_t   g_ch;
static uint32_t  g_arr;
static uint32_t  g_ccr;

/* CNT helpers (16/32-bit compatible) */
static inline void tim_set_cnt(uintptr_t base, uint32_t cnt)
{
#ifdef HAVE_IP_TIMERS_V2
  putreg32(cnt, base + STM32_GTIM_CNT_OFFSET);
#else
  putreg16((uint16_t)cnt, base + STM32_GTIM_CNT_OFFSET);
#endif
}

static inline void tim_clear_tif(uintptr_t base)
{
  modifyreg16(base + STM32_GTIM_SR_OFFSET, ATIM_SR_TIF, 0);
}

static inline bool tim_tif(uintptr_t base)
{
  return (getreg16(base + STM32_GTIM_SR_OFFSET) & ATIM_SR_TIF) != 0;
}

int board_awd_pwm_latch_init(int tim, uint8_t ch, uint8_t awd,
                             uint8_t etf, bool etp,
                             uint32_t arr, uint32_t ccr)
{
  g_base = tim_base(tim);
  if (g_base == 0 || out_mask(ch) == 0 || awd < 1 || awd > 3 || ccr == 0)
    {
      return -EINVAL;
    }

  g_tim = tim;
  g_ch  = ch;
  g_arr = arr;
  g_ccr = ccr;

  /* Grab PWM device and basic setup */
  g_dev = (struct stm32_pwm_dev_s *)stm32_pwminitialize(tim);
  if (g_dev == NULL)
    {
      return -ENODEV;
    }

  PWM_SETUP(g_dev);

  /* Ensure timer is disabled (CEN=0) and outputs safe */
  PWM_TIM_ENABLE(g_dev, false);
  PWM_OUTPUTS_ENABLE(g_dev, out_mask(ch), false);
  PWM_SOFT_BREAK(g_dev, true); /* MOE=0 */

  /* Configure PWM2 on the selected channel, program ARR/CCR, and UG */
  PWM_MODE_UPDATE(g_dev, (uint8_t)(ch), STM32_CHANMODE_PWM2);
  PWM_ARR_UPDATE(g_dev, arr);
  PWM_CCR_UPDATE(g_dev, (uint8_t)(ch), ccr);
  PWM_SOFT_UPDATE(g_dev); /* EGR.UG to load preloads */

  /* Route AWDy -> ETR via AF1.ETRSEL; program ETR filter/polarity */
  uint32_t af1 = getreg32(g_base + STM32_ATIM_AF1_OFFSET);
  af1 &= ~ATIM_AF1_ETRSEL_MASK;
  af1 |= (uint32_t)STM32H5_ETRSEL_FROM_AWD(awd) << ATIM_AF1_ETRSEL_SHIFT;
  putreg32(af1, g_base + STM32_ATIM_AF1_OFFSET);

  uint32_t smcr = getreg32(g_base + STM32_ATIM_SMCR_OFFSET);
  smcr &= ~(ATIM_SMCR_TS_MASK | ATIM_SMCR_ETF_MASK | ATIM_SMCR_ETP | ATIM_SMCR_SMS_MASK);
  smcr |= ATIM_SMCR_ETRF;                                /* TRGI = ETRF */
  smcr |= ((uint32_t)(etf & 0xF) << ATIM_SMCR_ETF_SHIFT);/* filter      */
  if (etp) smcr |= ATIM_SMCR_ETP;                        /* polarity    */
  smcr |= ATIM_SMCR_RESET;                               /* SMS=RESET (0100) */
  putreg32(smcr, g_base + STM32_ATIM_SMCR_OFFSET);

  /* Safe off-state when disabled */
  modifyreg16(g_base + STM32_ATIM_BDTR_OFFSET, 0, ATIM_BDTR_OSSI | ATIM_BDTR_OSSR);

  tim_clear_tif(g_base);
  return OK;
}

int board_awd_pwm_latch_arm(void)
{
  if (!g_dev || !g_base) return -ENODEV;

  tim_clear_tif(g_base);

  /* Force ON state: CNT >= CCR (use CNT=ARR), keep CEN=0 */
  tim_set_cnt(g_base, g_arr);

  /* Enable outputs and MOE via LL ops */
  PWM_OUTPUTS_ENABLE(g_dev, out_mask(g_ch), true);  /* CCxE=1 */
  PWM_SOFT_BREAK(g_dev, false);                     /* MOE=1  */
  PWM_TIM_ENABLE(g_dev, false);                     /* CEN remains 0 */

  return OK;
}

int board_awd_pwm_latch_rearm(void)
{
  if (!g_dev || !g_base) return -ENODEV;
  tim_clear_tif(g_base);
  tim_set_cnt(g_base, g_arr);
  PWM_SOFT_BREAK(g_dev, false);
  PWM_OUTPUTS_ENABLE(g_dev, out_mask(g_ch), true);
  PWM_TIM_ENABLE(g_dev, false);
  return OK;
}

int board_awd_pwm_latch_disarm(void)
{
  if (!g_dev || !g_base) return -ENODEV;
  PWM_SOFT_BREAK(g_dev, true);                      /* MOE=0 */
  PWM_OUTPUTS_ENABLE(g_dev, out_mask(g_ch), false); /* CCxE=0 */
  return OK;
}

bool board_awd_pwm_latch_tripped(void)
{
  if (!g_base) return false;
  return tim_tif(g_base);
}

#endif /* CONFIG_NUCLEO_H563ZI_AWD_PWM_LATCH */
