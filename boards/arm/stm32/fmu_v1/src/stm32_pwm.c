/****************************************************************************
 * boards/arm/stm32/stm32f4discovery/src/stm32_pwm.c
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

#include <errno.h>
#include <debug.h>

#include <nuttx/timers/pwm.h>
#include <arch/board/board.h>

#include "chip.h"
#include "arm_internal.h"
#include "stm32_pwm.h"
#include "fmu_v1.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_pwm_setup
 *
 * Description:
 *   Initialize PWM and register the PWM device.
 *
 ****************************************************************************/

int stm32_pwm_setup(void) {
  static bool initialized = false;
  struct pwm_lowerhalf_s *pwm1;
  struct pwm_lowerhalf_s *pwm2;
  struct pwm_lowerhalf_s *pwm8;
  int ret;

  if (!initialized) {
    pwm1 = stm32_pwminitialize(1);
    if (!pwm1) {
      aerr("ERROR: Failed to get the STM32 TIM1 PWM lower half\n");
      return -ENODEV;
    }

    ret = pwm_register("/dev/pwm1", pwm1);
    if (ret < 0) {
      aerr("ERROR: pwm_register failed: %d\n", ret);
      return ret;
    }

    pwm2 = stm32_pwminitialize(2);
    if (!pwm2) {
      aerr("ERROR: Failed to get the STM32 TIM2 PWM lower half\n");
      return -ENODEV;
    }

    ret = pwm_register("/dev/pwm2", pwm2);
    if (ret < 0) {
      aerr("ERROR: pwm_register failed: %d\n", ret);
      return ret;
    }

    pwm8 = stm32_pwminitialize(8);
    if (!pwm8) {
      aerr("ERROR: Failed to get the STM32 TIM8 PWM lower half\n");
      return -ENODEV;
    }

    ret = pwm_register("/dev/pwm8", pwm8);
    if (ret < 0) {
      aerr("ERROR: pwm_register failed: %d\n", ret);
      return ret;
    }

    initialized = true;
  }

  return OK;
}
