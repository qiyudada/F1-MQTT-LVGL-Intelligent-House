/*
 * @defgroup private
 */
#include "IH_Task_Init.h"

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
/*TaskHandle--------------------------------------------------*/
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
    .priority = (osPriority_t)osPriorityHigh1,
};
/*Mqtt Client Initation*/
osThreadId_t MQTTInit_TaskHandle;
const osThreadAttr_t MqttInitTask_attributes = {
    .name = "MqttInitTask",
    .stack_size = 128 * 8,
    .priority = (osPriority_t)osPriorityHigh2,
};
/*LVGL Handler Task*/
osThreadId_t LvHandler_TaskHandle;
const osThreadAttr_t LvHandlerTask_attributes = {
    .name = "LvHandlerTask",
    .stack_size = 128 * 20,
    .priority = (osPriority_t)osPriorityLow,
};
/*Message Upload Task*/
osThreadId_t MessageUpload_TaskHandle;
const osThreadAttr_t MessageUpload_attributes = {
    .name = "MesuploadTask",
    .stack_size = 128 * 8,
    .priority = (osPriority_t)osPriorityLow,
};
/*Message Update Task*/
osThreadId_t MessageUpdate_TaskHandle;
const osThreadAttr_t MessageUpdate_attributes = {
    .name = "MesupdateTask",
    .stack_size = 128 * 6,
    .priority = (osPriority_t)osPriorityLow1,
};
/*MUTEX------------------------------------------------------*/
/*Message Upload Mutex*/
osMutexId_t MessageUpload_MutexHandle;
const osMutexAttr_t MessageUpload_Mutex_attributes = {
    .name = "MessageUpload_Mutex",
};

/*Queue--------------------------------------------------------*/
osMessageQueueId_t MessageUpdate_Queue;
osMessageQueueId_t MessageUpComplete_Queue;
/* Timers-------------------------------------------------------*/
osTimerId_t UpdataTimerHandle;

/**
 * @brief  Initialize all the tasks
 */
void User_Tasks_Init(void)
{

    UpdataTimerHandle = osTimerNew(UpdataTimerCallback, osTimerPeriodic, NULL, NULL);
    osTimerStart(UpdataTimerHandle, 1000); // 1s

    /*add queue,...*/
    MessageUpdate_Queue = osMessageQueueNew(1, 1, NULL);
    MessageUpComplete_Queue = osMessageQueueNew(1, 1, NULL);
    /* add Mutex,...*/
    MessageUpload_MutexHandle = osMutexNew(&MessageUpload_Mutex_attributes);/*No use Temporarily*/

    /* add threads, ... */
    /*Priority reference:(1)is biggest*/
    HardwareInit_TaskHandle = osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes); //(1)
    MQTTInit_TaskHandle = osThreadNew(MqttInitTask, NULL, &MqttInitTask_attributes);             //(2)
    ATRece_TaskHandle = osThreadNew(AT_RecvParse, NULL, &ATReceTask_attributes);                 //(3)
    MessageUpdate_TaskHandle = osThreadNew(MessageUpdateTask, NULL, &MessageUpdate_attributes);  //(4)
    MessageUpload_TaskHandle = osThreadNew(MqttSendTask, NULL, &MessageUpload_attributes);       //(5)
    LvHandler_TaskHandle = osThreadNew(LvHandlerTask, NULL, &LvHandlerTask_attributes);          //(5)
    /* add  others ... */
    uint8_t MessUpdataStr;
    osMessageQueuePut(MessageUpdate_Queue, &MessUpdataStr, 0, 1);/*first update message*/
}

/**
 * @brief Support heartbeat to LVGL
 */
void TaskTickHook(void)
{
    lv_tick_inc(1);
}
