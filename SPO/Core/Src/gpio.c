/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

  /**/
  LL_GPIO_ResetOutputPin(GPIOC, RELAY_1_Pin|RELAY_2_Pin|FCS_Pin|LL_GPIO_PIN_9);

  /**/
  LL_GPIO_ResetOutputPin(GPIOB, DB0_Pin|DB1_Pin|DB2_Pin|DB10_Pin
                          |DB11_Pin|DB12_Pin|DB3_Pin|DB4_Pin
                          |DB5_Pin|DB6_Pin|DB7_Pin|DB8_Pin
                          |DB9_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_8|ILED_Pin);

  /**/
  LL_GPIO_ResetOutputPin(SOUND_ON_GPIO_Port, SOUND_ON_Pin);

  /**/
  LL_GPIO_SetOutputPin(GPIOC, SD_CS_Pin|TFT_RD_Pin|TFT_DATA_COM_Pin|DRV_MODE_Pin);

  /**/
  LL_GPIO_SetOutputPin(GPIOA, TFT_RES_Pin|TFT_COM_EN_Pin|TFT_WR_Pin|TOUCH_CS_Pin);

  /**/
  GPIO_InitStruct.Pin = RELAY_1_Pin|RELAY_2_Pin|FCS_Pin|SD_CS_Pin
                          |TFT_RD_Pin|TFT_DATA_COM_Pin|LL_GPIO_PIN_9|DRV_MODE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = TFT_RES_Pin|TFT_COM_EN_Pin|TFT_WR_Pin|TOUCH_CS_Pin
                          |LL_GPIO_PIN_8|ILED_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = DB0_Pin|DB1_Pin|DB2_Pin|DB10_Pin
                          |DB11_Pin|DB12_Pin|DB3_Pin|DB4_Pin
                          |DB5_Pin|DB6_Pin|DB7_Pin|DB8_Pin
                          |DB9_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = METER_INP_Pin|PB_SENS_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = SOUND_ON_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(SOUND_ON_GPIO_Port, &GPIO_InitStruct);

  /**/
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE3);

  /**/
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE11);

  /**/
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE15);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_3;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_11;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_15;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  LL_GPIO_SetPinMode(TOUCH_INT_GPIO_Port, TOUCH_INT_Pin, LL_GPIO_MODE_FLOATING);

  /**/
  LL_GPIO_SetPinMode(OPT_SENS_GPIO_Port, OPT_SENS_Pin, LL_GPIO_MODE_FLOATING);

  /**/
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_15, LL_GPIO_MODE_FLOATING);

  /* EXTI interrupt init*/
  NVIC_SetPriority(EXTI3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),14, 0));
  NVIC_EnableIRQ(EXTI3_IRQn);
  NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),14, 0));
  NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */
void LED_BLINK(){
	LL_GPIO_TogglePin(ILED_GPIO_Port,ILED_Pin);
	wtc_time_t alT = *getTime();
	addSec(&alT,1);
	setAlarm(&alT, &LED_BLINK);
}

/* USER CODE END 2 */
