#include "CH446Q.h"

int CH446Q_Init(void)
{
    rt_pin_mode(DAT_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(CK_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(ENA_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(CSA_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(CSB_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(CSC_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(CSI_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(CSJ_PIN, PIN_MODE_OUTPUT);

    rt_pin_mode(RST_PIN, PIN_MODE_OUTPUT_OD);
//    rt_pin_mode(RST_PIN, PIN_MODE_OUTPUT);
		
		DAT_Clr();
		CK_Clr();
		ENA_Clr();
		CSA_Clr();
		CSB_Clr();
		CSC_Clr();
		CSI_Clr();
		CSJ_Clr();
	
    FromOSclearAllconnections();
    return 0;
}
INIT_DEVICE_EXPORT(CH446Q_Init);

void FromOSclearAllconnections()
{
    RST_Set();
		RST_Set();
		RST_Set();
    rt_thread_mdelay(500);
    RST_Clr();
		RST_Clr();
		RST_Clr();
}

void sendXYraw(uint8_t chip,uint16_t x,uint16_t y,uint16_t setorclear)
{
    uint8_t i;
    uint16_t data;
	
		if((chip == 8 || chip == 9) && (x == 4 || x == 5 || x == 0 || x == 1)) return;
		if(chip == 4 && (x == 9 || x == 8)) return;
		if(chip == 0 && (x == 0 || x == 1)) return;

    data = y << 5 | x << 1 | setorclear;

    ENA_Clr();
		rt_thread_mdelay(10);

    for(i = 0; i < 7; i++)
    {
        CK_Clr();
				rt_thread_mdelay(2);
        if(data & 0x80) DAT_Set();
        else DAT_Clr();
				rt_thread_mdelay(2);
        CK_Set();
				rt_thread_mdelay(2);
        data <<= 1;
    }

    if(data & 0x80) DAT_Set();
    else DAT_Clr();
		
		rt_thread_mdelay(2);

    if(chip <= CHIP_H)//Normal Chips
    {
        if(chip & 0x01) CSA_Set(); 
        else CSA_Clr();

        if(chip & 0x02) CSB_Set(); 
        else CSB_Clr();

        if(chip & 0x04) CSC_Set(); 
        else CSC_Clr();
				
				rt_thread_mdelay(2);
        ENA_Set();
				rt_thread_mdelay(2);
        ENA_Clr();

    }
    else
    {
        if(chip == CHIP_I)
        {
						rt_thread_mdelay(2);
            CSI_Set();
						rt_thread_mdelay(2);
            CSI_Clr();
        }

        else if(chip == CHIP_J)
        {
						rt_thread_mdelay(2);
            CSJ_Set();
						rt_thread_mdelay(2);
            CSJ_Clr();
        }
    }
    CK_Clr();
    DAT_Clr();
}