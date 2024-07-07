#ifndef INA219_H
#define INA219_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "driver_ina219.h"

void INA219_Delay_ms(uint32_t ms);
void INA219_Debug_Print(const char *const fmt, ...);
uint8_t INA219_I2C_Init();
uint8_t INA219_I2C_Deinit();
uint8_t INA219_I2C_Read(uint8_t addr,uint8_t reg,uint8_t *buf,uint16_t len);
uint8_t INA219_I2C_Write(uint8_t addr,uint8_t reg,uint8_t *buf,uint16_t len);


#endif