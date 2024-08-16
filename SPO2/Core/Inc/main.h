/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_rtc.h"
#include "stm32f1xx_ll_spi.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "time.h"
#include "HardSettings/uC_Settings.h"
#include "HardSettings/System_Settings.h"
#include "adc.h"
#include "crc.h"
#include "dma.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "Relays/Relay.h"
#include "System/System.h"
#include "Util\Util.h"
#include "Service/Service.h"
#include "TFT/Fonts/wtc_fonts.h"
#include "Motor/Motor.h"
#include "TFT/stm32_adafruit_lcd.h"
#include "TFT/stm32_adafruit_ts.h"
#include "TFT/bmp.h"
#include "GUI/GUI.h"
#include "TFT/lcd/ili9486/ili9486.h"
#include "TFT/lcd/ili9488/ili9488.h"
#include "TFT/lcd/st7796s/st7796s.h"
#include "PistonControl/PistonControl.h"
#include "Time/Time.h"
#include "FlowMeter/FlowMeter.h"
#include "Time/Alarm.h"
#include "GUI/Frames/mainFrame.h"
#include "FlashIC/FlashDriver.h"
#include "Filter/filter.h"
#include "FlashParams/FlashParam.h"
#include "Time/Time.h"
#include "PistonControl/PistonControl.h"
#include "Planner/Planner.h"
#include "Logger/Logger.h"

#include "GUI/TouchController.h"
#include "GUI/Frames/items.h"
#include "GUI/Frames/widgets.h"
#include "GUI/Frames/keyboardFrame.h"
#include "GUI/Frames/mainFrame.h"
#include "GUI/Frames/mainMenuFrame.h"
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
#include "GUI/Frames/clockSet.h"
#include "GUI/Frames/Calendar.h"
#include "GUI/Frames/stepsFrame.h"
#include "GUI/Frames/Calendar.h"
#include "GUI/Frames/waterCountBeforeRegen.h"
#include "GUI/Frames/serviceInfo.h"
#include "GUI/Frames/serviceDateSelect.h"
#include "GUI/Frames/loadTypeFrame.h"
#include "TFT/lcd/FT6336/ctpiic.h"
#include "GUI/Frames/ManualDriveControl.h"
#include "GUI/Frames/ManualFilteringSettings.h"
#include "GUI/Frames/historyErrorsFrame.h"
#include "GUI/Frames/historyFilterFrame.h"
#include "GUI/Frames/historyMaxWaterFrame.h"
#include "GUI/Frames/historyMenuFrame.h"
#include "GUI/Frames/historyWaterFrame.h"
#include "GUI/Frames/inputOneFrame.h"
#include "GUI/Frames/universalOutputFrame.h"
#include "GUI/Frames/elMagFrame.h"
#include "GUI/Frames/periodRegenFrame.h"
#include "GUI/Frames/filterCycleFrame.h"
#include "GUI/Frames/ImpulseExitWeight.h"
#include "GUI/Frames/ExitEnableCycle.h"
#include "GUI/Frames/MotorSettingsFrame.h"

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
#define TOUCH_I2C &hi2c2
#define MOT_TIM TIM3
#define LOGIC_TIM TIM10
#define PISTON_CONTROL_TIM TIM4
#define MEM_SPI &hspi1
#define TFT_SPI &hspi2
#define OPTIC_DELAY_TIM TIM13
#define FLOW_TIM TIM7
#define BL_TIM TIM8
#define DELAY_TIM TIM14
#define _10kHz_Presc 7199
#define PLANNER_TIM TIM11
#define Vbat_ADC_Pin LL_GPIO_PIN_0
#define Vbat_ADC_GPIO_Port GPIOC
#define V3v3_ADC_Pin LL_GPIO_PIN_1
#define V3v3_ADC_GPIO_Port GPIOC
#define Vpwr_ADC_Pin LL_GPIO_PIN_2
#define Vpwr_ADC_GPIO_Port GPIOC
#define V5v_ADC_Pin LL_GPIO_PIN_3
#define V5v_ADC_GPIO_Port GPIOC
#define TFT_RES_Pin LL_GPIO_PIN_0
#define TFT_RES_GPIO_Port GPIOA
#define TFT_CS_Pin LL_GPIO_PIN_1
#define TFT_CS_GPIO_Port GPIOA
#define SELF_RES_Pin LL_GPIO_PIN_2
#define SELF_RES_GPIO_Port GPIOA
#define SD_CS_Pin LL_GPIO_PIN_3
#define SD_CS_GPIO_Port GPIOA
#define TOUCH_RES_Pin LL_GPIO_PIN_4
#define TOUCH_RES_GPIO_Port GPIOA
#define DRV_1_FB_Pin LL_GPIO_PIN_5
#define DRV_1_FB_GPIO_Port GPIOA
#define TOUCH_IRQ_Pin LL_GPIO_PIN_6
#define TOUCH_IRQ_GPIO_Port GPIOA
#define TOUCH_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define DRV_2_FB_Pin LL_GPIO_PIN_7
#define DRV_2_FB_GPIO_Port GPIOA
#define TFT_DATA_COM_Pin LL_GPIO_PIN_4
#define TFT_DATA_COM_GPIO_Port GPIOC
#define Vrel_ADC_Pin LL_GPIO_PIN_5
#define Vrel_ADC_GPIO_Port GPIOC
#define DRV_IN2_Pin LL_GPIO_PIN_0
#define DRV_IN2_GPIO_Port GPIOB
#define DRV_IN1_Pin LL_GPIO_PIN_1
#define DRV_IN1_GPIO_Port GPIOB
#define DP_SWITCH_Pin LL_GPIO_PIN_2
#define DP_SWITCH_GPIO_Port GPIOB
#define DP_SWITCH_EXTI_IRQn EXTI2_IRQn
#define TOUCH_SCL_Pin LL_GPIO_PIN_10
#define TOUCH_SCL_GPIO_Port GPIOB
#define TOUCH_SDA_Pin LL_GPIO_PIN_11
#define TOUCH_SDA_GPIO_Port GPIOB
#define TFT_SCK_Pin LL_GPIO_PIN_13
#define TFT_SCK_GPIO_Port GPIOB
#define TFT_MISO_Pin LL_GPIO_PIN_14
#define TFT_MISO_GPIO_Port GPIOB
#define TFT_MOSI_Pin LL_GPIO_PIN_15
#define TFT_MOSI_GPIO_Port GPIOB
#define TFT_BL_Pin LL_GPIO_PIN_6
#define TFT_BL_GPIO_Port GPIOC
#define REL_DC_FB_Pin LL_GPIO_PIN_7
#define REL_DC_FB_GPIO_Port GPIOC
#define REL_AC_FB_Pin LL_GPIO_PIN_8
#define REL_AC_FB_GPIO_Port GPIOC
#define REL_DC_ON_Pin LL_GPIO_PIN_9
#define REL_DC_ON_GPIO_Port GPIOC
#define REL_AC_ON_Pin LL_GPIO_PIN_8
#define REL_AC_ON_GPIO_Port GPIOA
#define OPTIC_IRQ_Pin LL_GPIO_PIN_11
#define OPTIC_IRQ_GPIO_Port GPIOA
#define OPTIC_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define ILED_Pin LL_GPIO_PIN_12
#define ILED_GPIO_Port GPIOA
#define METER_IRQ_Pin LL_GPIO_PIN_15
#define METER_IRQ_GPIO_Port GPIOA
#define METER_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define FRAM_HOLD_Pin LL_GPIO_PIN_10
#define FRAM_HOLD_GPIO_Port GPIOC
#define MEM_CS_Pin LL_GPIO_PIN_11
#define MEM_CS_GPIO_Port GPIOC
#define MEM_RES_Pin LL_GPIO_PIN_12
#define MEM_RES_GPIO_Port GPIOC
#define MEM_SCK_Pin LL_GPIO_PIN_3
#define MEM_SCK_GPIO_Port GPIOB
#define MEM_MISO_Pin LL_GPIO_PIN_4
#define MEM_MISO_GPIO_Port GPIOB
#define MEM_MOSI_Pin LL_GPIO_PIN_5
#define MEM_MOSI_GPIO_Port GPIOB
#define MEM_WP_Pin LL_GPIO_PIN_6
#define MEM_WP_GPIO_Port GPIOB
#define FRAM_CS_Pin LL_GPIO_PIN_7
#define FRAM_CS_GPIO_Port GPIOB
#define BOOT_Pin LL_GPIO_PIN_8
#define BOOT_GPIO_Port GPIOB
#define FRAM_WP_Pin LL_GPIO_PIN_9
#define FRAM_WP_GPIO_Port GPIOB

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

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
