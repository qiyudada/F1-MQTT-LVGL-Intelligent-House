/*
*@file    test.h
*/
/*Copy this file as "Test.h" and set this value to "1" to enable content*/
#if 0
#ifndef __TEST_H__
#define __TEST_H__

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include "Lcd.h"
#include "Delay.h"
#include "GUI.h"
#include "Touch.h"


void DrawTestPage(u8 *str);
void Test_Color(void);
void Test_FillRec(void);
void Test_Circle(void);
void Test_Triangle(void);
void English_Font_test(void);
void Chinese_Font_test(void);
void Pic_test(void);
void Load_Drow_Dialog(void);
void Touch_Test(void);
void main_test(void);
void Rotate_Test(void);
void Test_Read(void);

#endif
#endif
