#ifndef _IH_DataManage_H_
#define _IH_DataManage_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "IH_Task_Init.h"

#define IH_USE_HARDWARE 1
/*User configuration*/
#if (IH_USE_HARDWARE)
#define IH_USE_SYS 1
#define IH_USE_LCD 1
#define IH_USE_MQTT 1
#define IH_USE_WIFI 1
#define IH_USE_LVGL 1
#define IH_USE_DTH11 1
#define IH_USE_Light 1
#define IH_USE_Buzzer 0
#define IH_USE_RTC 1
#define IH_USE_Smoke 1
#define IH_USE_MOTOR 0
#endif

/*User hardware include*/
#if (IH_USE_SYS)
#include "main.h"
#include "ring_buffer.h"
#endif

#if (IH_USE_LCD)
#include "Lcd.h"
#include "GUI.h"
#endif

#if (IH_USE_MQTT)
#include "mqttclient.h"
#endif

#if (IH_USE_WIFI)
#include "IH_ATcommand.h"
#endif

#if (IH_USE_LVGL)
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "ui.h"
#endif

#if (IH_USE_DTH11)
#include "DTH11.h"
#endif

#if (IH_USE_Light)
#include "Lightsensor.h"
#endif

#if (IH_USE_Buzzer)
#include "Buzzer.h"
#endif

#if (IH_USE_RTC)
#include "rtc.h"
#endif

#if (IH_USE_Smoke)
#include "MQ2.h"
#endif

#if (IH_USE_MOTOR)
#include "Motor.h"
#endif

    /*
     * @typedef Mqtt_Family_Structure
     */
    typedef struct
    {
        char *Ip_Port;
        char *Server_Ip;
        char *User_Topic;
        mqtt_client_t *client;
        mqtt_message_t msg;
        char Msg_Buffer[512];
    } Mqtt_Family_TypeDef;

    /*
     * @typedef DTH11_Family_Structure
     */
    typedef struct
    {
        int ConnectionError;
        int tempature;
        int humidity;
        int (*DTH11_ReadData)(int *temp, int *humid);
    } DTH11_Family_TypeDef;

    /*
     * @typedef Lightsensor_Family_Structure
     */
    typedef struct
    {
        int ConnectionError;
        int Light_Value;
        int (*Light_Read_Data)(int *Light);
    } Light_Family_TypeDef;

    /*
     * @typedef MQ2sensor_Family_Structure
     */
    typedef struct
    {
        int ConnectionError;
        int Concentration_Value;
        int (*MQ2_Read_Data)(int *Concentration);
    } MQ2_Family_TypeDef;
    /**
     * @brief  IH RTC DateTime structure definition
     */
    typedef struct
    {
        uint8_t WeekDay; /*!< Specifies the RTC Date WeekDay.
                             This parameter can be a value of @ref RTC_WeekDay_Definitions */

        uint8_t Month; /*!< Specifies the RTC Date Month (in BCD format).
                           This parameter can be a value of @ref RTC_Month_Date_Definitions */

        uint8_t Date; /*!< Specifies the RTC Date.
                          This parameter must be a number between Min_Data = 1 and Max_Data = 31 */

        uint8_t Year; /*!< Specifies the RTC Date Year.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 99 */

        uint8_t Hours; /*!< Specifies the RTC Time Hour.
                           This parameter must be a number between Min_Data = 0 and Max_Data = 12 if the RTC_HourFormat_12 is selected
                           This parameter must be a number between Min_Data = 0 and Max_Data = 23 if the RTC_HourFormat_24 is selected */

        uint8_t Minutes; /*!< Specifies the RTC Time Minutes.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 59 */

        uint8_t Seconds; /*!< Specifies the RTC Time Seconds.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 59 */

    } DateTime_Family_TypeDef;

    /**
     * @brief  IH RTC Interface definition
     */
    typedef struct
    {
        void (*GetTimeDate)(DateTime_Family_TypeDef *nowdatetime);
        void (*SetDate)(uint8_t year, uint8_t month, uint8_t date);
        void (*SetTime)(uint8_t hours, uint8_t minutes, uint8_t seconds);
        uint8_t (*CalculateWeekday)(uint8_t setyear, uint8_t setmonth, uint8_t setday, uint8_t century);
    } RTC_Family_TypeDef;

    /*
     * @typedef Intelligent_House_Structure
     */
    typedef struct
    {
        DateTime_Family_TypeDef NOWTIME;
        RTC_Family_TypeDef TIME;
        Light_Family_TypeDef Light;
        MQ2_Family_TypeDef CO2;
        DTH11_Family_TypeDef DTH11;
        Mqtt_Family_TypeDef MQTT;
    } IH_Family_TypeDef;

    extern IH_Family_TypeDef IH_Family;

#ifdef __cplusplus
}
#endif

#endif
