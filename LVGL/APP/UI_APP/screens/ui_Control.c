// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Control_screen_init(void)
{
    ui_Control = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Control, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_text_font(ui_Control, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LED1 = lv_obj_create(ui_Control);
    lv_obj_remove_style_all(ui_LED1);
    lv_obj_set_width(ui_LED1, 120);
    lv_obj_set_height(ui_LED1, 38);
    lv_obj_set_x(ui_LED1, 63);
    lv_obj_set_y(ui_LED1, -54);
    lv_obj_set_align(ui_LED1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_LED1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Led1TEXT = lv_textarea_create(ui_LED1);
    lv_obj_set_width(ui_Led1TEXT, 55);
    lv_obj_set_height(ui_Led1TEXT, LV_SIZE_CONTENT);    /// 25
    lv_obj_set_x(ui_Led1TEXT, -32);
    lv_obj_set_y(ui_Led1TEXT, -1);
    lv_obj_set_align(ui_Led1TEXT, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_Led1TEXT, "LED1");
    lv_textarea_set_placeholder_text(ui_Led1TEXT, "Placeholder...");
    lv_textarea_set_one_line(ui_Led1TEXT, true);
    lv_obj_set_style_text_font(ui_Led1TEXT, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_Led1SWITCH = lv_switch_create(ui_LED1);
    lv_obj_set_width(ui_Led1SWITCH, 50);
    lv_obj_set_height(ui_Led1SWITCH, 25);
    lv_obj_set_x(ui_Led1SWITCH, 30);
    lv_obj_set_y(ui_Led1SWITCH, -2);
    lv_obj_set_align(ui_Led1SWITCH, LV_ALIGN_CENTER);


    ui_LED2 = lv_obj_create(ui_Control);
    lv_obj_remove_style_all(ui_LED2);
    lv_obj_set_width(ui_LED2, 120);
    lv_obj_set_height(ui_LED2, 38);
    lv_obj_set_x(ui_LED2, 63);
    lv_obj_set_y(ui_LED2, -13);
    lv_obj_set_align(ui_LED2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_LED2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Led2TEXT = lv_textarea_create(ui_LED2);
    lv_obj_set_width(ui_Led2TEXT, 55);
    lv_obj_set_height(ui_Led2TEXT, LV_SIZE_CONTENT);    /// 25
    lv_obj_set_x(ui_Led2TEXT, -32);
    lv_obj_set_y(ui_Led2TEXT, -2);
    lv_obj_set_align(ui_Led2TEXT, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_Led2TEXT, "LED2");
    lv_textarea_set_placeholder_text(ui_Led2TEXT, "Placeholder...");
    lv_textarea_set_one_line(ui_Led2TEXT, true);
    lv_obj_set_style_text_font(ui_Led2TEXT, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_Led2Switch = lv_switch_create(ui_LED2);
    lv_obj_set_width(ui_Led2Switch, 50);
    lv_obj_set_height(ui_Led2Switch, 25);
    lv_obj_set_x(ui_Led2Switch, 30);
    lv_obj_set_y(ui_Led2Switch, -3);
    lv_obj_set_align(ui_Led2Switch, LV_ALIGN_CENTER);


    ui_BEEP = lv_obj_create(ui_Control);
    lv_obj_remove_style_all(ui_BEEP);
    lv_obj_set_width(ui_BEEP, 120);
    lv_obj_set_height(ui_BEEP, 38);
    lv_obj_set_x(ui_BEEP, 62);
    lv_obj_set_y(ui_BEEP, 28);
    lv_obj_set_align(ui_BEEP, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_BEEP, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_BeepTEXT = lv_textarea_create(ui_BEEP);
    lv_obj_set_width(ui_BeepTEXT, 55);
    lv_obj_set_height(ui_BeepTEXT, LV_SIZE_CONTENT);    /// 25
    lv_obj_set_x(ui_BeepTEXT, -31);
    lv_obj_set_y(ui_BeepTEXT, -2);
    lv_obj_set_align(ui_BeepTEXT, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_BeepTEXT, "Beep");
    lv_textarea_set_placeholder_text(ui_BeepTEXT, "Placeholder...");
    lv_textarea_set_one_line(ui_BeepTEXT, true);
    lv_obj_set_style_text_font(ui_BeepTEXT, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_BeepSWITCH = lv_switch_create(ui_BEEP);
    lv_obj_set_width(ui_BeepSWITCH, 50);
    lv_obj_set_height(ui_BeepSWITCH, 25);
    lv_obj_set_x(ui_BeepSWITCH, 31);
    lv_obj_set_y(ui_BeepSWITCH, -3);
    lv_obj_set_align(ui_BeepSWITCH, LV_ALIGN_CENTER);


    ui_MOTOR = lv_obj_create(ui_Control);
    lv_obj_remove_style_all(ui_MOTOR);
    lv_obj_set_width(ui_MOTOR, 120);
    lv_obj_set_height(ui_MOTOR, 38);
    lv_obj_set_x(ui_MOTOR, 62);
    lv_obj_set_y(ui_MOTOR, 69);
    lv_obj_set_align(ui_MOTOR, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_MOTOR, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_MotorTEXT = lv_textarea_create(ui_MOTOR);
    lv_obj_set_width(ui_MotorTEXT, 55);
    lv_obj_set_height(ui_MotorTEXT, LV_SIZE_CONTENT);    /// 25
    lv_obj_set_x(ui_MotorTEXT, -31);
    lv_obj_set_y(ui_MotorTEXT, -2);
    lv_obj_set_align(ui_MotorTEXT, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_MotorTEXT, "Motor");
    lv_textarea_set_placeholder_text(ui_MotorTEXT, "Placeholder...");
    lv_textarea_set_one_line(ui_MotorTEXT, true);
    lv_obj_set_style_text_font(ui_MotorTEXT, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_MotorSWITCH = lv_switch_create(ui_MOTOR);
    lv_obj_set_width(ui_MotorSWITCH, 50);
    lv_obj_set_height(ui_MotorSWITCH, 25);
    lv_obj_set_x(ui_MotorSWITCH, 31);
    lv_obj_set_y(ui_MotorSWITCH, -3);
    lv_obj_set_align(ui_MotorSWITCH, LV_ALIGN_CENTER);


    ui_PIC2 = lv_obj_create(ui_Control);
    lv_obj_remove_style_all(ui_PIC2);
    lv_obj_set_width(ui_PIC2, 120);
    lv_obj_set_height(ui_PIC2, 180);
    lv_obj_set_x(ui_PIC2, -60);
    lv_obj_set_y(ui_PIC2, -79);
    lv_obj_set_align(ui_PIC2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PIC2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_PIC2, &ui_img_iu2_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HOME = lv_obj_create(ui_Control);
    lv_obj_remove_style_all(ui_HOME);
    lv_obj_set_width(ui_HOME, 40);
    lv_obj_set_height(ui_HOME, 40);
    lv_obj_set_x(ui_HOME, -7);
    lv_obj_set_y(ui_HOME, 128);
    lv_obj_set_align(ui_HOME, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_HOME, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_HOME, &ui_img_icn_home_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_HOME, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_HOME, lv_color_hex(0xDEB0B4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_HOME, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WEATHER = lv_obj_create(ui_Control);
    lv_obj_remove_style_all(ui_WEATHER);
    lv_obj_set_width(ui_WEATHER, 100);
    lv_obj_set_height(ui_WEATHER, 74);
    lv_obj_set_x(ui_WEATHER, 64);
    lv_obj_set_y(ui_WEATHER, -116);
    lv_obj_set_align(ui_WEATHER, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_WEATHER, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_WEATHER, &ui_img_cloud_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_WEATHER, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_WEATHER, lv_color_hex(0xDEAAAC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_WEATHER, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Led1SWITCH, ui_event_Led1SWITCH, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Led2Switch, ui_event_Led2Switch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BeepSWITCH, ui_event_BeepSWITCH, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MotorSWITCH, ui_event_MotorSWITCH, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_HOME, ui_event_HOME, LV_EVENT_ALL, NULL);

}
