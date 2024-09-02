/*
 * @include
 */
#include "IH_MqttTask.h"
/*
* @other headfile
*/
#include "IH_Task_Init.h"
#include "IH_DataManage.h"



/**
 * @brief mqtt init task
 */
void MqttInitTask(void* argument)
{
    int err;
    while (1)
    {
        memset(&IH_Family.MQTT.msg, 0, sizeof(IH_Family.MQTT.msg));
        mqtt_log_init();
        IH_Family.MQTT.client = mqtt_lease();
        mqtt_set_port(IH_Family.MQTT.client, IH_Family.MQTT.Ip_Port);
        mqtt_set_host(IH_Family.MQTT.client, IH_Family.MQTT.Server_Ip);
        mqtt_set_client_id(IH_Family.MQTT.client, random_string(10));
        mqtt_set_user_name(IH_Family.MQTT.client, random_string(10));
        mqtt_set_password(IH_Family.MQTT.client, random_string(10));
        mqtt_set_clean_session(IH_Family.MQTT.client, 1);
        if (0 == mqtt_connect(IH_Family.MQTT.client))
        {
            /* subscribe topic1,topic2,topic3*/
            err = mqtt_subscribe(IH_Family.MQTT.client, "topic1", QOS0, NULL); /*subscribe topic1,Only once at most*/
            if (err)
            {
                QI_DEBUG("mqtt_subscribe topic1 err\r\n ");
            }
            err = mqtt_subscribe(IH_Family.MQTT.client, "topic2", QOS1, NULL); /*subscribe topic2,Only once at least*/
            if (err)
            {
                QI_DEBUG("mqtt_subscribe topic2 err\r\n");
            }
            err = mqtt_subscribe(IH_Family.MQTT.client, "topic3", QOS2, NULL); /*subscribe topic3, Only receive once*/
            if (err)
            {
                QI_DEBUG("mqtt_subscribe topic3 err\r\n");
            }
            /*subscribe self defined topic*/
            err = mqtt_subscribe(IH_Family.MQTT.client,(char*)IH_Family.MQTT.User_Topic, QOS0, NULL);
            if (err)
            {
                QI_DEBUG("subscribe err = %d\r\n", err);
            }
            else
            {
                QI_DEBUG("subscribe destination successfully\r\n");
            }
        }
        vTaskSuspend(NULL);
    }
}

/**
 * @brief send the message to MQTT servicer
 */
void MqttSendTask(void* argument)
{
     
    QI_DEBUG("enter MQTT_Platform successfully\r\n");
    char MQTT_buffer[200] = {0}; // data buffer Initialization
    IH_Family.MQTT.msg.payload = MQTT_buffer;
    IH_Family.MQTT.msg.qos= QOS0;
    while (1)
    {
        uint8_t MessComStr;
        //osMutexAcquire(MessageUpload_MutexHandle,portMAX_DELAY);
        if (osMessageQueueGet(MessageUpComplete_Queue, &MessComStr, NULL, pdMS_TO_TICKS(10)) == osOK)
        {
            sprintf(MQTT_buffer,"\"temperature\":\"%d\",\"humidity\":\"%d\",\"light:\"%d\"" \
            ,IH_Family.DTH11.tempature,IH_Family.DTH11.humidity,IH_Family.Light.Light_Value);

            IH_Family.MQTT.msg.payloadlen = strlen(MQTT_buffer);
            mqtt_publish(IH_Family.MQTT.client,IH_Family.MQTT.User_Topic,&IH_Family.MQTT.msg);
            memset(MQTT_buffer, 0, sizeof(MQTT_buffer));
            QI_DEBUG("send data to MQTT server successfully\r\n");
        }
        else
        {
            QI_DEBUG("No data received\r\n");
        }
       // osMutexRelease(MessageUpload_MutexHandle);
        osDelay(pdMS_TO_TICKS(500));
    }
}

