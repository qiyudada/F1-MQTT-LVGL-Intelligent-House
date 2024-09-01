#ifndef _Lightsensor_H
#define _Lightsensor_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

#include "platform_mutex.h"
#include "adc.h"
#include "usart.h"
#include "tim.h"
#include "semphr.h"

#include "Lcd.h"

/*A0->GPIOA_PIN_1*/

#define LIGHT_SENSOR_ADC_TIMEOUT 500

extern ADC_HandleTypeDef hadc1;



void LightSensor_Init(void);
int LightSensor_Read(int *pData);
void LightSensor_Test(void);
void Lv_LightSensor_Task(void);

#endif
