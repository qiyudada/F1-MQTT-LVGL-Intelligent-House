#ifndef _STM32_Hal_H
#define _STM32_Hal_H

#include <stdio.h>
#include "ring_buffer.h"
#include "WIFI_Uart_IRQ.h"


void Hal_Uart_Send(char* buf, int len);
void HAL_AT_Receive(char *c, int timeout);


#endif
