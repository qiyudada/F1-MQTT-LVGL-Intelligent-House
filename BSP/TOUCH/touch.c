#include "touch.h"
#include "Lcd.h"
#include "Delay.h"
#include <stdlib.h>
#include <math.h>
#include "24cxx.h"
#include "GUI.h"

const u8 *TP_REMIND_MSG_TBL = "Please use the stylus click the cross on the screen.The cross will always move until the screen adjustment is completed.";

_m_tp_dev tp_dev =
	{
		TP_Init,
		TP_Scan,
		TP_Adjust,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
};

u8 CMD_RDX = 0XD0;
u8 CMD_RDY = 0X90;

/*****************************************************************************
 * @name       :void TP_Write_Byte(u8 num)
 * @date       :2018-08-09
 * @function   :Write a byte data to the touch screen IC with SPI bus
 * @parameters :num:Data to be written
 * @retvalue   :None
 ******************************************************************************/
void TP_Write_Byte(u8 num)
{
	u8 count = 0;
	for (count = 0; count < 8; count++)
	{
		if (num & 0x80)
			TDIN = 1;
		else
			TDIN = 0;
		num <<= 1;
		TCLK = 0;
		TCLK = 1;
	}
}

/*****************************************************************************
 * @name       :u16 TP_Read_AD(u8 CMD)
 * @date       :2018-08-09
 * @function   :Reading adc values from touch screen IC with SPI bus
 * @parameters :CMD:Read command,0xD0 for x,0x90 for y
 * @retvalue   :Read data
 ******************************************************************************/
u16 TP_Read_AD(u8 CMD)
{
	u8 count = 0;
	u16 Num = 0;
	TCLK = 0;
	TDIN = 0;
	TCS = 0;
	TP_Write_Byte(CMD);
	Delay_us(6);
	TCLK = 0;
	Delay_us(1);
	TCLK = 1;
	TCLK = 0;
	for (count = 0; count < 16; count++)
	{
		Num <<= 1;
		TCLK = 0;
		TCLK = 1;
		if (DOUT)
			Num++;
	}
	Num >>= 4;
	TCS = 1;
	return (Num);
	// #endif
}

/*****************************************************************************
 * @name       :u16 TP_Read_XOY(u8 xy)
 * @date       :2018-08-09
 * @function   :Read the touch screen coordinates (x or y),
								Read the READ_TIMES secondary data in succession
								and sort the data in ascending order,
								Then remove the lowest and highest number of LOST_VAL
								and take the average
 * @parameters :xy:Read command(CMD_RDX/CMD_RDY)
 * @retvalue   :Read data
******************************************************************************/
u16 TP_Read_XOY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum = 0;
	u16 temp;
	for (i = 0; i < READ_TIMES; i++)
		buf[i] = TP_Read_AD(xy);
	for (i = 0; i < READ_TIMES - 1; i++)
	{
		for (j = i + 1; j < READ_TIMES; j++)
		{
			if (buf[i] > buf[j])
			{
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
	sum = 0;
	for (i = LOST_VAL; i < READ_TIMES - LOST_VAL; i++)
		sum += buf[i];
	temp = sum / (READ_TIMES - 2 * LOST_VAL);
	return temp;
}

/*****************************************************************************
 * @name       :u8 TP_Read_XY(u16 *x,u16 *y)
 * @date       :2018-08-09
 * @function   :Read touch screen x and y coordinates,
								The minimum value can not be less than 100
 * @parameters :x:Read x coordinate of the touch screen
								y:Read y coordinate of the touch screen
 * @retvalue   :0-fail,1-success
******************************************************************************/
u8 TP_Read_XY(u16 *x, u16 *y)
{
	u16 xtemp, ytemp;
	xtemp = TP_Read_XOY(CMD_RDX);
	ytemp = TP_Read_XOY(CMD_RDY);
	// if(xtemp<100||ytemp<100)return 0;
	*x = xtemp;
	*y = ytemp;
	return 1;
}

/*****************************************************************************
 * @name       :u8 TP_Read_XY2(u16 *x,u16 *y)
 * @date       :2018-08-09
 * @function   :Read the touch screen coordinates twice in a row,
								and the deviation of these two times can not exceed ERR_RANGE,
								satisfy the condition, then think the reading is correct,
								otherwise the reading is wrong.
								This function can greatly improve the accuracy.
 * @parameters :x:Read x coordinate of the touch screen
								y:Read y coordinate of the touch screen
 * @retvalue   :0-fail,1-success
******************************************************************************/
u8 TP_Read_XY2(u16 *x, u16 *y)
{
	u16 x1, y1;
	u16 x2, y2;
	u8 flag;
	flag = TP_Read_XY(&x1, &y1);
	if (flag == 0)
		return (0);
	flag = TP_Read_XY(&x2, &y2);
	if (flag == 0)
		return (0);
	if (((x2 <= x1 && x1 < x2 + ERR_RANGE) || (x1 <= x2 && x2 < x1 + ERR_RANGE)) // ǰ�����β�����+-50��
		&& ((y2 <= y1 && y1 < y2 + ERR_RANGE) || (y1 <= y2 && y2 < y1 + ERR_RANGE)))
	{
		*x = (x1 + x2) / 2;
		*y = (y1 + y2) / 2;
		return 1;
	}
	else
		return 0;
}

/*****************************************************************************
 * @name       :void TP_Drow_Touch_Point(u16 x,u16 y,u16 color)
 * @date       :2018-08-09
 * @function   :Draw a touch point,Used to calibrate
 * @parameters :x:Read x coordinate of the touch screen
								y:Read y coordinate of the touch screen
								color:the color value of the touch point
 * @retvalue   :None
******************************************************************************/
void TP_Drow_Touch_Point(u16 x, u16 y, u16 color)
{
	POINT_COLOR = color;
	LCD_DrawLine(x - 12, y, x + 13, y);
	LCD_DrawLine(x, y - 12, x, y + 13);
	LCD_DrawPoint(x + 1, y + 1);
	LCD_DrawPoint(x - 1, y + 1);
	LCD_DrawPoint(x + 1, y - 1);
	LCD_DrawPoint(x - 1, y - 1);
	gui_circle(x, y, POINT_COLOR, 6, 0);
}

/*****************************************************************************
 * @name       :void TP_Draw_Big_Point(u16 x,u16 y,u16 color)
 * @date       :2018-08-09
 * @function   :Draw a big point(2*2)
 * @parameters :x:Read x coordinate of the point
								y:Read y coordinate of the point
								color:the color value of the point
 * @retvalue   :None
******************************************************************************/
void TP_Draw_Big_Point(u16 x, u16 y, u16 color)
{
	POINT_COLOR = color;
	LCD_DrawPoint(x, y);
	LCD_DrawPoint(x + 1, y);
	LCD_DrawPoint(x, y + 1);
	LCD_DrawPoint(x + 1, y + 1);
}

/*****************************************************************************
 * @name       :u8 TP_Scan(u8 tp)
 * @date       :2018-08-09
 * @function   :Scanning touch event
 * @parameters :tp:
 * 				0-screen coordinate
				  1-Physical coordinates(For special occasions such as calibration)
 * @retvalue   :Current touch screen status,
								0-no touch
								1-touch
******************************************************************************/
u8 TP_Scan(u8 tp)
{
	if (PEN == 0)
	{
		if (tp)
			TP_Read_XY2(&tp_dev.x, &tp_dev.y);
		else if (TP_Read_XY2(&tp_dev.x, &tp_dev.y))
		{
			tp_dev.x = tp_dev.xfac * tp_dev.x + tp_dev.xoff;
			tp_dev.y = tp_dev.yfac * tp_dev.y + tp_dev.yoff;
		}
		if ((tp_dev.sta & TP_PRES_DOWN) == 0)
		{
			tp_dev.sta = TP_PRES_DOWN | TP_CATH_PRES;
			tp_dev.x0 = tp_dev.x;
			tp_dev.y0 = tp_dev.y;
		}
	}
	else
	{
		if (tp_dev.sta & TP_PRES_DOWN)
		{
			tp_dev.sta &= ~(1 << 7);
		}
		else
		{
			tp_dev.x0 = 0;
			tp_dev.y0 = 0;
			tp_dev.x = 0xffff;
			tp_dev.y = 0xffff;
		}
	}
	return tp_dev.sta & TP_PRES_DOWN;
}

/*****************************************************************************
 * @name       :void TP_Save_Adjdata(void)
 * @date       :2018-08-09
 * @function   :Save calibration parameters
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void TP_Save_Adjdata(void)
{
	s32 temp;

	temp = tp_dev.xfac * 100000000;
	AT24CXX_WriteLenByte(SAVE_ADDR_BASE, temp, 4);
	temp = tp_dev.yfac * 100000000;
	AT24CXX_WriteLenByte(SAVE_ADDR_BASE + 4, temp, 4);

	AT24CXX_WriteLenByte(SAVE_ADDR_BASE + 8, tp_dev.xoff, 2);

	AT24CXX_WriteLenByte(SAVE_ADDR_BASE + 10, tp_dev.yoff, 2);

	AT24CXX_WriteOneByte(SAVE_ADDR_BASE + 12, tp_dev.touchtype);

	AT24CXX_WriteOneByte(SAVE_ADDR_BASE + 13, temp);
}

/*****************************************************************************
 * @name       :u8 TP_Get_Adjdata(void)
 * @date       :2018-08-09
 * @function   :Gets the calibration values stored in the EEPROM
 * @parameters :None
 * @retvalue   :1-get the calibration values successfully
				0-get the calibration values unsuccessfully and Need to recalibrate
******************************************************************************/
u8 TP_Get_Adjdata(void)
{
	s32 tempfac;
	tempfac = AT24CXX_ReadOneByte(SAVE_ADDR_BASE + 13);
	if (tempfac == 0X1A)
	{
		tempfac = AT24CXX_ReadLenByte(SAVE_ADDR_BASE, 4);
		tp_dev.xfac = (float)tempfac / 100000000;
		tempfac = AT24CXX_ReadLenByte(SAVE_ADDR_BASE + 4, 4);
		tp_dev.yfac = (float)tempfac / 100000000;

		tp_dev.xoff = AT24CXX_ReadLenByte(SAVE_ADDR_BASE + 8, 2);

		tp_dev.yoff = AT24CXX_ReadLenByte(SAVE_ADDR_BASE + 10, 2);
		tp_dev.touchtype = AT24CXX_ReadOneByte(SAVE_ADDR_BASE + 12);
		if (tp_dev.touchtype)
		{
			CMD_RDX = 0X90;
			CMD_RDY = 0XD0;
		}
		else
		{
			CMD_RDX = 0XD0;
			CMD_RDY = 0X90;
		}
		return 1;
	}
	return 0;
}

/*****************************************************************************
 * @name       :void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac)
 * @date       :2018-08-09
 * @function   :Display calibration results
 * @parameters :x0:the x coordinates of first calibration point
								y0:the y coordinates of first calibration point
								x1:the x coordinates of second calibration point
								y1:the y coordinates of second calibration point
								x2:the x coordinates of third calibration point
								y2:the y coordinates of third calibration point
								x3:the x coordinates of fourth calibration point
								y3:the y coordinates of fourth calibration point
								fac:calibration factor
 * @retvalue   :None
******************************************************************************/
void TP_Adj_Info_Show(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 fac)
{
	POINT_COLOR = RED;
	LCD_ShowString(40, 140, 16, "x1:", 1);
	LCD_ShowString(40 + 80, 140, 16, "y1:", 1);
	LCD_ShowString(40, 160, 16, "x2:", 1);
	LCD_ShowString(40 + 80, 160, 16, "y2:", 1);
	LCD_ShowString(40, 180, 16, "x3:", 1);
	LCD_ShowString(40 + 80, 180, 16, "y3:", 1);
	LCD_ShowString(40, 200, 16, "x4:", 1);
	LCD_ShowString(40 + 80, 200, 16, "y4:", 1);
	LCD_ShowString(40, 220, 16, "fac is:", 1);
	LCD_ShowNum(40 + 24, 140, x0, 4, 16);
	LCD_ShowNum(40 + 24 + 80, 140, y0, 4, 16);
	LCD_ShowNum(40 + 24, 160, x1, 4, 16);
	LCD_ShowNum(40 + 24 + 80, 160, y1, 4, 16);
	LCD_ShowNum(40 + 24, 180, x2, 4, 16);
	LCD_ShowNum(40 + 24 + 80, 180, y2, 4, 16);
	LCD_ShowNum(40 + 24, 200, x3, 4, 16);
	LCD_ShowNum(40 + 24 + 80, 200, y3, 4, 16);
	LCD_ShowNum(40 + 56, 220, fac, 3, 16);
}

/*****************************************************************************
 * @name       :u8 TP_Get_Adjdata(void)
 * @date       :2018-08-09
 * @function   :Calibration touch screen and Get 4 calibration parameters
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void TP_Adjust(void)
{
	u16 pos_temp[4][2];
	u8 cnt = 0;
	u16 d1, d2;
	u32 tem1, tem2;
	float fac;
	u16 outtime = 0;
	cnt = 0;
	POINT_COLOR = BLUE;
	BACK_COLOR = WHITE;
	LCD_Clear(WHITE);
	POINT_COLOR = RED;
	LCD_Clear(WHITE);
	POINT_COLOR = BLACK;
	LCD_ShowString(10, 40, 16, "Please use the stylus click", 1);
	LCD_ShowString(10, 56, 16, "the cross on the screen.", 1);
	LCD_ShowString(10, 72, 16, "The cross will always move", 1);
	LCD_ShowString(10, 88, 16, "until the screen adjustment", 1);
	LCD_ShowString(10, 104, 16, "is completed.", 1);

	TP_Drow_Touch_Point(20, 20, RED);
	tp_dev.sta = 0;
	tp_dev.xfac = 0;
	while (1)
	{
		tp_dev.scan(1);
		if ((tp_dev.sta & 0xc0) == TP_CATH_PRES)
		{
			outtime = 0;
			tp_dev.sta &= ~(1 << 6);

			pos_temp[cnt][0] = tp_dev.x;
			pos_temp[cnt][1] = tp_dev.y;
			cnt++;
			switch (cnt)
			{
			case 1:
				TP_Drow_Touch_Point(20, 20, WHITE);
				TP_Drow_Touch_Point(lcddev.width - 20, 20, RED);
				break;
			case 2:
				TP_Drow_Touch_Point(lcddev.width - 20, 20, WHITE);
				TP_Drow_Touch_Point(20, lcddev.height - 20, RED);
				break;
			case 3:
				TP_Drow_Touch_Point(20, lcddev.height - 20, WHITE);
				TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, RED);
				break;
			case 4:

				tem1 = abs(pos_temp[0][0] - pos_temp[1][0]); // x1-x2
				tem2 = abs(pos_temp[0][1] - pos_temp[1][1]); // y1-y2
				tem1 *= tem1;
				tem2 *= tem2;
				d1 = sqrt(tem1 + tem2);

				tem1 = abs(pos_temp[2][0] - pos_temp[3][0]); // x3-x4
				tem2 = abs(pos_temp[2][1] - pos_temp[3][1]); // y3-y4
				tem1 *= tem1;
				tem2 *= tem2;
				d2 = sqrt(tem1 + tem2);
				fac = (float)d1 / d2;
				if (fac < 0.95 || fac > 1.05 || d1 == 0 || d2 == 0)
				{
					cnt = 0;
					TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE);																							 // �����4
					TP_Drow_Touch_Point(20, 20, RED);																															 // ����1
					TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100); // ��ʾ����
					continue;
				}
				tem1 = abs(pos_temp[0][0] - pos_temp[2][0]); // x1-x3
				tem2 = abs(pos_temp[0][1] - pos_temp[2][1]); // y1-y3
				tem1 *= tem1;
				tem2 *= tem2;
				d1 = sqrt(tem1 + tem2);

				tem1 = abs(pos_temp[1][0] - pos_temp[3][0]); // x2-x4
				tem2 = abs(pos_temp[1][1] - pos_temp[3][1]); // y2-y4
				tem1 *= tem1;
				tem2 *= tem2;
				d2 = sqrt(tem1 + tem2);
				fac = (float)d1 / d2;
				if (fac < 0.95 || fac > 1.05)
				{
					cnt = 0;
					TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE);																							 // �����4
					TP_Drow_Touch_Point(20, 20, RED);																															 // ����1
					TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100); // ��ʾ����
					continue;
				}

				tem1 = abs(pos_temp[1][0] - pos_temp[2][0]); // x1-x3
				tem2 = abs(pos_temp[1][1] - pos_temp[2][1]); // y1-y3
				tem1 *= tem1;
				tem2 *= tem2;
				d1 = sqrt(tem1 + tem2);

				tem1 = abs(pos_temp[0][0] - pos_temp[3][0]); // x2-x4
				tem2 = abs(pos_temp[0][1] - pos_temp[3][1]); // y2-y4
				tem1 *= tem1;
				tem2 *= tem2;
				d2 = sqrt(tem1 + tem2);
				fac = (float)d1 / d2;
				if (fac < 0.95 || fac > 1.05)
				{
					cnt = 0;
					TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE);																							 // �����4
					TP_Drow_Touch_Point(20, 20, RED);																															 // ����1
					TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100); // ��ʾ����
					continue;
				}

				tp_dev.xfac = (float)(lcddev.width - 40) / (pos_temp[1][0] - pos_temp[0][0]);
				tp_dev.xoff = (lcddev.width - tp_dev.xfac * (pos_temp[1][0] + pos_temp[0][0])) / 2;

				tp_dev.yfac = (float)(lcddev.height - 40) / (pos_temp[2][1] - pos_temp[0][1]);
				tp_dev.yoff = (lcddev.height - tp_dev.yfac * (pos_temp[2][1] + pos_temp[0][1])) / 2;
				if (abs(tp_dev.xfac) > 2 || abs(tp_dev.yfac) > 2)
				{
					cnt = 0;
					TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE);
					TP_Drow_Touch_Point(20, 20, RED);
					LCD_ShowString(40, 26, 16, "TP Need readjust!", 1);
					tp_dev.touchtype = !tp_dev.touchtype;
					if (tp_dev.touchtype)
					{
						CMD_RDX = 0X90;
						CMD_RDY = 0XD0;
					}
					else
					{
						CMD_RDX = 0XD0;
						CMD_RDY = 0X90;
					}
					continue;
				}
				POINT_COLOR = BLUE;
				LCD_Clear(WHITE);
				LCD_ShowString(35, 110, 16, "Touch Screen Adjust OK!", 1);
				Delay_ms(1000);
				TP_Save_Adjdata();
				LCD_Clear(WHITE);
				return;
			}
		}
		Delay_ms(10);
		outtime++;
		if (outtime > 1000)
		{
			TP_Get_Adjdata();
			break;
		}
	}
}

/*****************************************************************************
 * @name       :u8 TP_Init(void)
 * @date       :2018-08-09
 * @function   :Initialization touch screen
 * @parameters :None
 * @retvalue   :0-no calibration
				1-Has been calibrated
******************************************************************************/
u8 TP_Init(void)
{
	TP_Read_XY(&tp_dev.x, &tp_dev.y);
	if (TP_Get_Adjdata())
		return 0;
	else
	{
		LCD_Clear(WHITE);
		TP_Adjust();
		TP_Save_Adjdata();
	}
	TP_Get_Adjdata();
	return 1;
}
