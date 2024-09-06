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
 
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
