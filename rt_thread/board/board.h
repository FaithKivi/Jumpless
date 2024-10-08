/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 * 2020-8-6       NU-LL        Add stm32h750vbt6 support
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <stm32h7xx.h>
#include "drv_common.h"
#include "drv_gpio.h"
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RT_SOFT_I2C1_SCL_PIN GET_PIN(B, 6)
#define RT_SOFT_I2C1_SDA_PIN GET_PIN(B, 5)
#define RT_SOFT_I2C1_BUS_NAME "i2c1"
#define RT_SOFT_I2C1_TIMING_DELAY 10
#define RT_SOFT_I2C1_TIMING_TIMEOUT 99

/*-------------------------- CHIP CONFIG BEGIN --------------------------*/

#define CHIP_FAMILY_STM32
#define CHIP_SERIES_STM32H7
#define CHIP_NAME_STM32H750XBHX

/*-------------------------- CHIP CONFIG END --------------------------*/

/*-------------------------- ROM/RAM CONFIG BEGIN --------------------------*/
#define ROM_START              ((uint32_t)0x80000000)
#define ROM_SIZE               (128)
#define ROM_END                ((uint32_t)(ROM_START + ROM_SIZE * 1024))

#define RAM_START              (0x24000000)//DTCM_region
#define RAM_SIZE               (512)
#define RAM_END                (RAM_START + RAM_SIZE * 1024)

/*-------------------------- ROM/RAM CONFIG END --------------------------*/

/*-------------------------- CLOCK CONFIG BEGIN --------------------------*/

#define BSP_CLOCK_SOURCE                  ("HSE")
#define BSP_CLOCK_SOURCE_FREQ_MHZ         ((int32_t)0)
#define BSP_CLOCK_SYSTEM_FREQ_MHZ         ((int32_t)480)

/*-------------------------- CLOCK CONFIG END --------------------------*/

/*-------------------------- UART CONFIG BEGIN --------------------------*/

/** After configuring corresponding UART or UART DMA, you can use it.
 *
 * STEP 1, define macro define related to the serial port opening based on the serial port number
 *                 such as     #define BSP_USING_UATR1
 *
 * STEP 2, according to the corresponding pin of serial port, define the related serial port information macro
 *                 such as     #define BSP_UART1_TX_PIN       "PA9"
 *                             #define BSP_UART1_RX_PIN       "PA10"
 *
 * STEP 3, if you want using SERIAL DMA, you must open it in the RT-Thread Settings.
 *                 RT-Thread Setting -> Components -> Device Drivers -> Serial Device Drivers -> Enable Serial DMA Mode
 *
 * STEP 4, according to serial port number to define serial port tx/rx DMA function in the board.h file
 *                 such as     #define BSP_UART1_RX_USING_DMA
 *
 */
#define BSP_USING_UART1
#define UART1_TX_PORT       GPIOA
#define UART1_RX_PORT       GPIOA
#define UART1_TX_PIN        GPIO_PIN_9
#define UART1_RX_PIN        GPIO_PIN_10
#define BSP_UART1_RX_BUFSIZE   256
#define BSP_UART1_TX_BUFSIZE   256

#define BSP_USING_UART4
#define BSP_UART4_RX_BUFSIZE   256
#define BSP_UART4_TX_BUFSIZE   256

#define STM32_FLASH_START_ADRESS       ROM_START
#define STM32_FLASH_SIZE               ROM_SIZE
#define STM32_FLASH_END_ADDRESS        ROM_END

#define STM32_SRAM_SIZE                RAM_SIZE
#define STM32_SRAM_START               RAM_START
#define STM32_SRAM_END                 RAM_END

#if defined(BSP_USING_UART4)
#define UART4_TX_PORT       GPIOA
#define UART4_RX_PORT       GPIOA
#define UART4_TX_PIN        GPIO_PIN_12
#define UART4_RX_PIN        GPIO_PIN_11
#endif
#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      (&__bss_end)
#endif

#define HEAP_END        STM32_SRAM_END


void SystemClock_Config(void);
void MX_DMA_Init(void);
void MX_TIM1_Init(void);
void MX_ADC1_Init(void);
void MX_ADC2_Init(void);
void MX_DAC1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM6_Init(void);
void MX_LPTIM1_Init(void);
void MX_LPTIM2_Init(void);
#ifdef __cplusplus
}
#endif

#endif
