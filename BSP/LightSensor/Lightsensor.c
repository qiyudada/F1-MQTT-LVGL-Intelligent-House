#include "Lightsensor.h"

Light_Data L_Data;

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

void Lv_LightSensor_Task(void)
{
    platform_mutex_lock(&Mqtt_Func.G_xTaskMutex);
    if (!LightSensor_Read(&L_Data.Sample))
    {
        L_Data.Volt = L_Data.Sample * 330 / 4096;
        sprintf(L_Data.data_sensor, "\"Light\":\"%d\",\"Volt\":\"%d.%d%d\",", L_Data.Sample, L_Data.Volt / 100, (L_Data.Volt / 10) % 10, L_Data.Volt % 10);
        xQueueSend(Mqtt_Func.G_xMessageQueueToMQTT, &L_Data.data_sensor, NULL);
        QI_DEBUG("Send light datas successfully\r\n");
        memset(L_Data.data_sensor, 0, sizeof(L_Data));
    }
    else
    {
        QI_DEBUG("Light Sensor Read Fail\r\n");
    }
    platform_mutex_unlock(&Mqtt_Func.G_xTaskMutex);
}
