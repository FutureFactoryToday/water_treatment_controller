/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_rtc.h"
#include "stm32f1xx_ll_spi.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "Settings.h"
#include "System/System.h"
#include "Util.h"
#include "Service/Service.h"
#include "TFT/Fonts/wtc_fonts.h"
#include "Motor/Motor.h"
#include "TFT/stm32_adafruit_lcd.h"
#include "TFT/stm32_adafruit_ts.h"
#include "TFT/bmp.h"
#include "GUI/GUI.h"
#include "TFT/lcd/ili9486/ili9486.h"
#include "PistonControl/PistonControl.h"
#include "Time/Time.h"
#include "FlowMeter/FlowMeter.h"
#include "Time/Alarm.h"
#include "GUI/Frames/mainFrame.h"
#include "Planner/Planner.h"
#include "FlashParams/FlashParam.h"

#include "GUI/Frames/keyboardFrame.h"
#include "GUI/Frames/mainFrame.h"
#include "GUI/Frames/filterSelectionFrame.h"
#include "GUI/Frames/softeningFrame.h"
#include "GUI/Frames/filteringFrame.h"
#include "GUI/Frames/alarmListFrame.h"
#include "GUI/Frames/alarmNotiFrame.h"
#include "GUI/Frames/adjustmentFrame.h"
#include "GUI/Frames/regenServiceFrame.h"
#include "GUI/Frames/quantityCountServiceFrame.h"
#include "GUI/Frames/washingTimeServiceFrame.h"
#include "GUI/Frames/regenPeriodServiceFrame.h"
#include "GUI/Frames/serviceMenuFrame.h"
#include "GUI/Frames/daysBetweenRegenCustomerFrame.h"
#include "GUI/Frames/delayedRegenCustomerFrame.h"
#include "GUI/Frames/forcedRegenCustomerFrame.h"
#include "GUI/Frames/washingTimeCustomerFrame.h"
#include "GUI/Frames/PinCode.h"
#include "GUI/Frames/timeSetFrame.h"
#include "GUI/Frames/serviceMenuFrame.h"
#include "GUI/Frames/menuFrame.h"

//#include "USER/GUI.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern uint32_t _1ms_cnt;
extern uint8_t* errorCause;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RELAY_1_Pin LL_GPIO_PIN_0
#define RELAY_1_GPIO_Port GPIOC
#define RELAY_2_Pin LL_GPIO_PIN_1
#define RELAY_2_GPIO_Port GPIOC
#define FCS_Pin LL_GPIO_PIN_2
#define FCS_GPIO_Port GPIOC
#define SD_CS_Pin LL_GPIO_PIN_3
#define SD_CS_GPIO_Port GPIOC
#define TFT_RES_Pin LL_GPIO_PIN_0
#define TFT_RES_GPIO_Port GPIOA
#define TFT_COM_EN_Pin LL_GPIO_PIN_1
#define TFT_COM_EN_GPIO_Port GPIOA
#define TFT_WR_Pin LL_GPIO_PIN_2
#define TFT_WR_GPIO_Port GPIOA
#define TOUCH_INT_Pin LL_GPIO_PIN_3
#define TOUCH_INT_GPIO_Port GPIOA
#define TOUCH_INT_EXTI_IRQn EXTI3_IRQn
#define TOUCH_CS_Pin LL_GPIO_PIN_4
#define TOUCH_CS_GPIO_Port GPIOA
#define TFT_RD_Pin LL_GPIO_PIN_4
#define TFT_RD_GPIO_Port GPIOC
#define TFT_DATA_COM_Pin LL_GPIO_PIN_5
#define TFT_DATA_COM_GPIO_Port GPIOC
#define DB0_Pin LL_GPIO_PIN_0
#define DB0_GPIO_Port GPIOB
#define DB1_Pin LL_GPIO_PIN_1
#define DB1_GPIO_Port GPIOB
#define DB2_Pin LL_GPIO_PIN_2
#define DB2_GPIO_Port GPIOB
#define DB10_Pin LL_GPIO_PIN_10
#define DB10_GPIO_Port GPIOB
#define DB11_Pin LL_GPIO_PIN_11
#define DB11_GPIO_Port GPIOB
#define DB12_Pin LL_GPIO_PIN_12
#define DB12_GPIO_Port GPIOB
#define DB13_Pin LL_GPIO_PIN_13
#define DB13_GPIO_Port GPIOB
#define DB14_Pin LL_GPIO_PIN_14
#define DB14_GPIO_Port GPIOB
#define DB15_Pin LL_GPIO_PIN_15
#define DB15_GPIO_Port GPIOB
#define AIN1_Pin LL_GPIO_PIN_7
#define AIN1_GPIO_Port GPIOC
#define AIN2_Pin LL_GPIO_PIN_8
#define AIN2_GPIO_Port GPIOC
#define OPT_SENS_Pin LL_GPIO_PIN_11
#define OPT_SENS_GPIO_Port GPIOA
#define OPT_SENS_EXTI_IRQn EXTI15_10_IRQn
#define ILED_Pin LL_GPIO_PIN_12
#define ILED_GPIO_Port GPIOA
#define METER_INP_Pin LL_GPIO_PIN_10
#define METER_INP_GPIO_Port GPIOC
#define DRV_MODE_Pin LL_GPIO_PIN_11
#define DRV_MODE_GPIO_Port GPIOC
#define PB_SENS_Pin LL_GPIO_PIN_12
#define PB_SENS_GPIO_Port GPIOC
#define SOUND_ON_Pin LL_GPIO_PIN_2
#define SOUND_ON_GPIO_Port GPIOD
#define DB3_Pin LL_GPIO_PIN_3
#define DB3_GPIO_Port GPIOB
#define DB4_Pin LL_GPIO_PIN_4
#define DB4_GPIO_Port GPIOB
#define DB5_Pin LL_GPIO_PIN_5
#define DB5_GPIO_Port GPIOB
#define DB6_Pin LL_GPIO_PIN_6
#define DB6_GPIO_Port GPIOB
#define DB7_Pin LL_GPIO_PIN_7
#define DB7_GPIO_Port GPIOB
#define DB8_Pin LL_GPIO_PIN_8
#define DB8_GPIO_Port GPIOB
#define DB9_Pin LL_GPIO_PIN_9
#define DB9_GPIO_Port GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif
/* USER CODE BEGIN Private defines */
#define TRUE 1
#define FALSE 0

#define TFT_SPI_CS_Pin TFT_COM_EN_Pin
#define TFT_SPI_MISO_Pin LL_GPIO_PIN_14
#define TFT_SPI_MOSI_Pin LL_GPIO_PIN_15
#define TFT_SPI_SCK_Pin LL_GPIO_PIN_13

#define TFT_SPI_CS_Port TFT_COM_EN_GPIO_Port
#define TFT_SPI_MISO_Port GPIOB
#define TFT_SPI_MOSI_Port GPIOB
#define TFT_SPI_SCK_Port GPIOB

//#define AIN2_GPIO_Port GPIOC
//#define AIN2_Pin 9

//#define AIN1_GPIO_Port GPIOC
//#define AIN1_Pin 8

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
