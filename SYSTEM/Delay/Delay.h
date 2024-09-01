#ifndef __Delay_h
#define __Delay_h

#include "stm32f1xx_hal.h"
#include "sys.h"

void Delay_us(uint32_t us);
void Delay_ms(uint32_t nms);
void Delay_s(uint32_t xs);

#if (SYS_RTOS == 1)
uint64_t system_get_ns(void);
#endif

#endif


