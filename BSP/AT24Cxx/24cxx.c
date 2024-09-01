#include "24cxx.h"
#include "Delay.h"

/*****************************************************************************
 * @name       :u8 AT24CXX_ReadOneByte(u16 ReadAddr)
 * @date       :2018-08-09
 * @function   :Read out a data at a specified address in the AT24CXX
 * @parameters :ReadAddr:the address of start reading
 * @retvalue   :Read data
 ******************************************************************************/
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{
	u8 temp = 0;
	IIC_Start();
	if (EE_TYPE > AT24C16)
	{
		IIC_Send_Byte(0XA0);
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr >> 8);
		IIC_Wait_Ack();
	}
	else
		IIC_Send_Byte(0XA0 + ((ReadAddr / 256) << 1));

	IIC_Wait_Ack();
	IIC_Send_Byte(ReadAddr % 256);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0XA1);
	IIC_Wait_Ack();
	temp = IIC_Read_Byte(0);
	IIC_Stop();
	return temp;
}

/*****************************************************************************
 * @name       :void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
 * @date       :2018-08-09
 * @function   :Write a data at a specified address in AT24CXX
 * @parameters :WriteAddr:the destination address for writing data
								DataToWrite:Data to be written
 * @retvalue   :None
******************************************************************************/
void AT24CXX_WriteOneByte(u16 WriteAddr, u8 DataToWrite)
{
	IIC_Start();
	if (EE_TYPE > AT24C16)
	{
		IIC_Send_Byte(0XA0);
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr >> 8);
		IIC_Wait_Ack();
	}
	else
	{
		IIC_Send_Byte(0XA0 + ((WriteAddr / 256) << 1));
	}
	IIC_Wait_Ack();
	IIC_Send_Byte(WriteAddr % 256);
	IIC_Wait_Ack();
	IIC_Send_Byte(DataToWrite);
	IIC_Wait_Ack();
	IIC_Stop();
	Delay_ms(10);
}

/*****************************************************************************
 * @name       :void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
 * @date       :2018-08-09
 * @function   :begins to write data with a length of Len
								at the specified address in the AT24CXX
 * @parameters :WriteAddr:the address to start writing
								DataToWrite:the header address of the data array
								Len:Length of data to be written(2 or 4)
 * @retvalue   :None
******************************************************************************/
void AT24CXX_WriteLenByte(u16 WriteAddr, u32 DataToWrite, u8 Len)
{
	u8 t;
	for (t = 0; t < Len; t++)
	{
		AT24CXX_WriteOneByte(WriteAddr + t, (DataToWrite >> (8 * t)) & 0xff);
	}
}

/*****************************************************************************
 * @name       :u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
 * @date       :2018-08-09
 * @function   :begins to read data with a length of Len
								at the specified address in the AT24CXX,
								used to read 16bits or 32bits data
 * @parameters :ReadAddr:the address of start reading
								len:Length of data to be read(2 or 4)
 * @retvalue   :Read data
******************************************************************************/
u32 AT24CXX_ReadLenByte(u16 ReadAddr, u8 Len)
{
	u8 t;
	u32 temp = 0;
	for (t = 0; t < Len; t++)
	{
		temp <<= 8;
		temp += AT24CXX_ReadOneByte(ReadAddr + Len - t - 1);
	}
	return temp;
}

/*****************************************************************************
 * @name       :u8 AT24CXX_Check(void)
 * @date       :2018-08-09
 * @function   :Check that AT24CXX is normal or not,
								Use AT24CXX's last address (255) to store the token,
								if use the other 24C series, this address needs to be modified,
 * @parameters :None
 * @retvalue   :0-check successfully
								1-check failed
******************************************************************************/
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp = AT24CXX_ReadOneByte(255);
	if (temp == 0X55)
		return 0;
	else
	{
		AT24CXX_WriteOneByte(255, 0X55);
		temp = AT24CXX_ReadOneByte(255);
		if (temp == 0X55)
			return 0;
	}
	return 1;
}

/*****************************************************************************
 * @name       :void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
 * @date       :2018-08-09
 * @function   :begins to read out the specified number of data at
								the specified address in the AT24CXX
 * @parameters :ReadAddr:the address of start reading,it is 0~255 for 24c02
								pBuffer:the header address of the data array
								NumToRead:Number of data to be read
 * @retvalue   :None
******************************************************************************/
void AT24CXX_Read(u16 ReadAddr, u8 *pBuffer, u16 NumToRead)
{
	while (NumToRead)
	{
		*pBuffer++ = AT24CXX_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}

/*****************************************************************************
 * @name       :void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
 * @date       :2018-08-09
 * @function   :begins to write the specified number of data at
								the specified address in the AT24CXX
 * @parameters :WriteAddr:the address of start writing,it is 0~255 for 24c02
								pBuffer:the header address of the data array
								NumToRead:Number of data to be writen
 * @retvalue   :None
******************************************************************************/
void AT24CXX_Write(u16 WriteAddr, u8 *pBuffer, u16 NumToWrite)
{
	while (NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr, *pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
