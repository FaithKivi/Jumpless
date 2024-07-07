#ifndef CH446Q_H
#define CH446Q_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define CHIP_A 0
#define CHIP_B 1
#define CHIP_C 2
#define CHIP_D 3
#define CHIP_E 4
#define CHIP_F 5
#define CHIP_G 6
#define CHIP_H 7

#define CHIP_I 8
#define CHIP_J 9

#define DAT_PIN GET_PIN(E, 3)
#define CK_PIN  GET_PIN(E, 2)
#define ENA_PIN GET_PIN(E, 4)
#define RST_PIN GET_PIN(B, 7)
#define CSA_PIN GET_PIN(C, 15)
#define CSB_PIN GET_PIN(C, 14)
#define CSC_PIN GET_PIN(C, 13)
#define CSI_PIN GET_PIN(E, 6)
#define CSJ_PIN GET_PIN(E, 5)

#define DAT_Set() rt_pin_write(DAT_PIN, PIN_HIGH)
#define DAT_Clr() rt_pin_write(DAT_PIN, PIN_LOW)

#define CK_Set() rt_pin_write(CK_PIN, PIN_HIGH)
#define CK_Clr() rt_pin_write(CK_PIN, PIN_LOW)

#define ENA_Set() rt_pin_write(ENA_PIN, PIN_HIGH)
#define ENA_Clr() rt_pin_write(ENA_PIN, PIN_LOW)

#define CSA_Set() rt_pin_write(CSA_PIN, PIN_HIGH)
#define CSA_Clr() rt_pin_write(CSA_PIN, PIN_LOW)

#define CSB_Set() rt_pin_write(CSB_PIN, PIN_HIGH)
#define CSB_Clr() rt_pin_write(CSB_PIN, PIN_LOW)

#define CSC_Set() rt_pin_write(CSC_PIN, PIN_HIGH)
#define CSC_Clr() rt_pin_write(CSC_PIN, PIN_LOW)

#define CSI_Set() rt_pin_write(CSI_PIN, PIN_HIGH)
#define CSI_Clr() rt_pin_write(CSI_PIN, PIN_LOW)

#define CSJ_Set() rt_pin_write(CSJ_PIN, PIN_HIGH)
#define CSJ_Clr() rt_pin_write(CSJ_PIN, PIN_LOW)

#define RST_Set() rt_pin_write(RST_PIN, PIN_HIGH)
#define RST_Clr() rt_pin_write(RST_PIN, PIN_LOW)

int CH446Q_Init(void);
void sendXYraw(uint8_t chip,uint16_t x,uint16_t y,uint16_t setorclear);
void FromOSclearAllconnections();

#endif