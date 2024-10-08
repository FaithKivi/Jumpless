#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "stdint.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lcd_7789.h"

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define USE_HORIZONTAL 2  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

//Alter
#if USE_HORIZONTAL==0||USE_HORIZONTAL==1  //横竖屏时的长高不唯一
#define LCD_W 240
#define LCD_H 320

#else
#define LCD_W 320
#define LCD_H 240
#endif

//#define LCD_W 240
//#define LCD_H 320
 


//-----------------LCD端口定义---------------- 
#define RES_PIN GET_PIN(B,12)
#define DC_PIN GET_PIN(B,13)
#define BLK_PIN GET_PIN(B,15)
#define CS_PIN GET_PIN(B,14)

#define LCD_RES_Clr()  rt_pin_write(RES_PIN, PIN_LOW)
#define LCD_RES_Set()  rt_pin_write(RES_PIN, PIN_HIGH)

#define LCD_DC_Clr()   rt_pin_write(DC_PIN, PIN_LOW)
#define LCD_DC_Set()   rt_pin_write(DC_PIN, PIN_HIGH)

#define LCD_BLK_Clr()		rt_pin_write(BLK_PIN, PIN_LOW)
#define LCD_BLK_Set()  	rt_pin_write(BLK_PIN, PIN_HIGH)

#define LCD_CS_Clr()	rt_pin_write(CS_PIN, PIN_LOW)
#define LCD_CS_Set()  	rt_pin_write(CS_PIN, PIN_HIGH)

void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(uint8_t dat);//模拟SPI时序
void LCD_WR_DATA8(uint8_t dat);//写入一个字节
void LCD_WR_DATA(uint16_t dat);//写入两个字节
void LCD_WR_REG(uint8_t dat);//写入一个指令
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数
int LCD_Init(void);//LCD初始化
#endif




