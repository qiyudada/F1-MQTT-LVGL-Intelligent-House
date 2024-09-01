#include "Uart_Redefine.h"
#include <stdio.h>

/*
*@detail: define 1 to open semihosting function
*/
#if 1
#pragma import(__use_no_semihosting) // 确保没有从 C 库链接使用半主机的函数
void _sys_exit(int x)                // 定义 _sys_exit() 以避免使用半主机模式
{
  x = x;
}
struct __FILE // 标准库需要的支持函数
{
  int handle;
};
/* FILE is typedef ’ d in stdio.h. */
FILE __stdout;

#endif

int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY);
  return ch;
}

