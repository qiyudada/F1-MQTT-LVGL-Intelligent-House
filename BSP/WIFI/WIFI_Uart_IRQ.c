#include "WIFI_Uart_IRQ.h"

static ring_buffer uart3_buffer;
extern UART_HandleTypeDef huart3;
static platform_mutex_t uart_recv_mutex;

void Uart3_Lock_Init(void)
{
	platform_mutex_init(&uart_recv_mutex);
	platform_mutex_lock(&uart_recv_mutex);
	ring_buffer_init(&uart3_buffer);	
}

void USART3_IRQHandler(void) 
{
	/*如果是读中断，存入缓冲区*/
	uint32_t isrflags= READ_REG(huart3.Instance->SR);
	uint32_t cr1its= READ_REG(huart3.Instance->CR1);
	char c;

	if(((isrflags&USART_SR_RXNE)!=RESET)&&((cr1its&USART_CR1_RXNEIE)!=RESET))
	{
		// c = (char)HAL_UART_Receive_IT(&huart3, (uint8_t *)&c, 1);
		c=huart3.Instance->DR;
		ring_buffer_write(c, &uart3_buffer);
		platform_mutex_unlock_Fromisr(&uart_recv_mutex);/*must be unlocked before Initation*/
		return;
	}
}

void USART3_Write(char *buf,int len)
{
	int i=0;
	while(i<len)
	{
		while((huart3.Instance->SR & USART_SR_TXE)==0); 
		huart3.Instance->DR = buf[i];
		i++;
	}
}

void USART3_Read(char *c, int timeout)
{
	while(1)
	{
		if (0 == ring_buffer_read((unsigned char *)c, &uart3_buffer))
		{
			return;
		}
		else{
			platform_mutex_lock_timeout(&uart_recv_mutex, timeout);
		}
		
	}
}
