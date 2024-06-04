/****************************************************************************
 * boards/arm/stm32/stm32f4discovery/src/stm32_bringup.c
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

#include <stdbool.h>
#include <stdio.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/fs/fs.h>

#ifdef CONFIG_USERLED
#  include <nuttx/leds/userled.h>
#endif

#ifdef CONFIG_USBMONITOR
#include <nuttx/usb/usbmonitor.h>
#endif

#include "stm32.h"

#include "fmu_v1.h"

/****************************************************************************
 * Public Functions
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
 *   CONFIG_BOARD_LATE_INITIALIZE=n && CONFIG_BOARDCTL=y :
 *     Called from the NSH library
 *
 ****************************************************************************/

int stm32_bringup(void) {
    int ret = OK;

#if defined(CONFIG_FAT_DMAMEMORY)

    if (stm32_dma_alloc_init() < 0) {
        syslog(LOG_ERR, "DMA alloc FAILED");
    }

#endif

#ifdef HAVE_SDIO

    ret = stm32_sdio_initialize();
    if (ret != OK) {
        ferr("ERROR: Failed to initialize MMC/SD driver: %d\n", ret);
        return ret;
    }

#endif

#ifdef CONFIG_FS_PROCFS

    ret = nx_mount(NULL, STM32_PROCFS_MOUNTPOINT, "procfs", 0, NULL);
    if (ret < 0) {
        serr("ERROR: Failed to mount procfs at %s: %d\n",
        STM32_PROCFS_MOUNTPOINT, ret);
    }

#endif

#ifdef HAVE_SDIO

    ret = nx_mount("/dev/mmcsd0", "/mnt/sd0", "vfat", 0, NULL);
    if (ret < 0) {
        ret = nx_mount("/dev/mmcsd0", "/mnt/sd0", "vfat", 0, "forceformat");
        if (ret < 0) {
            ferr("ERROR: Failed to mount the SD card: %d\n", ret);
            return ret;
        }
    }

#endif

#ifdef CONFIG_USERLED

    ret = userled_lower_initialize("/dev/userleds");
    if (ret < 0) {
        syslog(LOG_ERR, "ERROR: userled_lower_initialize() failed: %d\n", ret);
    }

#endif


#ifdef CONFIG_PWM

    ret = stm32_pwm_setup();
    if (ret < 0) {
        syslog(LOG_ERR, "ERROR: stm32_pwm_setup() failed: %d\n", ret);
    }

#endif

#ifdef CONFIG_CAPTURE

    ret = stm32_capture_setup();
    if (ret < 0) {
        syslog(LOG_ERR, "ERROR: stm32_capture_setup failed: %d\n", ret);
        return ret;
    }

#endif

    return ret;
}
