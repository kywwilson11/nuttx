/****************************************************************************
 * arch/arm/include/stm32h5/stm32h562xx_irq.h
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

#ifndef __ARCH_ARM_INCLUDE_STM32H5_STM32H562XX_IRQ_H
#define __ARCH_ARM_INCLUDE_STM32H5_STM32H562XX_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <arch/stm32h5/stm32h5_irq.h>

/****************************************************************************
 * Pre-processor Prototypes
 ****************************************************************************/

/* IRQ numbers.  The IRQ number corresponds vector number and hence map
 * directly to bits in the NVIC.  This does, however, waste several words of
 * memory in the IRQ to handle mapping tables.
 *
 * Processor Exceptions (vectors 0-15). These common definitions can be found
 * in the file nuttx/arch/arm/include/stm32h5/stm32h5_irq.h, which is
 * included above.
 *
 * External interrupts (vectors >= 16)
 *
 * These interrupts vectors was implemented based on RM0438 Table 88
 * (STM32H552xx and STM32H562xx vector table) and should work for
 * STM32H552xx and STL32H562xx.
 *
 */

#define STM32H5_IRQ_WWDG          (STM32H5_IRQ_FIRST + 0)   /* 0:   Window Watchdog interrupt */
#define STM32H5_IRQ_PVD_PVM       (STM32H5_IRQ_FIRST + 1)   /* 1:   PVD/PVM1/PVM2/PVM3/PVM4 */
#define STM32H5_IRQ_RTC           (STM32H5_IRQ_FIRST + 2)   /* 2:   RTC global interrupts */
#define STM32H5_IRQ_RTC_S         (STM32H5_IRQ_FIRST + 3)   /* 3:   RTC secure global interrupts */
#define STM32H5_IRQ_TAMP          (STM32H5_IRQ_FIRST + 4)   /* 4:   Tamper global interrupt */
#define STM32H5_IRQ_RAMCFG        (STM32H5_IRQ_FIRST + 5)   /* 5:   Tamper secure global interrupt */
#define STM32H5_IRQ_FLASH         (STM32H5_IRQ_FIRST + 6)   /* 6:   Flash memory global interrupt */
#define STM32H5_IRQ_FLASH_S       (STM32H5_IRQ_FIRST + 7)   /* 7:   Flash memory secure global interrupt */
#define STM32H5_IRQ_GTZC          (STM32H5_IRQ_FIRST + 8)   /* 8:   TZIC secure global interrupt */
#define STM32H5_IRQ_RCC           (STM32H5_IRQ_FIRST + 9)   /* 9:   RCC global interrupt */
#define STM32H5_IRQ_RCC_S         (STM32H5_IRQ_FIRST + 10)  /* 10:  RCC secure global interrupt */
#define STM32H5_IRQ_EXTI0         (STM32H5_IRQ_FIRST + 11)  /* 11:  EXTI Line 0 interrupt */
#define STM32H5_IRQ_EXTI1         (STM32H5_IRQ_FIRST + 12)  /* 12:  EXTI Line 1 interrupt */
#define STM32H5_IRQ_EXTI2         (STM32H5_IRQ_FIRST + 13)  /* 13:  EXTI Line 2 interrupt */
#define STM32H5_IRQ_EXTI3         (STM32H5_IRQ_FIRST + 14)  /* 14:  EXTI Line 3 interrupt */
#define STM32H5_IRQ_EXTI4         (STM32H5_IRQ_FIRST + 15)  /* 15:  EXTI Line 4 interrupt */
#define STM32H5_IRQ_EXTI5         (STM32H5_IRQ_FIRST + 16)  /* 16:  EXTI Line 5 interrupt */
#define STM32H5_IRQ_EXTI6         (STM32H5_IRQ_FIRST + 17)  /* 17:  EXTI Line 6 interrupt */
#define STM32H5_IRQ_EXTI7         (STM32H5_IRQ_FIRST + 18)  /* 18:  EXTI Line 7 interrupt */
#define STM32H5_IRQ_EXTI8         (STM32H5_IRQ_FIRST + 19)  /* 19:  EXTI Line 8 interrupt */
#define STM32H5_IRQ_EXTI9         (STM32H5_IRQ_FIRST + 20)  /* 20:  EXTI Line 9 interrupt */
#define STM32H5_IRQ_EXTI10        (STM32H5_IRQ_FIRST + 21)  /* 21:  EXTI Line 10 interrupt */
#define STM32H5_IRQ_EXTI11        (STM32H5_IRQ_FIRST + 22)  /* 22:  EXTI Line 11 interrupt */
#define STM32H5_IRQ_EXTI12        (STM32H5_IRQ_FIRST + 23)  /* 23:  EXTI Line 12 interrupt */
#define STM32H5_IRQ_EXTI13        (STM32H5_IRQ_FIRST + 24)  /* 24:  EXTI Line 13 interrupt */
#define STM32H5_IRQ_EXTI14        (STM32H5_IRQ_FIRST + 25)  /* 25:  EXTI Line 14 interrupt */
#define STM32H5_IRQ_EXTI15        (STM32H5_IRQ_FIRST + 26)  /* 26:  EXTI Line 15 interrupt */
#define STM32H5_IRQ_GPDMA1_CH0    (STM32H5_IRQ_FIRST + 27)  /* 27:  DMAMUX1 overRun interrupt */
#define STM32H5_IRQ_GPDMA1_CH1    (STM32H5_IRQ_FIRST + 28)  /* 27:  DMAMUX1 overRun interrupt */
#define STM32H5_IRQ_GPDMA1_CH2    (STM32H5_IRQ_FIRST + 29)  /* 27:  DMAMUX1 overRun interrupt */
#define STM32H5_IRQ_GPDMA1_CH3    (STM32H5_IRQ_FIRST + 30)  /* 27:  DMAMUX1 overRun interrupt */
#define STM32H5_IRQ_GPDMA1_CH4    (STM32H5_IRQ_FIRST + 31)  /* 27:  DMAMUX1 overRun interrupt */
#define STM32H5_IRQ_GPDMA1_CH5    (STM32H5_IRQ_FIRST + 32)  /* 27:  DMAMUX1 overRun interrupt */
#define STM32H5_IRQ_GPDMA1_CH6    (STM32H5_IRQ_FIRST + 33)  /* 27:  DMAMUX1 overRun interrupt */
#define STM32H5_IRQ_GPDMA1_CH7    (STM32H5_IRQ_FIRST + 34)  /* 27:  DMAMUX1 overRun interrupt */
#define STM32H5_IRQ_IWDG          (STM32H5_IRQ_FIRST + 35)  /* 35:  DMA1 Channel 7 global interrupt */
#define STM32H5_IRQ_SAES          (STM32H5_IRQ_FIRST + 36)  /* 36:  DMA1 Channel 8 global interrupt */
#define STM32H5_IRQ_ADC1          (STM32H5_IRQ_FIRST + 37)  /* 37:  ADC1_2 global interrupt */
#define STM32H5_IRQ_DAC1          (STM32H5_IRQ_FIRST + 38)  /* 38:  DAC global interrupt */
#define STM32H5_IRQ_FDCAN1_IT0    (STM32H5_IRQ_FIRST + 39)  /* 39:  FDCAN1_IT0: FDCAN1 Interrupt 0 */
#define STM32H5_IRQ_FDCAN1_IT1    (STM32H5_IRQ_FIRST + 40)  /* 40:  FDCAN1_IT0: FDCAN1 Interrupt 1 */
#define STM32H5_IRQ_TIM1_BRK      (STM32H5_IRQ_FIRST + 41)  /* 41:  TIM1 break */
#define STM32H5_IRQ_TIM1_UP       (STM32H5_IRQ_FIRST + 42)  /* 42:  TIM1 update */
#define STM32H5_IRQ_TIM1_TRG_COM  (STM32H5_IRQ_FIRST + 43)  /* 43:  TIM1 trigger and communication */
#define STM32H5_IRQ_TIM1_CC       (STM32H5_IRQ_FIRST + 44)  /* 44:  TIM1 capture compare interrupt */
#define STM32H5_IRQ_TIM2          (STM32H5_IRQ_FIRST + 45)  /* 45:  TIM2 global interrupt */
#define STM32H5_IRQ_TIM3          (STM32H5_IRQ_FIRST + 46)  /* 46:  TIM3 global interrupt */
#define STM32H5_IRQ_TIM4          (STM32H5_IRQ_FIRST + 47)  /* 47:  TIM4 global interrupt */
#define STM32H5_IRQ_TIM5          (STM32H5_IRQ_FIRST + 48)  /* 48:  TIM5 global interrupt */
#define STM32H5_IRQ_TIM6          (STM32H5_IRQ_FIRST + 49)  /* 49:  TIM6 global interrupt */
#define STM32H5_IRQ_TIM7          (STM32H5_IRQ_FIRST + 50)  /* 50:  TIM7 global interrupt */
#define STM32H5_IRQ_I2C1_EV       (STM32H5_IRQ_FIRST + 51)  /* 51:  TIM8 break */
#define STM32H5_IRQ_I2C1_ER       (STM32H5_IRQ_FIRST + 52)  /* 52:  TIM8 update */
#define STM32H5_IRQ_I2C2_EV       (STM32H5_IRQ_FIRST + 53)  /* 53:  TIM8 trigger and communication */
#define STM32H5_IRQ_I2C2_ER       (STM32H5_IRQ_FIRST + 54)  /* 54:  TIM8 capture compare interrupt */
#define STM32H5_IRQ_SPI1          (STM32H5_IRQ_FIRST + 55)  /* 55:  I2C1 event interrupt */
#define STM32H5_IRQ_SPI2          (STM32H5_IRQ_FIRST + 56)  /* 56:  I2C1 error interrupt */
#define STM32H5_IRQ_SPI3          (STM32H5_IRQ_FIRST + 57)  /* 57:  I2C2 event interrupt */
#define STM32H5_IRQ_USART1        (STM32H5_IRQ_FIRST + 58)  /* 58:  I2C2 error interrupt */
#define STM32H5_IRQ_USART2        (STM32H5_IRQ_FIRST + 59)  /* 59:  SPI1 global interrupt */
#define STM32H5_IRQ_USART3        (STM32H5_IRQ_FIRST + 60)  /* 60:  SPI2 global interrupt */
#define STM32H5_IRQ_UART4         (STM32H5_IRQ_FIRST + 61)  /* 61:  USART1 global interrupt */
#define STM32H5_IRQ_UART5         (STM32H5_IRQ_FIRST + 62)  /* 62:  USART2 global interrupt */
#define STM32H5_IRQ_LPUART1       (STM32H5_IRQ_FIRST + 63)  /* 63:  USART3 global interrupt */
#define STM32H5_IRQ_LPTIM1        (STM32H5_IRQ_FIRST + 64)  /* 64:  UART4 global interrupt */
#define STM32H5_IRQ_TIM8_BRK      (STM32H5_IRQ_FIRST + 65)  /* 65:  UART5 global interrupt */
#define STM32H5_IRQ_TIM8_UP       (STM32H5_IRQ_FIRST + 66)  /* 66:  LPUART 1 global interrupt */
#define STM32H5_IRQ_TIM8_TRG_COM  (STM32H5_IRQ_FIRST + 67)  /* 67:  LPTIM1 global interrupt */
#define STM32H5_IRQ_TIM8_CC       (STM32H5_IRQ_FIRST + 68)  /* 68:  LPTIM2 global interrupt */
#define STM32H5_IRQ_ADC2          (STM32H5_IRQ_FIRST + 69)  /* 69:  TIM15 global interrupt */
#define STM32H5_IRQ_LPTIM2        (STM32H5_IRQ_FIRST + 70)  /* 70:  TIM16 global interrupt */
#define STM32H5_IRQ_TIM15         (STM32H5_IRQ_FIRST + 71)  /* 71:  TIM17 global interrupt */
                                                            /* 72:  Reserved */
                                                            /* 73:  Reserved */
#define STM32H5_IRQ_USB_FS        (STM32H5_IRQ_FIRST + 74)  /* 74:  CRS global interrupt */
#define STM32H5_IRQ_CRS           (STM32H5_IRQ_FIRST + 75)  /* 75:  FMC global interrupt */
#define STM32H5_IRQ_UCPD1         (STM32H5_IRQ_FIRST + 76)  /* 76:  OCTOSPI1 global interrupt */
#define STM32H5_IRQ_FMC           (STM32H5_IRQ_FIRST + 77)  /* 77:  OCTOSPI1 global interrupt */
#define STM32H5_IRQ_OCTOSPI1      (STM32H5_IRQ_FIRST + 78)  /* 78:  SDMMC1 global interrupt */
#define STM32H5_IRQ_SDMMC1        (STM32H5_IRQ_FIRST + 79)  /* 79:  SDMMC1 global interrupt */
#define STM32H5_IRQ_I2C3_EV       (STM32H5_IRQ_FIRST + 80)  /* 80:  DMA2 Channel 1 global interrupt */
#define STM32H5_IRQ_I2C3_ER       (STM32H5_IRQ_FIRST + 81)  /* 81:  DMA2 Channel 2 global interrupt */
#define STM32H5_IRQ_SPI4          (STM32H5_IRQ_FIRST + 82)  /* 82:  DMA2 Channel 3 global interrupt */
                                                            /* 83:  Reserved */
                                                            /* 84:  Reserved */
#define STM32H5_IRQ_USART6        (STM32H5_IRQ_FIRST + 85)  /* 85:  DMA2 Channel 6 global interrupt */
                                                            /* 86:  Reserved */
                                                            /* 87:  Reserved */
                                                            /* 88:  Reserved */
                                                            /* 89:  Reserved */
#define STM32H5_IRQ_GPDMA2_CH0    (STM32H5_IRQ_FIRST + 90)  /* 90:  SAI1 global interrupt */
#define STM32H5_IRQ_GPDMA2_CH1    (STM32H5_IRQ_FIRST + 91)  /* 90:  SAI1 global interrupt */
#define STM32H5_IRQ_GPDMA2_CH2    (STM32H5_IRQ_FIRST + 92)  /* 90:  SAI1 global interrupt */
#define STM32H5_IRQ_GPDMA2_CH3    (STM32H5_IRQ_FIRST + 93)  /* 90:  SAI1 global interrupt */
#define STM32H5_IRQ_GPDMA2_CH4    (STM32H5_IRQ_FIRST + 94)  /* 90:  SAI1 global interrupt */
#define STM32H5_IRQ_GPDMA2_CH5    (STM32H5_IRQ_FIRST + 95)  /* 90:  SAI1 global interrupt */
#define STM32H5_IRQ_GPDMA2_CH6    (STM32H5_IRQ_FIRST + 96)  /* 90:  SAI1 global interrupt */
#define STM32H5_IRQ_GPDMA2_CH7    (STM32H5_IRQ_FIRST + 97)  /* 90:  SAI1 global interrupt */
                                                            /* 98:  Reserved */
                                                            /* 99:  Reserved */
                                                            /* 100: Reserved */
                                                            /* 101: Reserved */
                                                            /* 102: Reserved */
#define STM32H5_IRQ_FPU           (STM32H5_IRQ_FIRST + 103) /* 103: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_ICACHE        (STM32H5_IRQ_FIRST + 104) /* 104: DFSDM1 filter 2 global interrupt */
#define STM32H5_IRQ_DCACHE        (STM32H5_IRQ_FIRST + 105) /* 105: DFSDM1 filter 3 global interrupt */
                                                            /* 106: Reserved */
                                                            /* 107: Reserved */
#define STM32H5_IRQ_DCMI_PSSI     (STM32H5_IRQ_FIRST + 108) /* 108: OTFDEC1 global interrupt */
#define STM32H5_IRQ_FDCAN2_IT0    (STM32H5_IRQ_FIRST + 109) /* 109: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_FDCAN2_IT1    (STM32H5_IRQ_FIRST + 110) /* 110: DFSDM1 filter 1 global interrupt */
                                                            /* 111: Reserved */
                                                            /* 112: Reserved */
#define STM32H5_IRQ_DTS           (STM32H5_IRQ_FIRST + 113) /* 113: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_RNG           (STM32H5_IRQ_FIRST + 114) /* 114: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_OTFDEC1       (STM32H5_IRQ_FIRST + 115) /* 115: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_AES           (STM32H5_IRQ_FIRST + 116) /* 116: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_HASH          (STM32H5_IRQ_FIRST + 117  /* 117: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_PKA           (STM32H5_IRQ_FIRST + 118) /* 118: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_CEC           (STM32H5_IRQ_FIRST + 119) /* 119: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_TIM12         (STM32H5_IRQ_FIRST + 120) /* 120: DFSDM1 filter 1 global interrupt */
                                                            /* 121: Reserved */
                                                            /* 122: Reserved */
#define STM32H5_IRQ_I3C1_EV       (STM32H5_IRQ_FIRST + 123) /* 123: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_I3C_ER        (STM32H5_IRQ_FIRST + 124) /* 124: DFSDM1 filter 1 global interrupt */
                                                            /* 125: Reserved */
                                                            /* 126: Reserved */
                                                            /* 127: Reserved */
                                                            /* 128: Reserved */
                                                            /* 129: Reserved */
                                                            /* 130: Reserved */
#define STM32H5_IRQ_I3C2_EV       (STM32H5_IRQ_FIRST + 131) /* 131: DFSDM1 filter 1 global interrupt */
#define STM32H5_IRQ_I3C2_ER       (STM32H5_IRQ_FIRST + 132) /* 132: DFSDM1 filter 1 global interrupt */

#if defined(CONFIG_STM32H5_STM32H562XX)
#  define STM32H5_IRQ_NEXTINTS  133
#else
#  error "Unsupported STM32H5 chip"
#endif

/* (EXTI interrupts do not use IRQ numbers) */

#define NR_IRQS                 (STM32H5_IRQ_FIRST + STM32H5_IRQ_NEXTINTS)

#endif /* __ARCH_ARM_INCLUDE_STM32H5_STM32H562XX_IRQ_H */
