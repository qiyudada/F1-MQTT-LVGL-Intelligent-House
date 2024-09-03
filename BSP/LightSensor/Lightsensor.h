#ifndef _Lightsensor_H
#define _Lightsensor_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include "adc.h"
#include "Lcd.h"

/*A0->GPIOA_PIN_1*/

#define LIGHT_SENSOR_ADC_TIMEOUT 500

int LightSensor_Init(void);
int LightSensor_Read(int *pData);
void LightSensor_Test(void);

#endif
