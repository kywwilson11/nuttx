# ##############################################################################
# boards/arm/stm32/stm32f401rc-rs485/src/CMakeLists.txt
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

set(SRCS stm32_boot.c stm32_bringup.c)

if(CONFIG_ARCH_LEDS)
  list(APPEND SRCS stm32_autoleds.c)
endif()

if(CONFIG_USERLED)
  list(APPEND SRCS stm32_userleds.c)
endif()

if(CONFIG_BOARDCTL)
  list(APPEND SRCS stm32_appinit.c)
  if(CONFIG_BOARDCTL_RESET)
    list(APPEND SRCS stm32_reset.c)
  endif()
endif()

if(CONFIG_ARCH_BUTTONS)
  list(APPEND SRCS stm32_buttons.c)
endif()

if(CONFIG_ADC)
  list(APPEND SRCS stm32_adc.c)
endif()

if(CONFIG_STM32_SDIO)
  list(APPEND SRCS stm32_sdio.c)
endif()

if(CONFIG_STM32_OTGFS)
  list(APPEND SRCS stm32_usb.c)
endif()

if(CONFIG_STM32_CONFIG_I2C_EE_24XXEEPROM)
  list(APPEND SRCS stm32_at24.c)
endif()

if(CONFIG_STM32_PWM)
  list(APPEND SRCS stm32_pwm.c)
endif()

if(CONFIG_USBMSC)
  list(APPEND SRCS stm32_usbmsc.c)
endif()

if(CONFIG_DEV_GPIO)
  list(APPEND SRCS stm32_gpio.c)
endif()

if(CONFIG_VIDEO_FB)
  if(CONFIG_LCD_SSD1306)
    list(APPEND SRCS stm32_lcd_ssd1306.c)
  endif()
  if(CONFIG_LCD_ST7735)
    list(APPEND SRCS stm32_lcd_st7735.c)
  endif()
endif()

if(CONFIG_ADC_HX711)
  list(APPEND SRCS stm32_hx711.c)
endif()

target_sources(board PRIVATE ${SRCS})

if(CONFIG_ARCH_CHIP_STM32F401RC)
  set_property(GLOBAL PROPERTY LD_SCRIPT "${NUTTX_BOARD_DIR}/scripts/ld.script")
endif()
