#include "MQTT_Task.h"

/*User Web Configuration*/
static char *IP_Port = "1883";
static char *Server_IP = "47.114.187.247"; //"192.168.11.141"
static char *User_Topic = "mcu_test";

_MQTT_TASK_Handle Mqtt_task = {
    NULL,
    NULL,
    NULL,
};

_MQTT_Fun_Element Mqtt_Func={
    NULL,
    NULL,
    (0x01<<1),
    NULL,
    4,
    100,
    NULL,
};




static void Lvgl_Event_Send_Set(void)
{
    lv_event_send(ui_TempLabel, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_HumidLabel, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_DarkLabel, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Hour, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Minute, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Second, LV_EVENT_VALUE_CHANGED, NULL);
}

static void Lvgl_Task_Run_Set(void)
{
    HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);
    Lv_DTH11_Task();
    Lv_LightSensor_Task();
}
/*
 * @name: Lvgl_Display_Task
 * @brief:Display the data from Module
 */

void Lvgl_Display_Task(void *Param)
{
    ui_init();
    while (1)
    {
        Lvgl_Task_Run_Set();
        platform_mutex_lock(&Mqtt_Func.G_xTaskMutex);
        Lvgl_Event_Send_Set();
        lv_task_handler();
        xEventGroupSetBits(Mqtt_Func.Event_Handle,Mqtt_Func. UPDATE_MODE);
        platform_mutex_unlock(&Mqtt_Func.G_xTaskMutex);
        vTaskDelay(pdMS_TO_TICKS(180));
    }
}

/*
 *@function:MQTT_Platform
 *@brief:receive data from Module and send to MQTT
 */
static void MQTT_Platform(void *para)
{

    /*send the message to MQTT servicer*/
    QI_DEBUG("enter MQTT_Platform successfully\r\n");
    char MQTT_buffer[200] = {0}; // data buffer Initialization
    Mqtt_Func.msg.payload = MQTT_buffer;
    Mqtt_Func.msg.qos = QOS0;

    while (1)
    {
        // waitting for ping message
        xEventGroupWaitBits((EventGroupHandle_t)Mqtt_Func.Event_Handle,
                            (EventBits_t)Mqtt_Func.UPDATE_MODE, // add event signal in here
                            (BaseType_t)pdTRUE,       // clear the signal when complete once upload
                            (BaseType_t)pdTRUE,
                            (TickType_t)portMAX_DELAY);
        platform_mutex_lock(&Mqtt_Func.G_xTaskMutex);
        if (xQueueReceive(Mqtt_Func.G_xMessageQueueToMQTT, MQTT_buffer + strlen(MQTT_buffer), pdMS_TO_TICKS(10)) == pdPASS)
        {

            while (xQueueReceive(Mqtt_Func.G_xMessageQueueToMQTT, MQTT_buffer + strlen(MQTT_buffer), pdMS_TO_TICKS(10)) == pdPASS)
            {
                QI_DEBUG("MQTT stack is %d\r\n", (int *)uxTaskGetStackHighWaterMark(Mqtt_task.G_xQueuePlatform));
            }
            Mqtt_Func.msg.payloadlen = strlen(Mqtt_Func.msg.payload);
            mqtt_publish(Mqtt_Func.client, User_Topic, &Mqtt_Func.msg);      // publish the message to mqtt server
            memset(MQTT_buffer, 0, sizeof(MQTT_buffer)); // reset data buffer
            QI_DEBUG("send data to MQTT server successfully\r\n");
        }
        else
        {
            printf("No data received\r\n");
        }
        platform_mutex_unlock(&Mqtt_Func.G_xTaskMutex);
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
static void topic1_handler(void *client, message_data_t *msg)
{
    (void)client;
    MQTT_LOG_I("-----------------------------------------------------------------------------------");
    MQTT_LOG_I("%s:%d %s()...\r\ntopic: %s\r\nmessage:%s", __FILE__, __LINE__, __FUNCTION__, msg->topic_name, (char *)msg->message->payload);
    MQTT_LOG_I("-----------------------------------------------------------------------------------");
}
/*Gross Assigmment
 *Set up MQTT connection
 *Subscribe to topic and send messages
 */
void MQTT_Client_Init(void *Param)
{

    int err;
    while (1)
    {
        memset(&Mqtt_Func.msg, 0, sizeof(Mqtt_Func.msg));
        mqtt_log_init();
        Mqtt_Func.client = mqtt_lease();

        mqtt_set_port(Mqtt_Func.client, IP_Port);
        mqtt_set_host(Mqtt_Func.client, Server_IP);
        mqtt_set_client_id(Mqtt_Func.client, random_string(10));
        mqtt_set_user_name(Mqtt_Func.client, random_string(10));
        mqtt_set_password(Mqtt_Func.client, random_string(10));
        mqtt_set_clean_session(Mqtt_Func.client, 1);

        if (0 == mqtt_connect(Mqtt_Func.client))
        {
            /* subscribe topic1,topic2,topic3*/
            err = mqtt_subscribe(Mqtt_Func.client, "topic1", QOS0, topic1_handler); /*subscribe topic1,Only once at most*/
            if (err)
            {
                QI_DEBUG("mqtt_subscribe topic1 err\r\n ");
            }
            err = mqtt_subscribe(Mqtt_Func.client, "topic2", QOS1, NULL); /*subscribe topic2,Only once at least*/
            if (err)
            {

                QI_DEBUG("mqtt_subscribe topic2 err\r\n");
            }

            err = mqtt_subscribe(Mqtt_Func.client, "topic3", QOS2, NULL); /*subscribe topic3, Only receive once*/
            if (err)
            {
                QI_DEBUG("mqtt_subscribe topic3 err\r\n");
            }
            /*subscribe self defined topic*/
            err = mqtt_subscribe(Mqtt_Func.client, User_Topic, QOS0, NULL);
            if (err)
            {
                QI_DEBUG("subscribe err = %d\r\n", err);
            }
            else
            {
                QI_DEBUG("subscribe destination successfully\r\n");
            }
            /*create or clean the task*/
            taskENTER_CRITICAL();
            if (Mqtt_task.G_xMQTT_Client_Task == NULL)
            {
                xTaskCreate(MQTT_Client_Task, "MQTT_Client_Task", 128, NULL, osPriorityHigh2, &Mqtt_task.G_xMQTT_Client_Task);
            }
            vTaskSuspend(Mqtt_task.G_xMQTTClientInitHandle);
            taskEXIT_CRITICAL();
        }
    }
}

void MQTT_Client_Task(void *Param)
{
    QI_DEBUG("enter MQTTClientTask successfully\r\n");
    taskENTER_CRITICAL(); // enter critical area to prevent the task from being interrupted
    /*create Eventgroup task*/
    Mqtt_Func.Event_Handle = xEventGroupCreate();
    /*create Semaphore*/
    platform_mutex_init(&Mqtt_Func.G_xTaskMutex);
    /*create Message Queue*/
    Mqtt_Func.G_xMessageQueueToMQTT = xQueueCreate(Mqtt_Func.MESSAGE_DATA_TX_NUM, Mqtt_Func.MESSAGE_DATA_TX_LEN);

    /* create Process task */
    xTaskCreate(MQTT_Platform, "MQTT_Platform", 512, NULL, osPriorityAboveNormal, &Mqtt_task.G_xQueuePlatform);
    xTaskCreate(Lvgl_Display_Task, "LvglDisplayTask", 1536, NULL, osPriorityHigh, &Mqtt_task.G_xLvgl_Task_Handler);

    /*delete create task to free memory*/
    if (Mqtt_task.G_xMQTT_Client_Task != NULL)
    {
        vTaskDelete(Mqtt_task.G_xMQTT_Client_Task);
        Mqtt_task.G_xMQTT_Client_Task = NULL;
        QI_DEBUG("G_xMQTT_Client_Task task has deleted\r\n");
    }
    taskEXIT_CRITICAL();
}
