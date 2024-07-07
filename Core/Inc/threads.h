#ifndef THREADS_H
#define THREADS_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "CH446Q.h"
#include "NetManager.h"
#include "driver_ina219.h"
#include "2812_driver.h"

int Threads_Init(void);
void MatrixControl_Entry(void *parameter);
void CurrentSensor_Entry(void *parameter);

#endif