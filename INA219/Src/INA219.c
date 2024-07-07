#include "INA219.h"

struct ina219_handle_s Sensor_1 = {
    0x40,
    INA219_I2C_Init,
    INA219_I2C_Deinit,
    INA219_I2C_Read,
    INA219_I2C_Write,
    INA219_Delay_ms,
    INA219_Debug_Print,
    2.0
};

struct ina219_handle_s Sensor_2 = {
    0x41,
    INA219_I2C_Init,
    INA219_I2C_Deinit,
    INA219_I2C_Read,
    INA219_I2C_Write,
    INA219_Delay_ms,
    INA219_Debug_Print,
    2.0
};

void INA219_Delay_ms(uint32_t ms)
{
    rt_thread_mdelay((rt_int32_t)ms);
}

void INA219_Debug_Print(const char *const fmt, ...)
{
    rt_kprintf(fmt);
}

uint8_t INA219_I2C_Init()
{
    return 0;
}

uint8_t INA219_I2C_Deinit()
{
    return 0;
}

uint8_t INA219_I2C_Read(uint8_t addr,uint8_t reg,uint8_t *buf,uint16_t len)
{
    struct rt_i2c_bus_device *i2c_bus;
    struct rt_i2c_msg msgs;

    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find("i2c1");
    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find i2c1 device!\n");
        return 1;
    }

    msgs.addr = (rt_uint32_t)addr;
    msgs.flags = RT_I2C_WR;
    msgs.buf = (rt_uint8_t*)&reg;
    msgs.len = 1;

    if (rt_i2c_transfer(i2c_bus, &msgs, 1) == 1)
    {
        msgs.addr = (rt_uint32_t)addr;
        msgs.flags = RT_I2C_RD;
        msgs.buf = (rt_uint8_t*)buf;
        msgs.len = (rt_uint8_t)len;

        if (rt_i2c_transfer(i2c_bus, &msgs, 1) == 1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}

uint8_t INA219_I2C_Write(uint8_t addr,uint8_t reg,uint8_t *buf,uint16_t len)
{
    rt_uint8_t transmit_buf[3];
    struct rt_i2c_bus_device *i2c_bus;
    struct rt_i2c_msg msgs;
    
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find("i2c1");
    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find i2c1 device!\n");
    }

    transmit_buf[0] = (rt_uint8_t)reg;
    transmit_buf[1] = (rt_uint8_t)(buf[0]);
    transmit_buf[2] = (rt_uint8_t)(buf[1]);

    msgs.addr = (rt_uint32_t)addr;
    msgs.flags = RT_I2C_WR;
    msgs.buf = (rt_uint8_t*)transmit_buf;
    msgs.len = 3;

    if (rt_i2c_transfer(i2c_bus, &msgs, 1) == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}