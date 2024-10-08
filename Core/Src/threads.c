#include "threads.h"

#define LED1_PIN    GET_PIN(D, 1)
const RGB_Color_TypeDef rRED      = {255,0,0};   //??????RGB????
const RGB_Color_TypeDef rGREEN    = {0,255,0};
const RGB_Color_TypeDef rBLUE     = {0,0,255};
const RGB_Color_TypeDef rSKY      = {0,255,255};
const RGB_Color_TypeDef rMAGENTA  = {255,0,220};
const RGB_Color_TypeDef rYELLOW   = {127,216,0};
const RGB_Color_TypeDef rOEANGE   = {127,106,0};
const RGB_Color_TypeDef rBLACK    = {0,0,0};
const RGB_Color_TypeDef rWHITE    = {255,255,255};
uint8_t data_read[11];
uint8_t data_connect[4];
uint8_t ch2;
bool adc_process_flag =0;
extern struct ina219_handle_s Sensor_1,Sensor_2;
static rt_thread_t tid1 = RT_NULL,tid2 = RT_NULL,tid3 = RT_NULL, tid4=RT_NULL;
float mA_1,mA_2;
int16_t raw_1,raw_2;
uint8_t LPTIM_COUNT =0,Pre_LPTIM_COUNT = 0xff;//ï¿½Í¹ï¿½ï¿½Äµï¿½ï¿½ï¿½Ê±
uint8_t State =0;
extern LPTIM_HandleTypeDef hlptim1;
extern ADC_HandleTypeDef hadc1;
extern LPTIM_HandleTypeDef hlptim2;
uint8_t SampRate_num = 0,preSampRate_num =0xff;
uint8_t DAC_Trigger_num = 11,preDAC_Trigger_num = 0xff;//ï¿½ï¿½Ê¼Îª1950
uint8_t DAC_switch = 0 ;
uint8_t DAC_flag_Freq = 0;//DACÆµï¿½ï¿½ï¿½Þ¸Ä±ï¿½Ö¾Î»
uint8_t DAC_flag_Vpp =0;//DACï¿½ï¿½ï¿½Öµï¿½Þ¸Ä±ï¿½Ö¾Î»
uint16_t Show_Lin[640];
OSC_ OSC;   //ï¿½ï¿½ï¿½Ê¾ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
extern const uint8_t bmps;
extern uint16_t g_Wave[SIN_ROM_LENGTH];
static struct rt_semaphore rx_sem;
char temp_string[50];
int length;
typedef enum{
	tidle,
	dac,
	connect1,
	connect2,
	clear,
	wave_form,
	freq1,
	freq2,
	freq3,
	freq4,
	vpp1,
	vpp2,
	vpp3,
	vpp4,
	check,
}dac_state;
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* ´®¿Ú½ÓÊÕµ½Êý¾Ýºó²úÉúÖÐ¶Ï£¬µ÷ÓÃ´Ë»Øµ÷º¯Êý£¬È»ºó·¢ËÍ½ÓÊÕÐÅºÅÁ¿ */
    rt_sem_release(&rx_sem);

    return RT_EOK;
}


int Threads_Init(void)
{
    tid1 = rt_thread_create("MatrixControl",
                    MatrixControl_Entry,
                    RT_NULL,
                    1024,
                    31,
                    5);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    tid2 = rt_thread_create("CurrentSensor",
                    CurrentSensor_Entry,
                    RT_NULL,
                    1024,
                    0,
                    5);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

    tid3 = rt_thread_create("receive_data",
                    receive_data_Entry,
                    RT_NULL,
                    4096,
                    2,
                    5);
    if (tid3 != RT_NULL)
        rt_thread_startup(tid3);
    
		
		tid4 = rt_thread_create("ADDAControl",
										ADDAControl_Entry,
										RT_NULL,
										2048,
										0,
										5);
		if (tid4 != RT_NULL)
        rt_thread_startup(tid4);
		return 0; 
}
INIT_APP_EXPORT(Threads_Init);

void MatrixControl_Entry(void *parameter)
{
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    initPath();
	FromOSclearAllconnections();

	RGB_BLACK(64);

    while(1)
    {
        //sendAllPaths();
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(5000);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(5000);
    }
}

void CurrentSensor_Entry(void *parameter)
{
    uint16_t cal;
    ina219_pga_t pga;

    ina219_init(&Sensor_1);
    ina219_init(&Sensor_2);

    ina219_calculate_calibration(&Sensor_1,&cal);
    ina219_set_calibration(&Sensor_1,cal);
    ina219_calculate_calibration(&Sensor_2,&cal);
    ina219_set_calibration(&Sensor_2,cal);
		rt_device_open(serial,RT_DEVICE_OFLAG_RDWR|RT_DEVICE_FLAG_INT_RX); 

	while(1)
	{
				if(adc_process_flag==1)
		{
			  ADC_Data_Send(Show_Lin);
				adc_process_flag=0;
		}
		rt_thread_mdelay(100);
	}
}

void receive_data_Entry(void *parameter)
{
		rt_device_set_rx_indicate(serial, uart_input);
		rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
	while(1)
	{	
		     while (rt_device_read(serial, -1, &ch2, 1) != 1)
        {
					static dac_state cur_state = tidle;
					static uint8_t count =0;
						switch(cur_state)
					{
						case tidle:
							if(ch2==0xea)
							{
								data_read[count]=ch2;
								cur_state = wave_form;
								count++;
							}
							if(ch2==0xAA)//Á¬½ÓÁ½¸öµã
							{
								data_connect[count]=ch2;
								cur_state=connect1;
								count++;
							}
							if(ch2==0x9F)//Çå³ý
							{
								data_connect[count]=ch2;
								cur_state = clear;
								count++;
							}
							break;
						case connect1:
							data_connect[count]=ch2;
							cur_state = connect2;
							count++;
						break;
						case connect2:
							data_connect[count]=ch2;
							cur_state = check;
							count++;
						break;
						case clear://Çå³ý
							initPath();
							clearAllConnections();
							FromOSclearAllconnections();
							setLedColors();
							rt_kprintf("All connections cleared!\n");
							cur_state=tidle;
							count=0;
						break;
						case wave_form:
							data_read[count]=ch2;
							cur_state = freq1;
							count++;
						break;
						case freq1:
							data_read[count]=ch2;
							cur_state = freq2;
							count++;
						break;
						case freq2:
							data_read[count]=ch2;
							cur_state = freq3;
							count++;
						break;
						case freq3:
							data_read[count]=ch2;
							cur_state = freq4;
							count++;
						break;
						case freq4:
							data_read[count]=ch2;
							cur_state = vpp1;
							count++;
						break;
						case vpp1:
							data_read[count]=ch2;
							cur_state = vpp2;
							count++;
						break;
						case vpp2:
							data_read[count]=ch2;
							cur_state = vpp3;
							count++;
						break;
						case vpp3:
							data_read[count]=ch2;
							cur_state = vpp4;
							count++;
						break;
						case vpp4:
							data_read[count]=ch2;
							cur_state = check;
							count++;
						break;
						case check://Ð£ÑéÎ»
							if(ch2==0xfa)
							{
								data_read[count]=ch2;
								dac_read(data_read);
								count=0;
								cur_state = tidle;
							}
							else if(ch2==0xf5)
							{
								data_connect[count]=ch2;
								RST_Set();

								addPath(data_connect[1],data_connect[2]);
    
								assignNets();
								bridgesToPaths();
								printAllPaths();
								rt_thread_mdelay(500);
		
								RST_Clr();

								sendAllPaths();
								setLedColors();
								count=0;
								cur_state=tidle;
							}
							else
							{
								count=0;
								cur_state=tidle;
							}	
						break;
						default:
							cur_state = tidle;
						break;
					}
            /* ×èÈûµÈ´ý½ÓÊÕÐÅºÅÁ¿£¬µÈµ½ÐÅºÅÁ¿ºóÔÙ´Î¶ÁÈ¡Êý¾Ý */
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }

	}
}	
void ADDAControl_Entry(void *parameter)
{
	Relay1_Off();
	Relay2_Off();
	Relay3_Off();
	while (1)
  {
switch(State)
		{
			case 0://×´Ì¬ÇÐ»»
				if(preSampRate_num != SampRate_num)//²ÉÑùÇÐ»»
				{
					Osc_Time_Switch(SampRate_num);
					preSampRate_num = SampRate_num;
				}
				if(preDAC_Trigger_num!=DAC_Trigger_num)//´¥·¢Î»ÖÃ£¬Ä¬ÈÏ1950mV
				{
					Trigger_Open((DAC_Trigger_num+28)*50);
					preDAC_Trigger_num = DAC_Trigger_num;
				}
				DAC_processing(1,1,1);//DAC´¦Àí
			State = 1;
			break;
			case 1://´ò¿ª´¥·¢µÈ´ý´¥·¢
				Flag_Trigger = 0;
				Flag_overtime =0;
				Trigger_on();//´¥·¢¿ª
				HAL_LPTIM_Counter_Start_IT(&hlptim2,3120);//100ms×óÓÒ
				State = 2;
			break;
			case 2:
				if(Flag_Trigger == 1)//²úÉú´¥·¢
				{
					HAL_LPTIM_Counter_Stop_IT(&hlptim2);//¹Ø±Õ³¬Ê±
					State = 4;//Ìø×ªµÈ´ýADC½ÓÊÕÍê³É
				}
				if(Flag_overtime == 1 && Flag_Trigger == 0)//³¬Ê±ÇÒÎ´´¥·¢£¬¹Ø±Õ±È½ÏÆ÷ºÍ³¬Ê±¶¨Ê±Æ÷
				{
					HAL_LPTIM_Counter_Stop_IT(&hlptim2);//¹Ø±Õ³¬Ê±
					Trigger_off();//´¥·¢¹Ø
					State = 3;//Ìø×ª»ñÈ¡ADC
				}
			break;
			case 3://»ñÈ¡ADCÊý¾Ý
				if(adc_dma_complete_flag == notStarted)
				{
					adc_dma_complete_flag = inProgress;
					HAL_ADCEx_MultiModeStart_DMA(&hadc1,adc_dma_data1,ADC_DATA_LENGTH);
					State = 4;//µÈ´ý½ÓÊÕÍê³É
				}
			break;
			case 4:
					if(adc_dma_complete_flag == completed)//flagµÈÓÚ1±íÊ¾²É¼¯Íê³É
				{
					adc_dma_complete_flag = notStarted;//Êý¾Ý´¦ÀíÍê³ÉºóADC±êÖ¾Î»ÖÃÁã
					State =5;
				}
			break;
			case 5 ://ADCÊä³ö´¦ÀíÎªÏàÓ¦µÄ²¨ÐÎ.		
					ADC_Data_Processing(Show_Lin,&OSC);
					adc_process_flag=1;
					State = 0;
				break;
		}
				rt_thread_mdelay(100);
		}
}
void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim)
{
	if(hlptim == &hlptim1)
	{
			LPTIM_COUNT++;
	}
	if(hlptim == &hlptim2)
	{
			Flag_overtime = 1;
	}
}