#ifndef _WIFI_UART3_H
#define _WIFI_UART3_H

#include <stdio.h>
#include "platform_mutex.h"
#include "ring_buffer.h"

void USART3_Write(char *buf, int len);
void Uart3_Lock_Init(void);
void USART3_Read(char *c, int timeout);

#endif
