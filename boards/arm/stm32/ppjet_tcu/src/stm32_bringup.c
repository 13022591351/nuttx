/****************************************************************************
 * boards/arm/stm32/b-g431b-esc1/src/stm32_bringup.c
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

#include <sys/types.h>
#include <syslog.h>

#include <nuttx/board.h>
#include <nuttx/fs/fs.h>

#include <stm32.h>

#ifdef CONFIG_SENSORS_MAX31855
#include "stm32_max31855.h"
#endif

#include "ppjet_tcu.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_i2c_register
 *
 * Description:
 *   Register one I2C drivers for the I2C tool.
 *
 ****************************************************************************/

// #if defined(CONFIG_STM32_I2C1) || defined(CONFIG_STM32_I2C2) || defined(CONFIG_STM32_I2C3)

// static void stm32_i2c_register(int bus)
// {
//   struct i2c_master_s *i2c;
//   int ret;

//   i2c = stm32_i2cbus_initialize(bus);
//   if (i2c == NULL)
//     {
//       syslog(LOG_ERR, "ERROR: Failed to get I2C%d interface\n", bus);
//     }
//   else
//     {
//       ret = i2c_register(i2c, bus);
//       if (ret < 0)
//         {
//           syslog(LOG_ERR, "ERROR: Failed to register I2C%d driver: %d\n",
//                  bus, ret);
//           stm32_i2cbus_uninitialize(i2c);
//         }
//     }
// }

// #endif

/****************************************************************************
 * Name: stm32_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y :
 *     Called from board_late_initialize().
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=n && CONFIG_BOARDCTL=y :
 *     Called from the NSH library
 *
 ****************************************************************************/

int stm32_bringup(void)
{
  int ret;

#ifdef CONFIG_FS_PROCFS
  /* Mount the procfs file system */

  ret = nx_mount(NULL, STM32_PROCFS_MOUNTPOINT, "procfs", 0, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR,
             "ERROR: Failed to mount the PROC filesystem: %d\n",  ret);
    }
#endif /* CONFIG_FS_PROCFS */

#if defined(CONFIG_STM32_I2C1) || defined(CONFIG_STM32_I2C2) || defined(CONFIG_STM32_I2C3)

  stm32_i2cdev_initialize();

#endif

#ifdef CONFIG_PWM
  /* Initialize PWM and register the PWM driver. */

  ret = stm32_pwm_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: stm32_pwm_setup failed: %d\n", ret);
    }

#endif

#ifdef CONFIG_ADC
  /* Initialize ADC and register the ADC driver. */

  ret = stm32_adc_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: stm32_adc_setup failed: %d\n", ret);
    }

#endif

#ifdef CONFIG_STM32_FDCAN_CHARDRIVER
  /* Initialize CAN and register the CAN driver. */

  ret = stm32_can_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: stm32_fdcan_setup failed: %d\n", ret);
    }

#endif

#ifdef CONFIG_STM32_FDCAN_SOCKET
  /* Initialize CAN socket interface */

  ret = stm32_cansock_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: stm32_cansock_setup failed: %d\n", ret);
    }

#endif

#ifdef CONFIG_SENSORS_MAX31855
  /* Register device 0 on spi channel 2 */

  ret = board_max31855_initialize(0, 2);
  if (ret < 0)
    {
      serr("ERROR:  stm32_max31855initialize failed: %d\n", ret);
    }

#endif

  UNUSED(ret);
  return OK;
}
