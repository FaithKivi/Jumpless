/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-10-14     Dozingfiretruck   first version
 */
#ifndef __USBD_CONFIG_H__
#define __USBD_CONFIG_H__

#include <rtconfig.h>

#ifdef BSP_USBD_TYPE_HS
#define USBD_IRQ_TYPE     OTG_HS_IRQn
#define USBD_IRQ_HANDLER  OTG_HS_IRQHandler
#define USBD_INSTANCE     USB_OTG_HS
#else
#define USBD_IRQ_TYPE     OTG_FS_IRQn
#define USBD_IRQ_HANDLER  OTG_FS_IRQHandler
#define USBD_INSTANCE     USB_OTG_FS
#endif

#ifdef BSP_USBD_SPEED_HS
#define USBD_PCD_SPEED    PCD_SPEED_HIGH
#elif  BSP_USBD_SPEED_HSINFS
#define USBD_PCD_SPEED    PCD_SPEED_HIGH_IN_FULL
#else
#define USBD_PCD_SPEED    PCD_SPEED_FULL
#endif

#ifdef BSP_USBD_PHY_ULPI
#define USBD_PCD_PHY_MODULE    PCD_PHY_ULPI
#elif  BSP_USBD_PHY_UTMI
#define USBD_PCD_PHY_MODULE    PCD_PHY_UTMI
#else
#define USBD_PCD_PHY_MODULE    PCD_PHY_EMBEDDED
#endif

#endif
