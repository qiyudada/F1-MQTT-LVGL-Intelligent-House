#ifndef _MQTT_Task_H
#define _MQTT_Task_H

#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "task.h"
#include "mqttclient.h"
#include "platform_mutex.h"
#include "rtc.h"

#include "sys.h"
#include "Dth11.h"
#include "Lightsensor.h"
#include "ATcommand.h"
#include "lvgl.h"
#include "ui.h"
#include "ui_helpers.h"

#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

typedef struct
{
    /*Task handle*/
    TaskHandle_t G_xMQTTClientInitHandle;
    TaskHandle_t G_xMQTT_Client_Task;
    TaskHandle_t G_xQueuePlatform; /* Process data platform */
    TaskHandle_t G_xLvgl_Task_Handler;

} _MQTT_TASK_Handle;

typedef struct
{
    /*Semaphore handle*/
    platform_mutex_t G_xTaskMutex;

    /*Eventgroup handle*/
    EventGroupHandle_t Event_Handle;
    const int UPDATE_MODE;

    /*Queue handle*/
    QueueHandle_t G_xMessageQueueToMQTT;
    const UBaseType_t MESSAGE_DATA_TX_NUM; // Message Queue Maximun numbers
    const UBaseType_t MESSAGE_DATA_TX_LEN; // Message Queue unit size Byte

    /*MQTT Client name*/
    mqtt_client_t *client;
    mqtt_message_t msg;

} _MQTT_Fun_Element;

extern _MQTT_TASK_Handle Mqtt_task;
extern _MQTT_Fun_Element Mqtt_Func;

void Lvgl_Display_Task(void *Param);
void DHT11_MQTT_Task(void *para);
void MQTT_Client_Task(void *para);
void MQTT_Client_Init(void *para);

#endif
