/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-25     zylx         first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "main.h"
#include "lcd_7789.h"
#include "lcd_init.h"              
#define SAMPLE_UART_NAME       "uart1"    /* 串口设备名称 */               /* 串口设备句柄 */
/* defined the LED0 pin: PE3 */

#define LED0_PIN    GET_PIN(D, 2)

int main(void)
{

    int count = 1;
	
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
	
    while (count++)
    {		
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}
