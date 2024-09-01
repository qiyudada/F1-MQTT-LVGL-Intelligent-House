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
        vTaskSuspendAll();

        // /*********************DTH11 INITATION**********************/
        // DHT11_Start();
        // DHT11_Wait_Ack();
        // /*********************Lightsensor INITATION**********************/
        // LightSensor_Init();

        // /*********************LVGL INITATION**********************/
        // lv_init();
        // lv_port_disp_init();
        // lv_port_indev_init();
         xTaskResumeAll();
        // /*********************Uart INITATION**********************/
        // Uart3_Lock_Init();
        // /*********************Uart INITATION**********************/
        // ATInit();
        // printf("Hello World!\r\n");

        vTaskDelete(NULL);
        osDelay(500);
    }
}
