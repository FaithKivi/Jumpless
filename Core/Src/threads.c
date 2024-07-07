#include "threads.h"

#define LED1_PIN    GET_PIN(D, 1)

extern struct ina219_handle_s Sensor_1,Sensor_2;

static rt_thread_t tid1 = RT_NULL,tid2 = RT_NULL;
float mA;
int16_t raw;

int Threads_Init(void)
{
    tid1 = rt_thread_create("MatrixControl",
                    MatrixControl_Entry,
                    RT_NULL,
                    512,
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
    return 0;                
}
INIT_APP_EXPORT(Threads_Init);

void MatrixControl_Entry(void *parameter)
{
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    initPath();

    while(1)
    {
        sendAllPaths();
        rt_pin_write(LED1_PIN, PIN_HIGH);
		RGB_RED(64);
        rt_thread_mdelay(5000);
        rt_pin_write(LED1_PIN, PIN_LOW);
        RGB_GREEN(64);
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

    while(1)
    {
        ina219_read_current(&Sensor_1, &raw, &mA);
        rt_thread_mdelay(100);
    }   
}