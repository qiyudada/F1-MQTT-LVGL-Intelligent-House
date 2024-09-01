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
/*Hardware*/
#include "Dth11.h"
#include "LightSensor.h"
#include "ATcommand.h"
#include "Lcd.h"
#include "GUI.h"

/*LVGL*/
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "ui.h"
void HardwareInitTask(void *argument)
{
    while (1)
    {
        /*********************Uart INITATION**********************/
        /*!!! Any about Mutex/Semaphore/Queue/Timer/etc. should be initated out of vTasksuspend line!!!*/
        Uart3_Lock_Init();
        ATInit();

        // Delay_init();
        vTaskSuspendAll();
        /*********************DTH11 INITATION**********************/
        DHT11_Start();
        DHT11_Wait_Ack();
        /*********************Lightsensor INITATION**********************/
        LightSensor_Init();
        /*********************LVGL INITATION**********************/
        lv_init();
        lv_port_disp_init();
        lv_port_indev_init();
        xTaskResumeAll();
        /*********************Uart INITATION**********************/
        printf("Hello World!\r\n");
        /*********************TIM INITATION***************************/
        // HAL_TIM_Base_Start_IT(&htim3);
        vTaskDelete(NULL);
        vTaskDelay(500);
    }
}
