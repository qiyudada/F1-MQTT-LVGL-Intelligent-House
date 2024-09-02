/*
 * @include
 */
#include "IH_Hardware_Init.h"
/*
 * @other include
 */
/*SYSTEM*/
#include "main.h"
#include "ring_buffer.h"

/*Data managemrnt*/
#include "IH_DataManage.h"

/*Task*/
#include "IH_Task_Init.h"

void HardwareInitTask(void *argument)
{
    while (1)
    {
        /*********************Uart INITATION**********************/
        /*!!! Any about Mutex/Semaphore/Queue/Timer/etc. should be initated out of vTasksuspend line!!!*/
        Uart3_Lock_Init();
        ATInit();
        uint8_t num = 3;
        // Delay_init();
        /*********************DTH11 INITATION**********************/
        while (num && IH_Family.DTH11.ConnectionError)
        {
            num--;
            DHT11_Start();
            IH_Family.DTH11.ConnectionError = DHT11_Wait_Ack();
        }
        if (IH_Family.DTH11.ConnectionError)
        {
            QI_DEBUG("DHT11 Init error!\r\n");
        }
        /*********************Lightsensor INITATION**********************/
        num = 3;
        while (num && IH_Family.Light.ConnectionError)
        {
            num--;
            IH_Family.Light.ConnectionError = LightSensor_Init();
        }
        if (IH_Family.Light.ConnectionError)
        {
            QI_DEBUG("LightSensor Init error!\r\n");
        }
        /*********************LVGL INITATION**********************/
        lv_init();
        lv_port_disp_init();
        lv_port_indev_init();
        ui_init();
        /*Initiation completed*/
        printf("Hello World!\r\n");

        QI_DEBUG("HardwareInit stack is %d\r\n", (int *)osThreadGetStackSpace(HardwareInit_TaskHandle));
        /*********************TIM INITATION***************************/
        // HAL_TIM_Base_Start_IT(&htim3);
        vTaskDelete(NULL);
        osDelay(500);
    }
}

void MessageUpdateTask(void *argument)
{
    while (1)
    {
        uint8_t MessUpdataStr;
        if (osMessageQueueGet(MessageUpdate_Queue, &MessUpdataStr, NULL, 0) == osOK)
        {
            QI_DEBUG("MessageUpdateTask\r\n");
            /*Time data*/
            IH_Family.TIME.GetTimeDate(&IH_Family.NOWTIME);
            /*DTH11 data*/
            if (!(IH_Family.DTH11.ConnectionError))
            {
                // temp and humi messure
                int humi, temp;
                IH_Family.DTH11.DTH11_ReadData(&temp, &humi);
                // check
                if (temp > -10 && temp < 50 && humi > 0 && humi < 100)
                {
                    IH_Family.DTH11.humidity = humi;
                    IH_Family.DTH11.tempature = temp;
                }
            }
            /*Lightsensor data*/
            if (!(IH_Family.Light.ConnectionError))
            {
                int lightintens;
                IH_Family.Light.Light_Read_Data(&lightintens);
                IH_Family.Light.Light_Value = lightintens;
            }
            uint8_t MesCompStr = 0;
            osMessageQueuePut(MessageUpComplete_Queue, &MesCompStr, NULL, 10);
            QI_DEBUG("Messageupdate stack is %d\r\n", (int *)osThreadGetStackSpace(MessageUpdate_TaskHandle));

            QI_DEBUG("MessageUpdateTask end\r\n");
        }
        osDelay(500);
    }
}

void UpdataTimerCallback(void *argument)
{
    uint8_t MesSendStr = 0;
    Lv_Label_Update();
    osMessageQueuePut(MessageUpdate_Queue, &MesSendStr, NULL, 1);
}