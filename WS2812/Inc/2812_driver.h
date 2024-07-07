#ifndef __RGB_H__
#define __RGB_H__
 
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "stm32h7xx_hal.h"
#include "main.h"

#define STATUS_FLYMODE    			1 //1
#define STATUS_FIRSTMISSON     	2 //2
#define STATUS_SECONDMISSON  			3 //3?
#define STATUS_TAKEOFF			4 //4
#define STATUS_SENDMESS			5 //5
#define STATUS_TIME           6 //6
#define STATUS_FUNCTION         7 //分离控制
/*这里是上文计算所得CCR的宏定义*/
#define CODE_1       (194)       //1码定时器计数次数
#define CODE_0       (90)       //0码定时器计数次数

/*建立一个定义单个LED三原色值大小的结构体*/
typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}RGB_Color_TypeDef;
 
#define Pixel_NUM  64    //LED数量宏定义，这里我使用一个LED，（单词pixel为像素的意思）
 
void RGB_SetColor(uint8_t LedId,RGB_Color_TypeDef Color);//给一个LED装载24个颜色数据码（0码和1码）
void Reset_Load(void); //该函数用于将数组最后24个数据变为0，代表RESET_code
void RGB_SendArray(void);          //发送最终数组
void RGB_RED(uint16_t Pixel_Len);  //显示红灯
void RGB_GREEN(uint16_t Pixel_Len);//显示绿灯
void RGB_BLUE(uint16_t Pixel_Len); //显示蓝灯
void RGB_WHITE(uint16_t Pixel_Len);//显示白灯
void RGB_BLACK(uint16_t Pixel_Len);//显示黑灯
void flicker_RGB(uint16_t Pixel_Len,uint16_t color,int number);//灯光闪烁

void delay_ms(int32_t nms) ;//延时函数

uint32_t keyborad_scan(void) ;//矩阵键盘
#endif