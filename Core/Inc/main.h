/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "ring_buffer.h"
//#include "Uart3_IRQ.h"
//#include <platform_mutex.h>	
#include "Lcd.h"
#include "GUI.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "ATcommand.h"
#include "MQTT_Task.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
  
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MISO_Pin GPIO_PIN_8
#define MISO_GPIO_Port GPIOF
#define MOSI_Pin GPIO_PIN_9
#define MOSI_GPIO_Port GPIOF
#define PEN_Pin GPIO_PIN_10
#define PEN_GPIO_Port GPIOF
#define BL_EN_Pin GPIO_PIN_0
#define BL_EN_GPIO_Port GPIOB
#define T_CLK_Pin GPIO_PIN_1
#define T_CLK_GPIO_Port GPIOB
#define T_CS_Pin GPIO_PIN_2
#define T_CS_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_0
#define RS_GPIO_Port GPIOG
#define IIC_SCL_Pin GPIO_PIN_10
#define IIC_SCL_GPIO_Port GPIOB
#define IIC_SDA_Pin GPIO_PIN_11
#define IIC_SDA_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_11
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_12
#define LED2_GPIO_Port GPIOD
#define BEEP_Pin GPIO_PIN_13
#define BEEP_GPIO_Port GPIOD
#define DTH11_PIN_Pin GPIO_PIN_12
#define DTH11_PIN_GPIO_Port GPIOA
#define RD_Pin GPIO_PIN_4
#define RD_GPIO_Port GPIOD
#define WR_Pin GPIO_PIN_5
#define WR_GPIO_Port GPIOD
#define CS_Pin GPIO_PIN_12
#define CS_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */
  // STM32连接引脚是指TFTLCD插槽引脚内部连接的STM32引脚
  //=========================================电源接线================================================//
  //      LCD模块             TFTLCD插槽引脚        STM32连接引脚
  //       VDD       --->         5V/3.3              DC5V/3.3V          //电源
  //       GND       --->          GND                  GND              //电源�?????
  //=======================================液晶屏数据线接线==========================================//
  // 本模块默认数据�?�线类型�?????16位并口�?�线
  //      LCD模块             TFTLCD插槽引脚        STM32连接引脚
  //       DB0       --->          D0                   PD14        -|
  //       DB1       --->          D1                   PD15         |
  //       DB2       --->          D2                   PD0          |
  //       DB3       --->          D3                   PD1          |
  //       DB4       --->          D4                   PE7          |
  //       DB5       --->          D5                   PE8          |
  //       DB6       --->          D6                   PE9          |
  //       DB7       --->          D7                   PE10         |
  // 如果使用8位模式，请使用下面高8位并口数据引�?????                    |===>液晶�?????16位并口数据信�?????
  //       DB8       --->          D8                   PE11         |
  //       DB9       --->          D9                   PE12         |
  //       DB10      --->          D10                  PE13         |
  //       DB11      --->          D11                  PE14         |
  //       DB12      --->          D12                  PE15         |
  //       DB13      --->          D13                  PD8          |
  //       DB14      --->          D14                  PD9          |
  //       DB15      --->          D15                  PD10        -|
  //=======================================液晶屏控制线接线==========================================//
  //      LCD模块 				     TFTLCD插槽引脚        STM32连接引脚
  //        WR       --->          WR                   PD5             //液晶屏写数据控制信号
  //        RD       --->          RD                   PD4             //液晶屏读数据控制信号
  //        RS       --->          RS                   PG0             //液晶屏数�?????/命令控制信号
  //        RST      --->          RST                复位引脚          //液晶屏复位控制信�?????
  //        CS       --->          CS                   PG12            //液晶屏片选控制信�?????
  //        BL       --->          BL                   PB0             //液晶屏背光控制信�?????
  //=========================================触摸屏触接线=========================================//
  // 如果模块不带触摸功能或�?�带有触摸功能，但是不需要触摸功能，则不�?????要进行触摸屏接线
  //	   LCD模块             TFTLCD插槽引脚        STM32连接引脚
  //       PEN       --->          PEN                  PF10           //触摸屏触摸中断信�?????(input)
  //       MISO      --->          MISO                 PF8            //触摸屏SPI总线读信�?????(input)
  //       MOSI      --->          MOSI                 PF9            //触摸屏SPI总线写信�?????
  //       T_CS      --->          TCS                  PB2            //触摸屏片选控制信�?????
  //       T_CLK     --->          CLK                  PB1            //触摸屏SPI总线时钟信号
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
