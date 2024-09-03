#ifndef __MQ2_H__
#define __MQ2_H__

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <math.h>
#include "adc.h"
#include "Lcd.h"

#define MQ2_SENSOR_ADC_TIMEOUT 500

#define RL 10
#define CAL_PPM 10

int MQ2Sensor_Init(void);
float MQ2_PPM_Calibration(float volt);
int MQ2Sensor_Calculate_Concentration(uint32_t ADSample);
int MQ2Sensor_Read(int *pData);
void MQ2Sensor_Test(void);

#endif
