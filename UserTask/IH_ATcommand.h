#ifndef _AT_COM_H
#define _AT_COM_H

#include "IH_Task_Init.h"

#include <string.h>
#include <stdio.h>

#include "platform_mutex.h"
#include "Hal_Uart.h"

#include "mqttclient.h"

#define AT_OK 0
#define AT_ERROR -1
#define AT_TIMEOUT -2
#define AT_CMD_TIMOUT 1000
#define AT_RESP_LEN   100

int SetATstatus(int status);
int GetATStatus(void);
int ATInit(void);
int AT_SendCmd(char *cmd,char *resp,int resp_len, int timeout);
void AT_RecvParse(void *param);
int ATReadData(unsigned char *buf, int timeout);
int ATSendData(unsigned char *buf, int len, int timeout);



#endif
