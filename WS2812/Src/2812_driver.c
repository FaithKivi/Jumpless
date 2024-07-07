#include "2812_driver.h"
#include "math.h"
/*Some Static Colors------------------------------*/
const RGB_Color_TypeDef RED      = {255,0,0};   //��ʾ��ɫRGB����
const RGB_Color_TypeDef GREEN    = {0,255,0};
const RGB_Color_TypeDef BLUE     = {0,0,255};
const RGB_Color_TypeDef SKY      = {0,255,255};
const RGB_Color_TypeDef MAGENTA  = {255,0,220};
const RGB_Color_TypeDef YELLOW   = {127,216,0};
const RGB_Color_TypeDef OEANGE   = {127,106,0};
const RGB_Color_TypeDef BLACK    = {0,0,0};
const RGB_Color_TypeDef WHITE    = {255,255,255};
 
/*��ά����������PWM������飬ÿһ��24��
���ݴ���һ��LED�����һ��24��0����RESET��*/
uint32_t Pixel_Buf[Pixel_NUM+1][24];
extern TIM_HandleTypeDef htim1;
/*
���ܣ��趨����RGB LED����ɫ���ѽṹ����RGB��24BITת��Ϊ0���1��
������LedIdΪLED��ţ�Color���������ɫ�ṹ��
*/
//��ʱ����
 void delay_ms(int32_t nms) 
 {
  int32_t temp; 
  SysTick->LOAD = 10000*nms; 
  SysTick->VAL=0X00;//��ռ����� 
  SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ 
  do 
  { 
       temp=SysTick->CTRL;//��ȡ��ǰ������ֵ 
		
  } while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽�� 
   SysTick->CTRL=0x00; //�رռ����� 
   SysTick->VAL =0X00; //��ռ����� 
 }
void RGB_SetColor(uint8_t LedId,RGB_Color_TypeDef Color)
{
	uint8_t i; 
	if(LedId > Pixel_NUM)return; //avoid overflow ��ֹд��ID����LED����
	
	for(i=0;i<8;i++) Pixel_Buf[LedId][i]   = ( (Color.G & (1 << (7 -i)))? (CODE_1):CODE_0 );//����ĳһ��0~7ת�����G
	for(i=8;i<16;i++) Pixel_Buf[LedId][i]  = ( (Color.R & (1 << (15-i)))? (CODE_1):CODE_0 );//����ĳһ��8~15ת�����R
	for(i=16;i<24;i++) Pixel_Buf[LedId][i] = ( (Color.B & (1 << (23-i)))? (CODE_1):CODE_0 );//����ĳһ��16~23ת�����B
}
 
/*
���ܣ����һ��װ��24��0�����24������ռ�ձ�Ϊ0��PWM������Ϊ���reset��ʱ��������ʱ��Ϊ24*1.2=30us > 24us(Ҫ�����24us)
*/
void Reset_Load(void)
{
	uint8_t i;
	for(i=0;i<24;i++)
	{
		Pixel_Buf[Pixel_NUM][i] = 0;
	}
}
 
/*
���ܣ���������
������(&htim1)��ʱ��1��(TIM_CHANNEL_1)ͨ��1��((uint32_t *)Pixel_Buf)���������飬
			(Pixel_NUM+1)*24)���͸����������������
*/
void RGB_SendArray(void)
{
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)Pixel_Buf,(Pixel_NUM+1)*24);
	//HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)"sbsb",4);
}
 
/*
���ܣ���ʾ��ɫ
������Pixel_LenΪ��ʾLED����
*/
void RGB_RED(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//����Ӧ����LEDд���ɫ
	{
		RGB_SetColor(i,RED);
	}
	Reset_Load();
	RGB_SendArray();
}
 
/*
���ܣ���ʾ��ɫ
������Pixel_LenΪ��ʾLED����
*/
void RGB_GREEN(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//����Ӧ����LEDд����ɫ
	{
		RGB_SetColor(i,GREEN);
	}
	Reset_Load();
	RGB_SendArray();
}
 
/*
���ܣ���ʾ��ɫ
������Pixel_LenΪ��ʾLED����
*/
void RGB_BLUE(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//����Ӧ����LEDд����ɫ
	{
		RGB_SetColor(i,BLUE);
	}
	Reset_Load();
	RGB_SendArray();
}
 
/*
���ܣ���ʾ��ɫ
������Pixel_LenΪ��ʾLED����
*/
void RGB_WHITE(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//����Ӧ����LEDд���ɫ
	{
		RGB_SetColor(i,WHITE);
	}
	Reset_Load();
	RGB_SendArray();
}

void RGB_BLACK(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//����Ӧ����LEDд���ɫ
	{
		RGB_SetColor(i,BLACK);
	}
	Reset_Load();
	RGB_SendArray();
}

void flicker_RGB(uint16_t Pixel_Len,uint16_t color,int number)
{
	int i=0,j=1;
	if(j==1)
	{
	for(i=0;i<number;i++)
	{
		uint32_t starttime=HAL_GetTick();
		if(color==1)
		{
		RGB_RED(Pixel_Len);
    delay_ms(700);
		RGB_BLACK(Pixel_Len );
		delay_ms(150);
		}
		if(color==2)
		{
		RGB_GREEN(Pixel_Len);
    delay_ms(700);
		RGB_BLACK(Pixel_Len );
		delay_ms(150);
 
		}
		
	  if(color==3)
		{
		RGB_WHITE(Pixel_Len);
    delay_ms(700);
		RGB_BLACK(Pixel_Len );
		delay_ms(150);
		}	
	}
	j=2;
  }
	if(j==2)
	{
		for(i=0;i<6;i++)
	{
		delay_ms(1000);
	}
		j=1;
	}
	
}
//Ҳ���Լ�������������ɫ������ɫ�仯������





