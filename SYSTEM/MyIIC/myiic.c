#include "myiic.h"
#include "Delay.h"

/*****************************************************************************
 * @name       :void IIC_Start(void)
 * @date       :2018-08-09
 * @function   :Generating IIC starting signal
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void IIC_Start(void)
{
	SDA_OUT();
	IIC_SDA = 1;
	IIC_SCL = 1;
	Delay_us(4);
	IIC_SDA = 0; // START:when CLK is high,DATA change form high to low
	Delay_us(4);
	IIC_SCL = 0;
}

/*****************************************************************************
 * @name       :void IIC_Stop(void)
 * @date       :2018-08-09
 * @function   :Generating IIC stop signal
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL = 0;
	IIC_SDA = 0; // STOP:when CLK is high DATA change form low to high
	Delay_us(4);
	IIC_SCL = 1;
	IIC_SDA = 1;
	Delay_us(4);
}

/*****************************************************************************
 * @name       :u8 IIC_Wait_Ack(void)
 * @date       :2018-08-09
 * @function   :Wait for the response signal
 * @parameters :None
 * @retvalue   :0-receive response signal successfully
								1-receive response signal unsuccessfully
******************************************************************************/
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	SDA_IN();
	IIC_SDA = 1;
	Delay_us(1);
	IIC_SCL = 1;
	Delay_us(1);
	while (READ_SDA)
	{
		ucErrTime++;
		if (ucErrTime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL = 0;
	return 0;
}

/*****************************************************************************
 * @name       :void IIC_Ack(void)
 * @date       :2018-08-09
 * @function   :Generate ACK response signal
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void IIC_Ack(void)
{
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 0;
	Delay_us(2);
	IIC_SCL = 1;
	Delay_us(2);
	IIC_SCL = 0;
}

/*****************************************************************************
 * @name       :void IIC_NAck(void)
 * @date       :2018-08-09
 * @function   :Don't generate ACK response signal
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void IIC_NAck(void)
{
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 1;
	Delay_us(2);
	IIC_SCL = 1;
	Delay_us(2);
	IIC_SCL = 0;
}

/*****************************************************************************
 * @name       :void IIC_Send_Byte(u8 txd)
 * @date       :2018-08-09
 * @function   :send a byte data by IIC bus
 * @parameters :txd:Data to be sent
 * @retvalue   :None
 ******************************************************************************/
void IIC_Send_Byte(u8 txd)
{
	u8 t;
	SDA_OUT();
	IIC_SCL = 0;
	for (t = 0; t < 8; t++)
	{
		IIC_SDA = (txd & 0x80) >> 7;
		txd <<= 1;
		Delay_us(2);
		IIC_SCL = 1;
		Delay_us(2);
		IIC_SCL = 0;
		Delay_us(2);
	}
}

/*****************************************************************************
 * @name       :u8 IIC_Read_Byte(unsigned char ack)
 * @date       :2018-08-09
 * @function   :read a byte data by IIC bus
 * @parameters :ack:0-send nACK
									  1-send ACK
 * @retvalue   :Data to be read
******************************************************************************/
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	SDA_IN();
	for (i = 0; i < 8; i++)
	{
		IIC_SCL = 0;
		Delay_us(2);
		IIC_SCL = 1;
		receive <<= 1;
		if (READ_SDA)
			receive++;
		Delay_us(1);
	}
	if (!ack)
		IIC_NAck();
	else
		IIC_Ack();
	return receive;
}
