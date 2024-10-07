/****************************************************************************
 * arch/arm/src/stm32h7/hardware/stm32_fdcan.h
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

#ifndef __ARCH_ARM_SRC_STM32H7_HARDWARE_STM32_FDCAN_H
#define __ARCH_ARM_SRC_STM32H7_HARDWARE_STM32_FDCAN_H

/* **************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "chip.h"

/* **************************************************************************
 *                                                                          *
 *                Flexible Datarate Controller Area Network                 *
 *                                                                          *
 ****************************************************************************/

/* Register Offsets *********************************************************/

#define STM32_FDCAN_CREL_OFFSET       0x0000  /* FDCAN Core Release register */
#define STM32_FDCAN_ENDN_OFFSET       0x0004  /* FDCAN Endian register */
#define STM32_FDCAN_DBTP_OFFSET       0x000C  /* FDCAN Data Bit Timing & Prescaler register */
#define STM32_FDCAN_TEST_OFFSET       0x0010  /* FDCAN Test register */
#define STM32_FDCAN_RWD_OFFSET        0x0014  /* FDCAN RAM Watchdog register */
#define STM32_FDCAN_CCCR_OFFSET       0x0018  /* FDCAN CC Control register */
#define STM32_FDCAN_NBTP_OFFSET       0x001C  /* FDCAN Nominal Bit Timing & Prescaler register */
#define STM32_FDCAN_TSCC_OFFSET       0x0020  /* FDCAN Timestamp Counter Configuration register */
#define STM32_FDCAN_TSCV_OFFSET       0x0024  /* FDCAN Timestamp Counter Value register */
#define STM32_FDCAN_TOCC_OFFSET       0x0028  /* FDCAN Timeout Counter Configuration register */
#define STM32_FDCAN_TOCV_OFFSET       0x002C  /* FDCAN Timeout Counter Value register */
#define STM32_FDCAN_ECR_OFFSET        0x0040  /* FDCAN Error Counter register */
#define STM32_FDCAN_PSR_OFFSET        0x0044  /* FDCAN Protocol Status register */
#define STM32_FDCAN_TDCR_OFFSET       0x0048  /* FDCAN Transmitter Delay Compensation register */
#define STM32_FDCAN_IR_OFFSET         0x0050  /* FDCAN Interrupt register */
#define STM32_FDCAN_IE_OFFSET         0x0054  /* FDCAN Interrupt Enable register */
#define STM32_FDCAN_ILS_OFFSET        0x0058  /* FDCAN Interrupt Line Select register */
#define STM32_FDCAN_ILE_OFFSET        0x005C  /* FDCAN Interrupt Line Enable register */
#define STM32_FDCAN_RXGFC_OFFSET      0x0080  /* FDCAN Global Filter Configuration register */
#define STM32_FDCAN_XIDAM_OFFSET      0x0084  /* FDCAN Extended ID AND Mask register */
#define STM32_FDCAN_HPMS_OFFSET       0x0088  /* FDCAN High Priority Message Status register */
#define STM32_FDCAN_RXF0S_OFFSET      0x0090  /* FDCAN Rx FIFO 0 Status register */
#define STM32_FDCAN_RXF0A_OFFSET      0x0094  /* FDCAN Rx FIFO 0 Acknowledge register */
#define STM32_FDCAN_RXF1S_OFFSET      0x0098  /* FDCAN Rx FIFO 1 Status register */
#define STM32_FDCAN_RXF1A_OFFSET      0x009C  /* FDCAN Rx FIFO 1 Acknowledge register */
#define STM32_FDCAN_TXBC_OFFSET       0x00C0  /* FDCAN Tx Buffer Configuration register */
#define STM32_FDCAN_TXFQS_OFFSET      0x00C4  /* FDCAN Tx FIFO/Queue Status register */
#define STM32_FDCAN_TXBRP_OFFSET      0x00C8  /* FDCAN Tx Buffer Request Pending register */
#define STM32_FDCAN_TXBAR_OFFSET      0x00CC  /* FDCAN Tx Buffer Add Request register */
#define STM32_FDCAN_TXBCR_OFFSET      0x00D0  /* FDCAN Tx Buffer Cancellation Request register */
#define STM32_FDCAN_TXBTO_OFFSET      0x00D4  /* FDCAN Tx Buffer Transmission Occurred register */
#define STM32_FDCAN_TXBCF_OFFSET      0x00D8  /* FDCAN Tx Buffer Cancellation Finished register */
#define STM32_FDCAN_TXBTIE_OFFSET     0x00DC  /* FDCAN Tx Buffer Transmission Interrupt Enable register */
#define STM32_FDCAN_TXBCIE_OFFSET     0x00E0  /* FDCAN Tx Buffer Cancellation Finished Interrupt Enable register */
#define STM32_FDCAN_TXEFS_OFFSET      0x00E4  /* FDCAN Tx Event FIFO Status register */
#define STM32_FDCAN_TXEFA_OFFSET      0x00E8  /* FDCAN Tx Event FIFO Acknowledge register */
#define STM32_FDCAN_CKDIV_OFFSET     0x0100  /* FDCAN Global Filter Configuration register */

/* Register Addresses *******************************************************/

#define STM32_FDCAN1_CREL       (STM32_FDCAN1_BASE + STM32_FDCAN_CREL_OFFSET)
#define STM32_FDCAN1_ENDN       (STM32_FDCAN1_BASE + STM32_FDCAN_ENDN_OFFSET)
#define STM32_FDCAN1_DBTP       (STM32_FDCAN1_BASE + STM32_FDCAN_DBTP_OFFSET)
#define STM32_FDCAN1_TEST       (STM32_FDCAN1_BASE + STM32_FDCAN_TEST_OFFSET)
#define STM32_FDCAN1_RWD        (STM32_FDCAN1_BASE + STM32_FDCAN_RWD_OFFSET)
#define STM32_FDCAN1_CCCR       (STM32_FDCAN1_BASE + STM32_FDCAN_CCCR_OFFSET)
#define STM32_FDCAN1_NBTP       (STM32_FDCAN1_BASE + STM32_FDCAN_NBTP_OFFSET)
#define STM32_FDCAN1_TSCC       (STM32_FDCAN1_BASE + STM32_FDCAN_TSCC_OFFSET)
#define STM32_FDCAN1_TSCV       (STM32_FDCAN1_BASE + STM32_FDCAN_TSCV_OFFSET)
#define STM32_FDCAN1_TOCC       (STM32_FDCAN1_BASE + STM32_FDCAN_TOCC_OFFSET)
#define STM32_FDCAN1_TOCV       (STM32_FDCAN1_BASE + STM32_FDCAN_TOCV_OFFSET)
#define STM32_FDCAN1_ECR        (STM32_FDCAN1_BASE + STM32_FDCAN_ECR_OFFSET)
#define STM32_FDCAN1_PSR        (STM32_FDCAN1_BASE + STM32_FDCAN_PSR_OFFSET)
#define STM32_FDCAN1_TDCR       (STM32_FDCAN1_BASE + STM32_FDCAN_TDCR_OFFSET)
#define STM32_FDCAN1_IR         (STM32_FDCAN1_BASE + STM32_FDCAN_IR_OFFSET)
#define STM32_FDCAN1_IE         (STM32_FDCAN1_BASE + STM32_FDCAN_IE_OFFSET)
#define STM32_FDCAN1_ILS        (STM32_FDCAN1_BASE + STM32_FDCAN_ILS_OFFSET)
#define STM32_FDCAN1_ILE        (STM32_FDCAN1_BASE + STM32_FDCAN_ILE_OFFSET)
#define STM32_FDCAN1_RXGFC      (STM32_FDCAN1_BASE + STM32_FDCAN_RXGFC_OFFSET)
#define STM32_FDCAN1_XIDAM      (STM32_FDCAN1_BASE + STM32_FDCAN_XIDAM_OFFSET)
#define STM32_FDCAN1_HPMS       (STM32_FDCAN1_BASE + STM32_FDCAN_HPMS_OFFSET)
#define STM32_FDCAN1_RXF0S      (STM32_FDCAN1_BASE + STM32_FDCAN_RXF0S_OFFSET)
#define STM32_FDCAN1_RXF0A      (STM32_FDCAN1_BASE + STM32_FDCAN_RXF0A_OFFSET)
#define STM32_FDCAN1_RXF1S      (STM32_FDCAN1_BASE + STM32_FDCAN_RXF1S_OFFSET)
#define STM32_FDCAN1_RXF1A      (STM32_FDCAN1_BASE + STM32_FDCAN_RXF1A_OFFSET)
#define STM32_FDCAN1_TXBC       (STM32_FDCAN1_BASE + STM32_FDCAN_TXBC_OFFSET)
#define STM32_FDCAN1_TXFQS      (STM32_FDCAN1_BASE + STM32_FDCAN_TXFQS_OFFSET)
#define STM32_FDCAN1_TXBRP      (STM32_FDCAN1_BASE + STM32_FDCAN_TXBRP_OFFSET)
#define STM32_FDCAN1_TXBAR      (STM32_FDCAN1_BASE + STM32_FDCAN_TXBAR_OFFSET)
#define STM32_FDCAN1_TXBCR      (STM32_FDCAN1_BASE + STM32_FDCAN_TXBCR_OFFSET)
#define STM32_FDCAN1_TXBTO      (STM32_FDCAN1_BASE + STM32_FDCAN_TXBTO_OFFSET)
#define STM32_FDCAN1_TXBCF      (STM32_FDCAN1_BASE + STM32_FDCAN_TXBCF_OFFSET)
#define STM32_FDCAN1_TXBTIE     (STM32_FDCAN1_BASE + STM32_FDCAN_TXBTIE_OFFSET)
#define STM32_FDCAN1_TXBCIE     (STM32_FDCAN1_BASE + STM32_FDCAN_TXBCIE_OFFSET)
#define STM32_FDCAN1_TXEFS      (STM32_FDCAN1_BASE + STM32_FDCAN_TXEFS_OFFSET)
#define STM32_FDCAN1_TXEFA      (STM32_FDCAN1_BASE + STM32_FDCAN_TXEFA_OFFSET)

#define STM32_FDCAN2_CREL       (STM32_FDCAN2_BASE + STM32_FDCAN_CREL_OFFSET)
#define STM32_FDCAN2_ENDN       (STM32_FDCAN2_BASE + STM32_FDCAN_ENDN_OFFSET)
#define STM32_FDCAN2_DBTP       (STM32_FDCAN2_BASE + STM32_FDCAN_DBTP_OFFSET)
#define STM32_FDCAN2_TEST       (STM32_FDCAN2_BASE + STM32_FDCAN_TEST_OFFSET)
#define STM32_FDCAN2_RWD        (STM32_FDCAN2_BASE + STM32_FDCAN_RWD_OFFSET)
#define STM32_FDCAN2_CCCR       (STM32_FDCAN2_BASE + STM32_FDCAN_CCCR_OFFSET)
#define STM32_FDCAN2_NBTP       (STM32_FDCAN2_BASE + STM32_FDCAN_NBTP_OFFSET)
#define STM32_FDCAN2_TSCC       (STM32_FDCAN2_BASE + STM32_FDCAN_TSCC_OFFSET)
#define STM32_FDCAN2_TSCV       (STM32_FDCAN2_BASE + STM32_FDCAN_TSCV_OFFSET)
#define STM32_FDCAN2_TOCC       (STM32_FDCAN2_BASE + STM32_FDCAN_TOCC_OFFSET)
#define STM32_FDCAN2_TOCV       (STM32_FDCAN2_BASE + STM32_FDCAN_TOCV_OFFSET)
#define STM32_FDCAN2_ECR        (STM32_FDCAN2_BASE + STM32_FDCAN_ECR_OFFSET)
#define STM32_FDCAN2_PSR        (STM32_FDCAN2_BASE + STM32_FDCAN_PSR_OFFSET)
#define STM32_FDCAN2_TDCR       (STM32_FDCAN2_BASE + STM32_FDCAN_TDCR_OFFSET)
#define STM32_FDCAN2_IR         (STM32_FDCAN2_BASE + STM32_FDCAN_IR_OFFSET)
#define STM32_FDCAN2_IE         (STM32_FDCAN2_BASE + STM32_FDCAN_IE_OFFSET)
#define STM32_FDCAN2_ILS        (STM32_FDCAN2_BASE + STM32_FDCAN_ILS_OFFSET)
#define STM32_FDCAN2_ILE        (STM32_FDCAN2_BASE + STM32_FDCAN_ILE_OFFSET)
#define STM32_FDCAN2_RXGFC      (STM32_FDCAN2_BASE + STM32_FDCAN_RXGFC_OFFSET)
#define STM32_FDCAN2_SIDFC      (STM32_FDCAN2_BASE + STM32_FDCAN_SIDFC_OFFSET)
#define STM32_FDCAN2_XIDFC      (STM32_FDCAN2_BASE + STM32_FDCAN_XIDFC_OFFSET)
#define STM32_FDCAN2_XIDAM      (STM32_FDCAN2_BASE + STM32_FDCAN_XIDAM_OFFSET)
#define STM32_FDCAN2_HPMS       (STM32_FDCAN2_BASE + STM32_FDCAN_HPMS_OFFSET)
#define STM32_FDCAN2_RXF0S      (STM32_FDCAN2_BASE + STM32_FDCAN_RXF0S_OFFSET)
#define STM32_FDCAN2_RXF0A      (STM32_FDCAN2_BASE + STM32_FDCAN_RXF0A_OFFSET)
#define STM32_FDCAN2_RXF1S      (STM32_FDCAN2_BASE + STM32_FDCAN_RXF1S_OFFSET)
#define STM32_FDCAN2_RXF1A      (STM32_FDCAN2_BASE + STM32_FDCAN_RXF1A_OFFSET)
#define STM32_FDCAN2_TXBC       (STM32_FDCAN2_BASE + STM32_FDCAN_TXBC_OFFSET)
#define STM32_FDCAN2_TXFQS      (STM32_FDCAN2_BASE + STM32_FDCAN_TXFQS_OFFSET)
#define STM32_FDCAN2_TXBRP      (STM32_FDCAN2_BASE + STM32_FDCAN_TXBRP_OFFSET)
#define STM32_FDCAN2_TXBAR      (STM32_FDCAN2_BASE + STM32_FDCAN_TXBAR_OFFSET)
#define STM32_FDCAN2_TXBCR      (STM32_FDCAN2_BASE + STM32_FDCAN_TXBCR_OFFSET)
#define STM32_FDCAN2_TXBTO      (STM32_FDCAN2_BASE + STM32_FDCAN_TXBTO_OFFSET)
#define STM32_FDCAN2_TXBCF      (STM32_FDCAN2_BASE + STM32_FDCAN_TXBCF_OFFSET)
#define STM32_FDCAN2_TXBTIE     (STM32_FDCAN2_BASE + STM32_FDCAN_TXBTIE_OFFSET)
#define STM32_FDCAN2_TXBCIE     (STM32_FDCAN2_BASE + STM32_FDCAN_TXBCIE_OFFSET)
#define STM32_FDCAN2_TXEFS      (STM32_FDCAN2_BASE + STM32_FDCAN_TXEFS_OFFSET)
#define STM32_FDCAN2_TXEFA      (STM32_FDCAN2_BASE + STM32_FDCAN_TXEFA_OFFSET)

/* FDCAN control and status registers */
#define FDCAN_CREL_DAY_SHIFT      (0U)
#define FDCAN_CREL_DAY_MASK       (0xFFU << FDCAN_CREL_DAY_SHIFT)               /* 0x000000FF */
#define FDCAN_CREL_DAY            FDCAN_CREL_DAY_MASK                           /* Timestamp Day                           */
#define FDCAN_CREL_MON_SHIFT      (8U)
#define FDCAN_CREL_MON_MASK       (0xFFU << FDCAN_CREL_MON_SHIFT)               /* 0x0000FF00 */
#define FDCAN_CREL_MON            FDCAN_CREL_MON_MASK                           /* Timestamp Month                         */
#define FDCAN_CREL_YEAR_SHIFT     (16U)
#define FDCAN_CREL_YEAR_MASK      (0xFU << FDCAN_CREL_YEAR_SHIFT)               /* 0x000F0000 */
#define FDCAN_CREL_YEAR           FDCAN_CREL_YEAR_MASK                          /* Timestamp Year                          */
#define FDCAN_CREL_SUBSTEP_SHIFT  (20U)
#define FDCAN_CREL_SUBSTEP_MASK   (0xFU << FDCAN_CREL_SUBSTEP_SHIFT)            /* 0x00F00000 */
#define FDCAN_CREL_SUBSTEP        FDCAN_CREL_SUBSTEP_MASK                       /* Sub-step of Core release                */
#define FDCAN_CREL_STEP_SHIFT     (24U)
#define FDCAN_CREL_STEP_MASK      (0xFU << FDCAN_CREL_STEP_SHIFT)               /* 0x0F000000 */
#define FDCAN_CREL_STEP           FDCAN_CREL_STEP_MASK                          /* Step of Core release                    */
#define FDCAN_CREL_REL_SHIFT      (28U)
#define FDCAN_CREL_REL_MASK       (0xFU << FDCAN_CREL_REL_SHIFT)                /* 0xF0000000 */
#define FDCAN_CREL_REL            FDCAN_CREL_REL_MASK                           /* Core release                            */

/* ***************  Bit definition for FDCAN_ENDN register  *****************/
#define FDCAN_ENDN_ETV_SHIFT      (0U)
#define FDCAN_ENDN_ETV_MASK       (0xFFFFFFFFU << FDCAN_ENDN_ETV_SHIFT)         /* 0xFFFFFFFF */
#define FDCAN_ENDN_ETV            FDCAN_ENDN_ETV_MASK                           /* Endiannes Test Value                    */

/* ***************  Bit definition for FDCAN_DBTP register  *****************/
#define FDCAN_DBTP_DSJW_SHIFT     (0U)
#define FDCAN_DBTP_DSJW_MASK      (0xFU << FDCAN_DBTP_DSJW_SHIFT)               /* 0x0000000F */
#define FDCAN_DBTP_DSJW           FDCAN_DBTP_DSJW_MASK                          /* Synchronization Jump Width              */
#define FDCAN_DBTP_DTSEG2_SHIFT   (4U)
#define FDCAN_DBTP_DTSEG2_MASK    (0xFU << FDCAN_DBTP_DTSEG2_SHIFT)             /* 0x000000F0 */
#define FDCAN_DBTP_DTSEG2         FDCAN_DBTP_DTSEG2_MASK                        /* Data time segment after sample point    */
#define FDCAN_DBTP_DTSEG1_SHIFT   (8U)
#define FDCAN_DBTP_DTSEG1_MASK    (0xFU << FDCAN_DBTP_DTSEG1_SHIFT)             /* 0x00000F00 */
#define FDCAN_DBTP_DTSEG1         FDCAN_DBTP_DTSEG1_MASK                        /* Data time segment before sample point   */
#define FDCAN_DBTP_DBRP_SHIFT     (16U)
#define FDCAN_DBTP_DBRP_MASK      (0x1FU << FDCAN_DBTP_DBRP_SHIFT)              /* 0x001F0000 */
#define FDCAN_DBTP_DBRP           FDCAN_DBTP_DBRP_MASK                          /* Data BIt Rate Prescaler                 */
#define FDCAN_DBTP_TDC_SHIFT      (23U)
#define FDCAN_DBTP_TDC_MASK       (0x1U << FDCAN_DBTP_TDC_SHIFT)                /* 0x00800000 */
#define FDCAN_DBTP_TDC            FDCAN_DBTP_TDC_MASK                           /* Transceiver Delay Compensation          */

/* ***************  Bit definition for FDCAN_TEST register  *****************/
#define FDCAN_TEST_LBCK_SHIFT     (4U)
#define FDCAN_TEST_LBCK_MASK      (0x1U << FDCAN_TEST_LBCK_SHIFT)               /* 0x00000010 */
#define FDCAN_TEST_LBCK           FDCAN_TEST_LBCK_MASK                          /* Loop Back mode                           */
#define FDCAN_TEST_TX_SHIFT       (5U)
#define FDCAN_TEST_TX_MASK        (0x3U << FDCAN_TEST_TX_SHIFT)                 /* 0x00000060 */
#define FDCAN_TEST_TX             FDCAN_TEST_TX_MASK                            /* Control of Transmit Pin                  */
#define FDCAN_TEST_RX_SHIFT       (7U)
#define FDCAN_TEST_RX_MASK        (0x1U << FDCAN_TEST_RX_SHIFT)                 /* 0x00000080 */
#define FDCAN_TEST_RX             FDCAN_TEST_RX_MASK                            /* Receive Pin                              */

/* ***************  Bit definition for FDCAN_RWD register  ******************/
#define FDCAN_RWD_WDC_SHIFT       (0U)
#define FDCAN_RWD_WDC_MASK        (0xFU << FDCAN_RWD_WDC_SHIFT)                 /* 0x0000000F */
#define FDCAN_RWD_WDC             FDCAN_RWD_WDC_MASK                            /* Watchdog configuration                   */
#define FDCAN_RWD_WDV_SHIFT       (4U)
#define FDCAN_RWD_WDV_MASK        (0xFU << FDCAN_RWD_WDV_SHIFT)                 /* 0x000000F0 */
#define FDCAN_RWD_WDV             FDCAN_RWD_WDV_MASK                            /* Watchdog value                           */

/* ***************  Bit definition for FDCAN_CCCR register  *****************/
#define FDCAN_CCCR_INIT_SHIFT     (0U)
#define FDCAN_CCCR_INIT_MASK      (0x1U << FDCAN_CCCR_INIT_SHIFT)               /* 0x00000001 */
#define FDCAN_CCCR_INIT           FDCAN_CCCR_INIT_MASK                          /* Initialization                           */
#define FDCAN_CCCR_CCE_SHIFT      (1U)
#define FDCAN_CCCR_CCE_MASK       (0x1U << FDCAN_CCCR_CCE_SHIFT)                /* 0x00000002 */
#define FDCAN_CCCR_CCE            FDCAN_CCCR_CCE_MASK                           /* Configuration Change Enable              */
#define FDCAN_CCCR_ASM_SHIFT      (2U)
#define FDCAN_CCCR_ASM_MASK       (0x1U << FDCAN_CCCR_ASM_SHIFT)                /* 0x00000004 */
#define FDCAN_CCCR_ASM            FDCAN_CCCR_ASM_MASK                           /* ASM Restricted Operation Mode            */
#define FDCAN_CCCR_CSA_SHIFT      (3U)
#define FDCAN_CCCR_CSA_MASK       (0x1U << FDCAN_CCCR_CSA_SHIFT)                /* 0x00000008 */
#define FDCAN_CCCR_CSA            FDCAN_CCCR_CSA_MASK                           /* Clock Stop Acknowledge                   */
#define FDCAN_CCCR_CSR_SHIFT      (4U)
#define FDCAN_CCCR_CSR_MASK       (0x1U << FDCAN_CCCR_CSR_SHIFT)                /* 0x00000010 */
#define FDCAN_CCCR_CSR            FDCAN_CCCR_CSR_MASK                           /* Clock Stop Request                       */
#define FDCAN_CCCR_MON_SHIFT      (5U)
#define FDCAN_CCCR_MON_MASK       (0x1U << FDCAN_CCCR_MON_SHIFT)                /* 0x00000020 */
#define FDCAN_CCCR_MON            FDCAN_CCCR_MON_MASK                           /* Bus Monitoring Mode                      */
#define FDCAN_CCCR_DAR_SHIFT      (6U)
#define FDCAN_CCCR_DAR_MASK       (0x1U << FDCAN_CCCR_DAR_SHIFT)                /* 0x00000040 */
#define FDCAN_CCCR_DAR            FDCAN_CCCR_DAR_MASK                           /* Disable Automatic Retransmission         */
#define FDCAN_CCCR_TEST_SHIFT     (7U)
#define FDCAN_CCCR_TEST_MASK      (0x1U << FDCAN_CCCR_TEST_SHIFT)               /* 0x00000080 */
#define FDCAN_CCCR_TEST           FDCAN_CCCR_TEST_MASK                          /* Test Mode Enable                         */
#define FDCAN_CCCR_FDOE_SHIFT     (8U)
#define FDCAN_CCCR_FDOE_MASK      (0x1U << FDCAN_CCCR_FDOE_SHIFT)               /* 0x00000100 */
#define FDCAN_CCCR_FDOE           FDCAN_CCCR_FDOE_MASK                          /* FD Operation Enable                      */
#define FDCAN_CCCR_BRSE_SHIFT     (9U)
#define FDCAN_CCCR_BRSE_MASK      (0x1U << FDCAN_CCCR_BRSE_SHIFT)               /* 0x00000200 */
#define FDCAN_CCCR_BRSE           FDCAN_CCCR_BRSE_MASK                          /* FDCAN Bit Rate Switching                 */
#define FDCAN_CCCR_PXHD_SHIFT     (12U)
#define FDCAN_CCCR_PXHD_MASK      (0x1U << FDCAN_CCCR_PXHD_SHIFT)               /* 0x00001000 */
#define FDCAN_CCCR_PXHD           FDCAN_CCCR_PXHD_MASK                          /* Protocol Exception Handling Disable      */
#define FDCAN_CCCR_EFBI_SHIFT     (13U)
#define FDCAN_CCCR_EFBI_MASK      (0x1U << FDCAN_CCCR_EFBI_SHIFT)               /* 0x00002000 */
#define FDCAN_CCCR_EFBI           FDCAN_CCCR_EFBI_MASK                          /* Edge Filtering during Bus Integration    */
#define FDCAN_CCCR_TXP_SHIFT      (14U)
#define FDCAN_CCCR_TXP_MASK       (0x1U << FDCAN_CCCR_TXP_SHIFT)                /* 0x00004000 */
#define FDCAN_CCCR_TXP            FDCAN_CCCR_TXP_MASK                           /* Two CAN bit times Pause                  */
#define FDCAN_CCCR_NISO_SHIFT     (15U)
#define FDCAN_CCCR_NISO_MASK      (0x1U << FDCAN_CCCR_NISO_SHIFT)               /* 0x00008000 */
#define FDCAN_CCCR_NISO           FDCAN_CCCR_NISO_MASK                          /* Non ISO Operation                        */

/* ***************  Bit definition for FDCAN_NBTP register  *****************/
#define FDCAN_NBTP_TSEG2_SHIFT    (0U)
#define FDCAN_NBTP_TSEG2_MASK     (0x7FU << FDCAN_NBTP_TSEG2_SHIFT)             /* 0x0000007F */
#define FDCAN_NBTP_TSEG2          FDCAN_NBTP_TSEG2_MASK                         /* Nominal Time segment after sample point  */
#define FDCAN_NBTP_NTSEG1_SHIFT   (8U)
#define FDCAN_NBTP_NTSEG1_MASK    (0xFFU << FDCAN_NBTP_NTSEG1_SHIFT)            /* 0x0000FF00 */
#define FDCAN_NBTP_NTSEG1         FDCAN_NBTP_NTSEG1_MASK                        /* Nominal Time segment before sample point */
#define FDCAN_NBTP_NBRP_SHIFT     (16U)
#define FDCAN_NBTP_NBRP_MASK      (0x1FFU << FDCAN_NBTP_NBRP_SHIFT)             /* 0x01FF0000 */
#define FDCAN_NBTP_NBRP           FDCAN_NBTP_NBRP_MASK                          /* Bit Rate Prescaler                       */
#define FDCAN_NBTP_NSJW_SHIFT     (25U)
#define FDCAN_NBTP_NSJW_MASK      (0x7FU << FDCAN_NBTP_NSJW_SHIFT)              /* 0xFE000000 */
#define FDCAN_NBTP_NSJW           FDCAN_NBTP_NSJW_MASK                          /* Nominal (Re)Synchronization Jump Width   */

/* ***************  Bit definition for FDCAN_TSCC register  *****************/
#define FDCAN_TSCC_TSS_SHIFT      (0U)
#define FDCAN_TSCC_TSS_MASK       (0x3U << FDCAN_TSCC_TSS_SHIFT)                /* 0x00000003 */
#define FDCAN_TSCC_TSS            FDCAN_TSCC_TSS_MASK                           /* Timestamp Select                         */
#define FDCAN_TSCC_TCP_SHIFT      (16U)
#define FDCAN_TSCC_TCP_MASK       (0xFU << FDCAN_TSCC_TCP_SHIFT)                /* 0x000F0000 */
#define FDCAN_TSCC_TCP            FDCAN_TSCC_TCP_MASK                           /* Timestamp Counter Prescaler              */

/* ***************  Bit definition for FDCAN_TSCV register  *****************/
#define FDCAN_TSCV_TSC_SHIFT      (0U)
#define FDCAN_TSCV_TSC_MASK       (0xFFFFU << FDCAN_TSCV_TSC_SHIFT)             /* 0x0000FFFF */
#define FDCAN_TSCV_TSC            FDCAN_TSCV_TSC_MASK                           /* Timestamp Counter                        */

/* ***************  Bit definition for FDCAN_TOCC register  *****************/
#define FDCAN_TOCC_ETOC_SHIFT     (0U)
#define FDCAN_TOCC_ETOC_MASK      (0x1U << FDCAN_TOCC_ETOC_SHIFT)               /* 0x00000001 */
#define FDCAN_TOCC_ETOC           FDCAN_TOCC_ETOC_MASK                          /* Enable Timeout Counter                   */
#define FDCAN_TOCC_TOS_SHIFT      (1U)
#define FDCAN_TOCC_TOS_MASK       (0x3U << FDCAN_TOCC_TOS_SHIFT)                /* 0x00000006 */
#define FDCAN_TOCC_TOS            FDCAN_TOCC_TOS_MASK                           /* Timeout Select                           */
#define FDCAN_TOCC_TOP_SHIFT      (16U)
#define FDCAN_TOCC_TOP_MASK       (0xFFFFU << FDCAN_TOCC_TOP_SHIFT)             /* 0xFFFF0000 */
#define FDCAN_TOCC_TOP            FDCAN_TOCC_TOP_MASK                           /* Timeout Period                           */

/* ***************  Bit definition for FDCAN_TOCV register  *****************/
#define FDCAN_TOCV_TOC_SHIFT      (0U)
#define FDCAN_TOCV_TOC_MASK       (0xFFFFU << FDCAN_TOCV_TOC_SHIFT)             /* 0x0000FFFF */
#define FDCAN_TOCV_TOC            FDCAN_TOCV_TOC_MASK                           /* Timeout Counter                          */

/* ***************  Bit definition for FDCAN_ECR register  ******************/
#define FDCAN_ECR_TEC_SHIFT       (0U)
#define FDCAN_ECR_TEC_MASK        (0xFFU << FDCAN_ECR_TEC_SHIFT)                /* 0x0000000FF */
#define FDCAN_ECR_TEC             FDCAN_ECR_TEC_MASK                            /* Transmit Error Counter                   */
#define FDCAN_ECR_TREC_SHIFT      (8U)
#define FDCAN_ECR_TREC_MASK       (0x7FU << FDCAN_ECR_TREC_SHIFT)               /* 0x00007F00 */
#define FDCAN_ECR_TREC            FDCAN_ECR_TREC_MASK                           /* Receive Error Counter                    */
#define FDCAN_ECR_RP_SHIFT        (15U)
#define FDCAN_ECR_RP_MASK         (0x1U << FDCAN_ECR_RP_SHIFT)                  /* 0x00008000 */
#define FDCAN_ECR_RP              FDCAN_ECR_RP_MASK                             /* Receive Error Passive                    */
#define FDCAN_ECR_CEL_SHIFT       (16U)
#define FDCAN_ECR_CEL_MASK        (0xFFU << FDCAN_ECR_CEL_SHIFT)                /* 0x00FF0000 */
#define FDCAN_ECR_CEL             FDCAN_ECR_CEL_MASK                            /* CAN Error Logging                        */

/* Error codes */

#define FDCAN_PSR_EC_NO_ERROR       (0)                                    /* No error occurred since LEC has been reset */
#define FDCAN_PSR_EC_STUFF_ERROR    (1)                                    /* More than 5 equal bits in a sequence */
#define FDCAN_PSR_EC_FORM_ERROR     (2)                                    /* Part of a received frame has wrong format */
#define FDCAN_PSR_EC_ACK_ERROR      (3)                                    /* Message not acknowledged by another node */
#define FDCAN_PSR_EC_BIT1_ERROR     (4)                                    /* Send with recessive level, but bus value was dominant */
#define FDCAN_PSR_EC_BIT0_ERROR     (5)                                    /* Send with dominant level, but bus value was recessive */
#define FDCAN_PSR_EC_CRC_ERROR      (6)                                    /* CRC received message incorrect */
#define FDCAN_PSR_EC_NO_CHANGE      (7)                                    /* No CAN bus event was detected since last read */

/* ***************  Bit definition for FDCAN_PSR register  ******************/
#define FDCAN_PSR_LEC_SHIFT       (0U)
#define FDCAN_PSR_LEC_MASK        (0x7U << FDCAN_PSR_LEC_SHIFT)                 /* 0x00000007 */
#define FDCAN_PSR_LEC(n)          ((uint32_t)(n) << FDCAN_PSR_LEC_SHIFT)        /* See error codes above */
#define FDCAN_PSR_ACT_SHIFT       (3U)
#define FDCAN_PSR_ACT_MASK        (0x3U << FDCAN_PSR_ACT_SHIFT)                 /* 0x00000018 */
#define FDCAN_PSR_ACT             FDCAN_PSR_ACT_MASK                            /* Activity                                 */
#define FDCAN_PSR_EP_SHIFT        (5U)
#define FDCAN_PSR_EP_MASK         (0x1U << FDCAN_PSR_EP_SHIFT)                  /* 0x00000020 */
#define FDCAN_PSR_EP              FDCAN_PSR_EP_MASK                             /* Error Passive                            */
#define FDCAN_PSR_EW_SHIFT        (6U)
#define FDCAN_PSR_EW_MASK         (0x1U << FDCAN_PSR_EW_SHIFT)                  /* 0x00000040 */
#define FDCAN_PSR_EW              FDCAN_PSR_EW_MASK                             /* Warning Status                           */
#define FDCAN_PSR_BO_SHIFT        (7U)
#define FDCAN_PSR_BO_MASK         (0x1U << FDCAN_PSR_BO_SHIFT)                  /* 0x00000080 */
#define FDCAN_PSR_BO              FDCAN_PSR_BO_MASK                             /* Bus_Off Status                           */
#define FDCAN_PSR_DLEC_SHIFT      (8U)
#define FDCAN_PSR_DLEC_MASK       (0x7U << FDCAN_PSR_DLEC_SHIFT)                /* 0x00000700 */
#define FDCAN_PSR_DLEC(n)        ((uint32_t)(n) << FDCAN_PSR_DLEC_SHIFT)        /* See error codes above */
#define FDCAN_PSR_RESI_SHIFT      (11U)
#define FDCAN_PSR_RESI_MASK       (0x1U << FDCAN_PSR_RESI_SHIFT)                /* 0x00000800 */
#define FDCAN_PSR_RESI            FDCAN_PSR_RESI_MASK                           /* ESI flag of last received FDCAN Message  */
#define FDCAN_PSR_RBRS_SHIFT      (12U)
#define FDCAN_PSR_RBRS_MASK       (0x1U << FDCAN_PSR_RBRS_SHIFT)                /* 0x00001000 */
#define FDCAN_PSR_RBRS            FDCAN_PSR_RBRS_MASK                           /* BRS flag of last received FDCAN Message  */
#define FDCAN_PSR_REDL_SHIFT      (13U)
#define FDCAN_PSR_REDL_MASK       (0x1U << FDCAN_PSR_REDL_SHIFT)                /* 0x00002000 */
#define FDCAN_PSR_REDL            FDCAN_PSR_REDL_MASK                           /* Received FDCAN Message                   */
#define FDCAN_PSR_PXE_SHIFT       (14U)
#define FDCAN_PSR_PXE_MASK        (0x1U << FDCAN_PSR_PXE_SHIFT)                 /* 0x00004000 */
#define FDCAN_PSR_PXE             FDCAN_PSR_PXE_MASK                            /* Protocol Exception Event                 */
#define FDCAN_PSR_TDCV_SHIFT      (16U)
#define FDCAN_PSR_TDCV_MASK       (0x7FU << FDCAN_PSR_TDCV_SHIFT)               /* 0x007F0000 */
#define FDCAN_PSR_TDCV            FDCAN_PSR_TDCV_MASK                           /* Transmitter Delay Compensation Value     */

/* ***************  Bit definition for FDCAN_TDCR register  *****************/
#define FDCAN_TDCR_TDCF_SHIFT     (0U)
#define FDCAN_TDCR_TDCF_MASK      (0x7FU << FDCAN_TDCR_TDCF_SHIFT)              /* 0x0000007F */
#define FDCAN_TDCR_TDCF           FDCAN_TDCR_TDCF_MASK                          /* Transmitter Delay Compensation Filter    */
#define FDCAN_TDCR_TDCO_SHIFT     (8U)
#define FDCAN_TDCR_TDCO_MASK      (0x7FU << FDCAN_TDCR_TDCO_SHIFT)              /* 0x00007F00 */
#define FDCAN_TDCR_TDCO           FDCAN_TDCR_TDCO_MASK                          /* Transmitter Delay Compensation Offset    */

/* ***************  Bit definition for FDCAN_IR register  *******************/
#define FDCAN_IR_RF0N_SHIFT       (0U)
#define FDCAN_IR_RF0N_MASK        (0x1U << FDCAN_IR_RF0N_SHIFT)                 /* 0x00000001 */
#define FDCAN_IR_RF0N             FDCAN_IR_RF0N_MASK                            /* Rx FIFO 0 New Message                    */
#define FDCAN_IR_RF0W_SHIFT       (1U)
#define FDCAN_IR_RF0W_MASK        (0x1U << FDCAN_IR_RF0W_SHIFT)                 /* 0x00000002 */
#define FDCAN_IR_RF0W             FDCAN_IR_RF0W_MASK                            /* Rx FIFO 0 Watermark Reached              */
#define FDCAN_IR_RF0F_SHIFT       (2U)
#define FDCAN_IR_RF0F_MASK        (0x1U << FDCAN_IR_RF0F_SHIFT)                 /* 0x00000004 */
#define FDCAN_IR_RF0F             FDCAN_IR_RF0F_MASK                            /* Rx FIFO 0 Full                           */
#define FDCAN_IR_RF0L_SHIFT       (3U)
#define FDCAN_IR_RF0L_MASK        (0x1U << FDCAN_IR_RF0L_SHIFT)                 /* 0x00000008 */
#define FDCAN_IR_RF0L             FDCAN_IR_RF0L_MASK                            /* Rx FIFO 0 Message Lost                   */
#define FDCAN_IR_RF1N_SHIFT       (4U)
#define FDCAN_IR_RF1N_MASK        (0x1U << FDCAN_IR_RF1N_SHIFT)                 /* 0x00000010 */
#define FDCAN_IR_RF1N             FDCAN_IR_RF1N_MASK                            /* Rx FIFO 1 New Message                    */
#define FDCAN_IR_RF1W_SHIFT       (5U)
#define FDCAN_IR_RF1W_MASK        (0x1U << FDCAN_IR_RF1W_SHIFT)                 /* 0x00000020 */
#define FDCAN_IR_RF1W             FDCAN_IR_RF1W_MASK                            /* Rx FIFO 1 Watermark Reached              */
#define FDCAN_IR_RF1F_SHIFT       (6U)
#define FDCAN_IR_RF1F_MASK        (0x1U << FDCAN_IR_RF1F_SHIFT)                 /* 0x00000040 */
#define FDCAN_IR_RF1F             FDCAN_IR_RF1F_MASK                            /* Rx FIFO 1 Full                           */
#define FDCAN_IR_RF1L_SHIFT       (7U)
#define FDCAN_IR_RF1L_MASK        (0x1U << FDCAN_IR_RF1L_SHIFT)                 /* 0x00000080 */
#define FDCAN_IR_RF1L             FDCAN_IR_RF1L_MASK                            /* Rx FIFO 1 Message Lost                   */
#define FDCAN_IR_HPM_SHIFT        (8U)
#define FDCAN_IR_HPM_MASK         (0x1U << FDCAN_IR_HPM_SHIFT)                  /* 0x00000100 */
#define FDCAN_IR_HPM              FDCAN_IR_HPM_MASK                             /* High Priority Message                    */
#define FDCAN_IR_TC_SHIFT         (9U)
#define FDCAN_IR_TC_MASK          (0x1U << FDCAN_IR_TC_SHIFT)                   /* 0x00000200 */
#define FDCAN_IR_TC               FDCAN_IR_TC_MASK                              /* Transmission Completed                   */
#define FDCAN_IR_TCF_SHIFT        (10U)
#define FDCAN_IR_TCF_MASK         (0x1U << FDCAN_IR_TCF_SHIFT)                  /* 0x00000400 */
#define FDCAN_IR_TCF              FDCAN_IR_TCF_MASK                             /* Transmission Cancellation Finished       */
#define FDCAN_IR_TFE_SHIFT        (11U)
#define FDCAN_IR_TFE_MASK         (0x1U << FDCAN_IR_TFE_SHIFT)                  /* 0x00000800 */
#define FDCAN_IR_TFE              FDCAN_IR_TFE_MASK                             /* Tx FIFO Empty                            */
#define FDCAN_IR_TEFN_SHIFT       (12U)
#define FDCAN_IR_TEFN_MASK        (0x1U << FDCAN_IR_TEFN_SHIFT)                 /* 0x00001000 */
#define FDCAN_IR_TEFN             FDCAN_IR_TEFN_MASK                            /* Tx Event FIFO New Entry                  */
#define FDCAN_IR_TEFW_SHIFT       (13U)
#define FDCAN_IR_TEFW_MASK        (0x1U << FDCAN_IR_TEFW_SHIFT)                 /* 0x00002000 */
#define FDCAN_IR_TEFW             FDCAN_IR_TEFW_MASK                            /* Tx Event FIFO Watermark Reached          */
#define FDCAN_IR_TEFF_SHIFT       (14U)
#define FDCAN_IR_TEFF_MASK        (0x1U << FDCAN_IR_TEFF_SHIFT)                 /* 0x00004000 */
#define FDCAN_IR_TEFF             FDCAN_IR_TEFF_MASK                            /* Tx Event FIFO Full                       */
#define FDCAN_IR_TEFL_SHIFT       (15U)
#define FDCAN_IR_TEFL_MASK        (0x1U << FDCAN_IR_TEFL_SHIFT)                 /* 0x00008000 */
#define FDCAN_IR_TEFL             FDCAN_IR_TEFL_MASK                            /* Tx Event FIFO Element Lost               */
#define FDCAN_IR_TSW_SHIFT        (16U)
#define FDCAN_IR_TSW_MASK         (0x1U << FDCAN_IR_TSW_SHIFT)                  /* 0x00010000 */
#define FDCAN_IR_TSW              FDCAN_IR_TSW_MASK                             /* Timestamp Wraparound                     */
#define FDCAN_IR_MRAF_SHIFT       (17U)
#define FDCAN_IR_MRAF_MASK        (0x1U << FDCAN_IR_MRAF_SHIFT)                 /* 0x00020000 */
#define FDCAN_IR_MRAF             FDCAN_IR_MRAF_MASK                            /* Message RAM Access Failure               */
#define FDCAN_IR_TOO_SHIFT        (18U)
#define FDCAN_IR_TOO_MASK         (0x1U << FDCAN_IR_TOO_SHIFT)                  /* 0x00040000 */
#define FDCAN_IR_TOO              FDCAN_IR_TOO_MASK                             /* Timeout Occurred                         */
#define FDCAN_IR_DRX_SHIFT        (19U)
#define FDCAN_IR_DRX_MASK         (0x1U << FDCAN_IR_DRX_SHIFT)                  /* 0x00080000 */
#define FDCAN_IR_DRX              FDCAN_IR_DRX_MASK                             /* Message stored to Dedicated Rx Buffer    */
#define FDCAN_IR_ELO_SHIFT        (22U)
#define FDCAN_IR_ELO_MASK         (0x1U << FDCAN_IR_ELO_SHIFT)                  /* 0x00400000 */
#define FDCAN_IR_ELO              FDCAN_IR_ELO_MASK                             /* Error Logging Overflow                   */
#define FDCAN_IR_EP_SHIFT         (23U)
#define FDCAN_IR_EP_MASK          (0x1U << FDCAN_IR_EP_SHIFT)                   /* 0x00800000 */
#define FDCAN_IR_EP               FDCAN_IR_EP_MASK                              /* Error Passive                            */
#define FDCAN_IR_EW_SHIFT         (24U)
#define FDCAN_IR_EW_MASK          (0x1U << FDCAN_IR_EW_SHIFT)                   /* 0x01000000 */
#define FDCAN_IR_EW               FDCAN_IR_EW_MASK                              /* Warning Status                           */
#define FDCAN_IR_BO_SHIFT         (25U)
#define FDCAN_IR_BO_MASK          (0x1U << FDCAN_IR_BO_SHIFT)                   /* 0x02000000 */
#define FDCAN_IR_BO               FDCAN_IR_BO_MASK                              /* Bus_Off Status                           */
#define FDCAN_IR_WDI_SHIFT        (26U)
#define FDCAN_IR_WDI_MASK         (0x1U << FDCAN_IR_WDI_SHIFT)                  /* 0x04000000 */
#define FDCAN_IR_WDI              FDCAN_IR_WDI_MASK                             /* Watchdog Interrupt                       */
#define FDCAN_IR_PEA_SHIFT        (27U)
#define FDCAN_IR_PEA_MASK         (0x1U << FDCAN_IR_PEA_SHIFT)                  /* 0x08000000 */
#define FDCAN_IR_PEA              FDCAN_IR_PEA_MASK                             /* Protocol Error in Arbitration Phase      */
#define FDCAN_IR_PED_SHIFT        (28U)
#define FDCAN_IR_PED_MASK         (0x1U << FDCAN_IR_PED_SHIFT)                  /* 0x10000000 */
#define FDCAN_IR_PED              FDCAN_IR_PED_MASK                             /* Protocol Error in Data Phase             */
#define FDCAN_IR_ARA_SHIFT        (29U)
#define FDCAN_IR_ARA_MASK         (0x1U << FDCAN_IR_ARA_SHIFT)                  /* 0x20000000 */
#define FDCAN_IR_ARA              FDCAN_IR_ARA_MASK                             /* Access to Reserved Address               */

/* ***************  Bit definition for FDCAN_IE register  *******************/
#define FDCAN_IE_RF0NE_SHIFT      (0U)
#define FDCAN_IE_RF0NE_MASK       (0x1U << FDCAN_IE_RF0NE_SHIFT)                /* 0x00000001 */
#define FDCAN_IE_RF0NE            FDCAN_IE_RF0NE_MASK                           /* Rx FIFO 0 New Message Enable                 */
#define FDCAN_IE_RF0WE_SHIFT      (1U)
#define FDCAN_IE_RF0WE_MASK       (0x1U << FDCAN_IE_RF0WE_SHIFT)                /* 0x00000002 */
#define FDCAN_IE_RF0WE            FDCAN_IE_RF0WE_MASK                           /* Rx FIFO 0 Watermark Reached Enable           */
#define FDCAN_IE_RF0FE_SHIFT      (2U)
#define FDCAN_IE_RF0FE_MASK       (0x1U << FDCAN_IE_RF0FE_SHIFT)                /* 0x00000004 */
#define FDCAN_IE_RF0FE            FDCAN_IE_RF0FE_MASK                           /* Rx FIFO 0 Full Enable                        */
#define FDCAN_IE_RF0LE_SHIFT      (3U)
#define FDCAN_IE_RF0LE_MASK       (0x1U << FDCAN_IE_RF0LE_SHIFT)                /* 0x00000008 */
#define FDCAN_IE_RF0LE            FDCAN_IE_RF0LE_MASK                           /* Rx FIFO 0 Message Lost Enable                */
#define FDCAN_IE_RF1NE_SHIFT      (4U)
#define FDCAN_IE_RF1NE_MASK       (0x1U << FDCAN_IE_RF1NE_SHIFT)                /* 0x00000010 */
#define FDCAN_IE_RF1NE            FDCAN_IE_RF1NE_MASK                           /* Rx FIFO 1 New Message Enable                 */
#define FDCAN_IE_RF1WE_SHIFT      (5U)
#define FDCAN_IE_RF1WE_MASK       (0x1U << FDCAN_IE_RF1WE_SHIFT)                /* 0x00000020 */
#define FDCAN_IE_RF1WE            FDCAN_IE_RF1WE_MASK                           /* Rx FIFO 1 Watermark Reached Enable           */
#define FDCAN_IE_RF1FE_SHIFT      (6U)
#define FDCAN_IE_RF1FE_MASK       (0x1U << FDCAN_IE_RF1FE_SHIFT)                /* 0x00000040 */
#define FDCAN_IE_RF1FE            FDCAN_IE_RF1FE_MASK                           /* Rx FIFO 1 Full Enable                        */
#define FDCAN_IE_RF1LE_SHIFT      (7U)
#define FDCAN_IE_RF1LE_MASK       (0x1U << FDCAN_IE_RF1LE_SHIFT)                /* 0x00000080 */
#define FDCAN_IE_RF1LE            FDCAN_IE_RF1LE_MASK                           /* Rx FIFO 1 Message Lost Enable                */
#define FDCAN_IE_HPME_SHIFT       (8U)
#define FDCAN_IE_HPME_MASK        (0x1U << FDCAN_IE_HPME_SHIFT)                 /* 0x00000100 */
#define FDCAN_IE_HPME             FDCAN_IE_HPME_MASK                            /* High Priority Message Enable                 */
#define FDCAN_IE_TCE_SHIFT        (9U)
#define FDCAN_IE_TCE_MASK         (0x1U << FDCAN_IE_TCE_SHIFT)                  /* 0x00000200 */
#define FDCAN_IE_TCE              FDCAN_IE_TCE_MASK                             /* Transmission Completed Enable                */
#define FDCAN_IE_TCFE_SHIFT       (10U)
#define FDCAN_IE_TCFE_MASK        (0x1U << FDCAN_IE_TCFE_SHIFT)                 /* 0x00000400 */
#define FDCAN_IE_TCFE             FDCAN_IE_TCFE_MASK                            /* Transmission Cancellation Finished Enable    */
#define FDCAN_IE_TFEE_SHIFT       (11U)
#define FDCAN_IE_TFEE_MASK        (0x1U << FDCAN_IE_TFEE_SHIFT)                 /* 0x00000800 */
#define FDCAN_IE_TFEE             FDCAN_IE_TFEE_MASK                            /* Tx FIFO Empty Enable                         */
#define FDCAN_IE_TEFNE_SHIFT      (12U)
#define FDCAN_IE_TEFNE_MASK       (0x1U << FDCAN_IE_TEFNE_SHIFT)                /* 0x00001000 */
#define FDCAN_IE_TEFNE            FDCAN_IE_TEFNE_MASK                           /* Tx Event FIFO New Entry Enable               */
#define FDCAN_IE_TEFWE_SHIFT      (13U)
#define FDCAN_IE_TEFWE_MASK       (0x1U << FDCAN_IE_TEFWE_SHIFT)                /* 0x00002000 */
#define FDCAN_IE_TEFWE            FDCAN_IE_TEFWE_MASK                           /* Tx Event FIFO Watermark Reached Enable       */
#define FDCAN_IE_TEFFE_SHIFT      (14U)
#define FDCAN_IE_TEFFE_MASK       (0x1U << FDCAN_IE_TEFFE_SHIFT)                /* 0x00004000 */
#define FDCAN_IE_TEFFE            FDCAN_IE_TEFFE_MASK                           /* Tx Event FIFO Full Enable                    */
#define FDCAN_IE_TEFLE_SHIFT      (15U)
#define FDCAN_IE_TEFLE_MASK       (0x1U << FDCAN_IE_TEFLE_SHIFT)                /* 0x00008000 */
#define FDCAN_IE_TEFLE            FDCAN_IE_TEFLE_MASK                           /* Tx Event FIFO Element Lost Enable            */
#define FDCAN_IE_TSWE_SHIFT       (16U)
#define FDCAN_IE_TSWE_MASK        (0x1U << FDCAN_IE_TSWE_SHIFT)                 /* 0x00010000 */
#define FDCAN_IE_TSWE             FDCAN_IE_TSWE_MASK                            /* Timestamp Wraparound Enable                  */
#define FDCAN_IE_MRAFE_SHIFT      (17U)
#define FDCAN_IE_MRAFE_MASK       (0x1U << FDCAN_IE_MRAFE_SHIFT)                /* 0x00020000 */
#define FDCAN_IE_MRAFE            FDCAN_IE_MRAFE_MASK                           /* Message RAM Access Failure Enable            */
#define FDCAN_IE_TOOE_SHIFT       (18U)
#define FDCAN_IE_TOOE_MASK        (0x1U << FDCAN_IE_TOOE_SHIFT)                 /* 0x00040000 */
#define FDCAN_IE_TOOE             FDCAN_IE_TOOE_MASK                            /* Timeout Occurred Enable                      */
#define FDCAN_IE_DRXE_SHIFT       (19U)
#define FDCAN_IE_DRXE_MASK        (0x1U << FDCAN_IE_DRXE_SHIFT)                 /* 0x00080000 */
#define FDCAN_IE_DRXE             FDCAN_IE_DRXE_MASK                            /* Message stored to Dedicated Rx Buffer Enable */
#define FDCAN_IE_BECE_SHIFT       (20U)
#define FDCAN_IE_BECE_MASK        (0x1U << FDCAN_IE_BECE_SHIFT)                 /* 0x00100000 */
#define FDCAN_IE_BECE             FDCAN_IE_BECE_MASK                            /* Bit Error Corrected Interrupt Enable         */
#define FDCAN_IE_BEUE_SHIFT       (21U)
#define FDCAN_IE_BEUE_MASK        (0x1U << FDCAN_IE_BEUE_SHIFT)                 /* 0x00200000 */
#define FDCAN_IE_BEUE             FDCAN_IE_BEUE_MASK                            /* Bit Error Uncorrected Interrupt Enable       */
#define FDCAN_IE_ELOE_SHIFT       (22U)
#define FDCAN_IE_ELOE_MASK        (0x1U << FDCAN_IE_ELOE_SHIFT)                 /* 0x00400000 */
#define FDCAN_IE_ELOE             FDCAN_IE_ELOE_MASK                            /* Error Logging Overflow Enable                */
#define FDCAN_IE_EPE_SHIFT        (23U)
#define FDCAN_IE_EPE_MASK         (0x1U << FDCAN_IE_EPE_SHIFT)                  /* 0x00800000 */
#define FDCAN_IE_EPE              FDCAN_IE_EPE_MASK                             /* Error Passive Enable                         */
#define FDCAN_IE_EWE_SHIFT        (24U)
#define FDCAN_IE_EWE_MASK         (0x1U << FDCAN_IE_EWE_SHIFT)                  /* 0x01000000 */
#define FDCAN_IE_EWE              FDCAN_IE_EWE_MASK                             /* Warning Status Enable                        */
#define FDCAN_IE_BOE_SHIFT        (25U)
#define FDCAN_IE_BOE_MASK         (0x1U << FDCAN_IE_BOE_SHIFT)                  /* 0x02000000 */
#define FDCAN_IE_BOE              FDCAN_IE_BOE_MASK                             /* Bus_Off Status Enable                        */
#define FDCAN_IE_WDIE_SHIFT       (26U)
#define FDCAN_IE_WDIE_MASK        (0x1U << FDCAN_IE_WDIE_SHIFT)                 /* 0x04000000 */
#define FDCAN_IE_WDIE             FDCAN_IE_WDIE_MASK                            /* Watchdog Interrupt Enable                    */
#define FDCAN_IE_PEAE_SHIFT       (27U)
#define FDCAN_IE_PEAE_MASK        (0x1U << FDCAN_IE_PEAE_SHIFT)                 /* 0x08000000 */
#define FDCAN_IE_PEAE             FDCAN_IE_PEAE_MASK                            /* Protocol Error in Arbitration Phase Enable   */
#define FDCAN_IE_PEDE_SHIFT       (28U)
#define FDCAN_IE_PEDE_MASK        (0x1U << FDCAN_IE_PEDE_SHIFT)                 /* 0x10000000 */
#define FDCAN_IE_PEDE             FDCAN_IE_PEDE_MASK                            /* Protocol Error in Data Phase Enable          */
#define FDCAN_IE_ARAE_SHIFT       (29U)
#define FDCAN_IE_ARAE_MASK        (0x1U << FDCAN_IE_ARAE_SHIFT)                 /* 0x20000000 */
#define FDCAN_IE_ARAE             FDCAN_IE_ARAE_MASK                            /* Access to Reserved Address Enable            */

/* ***************  Bit definition for FDCAN_ILS register  ******************/
#define FDCAN_ILS_RF0NL_SHIFT     (0U)
#define FDCAN_ILS_RF0NL_MASK      (0x1U << FDCAN_ILS_RF0NL_SHIFT)               /* 0x00000001 */
#define FDCAN_ILS_RF0NL           FDCAN_ILS_RF0NL_MASK                          /* Rx FIFO 0 New Message Line                  */
#define FDCAN_ILS_RF0WL_SHIFT     (1U)
#define FDCAN_ILS_RF0WL_MASK      (0x1U << FDCAN_ILS_RF0WL_SHIFT)               /* 0x00000002 */
#define FDCAN_ILS_RF0WL           FDCAN_ILS_RF0WL_MASK                          /* Rx FIFO 0 Watermark Reached Line            */
#define FDCAN_ILS_RF0FL_SHIFT     (2U)
#define FDCAN_ILS_RF0FL_MASK      (0x1U << FDCAN_ILS_RF0FL_SHIFT)               /* 0x00000004 */
#define FDCAN_ILS_RF0FL           FDCAN_ILS_RF0FL_MASK                          /* Rx FIFO 0 Full Line                         */
#define FDCAN_ILS_RF0LL_SHIFT     (3U)
#define FDCAN_ILS_RF0LL_MASK      (0x1U << FDCAN_ILS_RF0LL_SHIFT)               /* 0x00000008 */
#define FDCAN_ILS_RF0LL           FDCAN_ILS_RF0LL_MASK                          /* Rx FIFO 0 Message Lost Line                 */
#define FDCAN_ILS_RF1NL_SHIFT     (4U)
#define FDCAN_ILS_RF1NL_MASK      (0x1U << FDCAN_ILS_RF1NL_SHIFT)               /* 0x00000010 */
#define FDCAN_ILS_RF1NL           FDCAN_ILS_RF1NL_MASK                          /* Rx FIFO 1 New Message Line                  */
#define FDCAN_ILS_RF1WL_SHIFT     (5U)
#define FDCAN_ILS_RF1WL_MASK      (0x1U << FDCAN_ILS_RF1WL_SHIFT)               /* 0x00000020 */
#define FDCAN_ILS_RF1WL           FDCAN_ILS_RF1WL_MASK                          /* Rx FIFO 1 Watermark Reached Line            */
#define FDCAN_ILS_RF1FL_SHIFT     (6U)
#define FDCAN_ILS_RF1FL_MASK      (0x1U << FDCAN_ILS_RF1FL_SHIFT)               /* 0x00000040 */
#define FDCAN_ILS_RF1FL           FDCAN_ILS_RF1FL_MASK                          /* Rx FIFO 1 Full Line                         */
#define FDCAN_ILS_RF1LL_SHIFT     (7U)
#define FDCAN_ILS_RF1LL_MASK      (0x1U << FDCAN_ILS_RF1LL_SHIFT)               /* 0x00000080 */
#define FDCAN_ILS_RF1LL           FDCAN_ILS_RF1LL_MASK                          /* Rx FIFO 1 Message Lost Line                 */
#define FDCAN_ILS_HPML_SHIFT      (8U)
#define FDCAN_ILS_HPML_MASK       (0x1U << FDCAN_ILS_HPML_SHIFT)                /* 0x00000100 */
#define FDCAN_ILS_HPML            FDCAN_ILS_HPML_MASK                           /* High Priority Message Line                  */
#define FDCAN_ILS_TCL_SHIFT       (9U)
#define FDCAN_ILS_TCL_MASK        (0x1U << FDCAN_ILS_TCL_SHIFT)                 /* 0x00000200 */
#define FDCAN_ILS_TCL             FDCAN_ILS_TCL_MASK                            /* Transmission Completed Line                 */
#define FDCAN_ILS_TCFL_SHIFT      (10U)
#define FDCAN_ILS_TCFL_MASK       (0x1U << FDCAN_ILS_TCFL_SHIFT)                /* 0x00000400 */
#define FDCAN_ILS_TCFL            FDCAN_ILS_TCFL_MASK                           /* Transmission Cancellation Finished Line     */
#define FDCAN_ILS_TFEL_SHIFT      (11U)
#define FDCAN_ILS_TFEL_MASK       (0x1U << FDCAN_ILS_TFEL_SHIFT)                /* 0x00000800 */
#define FDCAN_ILS_TFEL            FDCAN_ILS_TFEL_MASK                           /* Tx FIFO Empty Line                          */
#define FDCAN_ILS_TEFNL_SHIFT     (12U)
#define FDCAN_ILS_TEFNL_MASK      (0x1U << FDCAN_ILS_TEFNL_SHIFT)               /* 0x00001000 */
#define FDCAN_ILS_TEFNL           FDCAN_ILS_TEFNL_MASK                          /* Tx Event FIFO New Entry Line                */
#define FDCAN_ILS_TEFWL_SHIFT     (13U)
#define FDCAN_ILS_TEFWL_MASK      (0x1U << FDCAN_ILS_TEFWL_SHIFT)               /* 0x00002000 */
#define FDCAN_ILS_TEFWL           FDCAN_ILS_TEFWL_MASK                          /* Tx Event FIFO Watermark Reached Line        */
#define FDCAN_ILS_TEFFL_SHIFT     (14U)
#define FDCAN_ILS_TEFFL_MASK      (0x1U << FDCAN_ILS_TEFFL_SHIFT)               /* 0x00004000 */
#define FDCAN_ILS_TEFFL           FDCAN_ILS_TEFFL_MASK                          /* Tx Event FIFO Full Line                     */
#define FDCAN_ILS_TEFLL_SHIFT     (15U)
#define FDCAN_ILS_TEFLL_MASK      (0x1U << FDCAN_ILS_TEFLL_SHIFT)               /* 0x00008000 */
#define FDCAN_ILS_TEFLL           FDCAN_ILS_TEFLL_MASK                          /* Tx Event FIFO Element Lost Line             */
#define FDCAN_ILS_TSWL_SHIFT      (16U)
#define FDCAN_ILS_TSWL_MASK       (0x1U << FDCAN_ILS_TSWL_SHIFT)                /* 0x00010000 */
#define FDCAN_ILS_TSWL            FDCAN_ILS_TSWL_MASK                           /* Timestamp Wraparound Line                   */
#define FDCAN_ILS_MRAFE_SHIFT     (17U)
#define FDCAN_ILS_MRAFE_MASK      (0x1U << FDCAN_ILS_MRAFE_SHIFT)               /* 0x00020000 */
#define FDCAN_ILS_MRAFE           FDCAN_ILS_MRAFE_MASK                          /* Message RAM Access Failure Line             */
#define FDCAN_ILS_TOOE_SHIFT      (18U)
#define FDCAN_ILS_TOOE_MASK       (0x1U << FDCAN_ILS_TOOE_SHIFT)                /* 0x00040000 */
#define FDCAN_ILS_TOOE            FDCAN_ILS_TOOE_MASK                           /* Timeout Occurred Line                       */
#define FDCAN_ILS_DRXE_SHIFT      (19U)
#define FDCAN_ILS_DRXE_MASK       (0x1U << FDCAN_ILS_DRXE_SHIFT)                /* 0x00080000 */
#define FDCAN_ILS_DRXE            FDCAN_ILS_DRXE_MASK                           /* Message stored to Dedicated Rx Buffer Line  */
#define FDCAN_ILS_BECE_SHIFT      (20U)
#define FDCAN_ILS_BECE_MASK       (0x1U << FDCAN_ILS_BECE_SHIFT)                /* 0x00100000 */
#define FDCAN_ILS_BECE            FDCAN_ILS_BECE_MASK                           /* Bit Error Corrected Interrupt Line          */
#define FDCAN_ILS_BEUE_SHIFT      (21U)
#define FDCAN_ILS_BEUE_MASK       (0x1U << FDCAN_ILS_BEUE_SHIFT)                /* 0x00200000 */
#define FDCAN_ILS_BEUE            FDCAN_ILS_BEUE_MASK                           /* Bit Error Uncorrected Interrupt Line        */
#define FDCAN_ILS_ELOE_SHIFT      (22U)
#define FDCAN_ILS_ELOE_MASK       (0x1U << FDCAN_ILS_ELOE_SHIFT)                /* 0x00400000 */
#define FDCAN_ILS_ELOE            FDCAN_ILS_ELOE_MASK                           /* Error Logging Overflow Line                 */
#define FDCAN_ILS_EPE_SHIFT       (23U)
#define FDCAN_ILS_EPE_MASK        (0x1U << FDCAN_ILS_EPE_SHIFT)                 /* 0x00800000 */
#define FDCAN_ILS_EPE             FDCAN_ILS_EPE_MASK                            /* Error Passive Line                          */
#define FDCAN_ILS_EWE_SHIFT       (24U)
#define FDCAN_ILS_EWE_MASK        (0x1U << FDCAN_ILS_EWE_SHIFT)                 /* 0x01000000 */
#define FDCAN_ILS_EWE             FDCAN_ILS_EWE_MASK                            /* Warning Status Line                         */
#define FDCAN_ILS_BOE_SHIFT       (25U)
#define FDCAN_ILS_BOE_MASK        (0x1U << FDCAN_ILS_BOE_SHIFT)                 /* 0x02000000 */
#define FDCAN_ILS_BOE             FDCAN_ILS_BOE_MASK                            /* Bus_Off Status Line                         */
#define FDCAN_ILS_WDIE_SHIFT      (26U)
#define FDCAN_ILS_WDIE_MASK       (0x1U << FDCAN_ILS_WDIE_SHIFT)                /* 0x04000000 */
#define FDCAN_ILS_WDIE            FDCAN_ILS_WDIE_MASK                           /* Watchdog Interrupt Line                     */
#define FDCAN_ILS_PEAE_SHIFT      (27U)
#define FDCAN_ILS_PEAE_MASK       (0x1U << FDCAN_ILS_PEAE_SHIFT)                /* 0x08000000 */
#define FDCAN_ILS_PEAE            FDCAN_ILS_PEAE_MASK                           /* Protocol Error in Arbitration Phase Line    */
#define FDCAN_ILS_PEDE_SHIFT      (28U)
#define FDCAN_ILS_PEDE_MASK       (0x1U << FDCAN_ILS_PEDE_SHIFT)                /* 0x10000000 */
#define FDCAN_ILS_PEDE            FDCAN_ILS_PEDE_MASK                           /* Protocol Error in Data Phase Line           */
#define FDCAN_ILS_ARAE_SHIFT      (29U)
#define FDCAN_ILS_ARAE_MASK       (0x1U << FDCAN_ILS_ARAE_SHIFT)                /* 0x20000000 */
#define FDCAN_ILS_ARAE            FDCAN_ILS_ARAE_MASK                           /* Access to Reserved Address Line             */

/* ***************  Bit definition for FDCAN_ILE register  ******************/
#define FDCAN_ILE_EINT0_SHIFT       (0U)
#define FDCAN_ILE_EINT0_MASK       (0x1U << FDCAN_ILE_EINT0_SHIFT)              /* 0x00000001 */
#define FDCAN_ILE_EINT0           FDCAN_ILE_EINT0_MASK                          /* Enable Interrupt Line 0                   */
#define FDCAN_ILE_EINT1_SHIFT       (1U)
#define FDCAN_ILE_EINT1_MASK       (0x1U << FDCAN_ILE_EINT1_SHIFT)              /* 0x00000002 */
#define FDCAN_ILE_EINT1           FDCAN_ILE_EINT1_MASK                          /* Enable Interrupt Line 1                   */

/* ***************  Bit definition for FDCAN_RXGFC register  ******************/
#define FDCAN_RXGFC_RRFE_SHIFT      (0U)
#define FDCAN_RXGFC_RRFE_MASK       (0x1U << FDCAN_RXGFC_RRFE_SHIFT)                /* 0x00000001 */
#define FDCAN_RXGFC_RRFE            FDCAN_RXGFC_RRFE_MASK                           /* Reject Remote Frames Extended             */
#define FDCAN_RXGFC_RRFS_SHIFT      (1U)
#define FDCAN_RXGFC_RRFS_MASK       (0x1U << FDCAN_RXGFC_RRFS_SHIFT)                /* 0x00000002 */
#define FDCAN_RXGFC_RRFS            FDCAN_RXGFC_RRFS_MASK                           /* Reject Remote Frames Standard             */
#define FDCAN_RXGFC_ANFE_SHIFT      (2U)
#define FDCAN_RXGFC_ANFE_MASK       (0x3U << FDCAN_RXGFC_ANFE_SHIFT)                /* 0x0000000C */
#define FDCAN_RXGFC_ANFE            FDCAN_RXGFC_ANFE_MASK                           /* Accept Non-matching Frames Extended       */
#define FDCAN_RXGFC_ANFS_SHIFT      (4U)
#define FDCAN_RXGFC_ANFS_MASK       (0x3U << FDCAN_RXGFC_ANFS_SHIFT)                /* 0x00000030 */
#define FDCAN_RXGFC_ANFS            FDCAN_RXGFC_ANFS_MASK                           /* Accept Non-matching Frames Standard       */
#define FDCAN_RXGFC_F1OM_SHIFT      (8U)
#define FDCAN_RXGFC_F1OM_MASK       (1U << FDCAN_RXGFC_F1OM_SHIFT)                  /* 0x00000100 */
#define FDCAN_RXGFC_F1OM            FDCAN_RXGFC_F1OM_MASK                           /* FIFO 1 Operation Mode */
#define FDCAN_RXGFC_F0OM_SHIFT      (9U)
#define FDCAN_RXGFC_F0OM_MASK       (1U << FDCAN_RXGFC_F0OM_SHIFT)                  /* 0x00000200 */
#define FDCAN_RXGFC_F0OM            FDCAN_RXGFC_F0OM_MASK                           /* FIFO 0 Operation Mode */
#define FDCAN_RXGFS_LSS_SHIFT       (16U)
#define FDCAN_RXGFS_LSS_MASK        (0x1fu << FDCAN_RXGFC_LSS_SHIFT)                /* 0x001f0000 */
#define FDCAN_RXGFS_LSS             FDCAN_RXGFS_LSS_MASK                            /* Number of standard filter elements in list */ 
#define FDCAN_RXGFS_LSE_SHIFT       (24U)
#define FDCAN_RXGFS_LSE_MASK        (0xfu << FDCAN_RXGFC_LSE_SHIFT)                 /* 0x0f000000 */
#define FDCAN_RXGFS_LSE             FDCAN_RXGFS_LSE_MASK                            /* Number of extended filter elements in list */ 

/* ***************  Bit definition for FDCAN_XIDAM register  ****************/
#define FDCAN_XIDAM_EIDM_SHIFT    (0U)
#define FDCAN_XIDAM_EIDM_MASK     (0x1FFFFFFFU << FDCAN_XIDAM_EIDM_SHIFT)       /* 0x1FFFFFFF */
#define FDCAN_XIDAM_EIDM          FDCAN_XIDAM_EIDM_MASK                         /* Extended ID Mask                          */

/* ***************  Bit definition for FDCAN_HPMS register  *****************/
#define FDCAN_HPMS_BIDX_SHIFT     (0U)
#define FDCAN_HPMS_BIDX_MASK      (0x3FU << FDCAN_HPMS_BIDX_SHIFT)              /* 0x0000003F */
#define FDCAN_HPMS_BIDX           FDCAN_HPMS_BIDX_MASK                          /* Buffer Index                              */
#define FDCAN_HPMS_MSI_SHIFT      (6U)
#define FDCAN_HPMS_MSI_MASK       (0x3U << FDCAN_HPMS_MSI_SHIFT)                /* 0x000000C0 */
#define FDCAN_HPMS_MSI            FDCAN_HPMS_MSI_MASK                           /* Message Storage Indicator                 */
#define FDCAN_HPMS_FIDX_SHIFT     (8U)
#define FDCAN_HPMS_FIDX_MASK      (0x7FU << FDCAN_HPMS_FIDX_SHIFT)              /* 0x00007F00 */
#define FDCAN_HPMS_FIDX           FDCAN_HPMS_FIDX_MASK                          /* Filter Index                              */
#define FDCAN_HPMS_FLST_SHIFT     (15U)
#define FDCAN_HPMS_FLST_MASK      (0x1U << FDCAN_HPMS_FLST_SHIFT)               /* 0x00008000 */
#define FDCAN_HPMS_FLST           FDCAN_HPMS_FLST_MASK                          /* Filter List                               */



/* ***************  Bit definition for FDCAN_RXF0S register  ****************/
#define FDCAN_RXF0S_F0FL_SHIFT    (0U)
#define FDCAN_RXF0S_F0FL_MASK     (0x7FU << FDCAN_RXF0S_F0FL_SHIFT)             /* 0x0000007F */
#define FDCAN_RXF0S_F0FL          FDCAN_RXF0S_F0FL_MASK                         /* Rx FIFO 0 Fill Level                      */
#define FDCAN_RXF0S_F0GI_SHIFT    (8U)
#define FDCAN_RXF0S_F0GI_MASK     (0x3FU << FDCAN_RXF0S_F0GI_SHIFT)             /* 0x00003F00 */
#define FDCAN_RXF0S_F0GI          FDCAN_RXF0S_F0GI_MASK                         /* Rx FIFO 0 Get Index                       */
#define FDCAN_RXF0S_F0PI_SHIFT    (16U)
#define FDCAN_RXF0S_F0PI_MASK     (0x3FU << FDCAN_RXF0S_F0PI_SHIFT)             /* 0x003F0000 */
#define FDCAN_RXF0S_F0PI          FDCAN_RXF0S_F0PI_MASK                         /* Rx FIFO 0 Put Index                       */
#define FDCAN_RXF0S_F0F_SHIFT     (24U)
#define FDCAN_RXF0S_F0F_MASK      (0x1U << FDCAN_RXF0S_F0F_SHIFT)               /* 0x01000000 */
#define FDCAN_RXF0S_F0F           FDCAN_RXF0S_F0F_MASK                          /* Rx FIFO 0 Full                            */
#define FDCAN_RXF0S_RF0L_SHIFT    (25U)
#define FDCAN_RXF0S_RF0L_MASK     (0x1U << FDCAN_RXF0S_RF0L_SHIFT)              /* 0x02000000 */
#define FDCAN_RXF0S_RF0L          FDCAN_RXF0S_RF0L_MASK                         /* Rx FIFO 0 Message Lost                    */

/* ***************  Bit definition for FDCAN_RXF0A register  ****************/
#define FDCAN_RXF0A_F0AI_SHIFT    (0U)
#define FDCAN_RXF0A_F0AI_MASK     (0x3FU << FDCAN_RXF0A_F0AI_SHIFT)             /* 0x0000003F */
#define FDCAN_RXF0A_F0AI          FDCAN_RXF0A_F0AI_MASK                         /* Rx FIFO 0 Acknowledge Index               */


/* ***************  Bit definition for FDCAN_RXF1S register  ****************/
#define FDCAN_RXF1S_F1FL_SHIFT    (0U)
#define FDCAN_RXF1S_F1FL_MASK     (0x7FU << FDCAN_RXF1S_F1FL_SHIFT)             /* 0x0000007F */
#define FDCAN_RXF1S_F1FL          FDCAN_RXF1S_F1FL_MASK                         /* Rx FIFO 1 Fill Level                      */
#define FDCAN_RXF1S_F1GI_SHIFT    (8U)
#define FDCAN_RXF1S_F1GI_MASK     (0x3FU << FDCAN_RXF1S_F1GI_SHIFT)             /* 0x00003F00 */
#define FDCAN_RXF1S_F1GI          FDCAN_RXF1S_F1GI_MASK                         /* Rx FIFO 1 Get Index                       */
#define FDCAN_RXF1S_F1PI_SHIFT    (16U)
#define FDCAN_RXF1S_F1PI_MASK     (0x3FU << FDCAN_RXF1S_F1PI_SHIFT)             /* 0x003F0000 */
#define FDCAN_RXF1S_F1PI          FDCAN_RXF1S_F1PI_MASK                         /* Rx FIFO 1 Put Index                       */
#define FDCAN_RXF1S_F1F_SHIFT     (24U)
#define FDCAN_RXF1S_F1F_MASK      (0x1U << FDCAN_RXF1S_F1F_SHIFT)               /* 0x01000000 */
#define FDCAN_RXF1S_F1F           FDCAN_RXF1S_F1F_MASK                          /* Rx FIFO 1 Full                            */
#define FDCAN_RXF1S_RF1L_SHIFT    (25U)
#define FDCAN_RXF1S_RF1L_MASK     (0x1U << FDCAN_RXF1S_RF1L_SHIFT)              /* 0x02000000 */
#define FDCAN_RXF1S_RF1L          FDCAN_RXF1S_RF1L_MASK                         /* Rx FIFO 1 Message Lost                    */

/* ***************  Bit definition for FDCAN_RXF1A register  ****************/
#define FDCAN_RXF1A_F1AI_SHIFT    (0U)
#define FDCAN_RXF1A_F1AI_MASK     (0x3FU << FDCAN_RXF1A_F1AI_SHIFT)             /* 0x0000003F */
#define FDCAN_RXF1A_F1AI          FDCAN_RXF1A_F1AI_MASK                         /* Rx FIFO 1 Acknowledge Index               */


/* ***************  Bit definition for FDCAN_TXBC register  *****************/
#define FDCAN_TXBC_TBSA_SHIFT     (2U)
#define FDCAN_TXBC_TBSA_MASK      (0x3FFFU << FDCAN_TXBC_TBSA_SHIFT)            /* 0x0000FFFC */
#define FDCAN_TXBC_TBSA           FDCAN_TXBC_TBSA_MASK                          /* Tx Buffers Start Address                  */
#define FDCAN_TXBC_NDTB_SHIFT     (16U)
#define FDCAN_TXBC_NDTB_MASK      (0x3FU << FDCAN_TXBC_NDTB_SHIFT)              /* 0x003F0000 */
#define FDCAN_TXBC_NDTB           FDCAN_TXBC_NDTB_MASK                          /* Number of Dedicated Transmit Buffers      */
#define FDCAN_TXBC_TFQS_SHIFT     (24U)
#define FDCAN_TXBC_TFQS_MASK      (0x3FU << FDCAN_TXBC_TFQS_SHIFT)              /* 0x3F000000 */
#define FDCAN_TXBC_TFQS           FDCAN_TXBC_TFQS_MASK                          /* Transmit FIFO/Queue Size                  */
#define FDCAN_TXBC_TFQM_SHIFT     (30U)
#define FDCAN_TXBC_TFQM_MASK      (0x1U << FDCAN_TXBC_TFQM_SHIFT)               /* 0x40000000 */
#define FDCAN_TXBC_TFQM           FDCAN_TXBC_TFQM_MASK                          /* Tx FIFO/Queue Mode                        */

/* ***************  Bit definition for FDCAN_TXFQS register  ****************/
#define FDCAN_TXFQS_TFFL_SHIFT    (0U)
#define FDCAN_TXFQS_TFFL_MASK     (0x3FU << FDCAN_TXFQS_TFFL_SHIFT)             /* 0x0000003F */
#define FDCAN_TXFQS_TFFL          FDCAN_TXFQS_TFFL_MASK                         /* Tx FIFO Free Level                        */
#define FDCAN_TXFQS_TFGI_SHIFT    (8U)
#define FDCAN_TXFQS_TFGI_MASK     (0x1FU << FDCAN_TXFQS_TFGI_SHIFT)             /* 0x00001F00 */
#define FDCAN_TXFQS_TFGI          FDCAN_TXFQS_TFGI_MASK                         /* Tx FIFO Get Index                         */
#define FDCAN_TXFQS_TFQPI_SHIFT   (16U)
#define FDCAN_TXFQS_TFQPI_MASK    (0x1FU << FDCAN_TXFQS_TFQPI_SHIFT)            /* 0x001F0000 */
#define FDCAN_TXFQS_TFQPI         FDCAN_TXFQS_TFQPI_MASK                        /* Tx FIFO/Queue Put Index                   */
#define FDCAN_TXFQS_TFQF_SHIFT    (21U)
#define FDCAN_TXFQS_TFQF_MASK     (0x1U << FDCAN_TXFQS_TFQF_SHIFT)              /* 0x00200000 */
#define FDCAN_TXFQS_TFQF          FDCAN_TXFQS_TFQF_MASK                         /* Tx FIFO/Queue Full                        */

/* ***************  Bit definition for FDCAN_TXBRP register  ****************/
#define FDCAN_TXBRP_TRP_SHIFT     (0U)
#define FDCAN_TXBRP_TRP_MASK      (0xFFFFFFFFU << FDCAN_TXBRP_TRP_SHIFT)        /* 0xFFFFFFFF */
#define FDCAN_TXBRP_TRP           FDCAN_TXBRP_TRP_MASK                          /* Transmission Request Pending              */

/* ***************  Bit definition for FDCAN_TXBAR register  ****************/
#define FDCAN_TXBAR_AR_SHIFT      (0U)
#define FDCAN_TXBAR_AR_MASK       (0xFFFFFFFFU << FDCAN_TXBAR_AR_SHIFT)         /* 0xFFFFFFFF */
#define FDCAN_TXBAR_AR            FDCAN_TXBAR_AR_MASK                           /* Add Request                               */

/* ***************  Bit definition for FDCAN_TXBCR register  ****************/
#define FDCAN_TXBCR_CR_SHIFT      (0U)
#define FDCAN_TXBCR_CR_MASK       (0xFFFFFFFFU << FDCAN_TXBCR_CR_SHIFT)         /* 0xFFFFFFFF */
#define FDCAN_TXBCR_CR            FDCAN_TXBCR_CR_MASK                           /* Cancellation Request                      */

/* ***************  Bit definition for FDCAN_TXBTO register  ****************/
#define FDCAN_TXBTO_TO_SHIFT      (0U)
#define FDCAN_TXBTO_TO_MASK       (0xFFFFFFFFU << FDCAN_TXBTO_TO_SHIFT)         /* 0xFFFFFFFF */
#define FDCAN_TXBTO_TO            FDCAN_TXBTO_TO_MASK                           /* Transmission Occurred                     */

/* ***************  Bit definition for FDCAN_TXBCF register  ****************/
#define FDCAN_TXBCF_CF_SHIFT      (0U)
#define FDCAN_TXBCF_CF_MASK       (0xFFFFFFFFU << FDCAN_TXBCF_CF_SHIFT)         /* 0xFFFFFFFF */
#define FDCAN_TXBCF_CF            FDCAN_TXBCF_CF_MASK                           /* Cancellation Finished                     */

/* ***************  Bit definition for FDCAN_TXBTIE register  ***************/
#define FDCAN_TXBTIE_TIE_SHIFT    (0U)
#define FDCAN_TXBTIE_TIE_MASK     (0xFFFFFFFFU << FDCAN_TXBTIE_TIE_SHIFT)       /* 0xFFFFFFFF */
#define FDCAN_TXBTIE_TIE          FDCAN_TXBTIE_TIE_MASK                         /* Transmission Interrupt Enable             */

/* ***************  Bit definition for FDCAN_ TXBCIE register  **************/
#define FDCAN_TXBCIE_CF_SHIFT     (0U)
#define FDCAN_TXBCIE_CF_MASK      (0xFFFFFFFFU << FDCAN_TXBCIE_CF_SHIFT)        /* 0xFFFFFFFF */
#define FDCAN_TXBCIE_CF           FDCAN_TXBCIE_CF_MASK                          /* Cancellation Finished Interrupt Enable    */

/* ***************  Bit definition for FDCAN_TXEFS register  ****************/
#define FDCAN_TXEFS_EFFL_SHIFT    (0U)
#define FDCAN_TXEFS_EFFL_MASK     (0x3FU << FDCAN_TXEFS_EFFL_SHIFT)             /* 0x0000003F */
#define FDCAN_TXEFS_EFFL          FDCAN_TXEFS_EFFL_MASK                         /* Event FIFO Fill Level                     */
#define FDCAN_TXEFS_EFGI_SHIFT    (8U)
#define FDCAN_TXEFS_EFGI_MASK     (0x1FU << FDCAN_TXEFS_EFGI_SHIFT)             /* 0x00001F00 */
#define FDCAN_TXEFS_EFGI          FDCAN_TXEFS_EFGI_MASK                         /* Event FIFO Get Index                      */
#define FDCAN_TXEFS_EFPI_SHIFT    (16U)
#define FDCAN_TXEFS_EFPI_MASK     (0x1FU << FDCAN_TXEFS_EFPI_SHIFT)             /* 0x001F0000 */
#define FDCAN_TXEFS_EFPI          FDCAN_TXEFS_EFPI_MASK                         /* Event FIFO Put Index                      */
#define FDCAN_TXEFS_EFF_SHIFT     (24U)
#define FDCAN_TXEFS_EFF_MASK      (0x1U << FDCAN_TXEFS_EFF_SHIFT)               /* 0x01000000 */
#define FDCAN_TXEFS_EFF           FDCAN_TXEFS_EFF_MASK                          /* Event FIFO Full                           */
#define FDCAN_TXEFS_TEFL_SHIFT    (25U)
#define FDCAN_TXEFS_TEFL_MASK     (0x1U << FDCAN_TXEFS_TEFL_SHIFT)              /* 0x02000000 */
#define FDCAN_TXEFS_TEFL          FDCAN_TXEFS_TEFL_MASK                         /* Tx Event FIFO Element Lost                */

/* ***************  Bit definition for FDCAN_TXEFA register  ****************/
#define FDCAN_TXEFA_EFAI_SHIFT    (0U)
#define FDCAN_TXEFA_EFAI_MASK     (0x1FU << FDCAN_TXEFA_EFAI_SHIFT)             /* 0x0000001F */
#define FDCAN_TXEFA_EFAI          FDCAN_TXEFA_EFAI_MASK                         /* Event FIFO Acknowledge Index              */

/* ***************  Bit definition for FDCAN_CKDIV register  ****************/
#define FDCAN_CKDIV_PDIV_SHIFT    (0U)
#define FDCAN_CKDIV_PDIV_MASK     (0xFU << FDCAN_CKDIV_PDIV_SHIFT)              /* 0x0000000F */
#define FDCAN_CKDIV_PDIV          FDCAN_CKDIV_PDIV_MASK                         /* Input Clock Divider */


#endif /* __ARCH_ARM_SRC_STM32H7_HARDWARE_STM32_FDCAN_H */
