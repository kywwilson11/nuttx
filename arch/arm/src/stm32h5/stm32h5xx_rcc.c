/****************************************************************************
 * arch/arm/src/stm32h5/stm32h562xx_rcc.c
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
#include <arch/stm32h5/chip.h>
#include <arch/board/board.h>

#include "stm32h5_pwr.h"
#include "stm32h5_flash.h"
#include "stm32h5_rcc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Allow up to 100 milliseconds for the high speed clock to become ready.
 * that is a very long delay, but if the clock does not become ready we are
 * hosed anyway.  Normally this is very fast, but I have seen at least one
 * board that required this long, long timeout for the HSE to be ready.
 */

#define HSERDY_TIMEOUT (100 * CONFIG_BOARD_LOOPSPERMSEC)

/* Same for HSI and MSI */

#define HSIRDY_TIMEOUT HSERDY_TIMEOUT
#define LSIRDY_TIMEOUT HSERDY_TIMEOUT

/* HSE divisor to yield ~1MHz RTC clock */

#define HSE_DIVISOR (STM32H5_HSE_FREQUENCY + 500000) / 1000000

/* Determine if board wants to use HSI48 as 48 MHz oscillator. */

#if defined(CONFIG_STM32H5_HAVE_HSI48) && defined(STM32H5_USE_CLK48)
#  if STM32H5_CLK48_SEL == RCC_CCIPR_CLK48SEL_HSI48
#    define STM32H5_USE_HSI48
#  endif
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rcc_enableahb1
 *
 * Description:
 *   Enable selected AHB1 peripherals
 *
 ****************************************************************************/

static inline void rcc_enableahb1(void)
{
  uint32_t regval;

  /* Set the appropriate bits in the AHB1ENR register to enabled the
   * selected AHB1 peripherals.
   */

  regval = getreg32(STM32H5_RCC_AHB1ENR);

#ifdef CONFIG_STM32H5_GPDMA1
  /* DMA 1 clock enable */

  regval |= RCC_AHB1ENR_GPDMA1EN;
#endif

#ifdef CONFIG_STM32H5_GPDMA2
  /* DMA 2 clock enable */

  regval |= RCC_AHB1ENR_GPDMA2EN;
#endif

#ifdef CONFIG_STM32H5_FLASHEN
  /* Flash memory interface clock enable */

  regval |= RCC_AHB1ENR_FLASHEN;
#endif

#ifdef CONFIG_STM32H5_CRC
  /* CRC clock enable */

  regval |= RCC_AHB1ENR_CRCEN;
#endif

#ifdef CONFIG_STM32H5_CORDIC
  /* CORDIC clock enable */

  regval |= RCC_AHB1ENR_CORDICEN;
#endif

#ifdef CONFIG_STM32H5_FMAC
  /* FMAC clock enable */

  regval |= RCC_AHB1ENR_FMACEN;
#endif

#ifdef CONFIG_STM32H5_RAMCFG
  /* RAMCFG clock enable */

  regval |= RCC_AHB1ENR_RAMCFGEN;
#endif

#ifdef CONFIG_STM32H5_ETH
  /* ETH clock enable */

  regval |= RCC_AHB1ENR_ETHEN;
#endif
#ifdef CONFIG_STM32H5_ETHTX
  /* ETH TX clock enable */

  regval |= RCC_AHB1ENR_ETHTXEN;
#endif

#ifdef CONFIG_STM32H5_ETHRX
  /* ETH RX clock enable */

  regval |= RCC_AHB1ENR_ETHRXEN;
#endif

#ifdef CONFIG_STM32H5_TZSC1


  regval |= RCC_AHB1ENR_TZSC1EN;
#endif

#ifdef CONFIG_STM32H5_BKPRAM
  /* BKPRAM clock enable */

  regval |= RCC_AHB1ENR_BKPRAMEN;
#endif

#ifdef CONFIG_STM32H5_DCACHE
  /* DCACHE clock enable */

  regval |= RCC_AHB1ENR_DCACHEEN;
#endif

#ifdef CONFIG_STM32H5_SRAM1
  /* ETH clock enable */

  regval |= RCC_AHB1ENR_SRAM1EN;
#endif

  putreg32(regval, STM32H5_RCC_AHB1ENR);   /* Enable peripherals */
}

/****************************************************************************
 * Name: rcc_enableahb2
 *
 * Description:
 *   Enable selected AHB2 peripherals
 *
 ****************************************************************************/

static inline void rcc_enableahb2(void)
{
  uint32_t regval;

  /* Set the appropriate bits in the AHB2ENR register to enable the
   * selected AHB2 peripherals.
   */

  regval = getreg32(STM32H5_RCC_AHB2ENR);

  /* Enable GPIOA, GPIOB, .... GPIOH */

#if STM32H5_NPORTS > 0
  regval |= (RCC_AHB2ENR_GPIOAEN
#if STM32H5_NPORTS > 1
             | RCC_AHB2ENR_GPIOBEN
#endif
#if STM32H5_NPORTS > 2
             | RCC_AHB2ENR_GPIOCEN
#endif
#if STM32H5_NPORTS > 3
             | RCC_AHB2ENR_GPIODEN
#endif
#if STM32H5_NPORTS > 4
             | RCC_AHB2ENR_GPIOEEN
#endif
#if STM32H5_NPORTS > 5
             | RCC_AHB2ENR_GPIOFEN
#endif
#if STM32H5_NPORTS > 6
             | RCC_AHB2ENR_GPIOGEN
#endif
#if STM32H5_NPORTS > 7
             | RCC_AHB2ENR_GPIOHEN
#endif
#if STM32H5_NPORTS > 7
             | RCC_AHB2ENR_GPIOIEN
#endif

	     );
#endif

#if defined(CONFIG_STM32H5_ADC)
  /* ADC clock enable */

  regval |= RCC_AHB2ENR_ADCEN;
#endif

#ifdef CONFIG_STM32H5_DAC1
  /* DAC1 clock enable */

  regval |= RCC_AHB2ENR_DAC1EN;
#endif

#ifdef CONFIG_STM32H5_DCMI_PSSI
  /* Digital Camera Interface clock enable */

  regval |= RCC_AHB2ENR_DCMI_PSSIEN;
#endif

#ifdef CONFIG_STM32H5_AES
  /* Cryptographic modules clock enable */

  regval |= RCC_AHB2ENR_AESEN;
#endif

#ifdef CONFIG_STM32H5_HASH
  /* Hash module enable */

  regval |= RCC_AHB2ENR_HASHEN
#endif

#ifdef CONFIG_STM32H5_RNG
  /* Random number generator clock enable */

  regval |= RCC_AHB2ENR_RNGEN;
#endif

#ifdef CONFIG_STM32H5_PKA
  /* Public Key Accelerator clock enable */

  regval |= RCC_AHB2ENR_PKAEN;
#endif

#ifdef CONFIG_STM32H5_SAES
  /* Secure AES coprocessor clock enable */

  regval |= RCC_AHB2ENR_SAESEN;
#endif

#ifdef CONFIG_STM32H5_SRAM2
  /* SRAM2 clock enable */

  regval |= RCC_AHB2ENR_SRAM2EN;
#endif

#ifdef CONFIG_STM32H5_SRAM3
  /* SRAM2 clock enable */

  regval |= RCC_AHB2ENR_SRAM3EN;
#endif

  putreg32(regval, STM32H5_RCC_AHB2ENR);   /* Enable peripherals */
}

/****************************************************************************
 * Name: rcc_enableahb4
 *
 * Description:
 *   Enable selected AHB4 peripherals
 *
 ****************************************************************************/

static inline void rcc_enableahb4(void)
{
  uint32_t regval;

  /* Set the appropriate bits in the AHB4ENR register to enabled the
   * selected AHB4 peripherals.
   */

  regval = getreg32(STM32H5_RCC_AHB4ENR);

#ifdef CONFIG_STM32H5_OTFDEC1EN
  /* On-the-fly-decryption module clock enable */

  regval |= RCC_AHB4ENR_OTFDEC1EN;
#endif

#ifdef CONFIG_STM32H5_SDMMC1
  /* SDMMC1 clock enable */

  regval |= RCC_AHB4ENR_SDMMC1EN;
#endif

#ifdef CONFIG_STM32H5_SDMMC2
  /* SDMMC1 clock enable */

  regval |= RCC_AHB4ENR_SDMMC2EN;
#endif


#ifdef CONFIG_STM32H5_FMC
  /* Flexible memory controller clock enable */

  regval |= RCC_AHB4ENR_FMCEN;
#endif

#ifdef CONFIG_STM32H5_OCTOSPI1
  /* OCTOSPI1 module clock enable */

  regval |= RCC_AHB4ENR_OSPI1EN;
#endif

  putreg32(regval, STM32H5_RCC_AHB4ENR);   /* Enable peripherals */
}

/****************************************************************************
 * Name: rcc_enableapb1l
 *
 * Description:
 *   Enable selected APB1L peripherals
 *
 ****************************************************************************/

static inline void rcc_enableapb1l(void)
{
  uint32_t regval;

  /* Set the appropriate bits in the APB1LENR register to enabled the
   * selected APB1L peripherals.
   */
 
  regval = getreg32(STM32H5_RCC_APB1LENR);

#ifdef CONFIG_STM32H5_TIM2
  /* Bit 0:  TIM2 clock enable */

  regval |= RCC_APB1LENR_TIM2EN;
#endif

#ifdef CONFIG_STM32H5_TIM3
  /* Bit 1:  TIM3 clock enable */

  regval |= RCC_APB1LENR_TIM3EN;
#endif

#ifdef CONFIG_STM32H5_TIM4
  /* Bit 2:  TIM4 clock enable */

  regval |= RCC_APB1LENR_TIM4EN;
#endif

#ifdef CONFIG_STM32H5_TIM5
  /* Bit 3:  TIM5 clock enable */

  regval |= RCC_APB1LENR_TIM5EN;
#endif

#ifdef CONFIG_STM32H5_TIM6
  /* Bit 4:  TIM6 clock enable */

  regval |= RCC_APB1LENR_TIM6EN;
#endif

#ifdef CONFIG_STM32H5_TIM7
  /* Bit 5:  TIM7 clock enable */

  regval |= RCC_APB1LENR_TIM7EN;
#endif

#ifdef CONFIG_STM32H5_TIM12
  /* Bit 5:  TIM12 clock enable */

  regval |= RCC_APB1LENR_TIM12EN;
#endif

#ifdef CONFIG_STM32H5_TIM13
  /* Bit 5:  TIM13 clock enable */

  regval |= RCC_APB1LENR_TIM13EN;
#endif

#ifdef CONFIG_STM32H5_TIM14
  /* Bit 5:  TIM14 clock enable */

  regval |= RCC_APB1LENR_TIM14EN;
#endif

#ifdef CONFIG_STM32H5_SPI2
  /* Bit 14: SPI2 clock enable */

  regval |= RCC_APB1LENR_SPI2EN;
#endif

#ifdef CONFIG_STM32H5_SPI3
  /* Bit 15: SPI3 clock enable */

  regval |= RCC_APB1LENR_SPI3EN;
#endif

#ifdef CONFIG_STM32H5_USART2
  /* Bit 17: USART2 clock enable */

  regval |= RCC_APB1LENR_USART2EN;
#endif

#ifdef CONFIG_STM32H5_USART3
  /* Bit 18: USART3 clock enable */

  regval |= RCC_APB1LENR_USART3EN;
#endif

#ifdef CONFIG_STM32H5_UART4
  /* Bit 19: UART4 clock enable */

  regval |= RCC_APB1LENR_UART4EN;
#endif

#ifdef CONFIG_STM32H5_UART5
  /* Bit 20: UART5 clock enable */

  regval |= RCC_APB1LENR_UART5EN;
#endif

#ifdef CONFIG_STM32H5_I2C1
  /* Bit 21: I2C1 clock enable */

  regval |= RCC_APB1LENR_I2C1EN;
#endif

#ifdef CONFIG_STM32H5_I2C2
  /* Bit 22: I2C2 clock enable */

  regval |= RCC_APB1LENR_I2C2EN;
#endif

#ifdef CONFIG_STM32H5_I3C1
  /* Bit 23: I3C1 clock enable */

  regval |= RCC_APB1LENR_I3C1EN;
#endif

#ifdef STM32H5_USE_HSI48
  if (STM32H5_HSI48_SYNCSRC != SYNCSRC_NONE)
    {
      /* Bit 24: CRS clock enable */

  regval |= RCC_APB1LENR_CRSEN;
    }
#endif

#ifdef CONFIG_STM32H5_USART6
  /* Bit 25: USART6 clock enable */

  regval |= RCC_APB1LENR_USART6EN;
#endif

#ifdef CONFIG_STM32H5_USART10
  /* Bit 26: USART10 clock enable */

  regval |= RCC_APB1LENR_USART10EN;
#endif

#ifdef CONFIG_STM32H5_USART11
  /* Bit 27: USART11 clock enable */

  regval |= RCC_APB1LENR_USART11EN;
#endif

#ifdef CONFIG_STM32H5_CEC
  /* Bit 28: CEC clock enable */

  regval |= RCC_APB1LENR_CECEN;
#endif

#ifdef CONFIG_STM32H5_UART7
  /* Bit 30: UART7 clock enable */

  regval |= RCC_APB1LENR_UART7EN;
#endif

#ifdef CONFIG_STM32H5_UART8
  /* Bit 31: UART8 clock enable */

  regval |= RCC_APB1LENR_UART8EN;
#endif

  putreg32(regval, STM32H5_RCC_APB1LENR);   /* Enable peripherals */
}

/****************************************************************************
 * Name: rcc_enableapb1h
 *
 * Description:
 *   Enable selected APB1H peripherals
 *
 ****************************************************************************/

static inline void rcc_enableapb1h(void)
{
  uint32_t regval;

  /* Set the appropriate bits in the APB1HENR register to enabled the
   * selected APB1H peripherals.
   */
  
  regval = getreg32(STM32H5_RCC_APB1HENR);

#ifdef CONFIG_STM32H5_UART9
  /* Bit 0:  UART9 clock enable */

  regval |= RCC_APB1HENR_UART9EN;
#endif

#ifdef CONFIG_STM32H5_UART12
  /* Bit 1:  UART12 clock enable */

  regval |= RCC_APB1HENR_UART12EN;
#endif

#ifdef CONFIG_STM32H5_DTS
  /* Bit 3:  DTS clock enable */

  regval |= RCC_APB1HENR_DTSEN;
#endif

#ifdef CONFIG_STM32H5_LPTIM2
  /* Bit 5:  Low-power Timer 2 clock enable */

  regval |= RCC_APB1HENR_LPTIM2EN;
#endif

#ifdef CONFIG_STM32H5_FDCAN
  /* Bit 9:  FDCAN clock enable */

  regval |= RCC_APB1HENR_FDCANEN;
#endif

#ifdef CONFIG_STM32H5_UCPD1
  /* Bit 23: UCPD1 clock enable */

  regval |= RCC_APB1HENR_UCPD1EN;
#endif
  
  /* Enable APB1H peripherals */
  
  putreg32(regval, STM32H5_RCC_APB1HENR);

}

/****************************************************************************
 * Name: rcc_enableapb2
 *
 * Description:
 *   Enable selected APB2 peripherals
 *
 ****************************************************************************/

static inline void rcc_enableapb2(void)
{
  uint32_t regval;

  /* Set the appropriate bits in the APB2ENR register to enabled the
   * selected APB2 peripherals.
   */

  regval = getreg32(STM32H5_RCC_APB2ENR);


#ifdef CONFIG_STM32H5_TIM1
  /* TIM1 clock enable */

  regval |= RCC_APB2ENR_TIM1EN;
#endif

#ifdef CONFIG_STM32H5_SPI1
  /* SPI1 clock enable */

  regval |= RCC_APB2ENR_SPI1EN;
#endif

#ifdef CONFIG_STM32H5_TIM8
  /* TIM8 clock enable */

  regval |= RCC_APB2ENR_TIM8EN;
#endif

#ifdef CONFIG_STM32H5_USART1
  /* USART1 clock enable */

  regval |= RCC_APB2ENR_USART1EN;
#endif

#ifdef CONFIG_STM32H5_TIM15
  /* TIM15 clock enable */

  regval |= RCC_APB2ENR_TIM15EN;
#endif

#ifdef CONFIG_STM32H5_TIM16
  /* TIM16 clock enable */

  regval |= RCC_APB2ENR_TIM16EN;
#endif

#ifdef CONFIG_STM32H5_TIM17
  /* TIM17 clock enable */

  regval |= RCC_APB2ENR_TIM17EN;
#endif

#ifdef CONFIG_STM32H5_SPI4
  /* SPI4 clock enable */

  regval |= RCC_APB2ENR_SPI4EN;
#endif

#ifdef CONFIG_STM32H5_SPI6
  /* SPI6 clock enable */

  regval |= RCC_APB2ENR_SPI6EN;
#endif

#ifdef CONFIG_STM32H5_SAI1
  /* SAI1 clock enable */

  regval |= RCC_APB2ENR_SAI1EN;
#endif

#ifdef CONFIG_STM32H5_SAI2
  /* SAI2 clock enable */

  regval |= RCC_APB2ENR_SAI2EN;
#endif

#ifdef CONFIG_STM32H5_USB
  /* USB clock enable */

  regval |= RCC_APB2ENR_USBEN;
#endif

  putreg32(regval, STM32H5_RCC_APB2ENR);   /* Enable peripherals */
}

/****************************************************************************
 * Name: rcc_enableapb3
 *
 * Description:
 *   Enable selected APB3 peripherals
 *
 ****************************************************************************/

static inline void rcc_enableapb3(void)
{
  uint32_t regval;

  /* Set the appropriate bits in the APB2ENR register to enabled the
   * selected APB2 peripherals.
   */

  regval = getreg32(STM32H5_RCC_APB3ENR);


#ifdef CONFIG_STM32H5_SBS
  /* Bit 1: SBS clock enable */

  regval |= RCC_APB3ENR_SBSEN;
#endif

#ifdef CONFIG_STM32H5_SPI5
  /* Bit 5: SPI5 clock enable */

  regval |= RCC_APB3ENR_SPI5EN;
#endif

#ifdef CONFIG_STM32H5_LPUART1
  /* Bit 6: LPUART1 clock enable */

  regval |= RCC_APB3ENR_LPUART1EN;
#endif

#ifdef CONFIG_STM32H5_I2C3
  /* Bit 7: I2C3 clock enable */

  regval |= RCC_APB3ENR_I2C3EN;
#endif

#ifdef CONFIG_STM32H5_I2C4
  /* Bit 8: I2C4 clock enable */

  regval |= RCC_APB3ENR_I2C4EN;
#endif

#ifdef CONFIG_STM32H5_I3C2
  /* Bit 9: I3C2 clock enable */

  regval |= RCC_APB3ENR_I3C2EN;
#endif

#ifdef CONFIG_STM32H5_LPTIM1
  /* Bit 11: LPTIM1 clock enable */

  regval |= RCC_APB3ENR_LPTIM1EN;
#endif

#ifdef CONFIG_STM32H5_LPTIM3
  /* Bit 12: LPTIM3 clock enable */

  regval |= RCC_APB3ENR_LPTIM3EN;
#endif

#ifdef CONFIG_STM32H5_LPTIM4
  /* Bit 13: LPTIM4 clock enable */

  regval |= RCC_APB3ENR_LPTIM4EN;
#endif

#ifdef CONFIG_STM32H5_LPTIM5
  /* Bit 14: LPTIM5 clock enable */

  regval |= RCC_APB3ENR_LPTIM5EN;
#endif

#ifdef CONFIG_STM32H5_LPTIM6
  /* Bit 15: LPTIM6 clock enable */

  regval |= RCC_APB3ENR_LPTIM6EN;
#endif

#ifdef CONFIG_STM32H5_VREF
  /* Bit 20: VREF clock enable */

  regval |= RCC_APB3ENR_VREFEN;
#endif

#ifdef CONFIG_STM32H5_RTCAPB
  /* Bit 21: RTCABP clock enable */

  regval |= RCC_APB3ENR_RTCAPBEN;
#endif


  /* Enable peripherals */
  
  putreg32(regval, STM32H5_RCC_APB3ENR);   

}
/****************************************************************************
 * Name: rcc_enableccip
 *
 * Description:
 *   Set peripherals independent clock configuration.
 *
 ****************************************************************************/

static inline void rcc_enableccip(void)
{
  /* Certain peripherals have no clock selected even when their enable bit is
   * set. Set some defaults in the CCIPR register so those peripherals
   * will at least have a clock.
   */
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32h5_rcc_enableperipherals
 ****************************************************************************/

void stm32h5_rcc_enableperipherals(void)
{
  rcc_enableccip();
  rcc_enableahb1();
  rcc_enableahb2();
  rcc_enableahb4();
  rcc_enableapb1l();
  rcc_enableapb1h();
  rcc_enableapb2();
  rcc_enableapb3();
}

/****************************************************************************
 * Name: stm32h5_stdclockconfig
 *
 * Description:
 *   Called to change to new clock based on settings in board.h
 *
 *   NOTE:  This logic would need to be extended if you need to select low-
 *   power clocking modes!
 ****************************************************************************/

#ifndef CONFIG_ARCH_BOARD_STM32H5_CUSTOM_CLOCKCONFIG
void stm32h5_stdclockconfig(void)
{
  uint32_t regval;
  volatile int32_t timeout;

#if defined(STM32H5_BOARD_USEHSI)
  /* Enable Internal High-Speed Clock (HSI) */

  regval  = getreg32(STM32H5_RCC_CR);
  regval |= RCC_CR_HSION;           /* Enable HSI */
  putreg32(regval, STM32H5_RCC_CR);

  /* Wait until the HSI is ready (or until a timeout elapsed) */

  for (timeout = HSIRDY_TIMEOUT; timeout > 0; timeout--)
    {
      /* Check if the HSIRDY flag is the set in the CR */

      if ((getreg32(STM32H5_RCC_CR) & RCC_CR_HSIRDY) != 0)
        {
          /* If so, then break-out with timeout > 0 */

          break;
        }
    }
#endif

#if defined(STM32H5_BOARD_USEHSI)
  /* Already set above */

#elif defined(STM32H5_BOARD_USECSI)
  /* Enable Internal Low Power Internal Clock (CSI) */

  /* Wait until the CSI is either off or ready (or until a timeout elapsed) */

  for (timeout = CSIRDY_TIMEOUT; timeout > 0; timeout--)
    {
      if ((regval = getreg32(STM32H5_RCC_CR)),
          (regval & RCC_CR_CSIRDY) || ~(regval & RCC_CR_CSION))
        {
          /* If so, then break-out with timeout > 0 */

          break;
        }
    }

  regval  = getreg32(STM32H5_RCC_CR);
  regval |= RCC_CR_CSION;    /* Enable CSI */
  putreg32(regval, STM32H5_RCC_CR);

  /* Wait until the CSI is ready (or until a timeout elapsed) */

  for (timeout = CSIRDY_TIMEOUT; timeout > 0; timeout--)
    {
      /* Check if the CSIRDY flag is the set in the CR */

      if ((getreg32(STM32H5_RCC_CR) & RCC_CR_CSIRDY) != 0)
        {
          /* If so, then break-out with timeout > 0 */

          break;
        }
    }

#elif defined(STM32H5_BOARD_USEHSE)
  /* Enable External High-Speed Clock (HSE) */

  regval  = getreg32(STM32H5_RCC_CR);
  regval |= RCC_CR_HSEON;           /* Enable HSE */
  putreg32(regval, STM32H5_RCC_CR);

  /* Wait until the HSE is ready (or until a timeout elapsed) */

  for (timeout = HSERDY_TIMEOUT; timeout > 0; timeout--)
    {
      /* Check if the HSERDY flag is the set in the CR */

      if ((getreg32(STM32H5_RCC_CR) & RCC_CR_HSERDY) != 0)
        {
          /* If so, then break-out with timeout > 0 */

          break;
        }
    }
#else

#  error stm32h5_stdclockconfig(), must have one of STM32H5_BOARD_USEHSI, STM32H5_BOARD_USECSI, STM32H5_BOARD_USEHSE defined

#endif

  /* Check for a timeout.  If this timeout occurs, then we are hosed.  We
   * have no real back-up plan, although the following logic makes it look
   * as though we do.
   */

  if (timeout > 0)
    {
      /* TODO Look at power stuff next */
      /* Select main regulator voltage range according to system clock
       * frequency.
       */

      /* Ensure Power control is enabled before modifying it. */

      stm32h5_pwr_enableclk(true);

      /* Select correct main regulator range */

      regval = getreg32(STM32H5_PWR_CR1);
      regval &= ~PWR_CR1_VOS_MASK;

      if (STM32H5_SYSCLK_FREQUENCY > 80000000)
        {
          regval |= PWR_CR1_VOS_RANGE0;
        }
      else if (STM32H5_SYSCLK_FREQUENCY > 26000000)
        {
          regval |= PWR_CR1_VOS_RANGE1;
        }
      else
        {
          regval |= PWR_CR1_VOS_RANGE0;
        }

      putreg32(regval, STM32H5_PWR_CR1);

      /* Wait for voltage regulator to stabilize */

      while (getreg32(STM32H5_PWR_SR2) & PWR_SR2_VOSF)
        {
        }

      /* Set the HCLK source/divider */

      regval  = getreg32(STM32H5_RCC_CFGR2);
      regval &= ~RCC_CFGR2_HPRE_MASK;
      regval |= STM32H5_RCC_CFGR2_HPRE;
      putreg32(regval, STM32H5_RCC_CFGR2);

      /* Set the PCLK2 divider */

      regval  = getreg32(STM32H5_RCC_CFGR2);
      regval &= ~RCC_CFGR2_PPRE2_MASK;
      regval |= STM32H5_RCC_CFGR2_PPRE2;
      putreg32(regval, STM32H5_RCC_CFGR2);

      /* Set the PCLK1 divider */

      regval  = getreg32(STM32H5_RCC_CFGR2);
      regval &= ~RCC_CFGR2_PPRE1_MASK;
      regval |= STM32H5_RCC_CFGR2_PPRE1;
      putreg32(regval, STM32H5_RCC_CFGR2);

#ifdef CONFIG_STM32H5_RTC_HSECLOCK
      /* Set the RTC clock divisor */

      regval  = getreg32(STM32H5_RCC_CFGR1);
      regval &= ~RCC_CFGR1_RTCPRE_MASK;
      regval |= RCC_CFGR1_RTCPRE(HSE_DIVISOR);
      putreg32(regval, STM32H5_RCC_CFGR1);
#endif

      /* Set the PLL1 source and main divider */

      regval  = getreg32(STM32H5_RCC_PLL1CFGR);

      /* Configure PLL1 */

      /* Set the PLL dividers and multipliers to configure PLL1 */

      regval = (STM32H5_PLL1CFGR_PLLM | STM32H5_PLL1CFGR_PLLP | 
		STM32H5_PLL1CFGR_PLLQ | STM32H5_PLL1CFGR_PLLR);

#ifdef STM32H5_PLLCFG_PLLP_ENABLED
      regval |= RCC_PLL1CFGR_PLLPEN;
#endif
#ifdef STM32H5_PLLCFG_PLLQ_ENABLED
      regval |= RCC_PLL1CFGR_PLLQEN;
#endif
#ifdef STM32H5_PLLCFG_PLLR_ENABLED
      regval |= RCC_PLL1CFGR_PLLREN;
#endif

      /* XXX The choice of clock source to PLL1 (all three) is independent
       * of the sys clock source choice, review the STM32H5_BOARD_USEHSI
       * name; probably split it into two, one for PLL source and one
       * for sys clock source.
       */

#ifdef STM32H5_BOARD_USEHSI
      regval |= RCC_PLL1CFGR_PLL1SRC_HSI;
#elif defined(STM32H5_BOARD_USECSI)
      regval |= RCC_PLL1CFGR_PLL1SRC_CSI;
#else /* if STM32H5_BOARD_USEHSE */
      regval |= RCC_PLL1CFGR_PLL1SRC_HSE;
#endif

      putreg32(regval, STM32H5_RCC_PLL1CFGR);

      /* Enable PLL1 */

      regval  = getreg32(STM32H5_RCC_CR);
      regval |= RCC_CR_PLL1ON;
      putreg32(regval, STM32H5_RCC_CR);

      /* Wait until PLL1 is ready */

      while ((getreg32(STM32H5_RCC_CR) & RCC_CR_PLL1RDY) == 0)
        {
        }

      /* Set the PLL2 source and main divider */

      regval  = getreg32(STM32H5_RCC_PLL2CFGR);

      /* Configure PLL2 */

      /* Set the PLL dividers and multipliers to configure PLL2 */

      regval = (STM32H5_PLL2CFGR_PLLM | STM32H5_PLL2CFGR_PLLP | 
		STM32H5_PLL2CFGR_PLLQ | STM32H5_PLL2CFGR_PLLR);

#ifdef STM32H5_PLLCFG_PLLP_ENABLED
      regval |= RCC_PLL2CFGR_PLLPEN;
#endif
#ifdef STM32H5_PLLCFG_PLLQ_ENABLED
      regval |= RCC_PLL2CFGR_PLLQEN;
#endif
#ifdef STM32H5_PLLCFG_PLLR_ENABLED
      regval |= RCC_PLL2CFGR_PLLREN;
#endif

      /* XXX The choice of clock source to PLL (all three) is independent
       * of the sys clock source choice, review the STM32H5_BOARD_USEHSI
       * name; probably split it into two, one for PLL source and one
       * for sys clock source.
       */

#ifdef STM32H5_BOARD_USEHSI
      regval |= RCC_PLL2CFGR_PLL2SRC_HSI;
#elif defined(STM32H5_BOARD_USECSI)
      regval |= RCC_PLL2CFGR_PLL2SRC_CSI;
#else /* if STM32H5_BOARD_USEHSE */
      regval |= RCC_PLL2CFGR_PLL2SRC_HSE;
#endif

      putreg32(regval, STM32H5_RCC_PLL2CFGR);

      /* Enable the main PLL */

      regval  = getreg32(STM32H5_RCC_CR);
      regval |= RCC_CR_PLL2ON;
      putreg32(regval, STM32H5_RCC_CR);

      /* Wait until the PLL is ready */

      while ((getreg32(STM32H5_RCC_CR) & RCC_CR_PLL2RDY) == 0)
        {
        }

#ifdef CONFIG_STM32H5_SAI1PLL
      /* Configure SAI1 PLL */

      regval  = getreg32(STM32H5_RCC_PLLSAI1CFG);

      /* Set the PLL dividers and multipliers to configure the SAI1 PLL */

      regval = (STM32H5_PLLSAI1CFG_PLLN | STM32H5_PLLSAI1CFG_PLLP
                 | STM32H5_PLLSAI1CFG_PLLQ | STM32H5_PLLSAI1CFG_PLLR);

#ifdef STM32H5_PLLSAI1CFG_PLLP_ENABLED
      regval |= RCC_PLLSAI1CFG_PLLPEN;
#endif
#ifdef STM32H5_PLLSAI1CFG_PLLQ_ENABLED
      regval |= RCC_PLLSAI1CFG_PLLQEN;
#endif
#ifdef STM32H5_PLLSAI1CFG_PLLR_ENABLED
      regval |= RCC_PLLSAI1CFG_PLLREN;
#endif

      putreg32(regval, STM32H5_RCC_PLLSAI1CFG);

      /* Enable the SAI1 PLL */

      regval  = getreg32(STM32H5_RCC_CR);
      regval |= RCC_CR_PLLSAI1ON;
      putreg32(regval, STM32H5_RCC_CR);

      /* Wait until the PLL is ready */

      while ((getreg32(STM32H5_RCC_CR) & RCC_CR_PLLSAI1RDY) == 0)
        {
        }
#endif

#ifdef CONFIG_STM32H5_SAI2PLL
      /* Configure SAI2 PLL */

      regval  = getreg32(STM32H5_RCC_PLLSAI2CFG);

      /* Set the PLL dividers and multipliers to configure the SAI2 PLL */

      regval = (STM32H5_PLLSAI2CFG_PLLN | STM32H5_PLLSAI2CFG_PLLP |
                STM32H5_PLLSAI2CFG_PLLR);

#ifdef STM32H5_PLLSAI2CFG_PLLP_ENABLED
      regval |= RCC_PLLSAI2CFG_PLLPEN;
#endif
#ifdef STM32H5_PLLSAI2CFG_PLLR_ENABLED
      regval |= RCC_PLLSAI2CFG_PLLREN;
#endif

      putreg32(regval, STM32H5_RCC_PLLSAI2CFG);

      /* Enable the SAI2 PLL */

      regval  = getreg32(STM32H5_RCC_CR);
      regval |= RCC_CR_PLLSAI2ON;
      putreg32(regval, STM32H5_RCC_CR);

      /* Wait until the PLL is ready */

      while ((getreg32(STM32H5_RCC_CR) & RCC_CR_PLLSAI2RDY) == 0)
        {
        }
#endif

      /* Enable FLASH 5 wait states */

      regval = FLASH_ACR_LATENCY_5;
      putreg32(regval, STM32H5_FLASH_ACR);

      /* Select the main PLL as system clock source */

      regval  = getreg32(STM32H5_RCC_CFGR);
      regval &= ~RCC_CFGR_SW_MASK;
      regval |= RCC_CFGR_SW_PLL;
      putreg32(regval, STM32H5_RCC_CFGR);

      /* Wait until the PLL source is used as the system clock source */

      while ((getreg32(STM32H5_RCC_CFGR) & RCC_CFGR_SWS_MASK) !=
             RCC_CFGR_SWS_PLL)
        {
        }

#if defined(CONFIG_STM32H5_IWDG) || defined(CONFIG_STM32H5_RTC_LSICLOCK)
      /* Low speed internal clock source LSI */

      stm32h5_rcc_enablelsi();
#endif

#if defined(STM32H5_USE_LSE)
      /* Low speed external clock source LSE
       *
       * TODO: There is another case where the LSE needs to
       * be enabled: if the MCO1 pin selects LSE as source.
       * XXX and other cases, like automatic trimming of MSI for USB use
       */

      /* ensure Power control is enabled since it is indirectly required
       * to alter the LSE parameters.
       */

      stm32h5_pwr_enableclk(true);

      /* XXX other LSE settings must be made before turning on the oscillator
       * and we need to ensure it is first off before doing so.
       */

      /* Turn on the LSE oscillator
       * XXX this will almost surely get moved since we also want to use
       * this for automatically trimming MSI, etc.
       */

      stm32h5_rcc_enablelse();

#  if defined(STM32H5_BOARD_USEMSI)
      /* Now that LSE is up, auto trim the MSI */

      regval  = getreg32(STM32H5_RCC_CR);
      regval |= RCC_CR_MSIPLLEN;
      putreg32(regval, STM32H5_RCC_CR);
#  endif
#endif /* STM32H5_USE_LSE */
    }
}
#endif
