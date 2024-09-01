#include "Hal_Uart.h"

void Hal_Uart_Send(char* buf, int len)
{
    USART3_Write(buf,len);
}

void HAL_AT_Receive(char *c, int timeout)
{
	/* 从环形缓冲区中得到数据 */
	/* 无数据则阻塞 */
	USART3_Read(c, timeout);
}
