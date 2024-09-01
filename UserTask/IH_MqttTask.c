/*
 * @include
 */
#include "IH_MqttTask.h"


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
