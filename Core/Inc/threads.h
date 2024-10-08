#ifndef THREADS_H
#define THREADS_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "main.h"
#include "CH446Q.h"
#include "NetManager.h"
#include "driver_ina219.h"
#include "2812_driver.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "ADC/DRP.h"
#include "DAC/dac_cs.h"
#include "RELAY/relay.h"
#include "lcd_7789.h"
#include "lcd_init.h"    
int Threads_Init(void);
void MatrixControl_Entry(void *parameter);
void CurrentSensor_Entry(void *parameter);
void receive_data_Entry(void *parameter);
void ADDAControl_Entry(void *parameter);
static rt_device_t serial;
#define serial			rt_device_find("uart1")
#endif