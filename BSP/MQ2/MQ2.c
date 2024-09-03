#include "MQ2.h"

static ADC_HandleTypeDef *g_HADC_MQ2Sensor = &hadc2;
static float R0 = 0;

/*function: MQ2Sensor_Init
parameter: none
return: 0
*/
int MQ2Sensor_Init(void)
{
    /* PA2用作ADC(ADC2_IN2) */
    return HAL_ADC_Start_IT(&hadc2);
}

/*
 * @brief Calculate the R0 value
 */
float MQ2_PPM_Calibration(float volt)
{
    float Temp_RS = 0;
    float Temp_R0 = 0;
    Temp_RS = (3.3f - volt) / volt * RL;
    Temp_R0 = Temp_RS / pow(CAL_PPM / 98.322, 1 / -1.458f);
    return Temp_R0;
}
int MQ2Sensor_Calculate_Concentration(uint32_t ADSample)
{
    float voltage = 0;

    voltage = (3.3f / 4095.0f) * (ADSample);
    /*My RL value is 10*/
    float RS = (3.3f - voltage) / voltage * RL;
    /*Only calculate R0 once*/
    if (R0 == 0)
    {
        R0 = MQ2_PPM_Calibration(voltage);
    }
    /*refer to web blogger document*/
    float ppm = 98.322f * pow(RS / R0, -1.458f);
    return (int)ppm;
}

/*function:MQ2Sensor_Read
parameter: pData
return: 0 success, -1 fail
*/
int MQ2Sensor_Read(int *pData)
{
    uint32_t voltageSample = 0;

    HAL_ADC_Start(g_HADC_MQ2Sensor);
    if (HAL_OK == HAL_ADC_PollForConversion(g_HADC_MQ2Sensor, MQ2_SENSOR_ADC_TIMEOUT))
    {
        voltageSample = HAL_ADC_GetValue(g_HADC_MQ2Sensor);
        *pData = MQ2Sensor_Calculate_Concentration(voltageSample);
        return 0;
    }
    else
    {
        return -1;
    }
}
/*function:MQ2Sensor_Test
parameter: none
return: none
*/
void MQ2Sensor_Test(void)
{
    int ADC_Sample, ADC_Volt;

    MQ2Sensor_Init();

    while (1)
    {

        if (!MQ2Sensor_Read(&ADC_Sample))
        {
            ADC_Volt = ADC_Sample * 330 / 4096;
            printf("MQ2 Sensor Voltage: %d.%d%d\r\n", ADC_Volt / 100, (ADC_Volt / 10) % 10, ADC_Volt % 10);
            printf("MQ2 Sensor Sample: %d\r\n", ADC_Sample);
            // LCD_PrintSignedVal(0, 2, ADC_Sample);
        }
        Delay_ms(2000);
    }
}
