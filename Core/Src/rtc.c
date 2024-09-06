/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    rtc.c
 * @brief   This file provides code for the configuration
 *          of the RTC instances.
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
/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
RTC_DateTypeDef datebuff;
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */
  __HAL_RCC_BKP_CLK_ENABLE(); // �???启后备区域时�???
  __HAL_RCC_PWR_CLK_ENABLE(); // �???启电源时�???
  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
  if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x5051)
  {
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x16;
  sTime.Minutes = 0x46;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_TUESDAY;
  DateToUpdate.Month = RTC_MONTH_AUGUST;
  DateToUpdate.Date = 0x27;
  DateToUpdate.Year = 0x24;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
    __HAL_RTC_SECOND_ENABLE_IT(&hrtc, RTC_IT_SEC);
    datebuff = DateToUpdate;
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x5051);
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, (uint16_t)datebuff.Year);
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, (uint16_t)datebuff.Month);
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, (uint16_t)datebuff.Date);
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, (uint16_t)datebuff.WeekDay);
  }
  else
  {
    datebuff.Year = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
    datebuff.Month = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3);
    datebuff.Date = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4);
    datebuff.WeekDay = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR5);
    DateToUpdate = datebuff;
    if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
    {
      Error_Handler();
    }
    __HAL_RTC_SECOND_ENABLE_IT(&hrtc, RTC_IT_SEC);
  }
  /* USER CODE END RTC_Init 2 */

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    HAL_PWR_EnableBkUpAccess();
    /* Enable BKP CLK enable for backup registers */
    __HAL_RCC_BKP_CLK_ENABLE();
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();

    /* RTC interrupt Init */
    HAL_NVIC_SetPriority(RTC_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(RTC_IRQn);
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();

    /* RTC interrupt Deinit */
    HAL_NVIC_DisableIRQ(RTC_IRQn);
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
uint8_t weekday_calculate(int y, int m, int d, int c)
{
  int w;
  if (m == 1 || m == 2)
  {
    y--, m += 12;
  }
  w = y + y / 4 + c / 4 + 26 * (m + 1) / 10 + d - 1 - 2 * c;
  while (w < 0)
    w += 7;
  w %= 7;
  w = (w == 0) ? 7 : w;
  return w;
}
void RTC_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
  RTC_TimeTypeDef time = {0};
  time.Hours = hours;
  time.Minutes = minutes;
  time.Seconds = seconds;
  if (HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}

void RTC_SetDate(uint8_t year, uint8_t month, uint8_t date)
{
  RTC_DateTypeDef setdate = {0};
  setdate.Date = date;
  setdate.Month = month;
  setdate.Year = year;

  // culculat the weekday
  setdate.WeekDay = weekday_calculate(year, month, date, 20);

  if (HAL_RTC_SetDate(&hrtc, &setdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}
/* USER CODE END 1 */
