#ifndef __MYIIC_H
#define __MYIIC_H

#include "main.h"
#include "sys.h"

#define SDA_IN()                    \
	{                               \
		GPIOB->CRL &= 0X0FFFFFFF;   \
		GPIOB->CRL |= (u32)8 << 28; \
	}
#define SDA_OUT()                   \
	{                               \
		GPIOB->CRL &= 0X0FFFFFFF;   \
		GPIOB->CRL |= (u32)3 << 28; \
	}

#define IIC_SCL PBout(10)
#define IIC_SDA PBout(11)
#define READ_SDA PBin(11)

void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte(u8 txd);
u8 IIC_Read_Byte(unsigned char ack);
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Write_One_Byte(u8 daddr, u8 addr, u8 data);
u8 IIC_Read_One_Byte(u8 daddr, u8 addr);

#endif
