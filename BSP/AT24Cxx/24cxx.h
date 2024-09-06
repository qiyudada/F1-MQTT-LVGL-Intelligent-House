#ifndef __24CXX_H
#define __24CXX_H

#include "sys.h"

/* 根据不同的24CXX型号, 发送高位地址
 * 1, 24C16以上的型号, 分2个字节发送地址
 * 2, 24C16及以下的型号, 分1个低字节地址 + 占用器件地址的bit1~bit3位 用于表示高位地址, 最多11位地址
 *    对于24C01/02, 其器件地址格式(8bit)为: 1  0  1  0  A2  A1  A0  R/W
 *    对于24C04,    其器件地址格式(8bit)为: 1  0  1  0  A2  A1  a8  R/W
 *    对于24C08,    其器件地址格式(8bit)为: 1  0  1  0  A2  a9  a8  R/W
 *    对于24C16,    其器件地址格式(8bit)为: 1  0  1  0  a10 a9  a8  R/W
 *    R/W      : 读/写控制位 0,表示写; 1,表示读;
 *    A0/A1/A2 : 对应器件的1,2,3引脚(只有24C01/02/04/8有这些脚)
 *    a8/a9/a10: 对应存储整列的高位地址, 11bit地址最多可以表示2048个位置,可以寻址24C16及以内的型号
 */
#define AT24C01 127
#define AT24C02 255
#define AT24C04 511
#define AT24C08 1023
#define AT24C16 2047
#define AT24C32 4095
#define AT24C64 8191
#define AT24C128 16383
#define AT24C256 32767

#define EE_TYPE AT24C02

void AT24Cxx_Init(void); /* 初始化IIC */

uint8_t AT24Cxx_Check(void); /* 检查器件 */

uint8_t AT24Cxx_Read_One_Byte(uint16_t addr); /* 指定地址读取一个字节 */

void AT24Cxx_Write_One_Byte(uint16_t addr, uint8_t data); /* 指定地址写入一个字节 */

void AT24Cxx_Write(uint16_t addr, uint8_t *pbuf, uint16_t datalen); /* 从指定地址开始写入指定长度的数据 */

void AT24Cxx_Read(uint16_t addr, uint8_t *pbuf, uint16_t datalen); /* 从指定地址开始读出指定长度的数据 */

#endif
