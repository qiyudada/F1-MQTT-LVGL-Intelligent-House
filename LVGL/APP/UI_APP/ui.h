// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_Menu
void ui_Menu_screen_init(void);
extern lv_obj_t * ui_Menu;
extern lv_obj_t * ui_Tempature;
extern lv_obj_t * ui_TempArc;
extern lv_obj_t * ui_TempatureNum;
void ui_event_TempLabel(lv_event_t * e);
extern lv_obj_t * ui_TempLabel;
extern lv_obj_t * ui_Humidity;
extern lv_obj_t * ui_humidPic;
extern lv_obj_t * ui_HumidText;
void ui_event_HumidLable(lv_event_t * e);
extern lv_obj_t * ui_HumidLabel;
extern lv_obj_t * ui_Time;
extern lv_obj_t * ui_ClockPic;
extern lv_obj_t * ui_TimeContent;
void ui_event_Hour(lv_event_t * e);
extern lv_obj_t * ui_Hour;
void ui_event_Minute(lv_event_t * e);
extern lv_obj_t * ui_Minute;
void ui_event_Second(lv_event_t * e);
extern lv_obj_t * ui_Second;
void ui_event_Year(lv_event_t * e);
extern lv_obj_t * ui_Year;
void ui_event_Month(lv_event_t * e);
extern lv_obj_t * ui_Month;
void ui_event_Day(lv_event_t * e);
extern lv_obj_t * ui_Day;
extern lv_obj_t * ui_Picture;
extern lv_obj_t * ui_Light;
extern lv_obj_t * ui_DarkPic;
extern lv_obj_t * ui_DarkContain;
void ui_event_DarkLabel(lv_event_t * e);
extern lv_obj_t * ui_DarkLabel;
extern lv_obj_t * ui_CO2;
extern lv_obj_t * ui_CO2Pic;
extern lv_obj_t * ui_CO2Text;
void ui_event_CO2Lable(lv_event_t * e);
extern lv_obj_t * ui_CO2Label;
void ui_event_Controlpage(lv_event_t * e);
extern lv_obj_t * ui_Controlpage;
// SCREEN: ui_Control
void ui_Control_screen_init(void);
extern lv_obj_t * ui_Control;
extern lv_obj_t * ui_LED1;
extern lv_obj_t * ui_Led1TEXT;
void ui_event_Led1SWITCH(lv_event_t * e);
extern lv_obj_t * ui_Led1SWITCH;
extern lv_obj_t * ui_LED2;
extern lv_obj_t * ui_Led2TEXT;
void ui_event_Led2Switch(lv_event_t * e);
extern lv_obj_t * ui_Led2Switch;
extern lv_obj_t * ui_BEEP;
extern lv_obj_t * ui_BeepTEXT;
void ui_event_BeepSWITCH(lv_event_t * e);
extern lv_obj_t * ui_BeepSWITCH;
extern lv_obj_t * ui_MOTOR;
extern lv_obj_t * ui_MotorTEXT;
void ui_event_MotorSWITCH(lv_event_t * e);
extern lv_obj_t * ui_MotorSWITCH;
extern lv_obj_t * ui_PIC2;
void ui_event_HOME(lv_event_t * e);
extern lv_obj_t * ui_HOME;
extern lv_obj_t * ui_WEATHER;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui__temporary_image);
LV_IMG_DECLARE(ui_img_weather_1_png);    // assets/weather_1.png
LV_IMG_DECLARE(ui_img_time_png);    // assets/time.png
LV_IMG_DECLARE(ui_img_iu1_png);    // assets/IU1.png
LV_IMG_DECLARE(ui_img_dark_png);    // assets/dark.png
LV_IMG_DECLARE(ui_img_co2_png);    // assets/CO2.png
LV_IMG_DECLARE(ui_img_icn_control_png);    // assets/icn_control.png
LV_IMG_DECLARE(ui_img_iu2_png);    // assets/IU2.png
LV_IMG_DECLARE(ui_img_icn_home_png);    // assets/icn_home.png
LV_IMG_DECLARE(ui_img_cloud_png);    // assets/cloud.png



LV_FONT_DECLARE(ui_font_Number);



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
