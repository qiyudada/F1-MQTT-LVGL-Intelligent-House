#include "Lcd.h"

_lcd_dev lcddev;
// 画笔颜色,背景颜色
uint16_t POINT_COLOR = 0x0000, BACK_COLOR = 0xFFFF;
uint16_t DeviceCode;

/*****************************************************************************
 * @name       :void LCD_read(void)
 * @date       :2018-08-09
 * @function   :Read the data from the LCD Ram
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
uint16_t LCD_read(void)
{
	volatile uint16_t data; // 防止被优化
	data = LCD->LCD_RAM;
#if LCD_USE8BIT_MODEL
	return (data >> 8);
#else
	return data;
#endif
}

/*****************************************************************************
 * @name       :void LCD_WR_REG(u16 data)
 * @date       :2018-08-09
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
 ******************************************************************************/
void LCD_WR_REG(uint16_t data)
{
#if LCD_USE8BIT_MODEL
	LCD->LCD_REG = (data << 8); // 写入要写的寄存器序号
#else
	LCD->LCD_REG = data; // 写入要写的寄存器序号
#endif
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u16 data)
 * @date       :2018-08-09
 * @function   :Write an 16-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
 ******************************************************************************/
void LCD_WR_DATA(uint16_t data)
{
#if LCD_USE8BIT_MODEL
	LCD->LCD_RAM = (data << 8); // 写入要写的数据
#else
	LCD->LCD_RAM = data; // 写入要写的数据
#endif
}

/*****************************************************************************
 * @name       :u16 LCD_RD_DATA(void)
 * @date       :2018-11-13
 * @function   :Read an 16-bit value from the LCD screen
 * @parameters :None
 * @retvalue   :read value
 ******************************************************************************/
uint16_t LCD_RD_DATA(void)
{
	return LCD_read();
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
				LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
#if LCD_USE8BIT_MODEL
	LCD->LCD_REG = (LCD_Reg << 8);		// 写入要写的寄存器序号
	LCD->LCD_RAM = (LCD_RegValue << 8); // 写入数据
#else
	LCD->LCD_REG = LCD_Reg;		 // 写入要写的寄存器序号
	LCD->LCD_RAM = LCD_RegValue; // 写入数据
#endif
}

/*****************************************************************************
 * @name       :u16 LCD_ReadReg(u16 LCD_Reg)
 * @date       :2018-11-13
 * @function   :read value from specially registers
 * @parameters :LCD_Reg:Register address
 * @retvalue   :read value
 ******************************************************************************/
void LCD_ReadReg(uint16_t LCD_Reg, uint8_t *Rval, int n)
{
	LCD_WR_REG(LCD_Reg);
	while (n--)
	{
		*(Rval++) = LCD_RD_DATA();
		Delay_us(100);
	}
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}

/*****************************************************************************
 * @name       :void LCD_ReadRAM_Prepare(void)
 * @date       :2018-11-13
 * @function   :Read GRAM
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void LCD_ReadRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.rramcmd);
}

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(u16 Data)
 * @date       :2018-08-09
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
 ******************************************************************************/
void Lcd_WriteData_16Bit(uint16_t Data)
{
#if LCD_USE8BIT_MODEL
	LCD->LCD_RAM = Data;
	LCD->LCD_RAM = Data << 8;
#else
	LCD->LCD_RAM = Data;
#endif
}

uint16_t Color_To_565(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

/*****************************************************************************
 * @name       :u16 Lcd_ReadData_16Bit(void)
 * @date       :2018-11-13
 * @function   :Read an 16-bit value from the LCD screen
 * @parameters :None
 * @retvalue   :read value
 ******************************************************************************/
uint16_t Lcd_ReadData_16Bit(void)
{
	uint16_t r, g, b;
	// dummy data
	r = LCD_RD_DATA();
	Delay_us(1); // 延时1us
	// 8bit:red data
	// 16bit:red and green data
	r = LCD_RD_DATA();
	Delay_us(1); // 延时1us
	// 8bit:green data
	// 16bit:blue data
	g = LCD_RD_DATA();
#if LCD_USE8BIT_MODEL
	Delay_us(1); // 延时1us
	// 8bit:blue data
	b = LCD_RD_DATA();
#else
	b = g >> 8;
	g = r & 0xFF;
	r = r >> 8;
#endif
	return Color_To_565(r, g, b);
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
				y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/
void LCD_DrawPoint(uint16_t x, uint16_t y)
{
	LCD_SetCursor(x, y); // 设置光标位置
	Lcd_WriteData_16Bit(POINT_COLOR);
}

/*****************************************************************************
 * @name       :u16 LCD_ReadPoint(u16 x,u16 y)
 * @date       :2018-11-13
 * @function   :Read a pixel color value at a specified location
 * @parameters :x:the x coordinate of the pixel
				y:the y coordinate of the pixel
 * @retvalue   :the read color value
******************************************************************************/
uint16_t LCD_ReadPoint(uint16_t x, uint16_t y)
{
	uint16_t color;
	if (x >= lcddev.width || y >= lcddev.height)
	{
		return 0; // 超过了范围,直接返回
	}
	LCD_SetCursor(x, y); // 设置光标位置
	LCD_ReadRAM_Prepare();
	color = Lcd_ReadData_16Bit();
	return color;
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
 ******************************************************************************/
void LCD_Clear(uint16_t Color)
{
	unsigned int i;
	uint32_t total_point = lcddev.width * lcddev.height;
	LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
	for (i = 0; i < total_point; i++)
	{
#if LCD_USE8BIT_MODEL
		LCD->LCD_RAM = Color;
		LCD->LCD_RAM = Color << 8;
#else
		LCD->LCD_RAM = Color;
#endif
	}
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void LCD_Init(void)
{
	Delay_ms(100);
	//*************2.8inch ILI9341初始化**********//
	LCD_WR_REG(0xCF);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC9); // C1
	LCD_WR_DATA(0X30);
	LCD_WR_REG(0xED);
	LCD_WR_DATA(0x64);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0X12);
	LCD_WR_DATA(0X81);
	LCD_WR_REG(0xE8);
	LCD_WR_DATA(0x85);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x7A);
	LCD_WR_REG(0xCB);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x34);
	LCD_WR_DATA(0x02);
	LCD_WR_REG(0xF7);
	LCD_WR_DATA(0x20);
	LCD_WR_REG(0xEA);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xC0);  // Power control
	LCD_WR_DATA(0x1B); // VRH[5:0]
	LCD_WR_REG(0xC1);  // Power control
	LCD_WR_DATA(0x00); // SAP[2:0];BT[3:0] 01
	LCD_WR_REG(0xC5);  // VCM control
	LCD_WR_DATA(0x30); // 3F
	LCD_WR_DATA(0x30); // 3C
	LCD_WR_REG(0xC7);  // VCM control2
	LCD_WR_DATA(0XB7);
	LCD_WR_REG(0x36); // Memory Access Control
	LCD_WR_DATA(0x08);
	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);
	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x1A);
	LCD_WR_REG(0xB6); // Display Function Control
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0xA2);
	LCD_WR_REG(0xF2); // 3Gamma Function Disable
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0x26); // Gamma curve selected
	LCD_WR_DATA(0x01);
	LCD_WR_REG(0xE0); // Set Gamma
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x2A);
	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x54);
	LCD_WR_DATA(0XA9);
	LCD_WR_DATA(0x43);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0XE1); // Set Gamma
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x15);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x2B);
	LCD_WR_DATA(0x56);
	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0x2B);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x3f);
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xef);
	LCD_WR_REG(0x11); // Exit Sleep
	Delay_ms(120);
	LCD_WR_REG(0x29);			   // display on
	LCD_direction(USE_HORIZONTAL); // 设置LCD显示方向
	LCD_LED(1);					   // 点亮背光
	LCD_Clear(WHITE);			   // 清全屏白色
}

/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/
void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd)
{
	LCD_WR_REG(lcddev.setxcmd);
	LCD_WR_DATA(xStar >> 8);
	LCD_WR_DATA(0x00FF & xStar);
	LCD_WR_DATA(xEnd >> 8);
	LCD_WR_DATA(0x00FF & xEnd);

	LCD_WR_REG(lcddev.setycmd);
	LCD_WR_DATA(yStar >> 8);
	LCD_WR_DATA(0x00FF & yStar);
	LCD_WR_DATA(yEnd >> 8);
	LCD_WR_DATA(0x00FF & yEnd);

	LCD_WriteRAM_Prepare(); // 开始写入GRAM
}

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	LCD_SetWindows(Xpos, Ypos, Xpos, Ypos);
}

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
						  1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/
void LCD_direction(uint8_t direction)
{
	lcddev.setxcmd = 0x2A;
	lcddev.setycmd = 0x2B;
	lcddev.wramcmd = 0x2C;
	lcddev.rramcmd = 0x2E;
	switch (direction)
	{
	case 0:
		lcddev.width = LCD_W;
		lcddev.height = LCD_H;
		LCD_WriteReg(0x36, (1 << 3));
		break;
	case 1:
		lcddev.width = LCD_H;
		lcddev.height = LCD_W;
		LCD_WriteReg(0x36, (1 << 3) | (1 << 5) | (1 << 6));
		break;
	case 2:
		lcddev.width = LCD_W;
		lcddev.height = LCD_H;
		LCD_WriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 4) | (1 << 6));
		break;
	case 3:
		lcddev.width = LCD_H;
		lcddev.height = LCD_W;
		LCD_WriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 5) | (1 << 4));
		break;
	default:
		break;
	}
}

/*****************************************************************************
 * @name       :u16 LCD_Read_ID(void)
 * @date       :2018-11-13
 * @function   :Read ID
 * @parameters :None
 * @retvalue   :ID value
 ******************************************************************************/
uint16_t LCD_Read_ID(void)
{
	uint8_t val[4] = {0};
	LCD_ReadReg(0xD3, val, 4);
	return (val[2] << 8) | val[3];
}
