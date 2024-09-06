#include "24cxx.h"
#include "Delay.h"
#include "myiic.h"

/**
 * @brief       初始化IIC接口
 * @param       无
 * @retval      无
 */
void AT24Cxx_Init(void)
{
    IIC_Init();
}

/**
 * @brief       在AT24CXX指定地址读出一个数据
 * @param       readaddr: 开始读数的地址
 * @retval      读到的数据
 */
uint8_t AT24Cxx_Read_One_Byte(uint16_t addr)
{
    uint8_t temp = 0;
    IIC_Start(); /* 发送起始信号 */

    if (EE_TYPE > AT24C16) /* 24C16以上的型号, 分2个字节发送地址 */
    {
        IIC_Send_Byte(0XA0);      /* 发送写命令, IIC规定最低位是0, 表示写入 */
        IIC_Wait_Ack();           /* 每次发送完一个字节,都要等待ACK */
        IIC_Send_Byte(addr >> 8); /* 发送高字节地址 */
    }
    else
    {
        IIC_Send_Byte(0XA0 + ((addr >> 8) << 1)); /* 发送器件 0XA0 + 高位a8/a9/a10地址,写数据 */
    }

    IIC_Wait_Ack();            /* 每次发送完一个字节,都要等待ACK */
    IIC_Send_Byte(addr % 256); /* 发送低位地址 */
    IIC_Wait_Ack();            /* 等待ACK, 此时地址发送完成了 */

    IIC_Start();             /* 重新发送起始信号 */
    IIC_Send_Byte(0XA1);     /* 进入接收模式, IIC规定最低位是0, 表示读取 */
    IIC_Wait_Ack();          /* 每次发送完一个字节,都要等待ACK */
    temp = IIC_Read_Byte(0); /* 接收一个字节数据 */
    IIC_Stop();              /* 产生一个停止条件 */
    return temp;
}

/**
 * @brief       在AT24CXX指定地址写入一个数据
 * @param       addr: 写入数据的目的地址
 * @param       data: 要写入的数据
 * @retval      无
 */
void AT24Cxx_Write_One_Byte(uint16_t addr, uint8_t data)
{
    /* 原理说明见:at24cxx_read_one_byte函数, 本函数完全类似 */
    IIC_Start(); /* 发送起始信号 */

    if (EE_TYPE > AT24C16) /* 24C16以上的型号, 分2个字节发送地址 */
    {
        IIC_Send_Byte(0XA0);      /* 发送写命令, IIC规定最低位是0, 表示写入 */
        IIC_Wait_Ack();           /* 每次发送完一个字节,都要等待ACK */
        IIC_Send_Byte(addr >> 8); /* 发送高字节地址 */
    }
    else
    {
        IIC_Send_Byte(0XA0 + ((addr >> 8) << 1)); /* 发送器件 0XA0 + 高位a8/a9/a10地址,写数据 */
    }

    IIC_Wait_Ack();            /* 每次发送完一个字节,都要等待ACK */
    IIC_Send_Byte(addr % 256); /* 发送低位地址 */
    IIC_Wait_Ack();            /* 等待ACK, 此时地址发送完成了 */

    /* 因为写数据的时候,不需要进入接收模式了,所以这里不用重新发送起始信号了 */
    IIC_Send_Byte(data); /* 发送1字节 */
    IIC_Wait_Ack();      /* 等待ACK */
    IIC_Stop();          /* 产生一个停止条件 */
    Delay_ms(10);        /* 注意: EEPROM 写入比较慢,必须等到10ms后再写下一个字节 */
}

/**
 * @brief       检查AT24CXX是否正常
 *   @note      检测原理: 在器件的末地址写如0X55, 然后再读取, 如果读取值为0X55
 *              则表示检测正常. 否则,则表示检测失败.
 *
 * @param       无
 * @retval      检测结果
 *              0: 检测成功
 *              1: 检测失败
 */
uint8_t AT24Cxx_Check(void)
{
    uint8_t temp;
    temp = AT24Cxx_Read_One_Byte(EE_TYPE); /* 避免每次开机都写AT24CXX */
    if (temp == 0X55)                      /* 读取数据正常 */
    {
        return 0;
    }
    else /* 排除第一次初始化的情况 */
    {
        AT24Cxx_Write_One_Byte(EE_TYPE, 0X55); /* 先写入数据 */
        temp = AT24Cxx_Read_One_Byte(255);     /* 再读取数据 */

        if (temp == 0X55)
            return 0;
    }

    return 1;
}

/**
 * @brief       在AT24CXX里面的指定地址开始读出指定个数的数据
 * @param       addr    : 开始读出的地址 对24c02为0~255
 * @param       pbuf    : 数据数组首地址
 * @param       datalen : 要读出数据的个数
 * @retval      无
 */
void AT24Cxx_Read(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while (datalen--)
    {
        *pbuf++ = AT24Cxx_Read_One_Byte(addr++);
    }
}

/**
 * @brief       在AT24CXX里面的指定地址开始写入指定个数的数据
 * @param       addr    : 开始写入的地址 对24c02为0~255
 * @param       pbuf    : 数据数组首地址
 * @param       datalen : 要写入数据的个数
 * @retval      无
 */
void AT24Cxx_Write(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while (datalen--)
    {
        AT24Cxx_Write_One_Byte(addr, *pbuf);
        addr++;
        pbuf++;
    }
}

