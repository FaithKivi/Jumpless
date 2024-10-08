#ifndef __LCD_H
#define __LCD_H		
#include "stdint.h"


void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);//ָ�����������ɫ
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);//��ָ��λ�û�һ����
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);//��ָ��λ�û�һ����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);//��ָ��λ�û�һ������
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);//��ָ��λ�û�һ��Բ

void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ���ִ�
void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����16x16����
void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����24x24����
void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����32x32����

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾһ���ַ�
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ�ַ���
uint32_t mypow(uint8_t m,uint8_t n);//����
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//��ʾ��������
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//��ʾ��λС������

void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[]);//��ʾͼƬ


//#define USE_COLOR_INVERSION  1

#ifdef USE_COLOR_INVERSION  //�����Ҫ��ɫ��ת
//��ɫ��ת
//������ɫ
#define WHITE         	 0x0000
#define BLACK         	 0xFFFF 
#define BLUE           	 0xFFE0 
#define BRED             0X07E0
#define GRED 			       0X001F
#define GBLUE			       0XF800
#define RED           	 0x07FF
#define MAGENTA       	 0x07E0
#define GREEN         	 0xF81F
#define CYAN          	 0x8000
#define YELLOW        	 0x001F
#define BROWN 			     0X43BF //��ɫ
#define BRRED 			     0X07F8 //�غ�ɫ
#define GRAY  			     0X7BCF //��ɫ
#define DARKBLUE      	 0XFE30	//����ɫ
#define LIGHTBLUE      	 0X8283	//ǳ��ɫ  
#define GRAYBLUE       	 0XABA7 //����ɫ
#define LIGHTGREEN     	 0X7BE0 //ǳ��ɫ
#define LGRAY 			     0X39E7 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0X59AE //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0XD4ED //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

#else         //�������Ҫ��ɫ��ת
//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //��ɫ
#define BRRED 			     0XFC07 //�غ�ɫ
#define GRAY  			     0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			     0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
#endif





#endif
