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

    FromOSclearAllconnections();
    return 0;
}
INIT_DEVICE_EXPORT(CH446Q_Init);

void FromOSclearAllconnections()
{
    RST_Set();
    rt_thread_mdelay(1);
    RST_Clr();
}

void sendXYraw(uint8_t chip,uint16_t x,uint16_t y,uint16_t setorclear)
{
    uint8_t i;
    uint16_t data;

    data = y << 5 | x << 1 | setorclear;

    ENA_Clr();

    for(i = 0; i < 7; i++)
    {
        CK_Clr();
        if(data & 0x80) DAT_Set();
        else DAT_Clr();
        CK_Set();
        data <<= 1;
    }

    if(data & 0x80) DAT_Set();
    else DAT_Clr();

    if(chip <= CHIP_H)//Normal Chips
    {
        if(chip & 0x01) CSA_Set(); 
        else CSA_Clr();

        if(chip & 0x02) CSB_Set(); 
        else CSB_Clr();

        if(chip & 0x04) CSC_Set(); 
        else CSC_Clr();
				
        ENA_Set();
        ENA_Clr();

    }
    else
    {
        if(chip == CHIP_I)
        {
            CSI_Set();
            CSI_Clr();
        }

        else if(chip == CHIP_J)
        {
            CSJ_Set();
            CSJ_Clr();
        }
    }
}