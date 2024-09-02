#ifndef __IH_TASK_INIT_H__
#define __IH_TASK_INIT_H__

/*
 * @ Data Management
 */
#include "IH_DataManage.h"


/*extern define*/
/*taskhanler*/
extern osThreadId_t HardwareInit_TaskHandle;
extern osThreadId_t ATRece_TaskHandle;
extern osThreadId_t MQTTInit_TaskHandle;
extern osThreadId_t LvHandler_TaskHandle;
extern osThreadId_t MessageUpload_TaskHandle;
extern osThreadId_t MessageUpdate_TaskHandle;


/*queue*/
extern osMessageQueueId_t MessageUpdate_Queue;
extern osMessageQueueId_t MessageUpComplete_Queue;

/*Mutex*/
extern osMutexId_t MessageUpload_MutexHandle;

/*Timer*/
extern osTimerId_t UpdataTimerHandle;


void User_Tasks_Init(void);
void TaskTickHook(void);

#endif
