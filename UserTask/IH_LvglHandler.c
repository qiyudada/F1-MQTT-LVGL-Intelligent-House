/*
 * @include
 */
#include "IH_LvglHandler.h"

/*
 * @other headfile
 */
#include "IH_DataManage.h"


static void Lv_Label_Update(void)
{
    lv_event_send(ui_TempLabel, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_HumidLabel, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_DarkLabel, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Hour, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Minute, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(ui_Second, LV_EVENT_VALUE_CHANGED, NULL);
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
        Lv_Label_Update();
        lv_task_handler();
        osDelay(10);
    }
}


