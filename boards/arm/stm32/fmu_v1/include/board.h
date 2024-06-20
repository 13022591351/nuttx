#ifndef __BOARDS_ARM_STM32_FMUV1_INCLUDE_BOARD_H
#define __BOARDS_ARM_STM32_FMUV1_INCLUDE_BOARD_H

#include <nuttx/config.h>

#ifndef __ASSEMBLY__
#  include <stdint.h>
#  include <stdbool.h>
#endif

/* Clocking *****************************************************************/

/* The STM32F4 Discovery board features a single 8MHz crystal.
 * Space is provided for a 32kHz RTC backup crystal, but it is not stuffed.
 *
 * This is the canonical configuration:
 *   System Clock source           : PLL (HSE)
 *   SYSCLK(Hz)                    : 168000000    Determined by PLL
 *                                                configuration
 *   HCLK(Hz)                      : 168000000    (STM32_RCC_CFGR_HPRE)
 *   AHB Prescaler                 : 1            (STM32_RCC_CFGR_HPRE)
 *   APB1 Prescaler                : 4            (STM32_RCC_CFGR_PPRE1)
 *   APB2 Prescaler                : 2            (STM32_RCC_CFGR_PPRE2)
 *   HSE Frequency(Hz)             : 8000000      (STM32_BOARD_XTAL)
 *   PLLM                          : 8            (STM32_PLLCFG_PLLM)
 *   PLLN                          : 336          (STM32_PLLCFG_PLLN)
 *   PLLP                          : 2            (STM32_PLLCFG_PLLP)
 *   PLLQ                          : 7            (STM32_PLLCFG_PLLQ)
 *   Main regulator output voltage : Scale1 mode  Needed for high speed
 *                                                SYSCLK
 *   Flash Latency(WS)             : 5
 *   Prefetch Buffer               : OFF
 *   Instruction cache             : ON
 *   Data cache                    : ON
 *   Require 48MHz for USB OTG FS, : Enabled
 *   SDIO and RNG clock
 */

/* HSI - 16 MHz RC factory-trimmed
 * LSI - 32 KHz RC
 * HSE - On-board crystal frequency is 8MHz
 * LSE - 32.768 kHz
 */

#define STM32_BOARD_XTAL        8000000ul

#define STM32_HSI_FREQUENCY     16000000ul
#define STM32_LSI_FREQUENCY     32000
#define STM32_HSE_FREQUENCY     STM32_BOARD_XTAL
#define STM32_LSE_FREQUENCY     32768

/* Main PLL Configuration.
 *
 * PLL source is HSE
 * PLL_VCO = (STM32_HSE_FREQUENCY / PLLM) * PLLN
 *         = (8,000,000 / 8) * 336
 *         = 336,000,000
 * SYSCLK  = PLL_VCO / PLLP
 *         = 336,000,000 / 2 = 168,000,000
 * USB OTG FS, SDIO and RNG Clock
 *         =  PLL_VCO / PLLQ
 *         = 48,000,000
 */

#define STM32_PLLCFG_PLLM       RCC_PLLCFG_PLLM(8)
#define STM32_PLLCFG_PLLN       RCC_PLLCFG_PLLN(336)
#define STM32_PLLCFG_PLLP       RCC_PLLCFG_PLLP_2
#define STM32_PLLCFG_PLLQ       RCC_PLLCFG_PLLQ(7)

#define STM32_SYSCLK_FREQUENCY  168000000ul

/* AHB clock (HCLK) is SYSCLK (168MHz) */

#define STM32_RCC_CFGR_HPRE     RCC_CFGR_HPRE_SYSCLK  /* HCLK  = SYSCLK / 1 */
#define STM32_HCLK_FREQUENCY    STM32_SYSCLK_FREQUENCY

/* APB1 clock (PCLK1) is HCLK/4 (42MHz) */

#define STM32_RCC_CFGR_PPRE1    RCC_CFGR_PPRE1_HCLKd4     /* PCLK1 = HCLK / 4 */
#define STM32_PCLK1_FREQUENCY   (STM32_HCLK_FREQUENCY/4)

/* Timers driven from APB1 will be twice PCLK1 */

#define STM32_APB1_TIM2_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM3_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM4_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM5_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM6_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM7_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM12_CLKIN  (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM13_CLKIN  (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM14_CLKIN  (2*STM32_PCLK1_FREQUENCY)

/* APB2 clock (PCLK2) is HCLK/2 (84MHz) */

#define STM32_RCC_CFGR_PPRE2    RCC_CFGR_PPRE2_HCLKd2     /* PCLK2 = HCLK / 2 */
#define STM32_PCLK2_FREQUENCY   (STM32_HCLK_FREQUENCY/2)

/* Timers driven from APB2 will be twice PCLK2 */

#define STM32_APB2_TIM1_CLKIN   (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM8_CLKIN   (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM9_CLKIN   (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM10_CLKIN  (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM11_CLKIN  (2*STM32_PCLK2_FREQUENCY)

/* Timer Frequencies, if APBx is set to 1, frequency is same to APBx
 * otherwise frequency is 2xAPBx.
 * Note: TIM1,8 are on APB2, others on APB1
 */

#define BOARD_TIM1_FREQUENCY    STM32_HCLK_FREQUENCY
#define BOARD_TIM2_FREQUENCY    (STM32_HCLK_FREQUENCY / 2)
#define BOARD_TIM3_FREQUENCY    (STM32_HCLK_FREQUENCY / 2)
#define BOARD_TIM4_FREQUENCY    (STM32_HCLK_FREQUENCY / 2)
#define BOARD_TIM5_FREQUENCY    (STM32_HCLK_FREQUENCY / 2)
#define BOARD_TIM6_FREQUENCY    (STM32_HCLK_FREQUENCY / 2)
#define BOARD_TIM7_FREQUENCY    (STM32_HCLK_FREQUENCY / 2)
#define BOARD_TIM8_FREQUENCY    STM32_HCLK_FREQUENCY

/* SDIO dividers.  Note that slower clocking is required when DMA is disabled
 * in order to avoid RX overrun/TX underrun errors due to delayed responses
 * to service FIFOs in interrupt driven mode.  These values have not been
 * tuned!!!
 *
 * SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(118+2)=400 KHz
 */

#define SDIO_INIT_CLKDIV        (118 << SDIO_CLKCR_CLKDIV_SHIFT)

/* DMA ON:  SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(1+2)=16 MHz
 * DMA OFF: SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(2+2)=12 MHz
 */

#ifdef CONFIG_SDIO_DMA
#  define SDIO_MMCXFR_CLKDIV    (1 << SDIO_CLKCR_CLKDIV_SHIFT)
#else
#  define SDIO_MMCXFR_CLKDIV    (2 << SDIO_CLKCR_CLKDIV_SHIFT)
#endif

/* DMA ON:  SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(1+2)=16 MHz
 * DMA OFF: SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(2+2)=12 MHz
 */

#ifdef CONFIG_SDIO_DMA
#  define SDIO_SDXFR_CLKDIV     (1 << SDIO_CLKCR_CLKDIV_SHIFT)
#else
#  define SDIO_SDXFR_CLKDIV     (2 << SDIO_CLKCR_CLKDIV_SHIFT)
#endif

/* LED definitions **********************************************************/
/* LED index values for use with board_userled() */

#define BOARD_LED1        0
#define BOARD_LED2        1
#define BOARD_NLEDS       2

/* LED bits for use with board_userled_all() */

#define BOARD_LED1_BIT    (1 << BOARD_LED1)
#define BOARD_LED2_BIT    (1 << BOARD_LED2)

/* PWM */

#define GPIO_TIM1_CH1OUT  GPIO_TIM1_CH1OUT_2
#define GPIO_TIM1_CH2OUT  GPIO_TIM1_CH2OUT_2
#define GPIO_TIM1_CH3OUT  GPIO_TIM1_CH3OUT_2
#define GPIO_TIM1_CH4OUT  GPIO_TIM1_CH4OUT_2

#define GPIO_TIM2_CH1OUT  GPIO_TIM2_CH1OUT_3
#define GPIO_TIM2_CH2OUT  GPIO_TIM2_CH2OUT_2
#define GPIO_TIM2_CH3OUT  GPIO_TIM2_CH3OUT_2
#define GPIO_TIM2_CH4OUT  GPIO_TIM2_CH4OUT_2

#define GPIO_TIM8_CH1OUT  GPIO_TIM8_CH1OUT_2
#define GPIO_TIM8_CH2OUT  GPIO_TIM8_CH2OUT_2
#define GPIO_TIM8_CH3OUT  GPIO_TIM8_CH3OUT_2
#define GPIO_TIM8_CH4OUT  GPIO_TIM8_CH4OUT_2


/* USART1 RS232
 *
 * ---------- -------------
 * PIO        SIGNAL       
 * ---------- -------------
 * PA10       USART1_RX
 * PA9        USART1_TX
 * ---------- -------------
 */

#define GPIO_USART1_RX    GPIO_USART1_RX_1
#define GPIO_USART1_TX    GPIO_USART1_TX_1

/* USART1 DMA */

#define DMAMAP_USART1_RX  DMAMAP_USART1_RX_1
// #define DMAMAP_USART1_TX  DMAMAP_USART1_TX

/* USART2 FMU
 *
 * ---------- -------------
 * PIO        SIGNAL       
 * ---------- -------------
 * PD6        USART2_RX
 * PD5        USART2_TX
 * ---------- -------------
 */

#define GPIO_USART2_RX    GPIO_USART2_RX_2
#define GPIO_USART2_TX    GPIO_USART2_TX_2

/* USART2 DMA */

// #define DMAMAP_USART2_RX  DMAMAP_USART2_RX
// #define DMAMAP_USART2_TX  DMAMAP_USART2_TX

/* USART3 UM982
 *
 * ---------- -------------
 * PIO        SIGNAL       
 * ---------- -------------
 * PD9        USART3_RX
 * PD8        USART3_TX
 * ---------- -------------
 */

#define GPIO_USART3_RX    GPIO_USART3_RX_3
#define GPIO_USART3_TX    GPIO_USART3_TX_3

/* USART3 DMA */

// #define DMAMAP_USART3_RX  DMAMAP_USART3_RX

/* USART6 RS422
 *
 * ---------- -------------
 * PIO        SIGNAL       
 * ---------- -------------
 * PC7        USART6_RX
 * PC6        USART6_TX
 * ---------- -------------
 */

#define GPIO_USART6_RX    GPIO_USART6_RX_1
#define GPIO_USART6_TX    GPIO_USART6_TX_1

/* USART6 DMA */

#define DMAMAP_USART6_RX  DMAMAP_USART6_RX_1
#define DMAMAP_USART6_TX  DMAMAP_USART6_TX_1

/* CAN1
 *
 * ---------- -------------
 * PIO        SIGNAL       
 * ---------- -------------
 * PB8        CAN1_RX
 * PB9        CAN1_TX
 * ---------- -------------
 */

#define GPIO_CAN1_RX      GPIO_CAN1_RX_2    /* PB8 */
#define GPIO_CAN1_TX      GPIO_CAN1_TX_2    /* PB9 */

/* CAN2
 *
 * ---------- -------------
 * PIO        SIGNAL       
 * ---------- -------------
 * PB5        CAN2_RX
 * PB6        CAN2_TX
 * ---------- -------------
 */

#define GPIO_CAN2_RX      GPIO_CAN2_RX_2    /* PB5 */
#define GPIO_CAN2_TX      GPIO_CAN2_TX_2    /* PB6 */

/* SPI2 */

#define GPIO_SPI2_MISO    GPIO_SPI2_MISO_1
#define GPIO_SPI2_MOSI    GPIO_SPI2_MOSI_1
#define GPIO_SPI2_SCK     GPIO_SPI2_SCK_2

/* SPI2 DMA */

#define DMACHAN_SPI2_RX   DMAMAP_SPI2_RX
#define DMACHAN_SPI2_TX   DMAMAP_SPI2_TX

/* Ethernet */

#if defined(CONFIG_STM32_ETHMAC)
  /* RMII interface to the LAN8720 PHY */

#  ifndef CONFIG_STM32_RMII
#    error CONFIG_STM32_RMII must be defined
#  endif

  /* Clocking is provided by an external 25Mhz XTAL */

#  ifndef CONFIG_STM32_RMII_EXTCLK
#    error CONFIG_STM32_RMII_EXTCLK must be defined
#  endif

  /* Pin disambiguation */

#  define GPIO_ETH_RMII_TX_EN GPIO_ETH_RMII_TX_EN_2
#  define GPIO_ETH_RMII_TXD0  GPIO_ETH_RMII_TXD0_2
#  define GPIO_ETH_RMII_TXD1  GPIO_ETH_RMII_TXD1_2
#  define GPIO_ETH_PPS_OUT    GPIO_ETH_PPS_OUT_2

#endif

/* SDIO DMA */

#define DMAMAP_SDIO DMAMAP_SDIO_1

#endif /* __BOARDS_ARM_STM32_FMUV1_INCLUDE_BOARD_H */
