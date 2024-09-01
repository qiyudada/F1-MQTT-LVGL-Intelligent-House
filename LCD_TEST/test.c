/*
*@file    test.c
*/
/*Copy this file as "Test.c" and set this value to "1" to enable content*/
#if 0

#include "test.h"
#include "pic.h"

//========================variable==========================//
u16 ColorTab[5] = {RED, GREEN, BLUE, YELLOW, BRED};
u16 ColornTab[8] = {RED, MAGENTA, GREEN, DARKBLUE, BLUE, BLACK, LIGHTGREEN};
//=====================end of variable======================//

/*****************************************************************************
 * @name       :void DrawTestPage(u8 *str)
 * @date       :2018-08-09
 * @function   :Drawing test interface
 * @parameters :str:the start address of the Chinese and English strings
 * @retvalue   :None
 ******************************************************************************/
void DrawTestPage(u8 *str)
{
	LCD_Clear(WHITE);
	LCD_Fill(0, 0, lcddev.width, 20, BLUE);
	LCD_Fill(0, lcddev.height - 20, lcddev.width, lcddev.height, BLUE);
	POINT_COLOR = WHITE;
	Gui_StrCenter(0, 2, WHITE, BLUE, str, 16, 1);										
	Gui_StrCenter(0, lcddev.height - 18, WHITE, BLUE, "Praymerry", 16, 1);
	// LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

/*****************************************************************************
 * @name       :void Test_Color(void)
 * @date       :2018-08-09
 * @function   :Color fill test(white,black,red,green,blue)
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void Test_Color(void)
{
	LCD_Fill(0, 0, lcddev.width, lcddev.height, WHITE);
	Show_Str(20, 30, BLUE, YELLOW, "BL Test", 16, 1);
	Delay_ms(800);
	LCD_Fill(0, 0, lcddev.width, lcddev.height, RED);
	Show_Str(20, 30, BLUE, YELLOW, "RED ", 16, 1);
	Delay_ms(800);
	LCD_Fill(0, 0, lcddev.width, lcddev.height, GREEN);
	Show_Str(20, 30, BLUE, YELLOW, "GREEN ", 16, 1);
	Delay_ms(800);
	LCD_Fill(0, 0, lcddev.width, lcddev.height, BLUE);
	Show_Str(20, 30, RED, YELLOW, "BLUE ", 16, 1);
	Delay_ms(800);
}

/*****************************************************************************
 * @name       :void Test_FillRec(void)
 * @date       :2018-08-09
 * @function   :Rectangular display and fill test
								Display red,green,blue,yellow,pink rectangular boxes in turn,
								1500 milliseconds later,
								Fill the rectangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_FillRec(void)
{
	u8 i = 0;
	DrawTestPage("Test 3: GUI Rectangle Fill");
	LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
	for (i = 0; i < 5; i++)
	{
		POINT_COLOR = ColorTab[i];
		LCD_DrawRectangle(lcddev.width / 2 - 80 + (i * 15), lcddev.height / 2 - 80 + (i * 15), lcddev.width / 2 - 80 + (i * 15) + 60, lcddev.height / 2 - 80 + (i * 15) + 60);
	}
	Delay_ms(1500);
	LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
	for (i = 0; i < 5; i++)
	{
		POINT_COLOR = ColorTab[i];
		LCD_DrawFillRectangle(lcddev.width / 2 - 80 + (i * 15), lcddev.height / 2 - 80 + (i * 15), lcddev.width / 2 - 80 + (i * 15) + 60, lcddev.height / 2 - 80 + (i * 15) + 60);
	}
	Delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Test_Circle(void)
 * @date       :2018-08-09
 * @function   :circular display and fill test
								Display red,green,blue,yellow,pink circular boxes in turn,
								1500 milliseconds later,
								Fill the circular in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Circle(void)
{
	u8 i = 0;
	DrawTestPage("Test 4: GUI Circle Fill");
	LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
	for (i = 0; i < 5; i++)
		gui_circle(lcddev.width / 2 - 80 + (i * 25), lcddev.height / 2 - 50 + (i * 25), ColorTab[i], 30, 0);
	Delay_ms(1500);
	LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
	for (i = 0; i < 5; i++)
		gui_circle(lcddev.width / 2 - 80 + (i * 25), lcddev.height / 2 - 50 + (i * 25), ColorTab[i], 30, 1);
	Delay_ms(1500);
}

/*****************************************************************************
 * @name       :void English_Font_test(void)
 * @date       :2018-08-09
 * @function   :English display test
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void English_Font_test(void)
{
	DrawTestPage("Test 6: GUI English display");
	Show_Str(10, 30, BLUE, YELLOW, "6X12:abcdefghijklmnopqrstuvwxyz0123456789", 12, 0);
	Show_Str(10, 45, BLUE, YELLOW, "6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 12, 1);
	Show_Str(10, 60, BLUE, YELLOW, "6X12:~!@#$%^&*()_+{}:<>?/|-+.", 12, 0);
	Show_Str(10, 80, BLUE, YELLOW, "8X16:abcdefghijklmnopqrstuvwxyz0123456789", 16, 0);
	Show_Str(10, 100, BLUE, YELLOW, "8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 16, 1);
	Show_Str(10, 120, BLUE, YELLOW, "8X16:~!@#$%^&*()_+{}:<>?/|-+.", 16, 0);
	Delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Test_Triangle(void)
 * @date       :2018-08-09
 * @function   :triangle display and fill test
								Display red,green,blue,yellow,pink triangle boxes in turn,
								1500 milliseconds later,
								Fill the triangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Triangle(void)
{
	u8 i = 0;
	DrawTestPage("Test 5: GUI Triangle Fill");
	LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
	for (i = 0; i < 5; i++)
	{
		POINT_COLOR = ColorTab[i];
		Draw_Triangel(lcddev.width / 2 - 80 + (i * 20), lcddev.height / 2 - 20 + (i * 15), lcddev.width / 2 - 50 - 1 + (i * 20), lcddev.height / 2 - 20 - 52 - 1 + (i * 15), lcddev.width / 2 - 20 - 1 + (i * 20), lcddev.height / 2 - 20 + (i * 15));
	}
	Delay_ms(1500);
	LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
	for (i = 0; i < 5; i++)
	{
		POINT_COLOR = ColorTab[i];
		Fill_Triangel(lcddev.width / 2 - 80 + (i * 20), lcddev.height / 2 - 20 + (i * 15), lcddev.width / 2 - 50 - 1 + (i * 20), lcddev.height / 2 - 20 - 52 - 1 + (i * 15), lcddev.width / 2 - 20 - 1 + (i * 20), lcddev.height / 2 - 20 + (i * 15));
	}
	Delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Chinese_Font_test(void)
 * @date       :2018-08-09
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void Chinese_Font_test(void)
{
	// DrawTestPage("����7:������ʾ����");
	// Show_Str(10, 30, BLUE, YELLOW, "16X16:ȫ�����Ӽ������޹�˾��ӭ��", 16, 0);
	// Show_Str(10, 50, BLUE, YELLOW, "16X16:Welcomeȫ������", 16, 0);
	// Show_Str(10, 70, BLUE, YELLOW, "24X24:���������Ĳ���", 24, 1);
	// Show_Str(10, 100, BLUE, YELLOW, "32X32:�������", 32, 1);
	// Delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Pic_test(void)
 * @date       :2018-08-09
 * @function   :picture display test
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void Pic_test(void)
{
	DrawTestPage("Test 8: GUI Picture");
	// LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Gui_Drawbmp16(30, 30, gImage_qq);
	Show_Str(30 + 12, 75, BLUE, YELLOW, "QQ", 16, 1);
	Gui_Drawbmp16(90, 30, gImage_qq);
	Show_Str(90 + 12, 75, BLUE, YELLOW, "QQ", 16, 1);
	Gui_Drawbmp16(150, 30, gImage_qq);
	Show_Str(150 + 12, 75, BLUE, YELLOW, "QQ", 16, 1);
	Delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Rotate_Test(void)
 * @date       :2018-08-09
 * @function   :rotate test
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void Rotate_Test(void)
{
	u8 i = 0;
	u8 *Direction[4] = {"Rotation:0", "Rotation:90", "Rotation:180", "Rotation:270"};

	for (i = 0; i < 4; i++)
	{
		LCD_direction(i);
		DrawTestPage("Test 9: GUI Rotate");
		Show_Str(20, 30, BLUE, YELLOW, Direction[i], 16, 1);
		Gui_Drawbmp16(30, 50, gImage_qq);
		Delay_ms(1000);
		Delay_ms(1000);
	}
	LCD_direction(USE_HORIZONTAL);
}

/*****************************************************************************
 * @name       :void Touch_Test(void)
 * @date       :2018-08-09
 * @function   :touch test
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void Touch_Test(void)
{
	u8 key;
	u16 i = 0;
	u16 j = 0;
	u16 colorTemp = 0;
	TP_Init();
	//KEY_Init();
	//LED_Init();
	DrawTestPage("Test 10:Touch(KEY0 Verify)  ");
	LCD_ShowString(lcddev.width - 24, 0, 16, "RST", 1); 
	POINT_COLOR = RED;
	LCD_Fill(lcddev.width - 50, 2, lcddev.width - 50 + 22, 18, RED);
	while (1)
	{
		//key = KEY_Scan();
		tp_dev.scan(0);
		if (tp_dev.sta & TP_PRES_DOWN) 
		{
			if (tp_dev.x < lcddev.width && tp_dev.y < lcddev.height)
			{
				if (tp_dev.x > (lcddev.width - 24) && tp_dev.y < 16)
				{
					DrawTestPage("Test 10:Touch(KEY0 Verify)     "); // ���
					LCD_ShowString(lcddev.width - 24, 0, 16, "RST", 1);			// ��ʾ��������
					POINT_COLOR = colorTemp;
					LCD_Fill(lcddev.width - 50, 2, lcddev.width - 50 + 22, 18, POINT_COLOR);
				}
				else if ((tp_dev.x > (lcddev.width - 50) && tp_dev.x < (lcddev.width - 50 + 22)) && tp_dev.y < 20)
				{
					LCD_Fill(lcddev.width - 50, 2, lcddev.width - 50 + 22, 18, ColorTab[j % 5]);
					POINT_COLOR = ColorTab[(j++) % 5];
					colorTemp = POINT_COLOR;
					Delay_ms(10);
				}

				else
					TP_Draw_Big_Point(tp_dev.x, tp_dev.y, POINT_COLOR); // ��ͼ
			}
		}
		else
			Delay_ms(10); // û�а������µ�ʱ��
		if (key == 1)	  // KEY_RIGHT����,��ִ��У׼����
		{

			LCD_Clear(WHITE); // ����
			TP_Adjust();	  // ��ĻУ׼
			TP_Save_Adjdata();
			DrawTestPage("Test 10:Touch(KEY0 Verify)      ");
			LCD_ShowString(lcddev.width - 24, 0, 16, "RST", 1); // ��ʾ��������
			POINT_COLOR = colorTemp;
			LCD_Fill(lcddev.width - 50, 2, lcddev.width - 50 + 22, 18, POINT_COLOR);
		}
		i++;
		if (i == 30)
		{
			i = 0;
			
			// break;
		}
	}
}

/*****************************************************************************
 * @name       :void Test_Read(void)
 * @date       :2018-11-13
 * @function   :read test
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void Test_Read(void)
{
	u16 lcd_id, color;
	u8 buf[10] = {0}, i;
	u8 cbuf[20] = {0};
	DrawTestPage("Test 11: GUI Read");
	LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
	lcd_id = LCD_Read_ID();
	sprintf((char *)buf, "ID:0x%x", lcd_id);
	Show_Str(50, 25, BLUE, YELLOW, buf, 16, 1);
	for (i = 0; i < 7; i++)
	{
		POINT_COLOR = ColornTab[i];
		LCD_DrawFillRectangle(40 - 10, 55 + i * 25 - 10, 40 + 10, 55 + i * 25 + 10);
		color = LCD_ReadPoint(40, 55 + i * 25);
		sprintf((char *)cbuf, "read color:0x%04X", color);
		Show_Str(40 + 20, 55 + i * 25 - 8, POINT_COLOR, YELLOW, cbuf, 16, 1);
	}
	Delay_ms(1500);
}

#endif
