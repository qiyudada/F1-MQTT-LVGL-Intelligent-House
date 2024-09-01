#include "Lightsensor.h"


static ADC_HandleTypeDef *g_HADC_LightSensor = &hadc1;

/*function: LightSensor_Init
parameter: none
return: none
*/
void LightSensor_Init(void)
{
    /* PA1用作ADC(ADC1_IN1) */
    HAL_ADC_Start_IT(&hadc1);
}
/*function:LightSensor_Read
parameter: pData
return: 0 success, -1 fail
*/
int LightSensor_Read(int *pData)
{
    HAL_ADC_Start(g_HADC_LightSensor);
    if (HAL_OK == HAL_ADC_PollForConversion(g_HADC_LightSensor, LIGHT_SENSOR_ADC_TIMEOUT))
    {
        *pData = HAL_ADC_GetValue(g_HADC_LightSensor);
        return 0;
    }
    else
    {
        return -1;
    }
}
/*function:LightSensor_Test
parameter: none
return: none
*/
void LightSensor_Test(void)
{
    int ADC_Sample, ADC_Volt;

    LightSensor_Init();

    while (1)
    {

        if (!LightSensor_Read(&ADC_Sample))
        {
            ADC_Volt = ADC_Sample * 330 / 4096;
            printf("Light Sensor Voltage: %d.%d%d\r\n", ADC_Volt / 100, (ADC_Volt / 10) % 10, ADC_Volt % 10);
            printf("Light Sensor Sample: %d\r\n", ADC_Sample);
            // LCD_PrintSignedVal(0, 2, ADC_Sample);
        }
        Delay_ms(2000);
    }
}


