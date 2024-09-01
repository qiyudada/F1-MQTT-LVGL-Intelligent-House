#ifndef __LCD_H
#define __LCD_H

#include "stm32f1xx_hal.h"
#include "main.h"
#include <stdlib.h>
#include "Delay.h"
#include "lvgl.h"

// LCD重要参数集
typedef struct
{
    uint16_t width;   // LCD 宽度
    uint16_t height;  // LCD 高度
    uint16_t id;      // LCD ID
    uint8_t dir;      // 横屏还是竖屏控制：0，竖屏；1，横屏。
    uint16_t wramcmd; // 开始写gram指令
    uint16_t rramcmd; // 开始读gram指令
    uint16_t setxcmd; // 设置x坐标指令
    uint16_t setycmd; // 设置y坐标指令
} _lcd_dev;

// LCD参数
extern _lcd_dev lcddev; // 管理LCD重要参数

/******************************User Configuration****************************************** */
#define USE_HORIZONTAL 0    // 定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转
#define LCD_USE8BIT_MODEL 0 // 定义数据总线是否使用8位模式 0,使用16位模式.1,使用8位模式
/********************************************************************************** */
// 定义LCD的尺寸
#define LCD_W 240
#define LCD_H 320

// TFTLCD部分外要调用的函数
extern uint16_t POINT_COLOR; // 默认红色
extern uint16_t BACK_COLOR;  // 背景颜色.默认为白色

//-----------------LCD端口定义----------------
#define LCD_LED(N) HAL_GPIO_WritePin(BL_EN_GPIO_Port, BL_EN_Pin, N == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET) // LCD背光

// LCD地址结构体
typedef struct
{
    volatile uint16_t LCD_REG;
    volatile uint16_t LCD_RAM;
} LCD_TypeDef;
/***********************************************************************************
 *使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A10作为数据命令区分线,// 使用16位模式时，注意设置时STM32内部地址需要右移一位对齐!*/

#define LCD_BASE ((uint32_t)(0x6C000000 | 0x000007FE))
#define LCD ((LCD_TypeDef *)LCD_BASE)

// 画笔颜色
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40 // 棕色
#define BRRED 0XFC07 // 棕红色
#define GRAY 0X8430  // 灰色
// GUI颜色

#define DARKBLUE 0X01CF  // 深蓝色
#define LIGHTBLUE 0X7D7C // 浅蓝色
#define GRAYBLUE 0X5458  // 灰蓝色
// 以上三色为PANEL的颜色

#define LIGHTGREEN 0X841F // 浅绿色
#define LIGHTGRAY 0XEF5B  // 浅灰色(PANNEL)
#define LGRAY 0XC618      // 浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE 0XA651  // 浅灰蓝色(中间层颜色)
#define LBBLUE 0X2B12     // 浅棕蓝色(选择条目的反色)
/********************************************************************************** */

void LCD_Init(void);
uint16_t LCD_read(void);
void LCD_Clear(uint16_t Color);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x, uint16_t y);
uint16_t LCD_ReadPoint(uint16_t x, uint16_t y);
void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd);
uint16_t LCD_RD_DATA(void);
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WR_REG(uint16_t data);
void LCD_WR_DATA(uint16_t data);
void LCD_ReadReg(uint16_t LCD_Reg, uint8_t *Rval, int n);
void LCD_WriteRAM_Prepare(void);
void LCD_ReadRAM_Prepare(void);
void Lcd_WriteData_16Bit(uint16_t Data);
uint16_t Lcd_ReadData_16Bit(void);
void LCD_direction(uint8_t direction);
uint16_t Color_To_565(uint8_t r, uint8_t g, uint8_t b);
uint16_t LCD_Read_ID(void);

#endif

