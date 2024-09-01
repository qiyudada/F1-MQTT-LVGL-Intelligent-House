#ifndef __IH_TASK_INIT_H__
#define __IH_TASK_INIT_H__


#include "FreeRTOS.h"
#include "cmsis_os.h"

void User_Tasks_Init(void);
void TaskTickHook(void);


#endif
