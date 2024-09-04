#include "IH_DataManage.h"

/**************************************************************************/
/*!
    @brief  to get the real time clock from the hardware

    @param  nowdatetime to storge the data&time

    @return None
*/
/**************************************************************************/
void IH_RTC_Get_TimeDate(DateTime_Family_TypeDef *nowdatetime)
{

#if IH_USE_RTC
    if (nowdatetime != NULL)
    {
        RTC_DateTypeDef nowdate;
        RTC_TimeTypeDef nowtime;
        HAL_RTC_GetTime(&hrtc, &nowtime, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc, &nowdate, RTC_FORMAT_BIN);
        nowdatetime->Year = nowdate.Year;
        nowdatetime->Month = nowdate.Month;
        nowdatetime->Date = nowdate.Date;
        nowdatetime->WeekDay = weekday_calculate(nowdatetime->Year, nowdatetime->Month, nowdatetime->Date, 20);
        nowdatetime->Hours = nowtime.Hours;
        nowdatetime->Minutes = nowtime.Minutes;
        nowdatetime->Seconds = nowtime.Seconds;
    }
#else
    nowdatetime->Year = 24;
    nowdatetime->Month = 6;
    nowdatetime->Date = 23;
    nowdatetime->WeekDay = 7;
    nowdatetime->Hours = 11;
    nowdatetime->Minutes = 59;
    nowdatetime->Seconds = 55;
#endif
}

/**************************************************************************/
/*!
    @brief  to set the RTC Date to hardware

    @param  nowdatetime to storge the data&time

    @return None
*/
/**************************************************************************/
void IH_RTC_Set_Date(uint8_t year, uint8_t month, uint8_t date)
{
#if IH_USE_RTC
    RTC_SetDate(year, month, date);
#endif
}

/**************************************************************************/
/*!
    @brief  to set the RTC Date to hardware

    @param  nowdatetime to storge the data&time

    @return None
*/
/**************************************************************************/
void IH_RTC_Set_Time(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
#if IH_USE_RTC
    RTC_SetTime(hours, minutes, seconds);
#endif
}

/**************************************************************************/
/*!
    @brief  to calculate the weekday

    @param  nowdatetime to storge the data&time

    @return None
*/
/**************************************************************************/
uint8_t IH_weekday_calculate(uint8_t setyear, uint8_t setmonth, uint8_t setday, uint8_t century)
{
    int w;
    if (setmonth == 1 || setmonth == 2)
    {
        setyear--, setmonth += 12;
    }
    w = setyear + setyear / 4 + century / 4 + 26 * (setmonth + 1) / 10 + setday - 1 - 2 * century;
    while (w < 0)
        w += 7;
    w %= 7;
    w = (w == 0) ? 7 : w;
    return w;
}

/*USER DATA DEFINE*/
IH_Family_TypeDef IH_Family = {
    .MQTT = {
        .client = NULL,
        .Ip_Port = "1883",
        .Server_Ip = "47.114.187.247",
        .User_Topic = "mcu_test",
        .Msg_Buffer = {0},
    },
    .DTH11 = {
        .ConnectionError = 1,
        .humidity = 65,
        .tempature = 26,
        .DTH11_ReadData = DHT11_Read_Data,
    },
    .Light = {
        .ConnectionError = 1,
        .Light_Value = 1000,
        .Light_Read_Data = LightSensor_Read,
    },
    .CO2 = {
        .ConnectionError = 1,
        .Concentration_Value = 10,
        .MQ2_Read_Data = MQ2Sensor_Read,
    },
    .TIME = {
        .GetTimeDate = IH_RTC_Get_TimeDate,
        .SetDate = IH_RTC_Set_Date,
        .SetTime = IH_RTC_Set_Time,
        .CalculateWeekday = IH_weekday_calculate,
    }};
