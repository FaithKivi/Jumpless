#include "commands.h"
#include "DAC/dac_cs.h"
extern uint8_t DAC_switch;
extern uint8_t DAC_flag_Freq;//DACƵ���޸ı�־λ
extern uint8_t DAC_flag_Vpp;//DAC���ֵ�޸ı�־λ
extern float mA_1;
extern uint8_t changewave;
extern int16_t raw_1;
extern DAC_ DAC;
extern const RGB_Color_TypeDef RED;
extern const RGB_Color_TypeDef GREEN;
extern const RGB_Color_TypeDef BLACK;
extern const RGB_Color_TypeDef BLUE;
extern const RGB_Color_TypeDef SKY;
extern const RGB_Color_TypeDef MAGENTA;
extern const RGB_Color_TypeDef YELLOW;
extern const RGB_Color_TypeDef OEANGE;
extern const RGB_Color_TypeDef WHITE;

static void connect(int argc, char**argv)
{
    if(argc < 2)
    {
        rt_kprintf("Illegal param\n");
        return;
    }

    RST_Set();

    addPath(atoi(argv[1]),atoi(argv[2]));
    
    assignNets();
    bridgesToPaths();
    printAllPaths();
		rt_thread_mdelay(500);
		
    RST_Clr();

    sendAllPaths();
	setLedColors();
}
MSH_CMD_EXPORT(connect, connect sample: connect <from|to>);

static void sendraw(int argc, char**argv)
{
    if(argc < 4)
    {
        rt_kprintf("Illegal param\n");
        return;
    }

    sendXYraw((uint8_t)atoi(argv[1]),(uint16_t)atoi(argv[2]),(uint16_t)atoi(argv[3]),(uint16_t)atoi(argv[4]));
}
MSH_CMD_EXPORT(sendraw, example);

static void step(int argc, char**argv)
{
	static int cnt = 0;
	switch(cnt){
		case 0:
			RGB_SetColor(0,BLACK);
			RGB_SetColor(1,BLACK);
			RGB_SetColor(2,BLACK);
			RGB_SetColor(3,BLACK);
			RGB_SetColor(4,BLACK);
			RGB_SetColor(5,BLACK);
			RGB_SetColor(6,BLACK);
			RGB_SetColor(7,BLACK);
			RGB_SetColor(8,BLACK);
			RGB_SetColor(9,BLACK);
			RGB_SetColor(10,BLACK);
			RGB_SetColor(11,BLACK);
			RGB_SetColor(12,BLACK);
			RGB_SetColor(13,BLACK);
			RGB_SetColor(14,BLACK);
			RGB_SetColor(15,BLACK);
			RGB_SetColor(16,BLACK);
			RGB_SetColor(17,BLACK);
			RGB_SetColor(18,BLACK);
			RGB_SetColor(19,BLACK);
			RGB_SetColor(20,BLACK);
			RGB_SetColor(21,BLACK);
			RGB_SetColor(22,BLACK);
			RGB_SetColor(23,BLACK);
			RGB_SetColor(24,BLACK);
			RGB_SetColor(25,BLACK);
			RGB_SetColor(26,BLACK);
			RGB_SetColor(27,BLACK);
			RGB_SetColor(28,BLACK);
			RGB_SetColor(29,BLACK);
			RGB_SetColor(30,BLACK);
			RGB_SetColor(31,BLACK);
			RGB_SetColor(32,RED);
			RGB_SetColor(33,GREEN);
			RGB_SetColor(34,BLUE);
			RGB_SetColor(35,YELLOW);
			RGB_SetColor(36,BLUE);
			RGB_SetColor(37,YELLOW);
			RGB_SetColor(38,BLACK);
			RGB_SetColor(39,BLACK);
			RGB_SetColor(40,BLACK);
			RGB_SetColor(41,BLACK);
			RGB_SetColor(42,BLACK);
			RGB_SetColor(43,BLACK);
			RGB_SetColor(44,BLACK);
			RGB_SetColor(45,BLACK);
			RGB_SetColor(46,BLACK);
			RGB_SetColor(47,BLACK);
			RGB_SetColor(34,BLACK);
			RGB_SetColor(35,BLACK);
			RGB_SetColor(36,BLACK);
			RGB_SetColor(37,BLACK);
			RGB_SetColor(38,BLACK);
			RGB_SetColor(39,BLACK);
			RGB_SetColor(40,BLACK);
			RGB_SetColor(41,BLACK);
			RGB_SetColor(42,BLACK);
			RGB_SetColor(43,BLACK);
			RGB_SetColor(44,BLACK);
			RGB_SetColor(45,BLACK);
			RGB_SetColor(46,BLACK);
			RGB_SetColor(47,BLACK);
			RGB_SetColor(48,BLACK);
			RGB_SetColor(49,BLACK);
			RGB_SetColor(50,BLACK);
			RGB_SetColor(51,BLACK);
			RGB_SetColor(52,MAGENTA);
			RGB_SetColor(53,BLACK);
			RGB_SetColor(54,BLACK);
			RGB_SetColor(55,BLACK);
			RGB_SetColor(56,BLACK);
			RGB_SetColor(57,BLACK);
			RGB_SetColor(58,BLACK);
			RGB_SetColor(59,BLACK);
			RGB_SetColor(60,SKY);
			RGB_SetColor(61,YELLOW);
			RGB_SetColor(62,GREEN);
			RGB_SetColor(63,OEANGE);
			Reset_Load();
			RGB_SendArray();
			
			RST_Set();
			addPath(3,68);//A3 <-> +8V
			addPath(35,69);//E3 <-> -8V
			
			addPath(12,73);//B4 <-> GND
			addPath(2,13);//B5 <-> A2
			
			addPath(14,66);//B6 <-> DA1
			addPath(15,1);//B7 <-> A1
			
			addPath(0,64);//A0 <-> AD1
			assignNets();
			bridgesToPaths();
			printAllPaths();
			RST_Clr();
			
			sendAllPaths();
			
			break;

		default:
			break;
	}
	cnt++;
}
MSH_CMD_EXPORT(step, step sample: connect <from|to>);

static void disconnect(int argc, char**argv)
{
    if(argc < 2)
    {
        rt_kprintf("Illegal param\n");
        return;
    }
    RST_Set();

    removePath(atoi(argv[1]),atoi(argv[2]));
    
    assignNets();
    bridgesToPaths();
    printAllPaths();
		
    RST_Clr();

    sendAllPaths();
	setLedColors();
}
MSH_CMD_EXPORT(disconnect, connect sample: disconnect <from|to>);

static void disconnectAll(int argc, char**argv)
{
	initPath();
    clearAllConnections();
    FromOSclearAllconnections();
		setLedColors();
    rt_kprintf("All connections cleared!\n");
}
MSH_CMD_EXPORT(disconnectAll, disconnectAll sample: disconnectAll);

static void getCurrent(int argc, char**argv)
{
    rt_kprintf("I = %d uA\n",(int)(mA_1*1000));
    //rt_kprintf("Raw = %d\n",raw);
}
MSH_CMD_EXPORT(getCurrent, getCurrent sample: getCurrent);