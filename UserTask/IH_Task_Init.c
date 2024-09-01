/*
 * @defgroup private
 */
#include "IH_Task_Init.h"
/*
 * @ Data Management
 */
#include "IH_DataManage.h"
/*
 * @ Hardware Initiation
 */
#include "IH_Hardware_Init.h"
/*
 * @ MQTT Initiation
 */
#include "IH_MqttTask.h"
/*
 *@ GUI
 */
#include "IH_LvglHandler.h"
/*
 * @Handle define
 */
/*Hardware Initiation*/
osThreadId_t HardwareInit_TaskHandle;
const osThreadAttr_t HardwareInitTask_attributes = {
    .name = "HardwareInitTask",
    .stack_size = 128 * 15,
    .priority = (osPriority_t)osPriorityHigh3,
};
/*ATCommand Receive*/
osThreadId_t ATRece_TaskHandle;
const osThreadAttr_t ATReceTask_attributes = {
    .name = "AtReceTask",
    .stack_size = 128 * 5,
    .priority = (osPriority_t)osPriorityNormal,
};
/*Mqtt Client Initation*/
osThreadId_t MQTTInit_TaskHandle;
const osThreadAttr_t MqttInitTask_attributes = {
    .name = "MqttInitTask",
    .stack_size = 128 *8,
    .priority = (osPriority_t)osPriorityHigh2,
};
/*LVGL Handler Task*/
osThreadId_t LvHandler_TaskHandle;
const osThreadAttr_t LvHandlerTask_attributes = {
    .name = "LvHandlerTask",
    .stack_size = 128 * 24,
    .priority = (osPriority_t)osPriorityLow,
};
/*Message Upload Task*/
osThreadId_t MessageUpload_TaskHandle;
const osThreadAttr_t MessageUpload_attributes = {
    .name = "MesuploadTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
void User_Tasks_Init(void)
{
    /* add threads, ... */
    HardwareInit_TaskHandle = osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes);
    ATRece_TaskHandle = osThreadNew(AT_RecvParse, NULL, &ATReceTask_attributes);
    MQTTInit_TaskHandle = osThreadNew(MqttInitTask, NULL, &MqttInitTask_attributes);
}
void TaskTickHook(void)
{
    lv_tick_inc(1);
}
