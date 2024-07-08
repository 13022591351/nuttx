/****************************************************************************
 * boards/arm/stm32/stm32f4discovery/src/stm32_spi.c
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

#include "ppjet_tcu.h"

#if defined(CONFIG_STM32_I2C1) || defined(CONFIG_STM32_I2C2) || defined(CONFIG_STM32_I2C3)

static void stm32_i2c_register(int bus)
{
  static struct i2c_master_s *i2c;
  int ret;

  i2c = stm32_i2cbus_initialize(bus);
  if (i2c == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to get I2C%d interface\n", bus);
    }
  else
    {
      ret = i2c_register(i2c, bus);
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to register I2C%d driver: %d\n",
                 bus, ret);
          stm32_i2cbus_uninitialize(i2c);
        }
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void stm32_i2cdev_initialize(void)
{
#if defined(CONFIG_STM32_I2C2)
  stm32_i2c_register(2);
#endif
}

#endif /* CONFIG_STM32_I2C1 || CONFIG_STM32_I2C2 || CONFIG_STM32_I2C3 */
