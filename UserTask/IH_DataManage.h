#ifndef _IH_DataManage_H_
#define _IH_DataManage_H_

#ifdef __cplusplus
extern "C"
{
#endif
#define IH_USE_HARDWARE 1
/*User configuration*/
#if (IH_USE_HARDWARE)
#define IH_USE_LCD 1
#define IH_USE_MQTT 1
#define IH_USE_WIFI 1
#define IH_USE_LVGL 1
#endif
/*User hardware include*/
#if (IH_USE_LCD)
#include "Lcd.h"
#endif
#if (IH_USE_MQTT)
#include "mqttclient.h"
#endif
#if (IH_USE_WIFI)
#include "ATcommand.h"
#endif
#if (IH_USE_LVGL)
#include "lvgl.h"
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
    } Mqtt_Family_TypeDef;
    /*
     * @typedef Intelligent_House_Structure
     */
    typedef struct
    {
        Mqtt_Family_TypeDef MQTT;
    } IH_Family_TypeDef;
    extern IH_Family_TypeDef IH_Family;
#ifdef __cplusplus
}
#endif


#endif
