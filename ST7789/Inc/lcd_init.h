#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "stdint.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lcd_7789.h"

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define USE_HORIZONTAL 2  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����

//Alter
#if USE_HORIZONTAL==0||USE_HORIZONTAL==1  //������ʱ�ĳ��߲�Ψһ
#define LCD_W 240
#define LCD_H 320

#else
#define LCD_W 320
#define LCD_H 240
#endif

//#define LCD_W 240
//#define LCD_H 320
 


//-----------------LCD�˿ڶ���---------------- 
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

void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(uint8_t dat);//ģ��SPIʱ��
void LCD_WR_DATA8(uint8_t dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t dat);//д��һ��ָ��
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
int LCD_Init(void);//LCD��ʼ��
#endif




