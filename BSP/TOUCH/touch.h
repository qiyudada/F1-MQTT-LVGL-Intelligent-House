#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "main.h"
#include "sys.h"

#define TP_PRES_DOWN 0x80 // Press
#define TP_CATH_PRES 0x40 // Touch
/*TP_Read_XOY*/
#define READ_TIMES 5
#define LOST_VAL 1
/*TP_Read_XY2*/
#define ERR_RANGE 50 
/*TP_Save_Adjdata*/
#define SAVE_ADDR_BASE 40


typedef struct
{
	u8 (*init)(void); // initation
	u8 (*scan)(u8);	  // Scan
	void (*adjust)(void);
	u16 x0; // originous coordinate
	u16 y0;
	u16 x; // current coordinate
	u16 y;
	u8 sta;		// pen status (1 press 0 no press)
	float xfac; // axis calibration
	float yfac;
	short xoff;
	short yoff;
	u8 touchtype; // 新增的参数,当触摸屏的左右上下完全颠倒时需要用到.touchtype=0的时候,适合左右为X坐标,上下为Y坐标的TP.touchtype=1的时候,适合左右为Y坐标,上下为X坐标的TP.
} _m_tp_dev;

extern _m_tp_dev tp_dev;

#define PEN PFin(10)  // PF10 INT
#define DOUT PFin(8)  // PB8  MISO
#define TDIN PFout(9) // PF9  MOSI
#define TCLK PBout(1) // PB1  SCLK
#define TCS  PBout(2)  // PB2  CS

void TP_Write_Byte(u8 num);
u16 TP_Read_AD(u8 CMD);
u16 TP_Read_XOY(u8 xy);
u8 TP_Read_XY(u16 *x, u16 *y);
u8 TP_Read_XY2(u16 *x, u16 *y);
void TP_Drow_Touch_Point(u16 x, u16 y, u16 color);
void TP_Draw_Big_Point(u16 x, u16 y, u16 color);
u8 TP_Scan(u8 tp);
void TP_Save_Adjdata(void);
u8 TP_Get_Adjdata(void);
void TP_Adjust(void);
u8 TP_Init(void);
void TP_Adj_Info_Show(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 fac);

#endif
