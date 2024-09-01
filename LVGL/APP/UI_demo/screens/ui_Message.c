// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Message_screen_init(void)
{
    ui_Message = lv_obj_create(NULL);
    lv_obj_add_flag(ui_Message, LV_OBJ_FLAG_CHECKABLE);     /// Flags
    lv_obj_clear_flag(ui_Message, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_set_style_bg_img_src(ui_Message, &ui__temporary_image, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    ui_Tempature = lv_obj_create(ui_Message);
    lv_obj_remove_style_all(ui_Tempature);
    lv_obj_set_width(ui_Tempature, 120);
    lv_obj_set_height(ui_Tempature, 120);
    lv_obj_set_x(ui_Tempature, 55);
    lv_obj_set_y(ui_Tempature, -38);
    lv_obj_set_align(ui_Tempature, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Tempature, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TempArc = lv_arc_create(ui_Tempature);
    lv_obj_set_width(ui_TempArc, 110);
    lv_obj_set_height(ui_TempArc, 110);
    lv_obj_set_x(ui_TempArc, 3);
    lv_obj_set_y(ui_TempArc, 4);
    lv_obj_set_align(ui_TempArc, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_TempArc, LV_OBJ_FLAG_CHECKABLE);     /// Flags
    lv_obj_clear_flag(ui_TempArc, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_arc_set_value(ui_TempArc, 50);
    lv_obj_set_style_arc_color(ui_TempArc, lv_color_hex(0xDAD8D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_TempArc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_TempArc, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_TempArc, lv_color_hex(0x038ED2), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_TempArc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_TempArc, 8, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_TempArc, 10, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TempArc, lv_color_hex(0x10BC9C), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TempArc, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_TempatureNum = lv_obj_create(ui_Tempature);
    lv_obj_remove_style_all(ui_TempatureNum);
    lv_obj_set_width(ui_TempatureNum, 50);
    lv_obj_set_height(ui_TempatureNum, 50);
    lv_obj_set_x(ui_TempatureNum, 3);
    lv_obj_set_y(ui_TempatureNum, 3);
    lv_obj_set_align(ui_TempatureNum, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_TempatureNum, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TempLabel = lv_label_create(ui_TempatureNum);
    lv_obj_set_width(ui_TempLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TempLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TempLabel, 0);
    lv_obj_set_y(ui_TempLabel, 1);
    lv_obj_set_align(ui_TempLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TempLabel, "Temp");
    lv_obj_add_flag(ui_TempLabel, LV_OBJ_FLAG_CHECKABLE);     /// Flags

    ui_Humidity = lv_obj_create(ui_Message);
    lv_obj_remove_style_all(ui_Humidity);
    lv_obj_set_width(ui_Humidity, 110);
    lv_obj_set_height(ui_Humidity, 40);
    lv_obj_set_x(ui_Humidity, -62);
    lv_obj_set_y(ui_Humidity, 48);
    lv_obj_set_align(ui_Humidity, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Humidity, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_humidPic = lv_obj_create(ui_Humidity);
    lv_obj_remove_style_all(ui_humidPic);
    lv_obj_set_width(ui_humidPic, 30);
    lv_obj_set_height(ui_humidPic, 30);
    lv_obj_set_x(ui_humidPic, -40);
    lv_obj_set_y(ui_humidPic, -1);
    lv_obj_set_align(ui_humidPic, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_humidPic, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_humidPic, &ui_img_weather_1_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_humidPic, lv_color_hex(0x3D4CA0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_humidPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HumidText = lv_obj_create(ui_Humidity);
    lv_obj_remove_style_all(ui_HumidText);
    lv_obj_set_width(ui_HumidText, 62);
    lv_obj_set_height(ui_HumidText, 30);
    lv_obj_set_x(ui_HumidText, 7);
    lv_obj_set_y(ui_HumidText, 0);
    lv_obj_set_align(ui_HumidText, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_HumidText, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_HumidLabel = lv_label_create(ui_HumidText);
    lv_obj_set_width(ui_HumidLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_HumidLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_HumidLabel, 0);
    lv_obj_set_y(ui_HumidLabel, -1);
    lv_obj_set_align(ui_HumidLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_HumidLabel, "humid");
    lv_obj_add_flag(ui_HumidLabel, LV_OBJ_FLAG_CHECKABLE);     /// Flags

    ui_Led1 = lv_obj_create(ui_Message);
    lv_obj_remove_style_all(ui_Led1);
    lv_obj_set_width(ui_Led1, 120);
    lv_obj_set_height(ui_Led1, 38);
    lv_obj_set_x(ui_Led1, -58);
    lv_obj_set_y(ui_Led1, 96);
    lv_obj_set_align(ui_Led1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Led1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Led1Text = lv_textarea_create(ui_Led1);
    lv_obj_set_width(ui_Led1Text, 55);
    lv_obj_set_height(ui_Led1Text, LV_SIZE_CONTENT);    /// 25
    lv_obj_set_x(ui_Led1Text, -32);
    lv_obj_set_y(ui_Led1Text, -1);
    lv_obj_set_align(ui_Led1Text, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_Led1Text, "LED1");
    lv_textarea_set_placeholder_text(ui_Led1Text, "Placeholder...");
    lv_textarea_set_one_line(ui_Led1Text, true);



    ui_Led1Switch = lv_switch_create(ui_Led1);
    lv_obj_set_width(ui_Led1Switch, 50);
    lv_obj_set_height(ui_Led1Switch, 25);
    lv_obj_set_x(ui_Led1Switch, 30);
    lv_obj_set_y(ui_Led1Switch, -2);
    lv_obj_set_align(ui_Led1Switch, LV_ALIGN_CENTER);


    ui_Led2 = lv_obj_create(ui_Message);
    lv_obj_remove_style_all(ui_Led2);
    lv_obj_set_width(ui_Led2, 120);
    lv_obj_set_height(ui_Led2, 38);
    lv_obj_set_x(ui_Led2, -58);
    lv_obj_set_y(ui_Led2, 138);
    lv_obj_set_align(ui_Led2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Led2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Led2Text = lv_textarea_create(ui_Led2);
    lv_obj_set_width(ui_Led2Text, 55);
    lv_obj_set_height(ui_Led2Text, LV_SIZE_CONTENT);    /// 25
    lv_obj_set_x(ui_Led2Text, -32);
    lv_obj_set_y(ui_Led2Text, -2);
    lv_obj_set_align(ui_Led2Text, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_Led2Text, "LED2");
    lv_textarea_set_placeholder_text(ui_Led2Text, "Placeholder...");
    lv_textarea_set_one_line(ui_Led2Text, true);



    ui_Led2Switch = lv_switch_create(ui_Led2);
    lv_obj_set_width(ui_Led2Switch, 50);
    lv_obj_set_height(ui_Led2Switch, 25);
    lv_obj_set_x(ui_Led2Switch, 30);
    lv_obj_set_y(ui_Led2Switch, -3);
    lv_obj_set_align(ui_Led2Switch, LV_ALIGN_CENTER);


    ui_Time = lv_obj_create(ui_Message);
    lv_obj_remove_style_all(ui_Time);
    lv_obj_set_width(ui_Time, 231);
    lv_obj_set_height(ui_Time, 50);
    lv_obj_set_x(ui_Time, -1);
    lv_obj_set_y(ui_Time, -130);
    lv_obj_set_align(ui_Time, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Time, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ClockPic = lv_obj_create(ui_Time);
    lv_obj_remove_style_all(ui_ClockPic);
    lv_obj_set_width(ui_ClockPic, 50);
    lv_obj_set_height(ui_ClockPic, 50);
    lv_obj_set_x(ui_ClockPic, -85);
    lv_obj_set_y(ui_ClockPic, -1);
    lv_obj_set_align(ui_ClockPic, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ClockPic, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ClockPic, &ui_img_time_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_ClockPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_ClockPic, lv_color_hex(0xB63707), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_ClockPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TimeContent = lv_obj_create(ui_Time);
    lv_obj_remove_style_all(ui_TimeContent);
    lv_obj_set_width(ui_TimeContent, 176);
    lv_obj_set_height(ui_TimeContent, 50);
    lv_obj_set_x(ui_TimeContent, 30);
    lv_obj_set_y(ui_TimeContent, -1);
    lv_obj_set_align(ui_TimeContent, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_TimeContent, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Hour = lv_label_create(ui_TimeContent);
    lv_obj_set_width(ui_Hour, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Hour, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Hour, -59);
    lv_obj_set_y(ui_Hour, 0);
    lv_obj_set_align(ui_Hour, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Hour, "Hour");

    ui_Minute = lv_label_create(ui_TimeContent);
    lv_obj_set_width(ui_Minute, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Minute, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Minute, -4);
    lv_obj_set_y(ui_Minute, 0);
    lv_obj_set_align(ui_Minute, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Minute, "Minute");

    ui_Second = lv_label_create(ui_TimeContent);
    lv_obj_set_width(ui_Second, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Second, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Second, 57);
    lv_obj_set_y(ui_Second, 0);
    lv_obj_set_align(ui_Second, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Second, "Second");

    ui_Picture = lv_obj_create(ui_Message);
    lv_obj_remove_style_all(ui_Picture);
    lv_obj_set_width(ui_Picture, 100);
    lv_obj_set_height(ui_Picture, 100);
    lv_obj_set_x(ui_Picture, -59);
    lv_obj_set_y(ui_Picture, -42);
    lv_obj_set_align(ui_Picture, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Picture, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_Picture, &ui_img_iu_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Beep = lv_obj_create(ui_Message);
    lv_obj_remove_style_all(ui_Beep);
    lv_obj_set_width(ui_Beep, 120);
    lv_obj_set_height(ui_Beep, 38);
    lv_obj_set_x(ui_Beep, 62);
    lv_obj_set_y(ui_Beep, 95);
    lv_obj_set_align(ui_Beep, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Beep, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_BeepText = lv_textarea_create(ui_Beep);
    lv_obj_set_width(ui_BeepText, 55);
    lv_obj_set_height(ui_BeepText, LV_SIZE_CONTENT);    /// 25
    lv_obj_set_x(ui_BeepText, -31);
    lv_obj_set_y(ui_BeepText, -2);
    lv_obj_set_align(ui_BeepText, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_BeepText, "Beep");
    lv_textarea_set_placeholder_text(ui_BeepText, "Placeholder...");
    lv_textarea_set_one_line(ui_BeepText, true);



    ui_BeepSwitch = lv_switch_create(ui_Beep);
    lv_obj_set_width(ui_BeepSwitch, 50);
    lv_obj_set_height(ui_BeepSwitch, 25);
    lv_obj_set_x(ui_BeepSwitch, 31);
    lv_obj_set_y(ui_BeepSwitch, -3);
    lv_obj_set_align(ui_BeepSwitch, LV_ALIGN_CENTER);


    ui_Motor = lv_obj_create(ui_Message);
    lv_obj_remove_style_all(ui_Motor);
    lv_obj_set_width(ui_Motor, 120);
    lv_obj_set_height(ui_Motor, 38);
    lv_obj_set_x(ui_Motor, 62);
    lv_obj_set_y(ui_Motor, 136);
    lv_obj_set_align(ui_Motor, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Motor, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_MotorText = lv_textarea_create(ui_Motor);
    lv_obj_set_width(ui_MotorText, 55);
    lv_obj_set_height(ui_MotorText, LV_SIZE_CONTENT);    /// 25
    lv_obj_set_x(ui_MotorText, -31);
    lv_obj_set_y(ui_MotorText, -2);
    lv_obj_set_align(ui_MotorText, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_MotorText, "Motor");
    lv_textarea_set_placeholder_text(ui_MotorText, "Placeholder...");
    lv_textarea_set_one_line(ui_MotorText, true);



    ui_MotorSwitch = lv_switch_create(ui_Motor);
    lv_obj_set_width(ui_MotorSwitch, 50);
    lv_obj_set_height(ui_MotorSwitch, 25);
    lv_obj_set_x(ui_MotorSwitch, 31);
    lv_obj_set_y(ui_MotorSwitch, -3);
    lv_obj_set_align(ui_MotorSwitch, LV_ALIGN_CENTER);


    ui_Light = lv_obj_create(ui_Message);
    lv_obj_remove_style_all(ui_Light);
    lv_obj_set_width(ui_Light, 110);
    lv_obj_set_height(ui_Light, 40);
    lv_obj_set_x(ui_Light, 62);
    lv_obj_set_y(ui_Light, 47);
    lv_obj_set_align(ui_Light, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Light, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DarkPic = lv_obj_create(ui_Light);
    lv_obj_remove_style_all(ui_DarkPic);
    lv_obj_set_width(ui_DarkPic, 30);
    lv_obj_set_height(ui_DarkPic, 30);
    lv_obj_set_x(ui_DarkPic, -40);
    lv_obj_set_y(ui_DarkPic, -1);
    lv_obj_set_align(ui_DarkPic, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_DarkPic, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_DarkPic, &ui_img_dark_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_DarkPic, lv_color_hex(0x3D4CA0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_DarkPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DarkContain = lv_obj_create(ui_Light);
    lv_obj_remove_style_all(ui_DarkContain);
    lv_obj_set_width(ui_DarkContain, 62);
    lv_obj_set_height(ui_DarkContain, 30);
    lv_obj_set_x(ui_DarkContain, 7);
    lv_obj_set_y(ui_DarkContain, 0);
    lv_obj_set_align(ui_DarkContain, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_DarkContain, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DarkLabel = lv_label_create(ui_DarkContain);
    lv_obj_set_width(ui_DarkLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DarkLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DarkLabel, 0);
    lv_obj_set_y(ui_DarkLabel, -1);
    lv_obj_set_align(ui_DarkLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DarkLabel, "intens");
    lv_obj_add_flag(ui_DarkLabel, LV_OBJ_FLAG_CHECKABLE);     /// Flags

    lv_obj_add_event_cb(ui_TempArc, ui_event_TempArc, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TempLabel, ui_event_TempLabel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_HumidLabel, ui_event_HumidLable, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Led1Switch, ui_event_Led1Switch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Led2Switch, ui_event_Led2Switch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Hour, ui_event_Hour, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Minute, ui_event_Minute, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Second, ui_event_Second, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Beep, ui_event_Beep, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DarkLabel, ui_event_DarkLabel, LV_EVENT_ALL, NULL);

}
