/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rtc.c
  * @brief   This file provides code for the configuration
  *          of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* USER CODE END 0 */

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */
	LL_RTC_ClearFlag_SEC(RTC);
  /* USER CODE END RTC_Init 0 */

  LL_RTC_InitTypeDef RTC_InitStruct = {0};
  LL_RTC_TimeTypeDef RTC_TimeStruct = {0};

    LL_PWR_EnableBkUpAccess();
    /* Enable BKP CLK enable for backup registers */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_BKP);
  /* Peripheral clock enable */
  LL_RCC_EnableRTC();

  /* RTC interrupt Init */
  NVIC_SetPriority(RTC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1, 0));
  NVIC_EnableIRQ(RTC_IRQn);

  /* USER CODE BEGIN RTC_Init 1 */
	if ((RTC->PRLH == 0 && RTC->PRLL == 0) ||
		LL_RTC_TIME_Get(RTC) == 0){
  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC and set the Time and Date
  */
  RTC_InitStruct.AsynchPrescaler = 32768;
  LL_RTC_Init(RTC, &RTC_InitStruct);
  LL_RTC_SetAsynchPrescaler(RTC, 32768);

  /** Initialize RTC and set the Time and Date
  */
  RTC_TimeStruct.Hours = 12;
  RTC_TimeStruct.Minutes = 0;
  RTC_TimeStruct.Seconds = 0;
  LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);

  /** Initialize RTC and set the Time and Date
  */

  /** Enable the Alarm A
  */
  LL_RTC_EnableIT_ALR(RTC);
  /* USER CODE BEGIN RTC_Init 2 */
		wtc_time_t defTime = DEFAULT_TIME;

		setSysTime(&defTime);
	}
  /* USER CODE END RTC_Init 2 */

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
