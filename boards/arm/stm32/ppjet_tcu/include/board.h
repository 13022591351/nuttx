/****************************************************************************
 * boards/arm/stm32/b-g431b-esc1/include/board.h
 *
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.  The
 *  ASF licenses this file to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance with the
 *  License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 *  License for the specific language governing permissions and limitations
 *  under the License.
 *
 ****************************************************************************/

#pragma once

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clocking *****************************************************************/

#define STM32_BOARD_XTAL               8000000ul           /* 8MHz */

#define STM32_HSI_FREQUENCY            16000000ul          /* 16MHz */
#define STM32_LSI_FREQUENCY            32000               /* 32kHz */
#define STM32_HSE_FREQUENCY            STM32_BOARD_XTAL    /* 8MHz on board */
#undef  STM32_LSE_FREQUENCY                                /* Not available on this board */

/* Main PLL Configuration.
 *
 * PLL source is HSE = 8MHz
 * PLLN = 40, PLLM = 1, PLLP = 10, PLLQ = 2, PLLR = 2
 *
 * f(VCO Clock) = f(PLL Clock Input) x (PLLN / PLLM)
 * f(PLL_P) = f(VCO Clock) / PLLP
 * f(PLL_Q) = f(VCO Clock) / PLLQ
 * f(PLL_R) = f(VCO Clock) / PLLR
 *
 * Where:
 * 8 <= PLLN <= 127
 * 1 <= PLLM <= 16
 * PLLP = 2 through 31
 * PLLQ = 2, 4, 6, or 8
 * PLLR = 2, 4, 6, or 8
 *
 * Do not exceed 170MHz on f(PLL_P), f(PLL_Q), or f(PLL_R).
 * 64MHz <= f(VCO Clock) <= 344MHz.
 *
 * Given the above:
 *
 * f(VCO Clock) = HSE   x PLLN / PLLM
 *              = 8MHz x 85   / 2
 *              = 340MHz
 *
 * PLLPCLK      = f(VCO Clock) / PLLP
 *              = 340MHz       / 10
 *              = 34MHz
 *                (May be used for ADC)
 *
 * PLLQCLK      = f(VCO Clock) / PLLQ
 *              = 340MHz       / 2
 *              = 170MHz
 *                (May be used for QUADSPI, FDCAN, SAI1, I2S3. If set to
 *                48MHz, may be used for USB, RNG.)
 *
 * PLLRCLK      = f(VCO Clock) / PLLR
 *              = 340MHz       / 2
 *              = 170MHz
 *                (May be used for SYSCLK and most peripherals.)
 */

#define STM32_PLLCFGR_PLLSRC           RCC_PLLCFGR_PLLSRC_HSE
#define STM32_PLLCFGR_PLLCFG           (RCC_PLLCFGR_PLLPEN | \
                                       RCC_PLLCFGR_PLLQEN | \
                                       RCC_PLLCFGR_PLLREN)

#define STM32_PLLCFGR_PLLN             RCC_PLLCFGR_PLLN(85)
#define STM32_PLLCFGR_PLLM             RCC_PLLCFGR_PLLM(2)
#define STM32_PLLCFGR_PLLP             RCC_PLLCFGR_PLLPDIV(10)
#define STM32_PLLCFGR_PLLQ             RCC_PLLCFGR_PLLQ_2
#define STM32_PLLCFGR_PLLR             RCC_PLLCFGR_PLLR_2

#define STM32_VCO_FREQUENCY            ((STM32_HSE_FREQUENCY / 2) * 85)
#define STM32_PLLP_FREQUENCY           (STM32_VCO_FREQUENCY / 10)
#define STM32_PLLQ_FREQUENCY           (STM32_VCO_FREQUENCY / 2)
#define STM32_PLLR_FREQUENCY           (STM32_VCO_FREQUENCY / 2)

/* Use the PLL and set the SYSCLK source to be PLLR (160MHz) */

#define STM32_SYSCLK_SW                RCC_CFGR_SW_PLL
#define STM32_SYSCLK_SWS               RCC_CFGR_SWS_PLL

#define STM32_SYSCLK_FREQUENCY         170000000ul

/* AHB clock (HCLK) is SYSCLK (160MHz) */

#define STM32_RCC_CFGR_HPRE            RCC_CFGR_HPRE_SYSCLK
#define STM32_HCLK_FREQUENCY           STM32_SYSCLK_FREQUENCY

/* APB1 clock (PCLK1) is HCLK (160MHz) */

#define STM32_RCC_CFGR_PPRE1           RCC_CFGR_PPRE1_HCLK
#define STM32_PCLK1_FREQUENCY          STM32_HCLK_FREQUENCY

/* APB2 clock (PCLK2) is HCLK (160MHz) */

#define STM32_RCC_CFGR_PPRE2           RCC_CFGR_PPRE2_HCLK
#define STM32_PCLK2_FREQUENCY          STM32_HCLK_FREQUENCY

/* APB2 timers 1, 8, 20 and 15-17 will receive PCLK2. */

/* Timers driven from APB2 will be PCLK2 */

#define STM32_APB2_TIM1_CLKIN   (STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM8_CLKIN   (STM32_PCLK2_FREQUENCY)
#define STM32_APB1_TIM15_CLKIN  (STM32_PCLK2_FREQUENCY)
#define STM32_APB1_TIM16_CLKIN  (STM32_PCLK2_FREQUENCY)
#define STM32_APB1_TIM17_CLKIN  (STM32_PCLK2_FREQUENCY)

/* APB1 timers 2-7 will be twice PCLK1 */

#define STM32_APB1_TIM2_CLKIN   (STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM3_CLKIN   (STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM4_CLKIN   (STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM6_CLKIN   (STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM7_CLKIN   (STM32_PCLK1_FREQUENCY)

/* USB divider -- Divide PLL clock by 1.5 */

#define STM32_CFGR_USBPRE       0

/* Timer Frequencies, if APBx is set to 1, frequency is same to APBx
 * otherwise frequency is 2xAPBx.
 */

#define BOARD_TIM1_FREQUENCY   (STM32_PCLK2_FREQUENCY)
#define BOARD_TIM2_FREQUENCY   (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM3_FREQUENCY   (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM4_FREQUENCY   (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM5_FREQUENCY   (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM6_FREQUENCY   (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM7_FREQUENCY   (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM8_FREQUENCY   (STM32_PCLK2_FREQUENCY)
#define BOARD_TIM15_FREQUENCY  (STM32_PCLK2_FREQUENCY)
#define BOARD_TIM16_FREQUENCY  (STM32_PCLK2_FREQUENCY)
#define BOARD_TIM17_FREQUENCY  (STM32_PCLK2_FREQUENCY)
#define BOARD_TIM20_FREQUENCY  (STM32_PCLK2_FREQUENCY)

#ifdef CONFIG_STM32_FDCAN
    #define STM32_CCIPR_FDCANSRC   (RCC_CCIPR_FDCANSEL_HSE)
    #define STM32_FDCAN_FREQUENCY  (STM32_HSE_FREQUENCY)
#endif

/* LED */

/* USART2 NSH */

#define GPIO_USART3_TX  (GPIO_USART3_TX_3 | GPIO_SPEED_50MHz)   /* PC10 */
#define GPIO_USART3_RX  (GPIO_USART3_RX_3 | GPIO_SPEED_50MHz)   /* PC11 */

/* CAN */

#define GPIO_FDCAN1_RX  (GPIO_FDCAN1_RX_1 | GPIO_SPEED_50MHz)   /* PA11 */
#define GPIO_FDCAN1_TX  (GPIO_FDCAN1_TX_1 | GPIO_SPEED_50MHz)   /* PA12 */

/* SPI1 */

#define GPIO_SPI1_SCK   (GPIO_SPI1_SCK_2  | GPIO_SPEED_50MHz)   /* PB03 */
#define GPIO_SPI1_MISO  (GPIO_SPI1_MISO_2 | GPIO_SPEED_50MHz)   /* PB04 */
#define GPIO_SPI1_MOSI  (GPIO_SPI1_MOSI_2 | GPIO_SPEED_50MHz)   /* PB05 */

/* SPI2 */

#define GPIO_SPI2_SCK   (GPIO_SPI2_SCK_1  | GPIO_SPEED_50MHz)   /* PB13 */
#define GPIO_SPI2_MISO  (GPIO_SPI2_MISO_2 | GPIO_SPEED_50MHz)   /* PB14 */

/* I2C */

#define GPIO_I2C2_SCL   (GPIO_I2C2_SCL_1  | GPIO_SPEED_50MHz)   /* PA09 */
#define GPIO_I2C2_SDA   (GPIO_I2C2_SDA_1  | GPIO_SPEED_50MHz)   /* PA08 */

/* TIM3 */

#define GPIO_TIM3_CH1OUT   (GPIO_TIM3_CH1OUT_1 | GPIO_SPEED_50MHz)  /* PA06 */

#define STM32_TIM3_TRGO     ATIM_CR2_MMS_OC2REF

/* TIM4 */

#define GPIO_TIM4_CH1OUT   (GPIO_TIM4_CH1OUT_2 | GPIO_SPEED_50MHz)  /* PB06 */
#define GPIO_TIM4_CH2OUT   (GPIO_TIM4_CH2OUT_2 | GPIO_SPEED_50MHz)  /* PB07 */

/* TIM8 */

#define GPIO_TIM8_CH1OUT   (GPIO_TIM8_CH1OUT_3 | GPIO_SPEED_50MHz)  /* PC06 */

#define STM32_TIM8_TRGO     ATIM_CR2_MMS_OC2REF

/* ADC1 */

#define GPIO_ADC1_IN12      GPIO_ADC1_IN12_0    /* PB01 */
#define GPIO_ADC1_IN14      GPIO_ADC1_IN14_0    /* PB11 */
#define GPIO_ADC1_IN15      GPIO_ADC1_IN15_0    /* PB00 */

/* ADC1 DMA */

#define ADC1_DMA_CHAN       DMAMAP_DMA12_ADC1_0

/* ADC2 */

#define GPIO_ADC2_IN14      GPIO_ADC2_IN14_0    /* PB11 */
#define GPIO_ADC2_IN17      GPIO_ADC2_IN17_0    /* PA04 */

/* ADC2 DMA */

#define ADC1_DMA_CHAN       DMAMAP_DMA12_ADC2_0
