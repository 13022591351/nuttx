/****************************************************************************
 * boards/arm/stm32h7/weact-stm32h743/src/weact-stm32h743.h
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

#ifndef __BOARDS_ARM_STM32H7_LINK_D20_SRC_LINK_D20_H
#define __BOARDS_ARM_STM32H7_LINK_D20_SRC_LINK_D20_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* procfs File System */

#ifdef CONFIG_FS_PROCFS
#  ifdef CONFIG_NSH_PROC_MOUNTPOINT
#    define STM32_PROCFS_MOUNTPOINT CONFIG_NSH_PROC_MOUNTPOINT
#  else
#    define STM32_PROCFS_MOUNTPOINT "/proc"
#  endif
#endif

/* GPIO pins used by the GPIO Subsystem */

#define BOARD_NGPIOIN     2 /* Amount of GPIO Input pins */
#define BOARD_NGPIOOUT    6 /* Amount of GPIO Output pins */

/* GPO LED */

#define GPO_LED1    (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | GPIO_OUTPUT_CLEAR | GPIO_PORTD | GPIO_PIN8 )
#define GPO_LED2    (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | GPIO_OUTPUT_CLEAR | GPIO_PORTD | GPIO_PIN9 )
#define GPO_LED3    (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | GPIO_OUTPUT_CLEAR | GPIO_PORTD | GPIO_PIN10)
#define GPO_LED4    (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | GPIO_OUTPUT_CLEAR | GPIO_PORTD | GPIO_PIN11)
#define GPO_LED5    (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | GPIO_OUTPUT_CLEAR | GPIO_PORTD | GPIO_PIN12)
#define GPO_LED6    (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | GPIO_OUTPUT_CLEAR | GPIO_PORTD | GPIO_PIN13)

/* GPI CX6602 */

#define GPI_IO1     (GPIO_INPUT | GPIO_FLOAT | GPIO_SPEED_50MHz | GPIO_PORTE | GPIO_PIN3 )
#define GPI_IO3     (GPIO_INPUT | GPIO_FLOAT | GPIO_SPEED_50MHz | GPIO_PORTE | GPIO_PIN2 )

/* ETHMAC nRST */

#if defined(CONFIG_STM32H7_ETHMAC)
#  define GPIO_EMAC_NRST    (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | GPIO_OUTPUT_SET | GPIO_PORTE | GPIO_PIN13)
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y :
 *     Called from board_late_initialize().
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=n && CONFIG_BOARDCTL=y &&
 *   CONFIG_NSH_ARCHINIT:
 *     Called from the NSH library
 *
 ****************************************************************************/

int stm32_bringup(void);

/****************************************************************************
 * Name: stm32_gpio_initialize
 *
 * Description:
 *   Initialize GPIO-Driver.
 *
 ****************************************************************************/

#if defined(CONFIG_DEV_GPIO) && !defined(CONFIG_GPIO_LOWER_HALF)
int stm32_gpio_initialize(void);
#endif

#endif /* __BOARDS_ARM_STM32H7_LINK_D20_SRC_LINK_D20_H */
