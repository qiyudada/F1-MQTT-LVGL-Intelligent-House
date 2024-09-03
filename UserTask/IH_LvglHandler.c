/*
 * @include
 */
#include "IH_LvglHandler.h"

/*
 * @other headfile
 */
#include "IH_DataManage.h"


void Lv_Label_Update(void)
{
    lv_event_send(ui_TempLabel, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_HumidLabel, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_DarkLabel, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_CO2Label, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Hour, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Minute, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Second, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Year, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Month, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Day, LV_EVENT_VALUE_CHANGED, NULL);

}



/**
 * @brief  LVGL Handler task, to run the lvgl
 * @param  argument: Not used
 * @retval None
 */
void LvHandlerTask(void *argument)
{
    //uint8_t IdleBreakstr = 0;
    while (1)
    {
        lv_task_handler();
        QI_DEBUG("lvtaskhandler stack is %d\r\n", (int *)osThreadGetStackSpace(LvHandler_TaskHandle));
        osDelay(10);
    }
}


