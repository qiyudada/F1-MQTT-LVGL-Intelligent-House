#ifndef __UART_REDEFINE_H
#define __UART_REDEFINE_H

#include "stm32f1xx_hal.h"
#include "usart.h"
#include <stdio.h>

int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif
