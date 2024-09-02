#ifndef __IH_TASK_INIT_H__
#define __IH_TASK_INIT_H__

/*
 * @ Data Management
 */
#include "IH_DataManage.h"


/*extern define*/
extern osMessageQueueId_t MessageUpdate_Queue;
extern osMessageQueueId_t MessageUpComplete_Queue;

extern osMutexId_t MessageUpload_MutexHandle;

void User_Tasks_Init(void);
void TaskTickHook(void);


#endif
