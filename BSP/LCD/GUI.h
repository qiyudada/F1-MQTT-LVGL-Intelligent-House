#ifndef __GUI_H__
#define __GUI_H__

#include "stm32f1xx_hal.h"
#include "lvgl.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

/*LCD Basic FUNCTION*/
/*fc is font color,bc is background color*/
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);

void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);

void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode);

void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);

void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len,u8 size,u8 mode);

void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode);

void LCD_ShowString2(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color);

void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2);

void lvgl_LCD_Color_Fill(u16 sx, u16 sy, u16 ex, u16 ey, lv_color_t *color);

/*GUI FUNCTION*/

void GUI_DrawPoint(u16 x,u16 y,u16 color);

void GUI_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);

void GUI_Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2);

void GUI_Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2);

void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);

void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);

void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);

void GUI_Show_String(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);

void GUI_Drawbmp16(u16 x,u16 y,const unsigned char *p); 

void GUI_Circle(int xc, int yc, u16 c, int r, int fill);

void GUI_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);



#endif

