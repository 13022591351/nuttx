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

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/spi/spi.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "chip.h"
#include "stm32.h"

#include "fmu_v1.h"

#if defined(CONFIG_STM32_SPI1) || defined(CONFIG_STM32_SPI2) || defined(CONFIG_STM32_SPI3)

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_spidev_initialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the stm32f4discovery
 *   board.
 *
 ****************************************************************************/

void weak_function stm32_spidev_initialize(void)
{
  stm32_configgpio(GPIO_AD7689_0_CS);
  stm32_configgpio(GPIO_AD7689_1_CS);
  stm32_configgpio(GPIO_AD7689_2_CS);
}

#ifdef CONFIG_STM32_SPI2
void stm32_spi2select(struct spi_dev_s *dev, uint32_t devid, bool selected)
{
  spiinfo("devid: %d CS: %s\n", (int)devid, selected ? "assert" : "de-assert");

  if (devid == SPIDEV_ADC(0))
  {
    stm32_gpiowrite(GPIO_AD7689_0_CS, !selected);
  }

  if (devid == SPIDEV_ADC(1))
  {
    stm32_gpiowrite(GPIO_AD7689_1_CS, !selected);
  }

  if (devid == SPIDEV_ADC(2))
  {
    stm32_gpiowrite(GPIO_AD7689_2_CS, !selected);
  }
}

uint8_t stm32_spi2status(struct spi_dev_s *dev, uint32_t devid)
{
  uint8_t ret = 0;
  return ret;
}
#endif

#endif /* CONFIG_STM32_SPI1 || CONFIG_STM32_SPI2 */
