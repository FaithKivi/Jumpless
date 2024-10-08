#include "lcd_init.h"
#include "pic1.h"
extern const unsigned char gImage_pic[44640];
struct rt_spi_device spi_dev_lcd;

void LCD_GPIO_Init()
{
	rt_pin_mode(RES_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(DC_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(BLK_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(CS_PIN, PIN_MODE_OUTPUT);
}

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(uint8_t dat) 
{
	rt_spi_send(&spi_dev_lcd, &dat,1);
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(uint16_t dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr();//写命令
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	//Alter
		else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
//	else if(USE_HORIZONTAL==1)
//	{
//		LCD_WR_REG(0x2a);//列地址设置
//		LCD_WR_DATA(x1);
//		LCD_WR_DATA(x2);
//		LCD_WR_REG(0x2b);//行地址设置
//		LCD_WR_DATA(y1+80);
//		LCD_WR_DATA(y2+80);
//		LCD_WR_REG(0x2c);//储存器写
//	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	//Alter
		else
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
//	else
//	{
//		LCD_WR_REG(0x2a);//列地址设置
//		LCD_WR_DATA(x1+80);
//		LCD_WR_DATA(x2+80);
//		LCD_WR_REG(0x2b);//行地址设置
//		LCD_WR_DATA(y1);
//		LCD_WR_DATA(y2);
//		LCD_WR_REG(0x2c);//储存器写
//	}
}

int LCD_Init(void)
{
	struct rt_spi_configuration config = {.mode = RT_SPI_MASTER|RT_SPI_MSB|RT_SPI_MODE_3|RT_SPI_NO_CS,.data_width = 8,.max_hz = 30 * 1000 *1000};
		
	LCD_GPIO_Init();//初始化GPIO
	rt_spi_bus_attach_device(&spi_dev_lcd, "spi_lcd", "spi3", RT_NULL);
	rt_spi_configure(&spi_dev_lcd,&config);
	
	LCD_RES_Clr();//复位
	rt_thread_mdelay(400);
	LCD_RES_Set();
	rt_thread_mdelay(200);
	
	LCD_BLK_Set();//打开背光
  rt_thread_mdelay(100);
	
	//************* Start Initial Sequence **********//
	LCD_WR_REG(0x11); //Sleep out 
	rt_thread_mdelay(120);              //Delay 120ms 
	//************* Start Initial Sequence **********// 
	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A); 
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33); 

	LCD_WR_REG(0xB7); 
	LCD_WR_DATA8(0x35);  

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x19);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x12);   

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);  

	LCD_WR_REG(0xC6); 
	LCD_WR_DATA8(0x0F);    

	LCD_WR_REG(0xD0); 
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x4C);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x44);
	LCD_WR_DATA8(0x51);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x20);
	LCD_WR_DATA8(0x23);
	//LCD_WR_REG(0x21); //颜色翻转

	LCD_WR_REG(0x29);
	
	LCD_Fill(0,0,320,240,WHITE);
	
//	lv_init();
//	lv_port_disp_init();
		LCD_Address_Set(0,0,320,240);
		LCD_ShowPicture(29,0,262,240,&gImage_pic1);

	return 0; 
}
INIT_ENV_EXPORT(LCD_Init);








