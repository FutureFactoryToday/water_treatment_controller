/**
  ******************************************************************************
  * @file    Settings.h
  * @brief   This file contains all settings for WTC project
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SETTINGS_H_
#define _SETTINGS_H_

/*Includes */
#include "main.h"

#define UTF-8
//SPI 
#define SPI_LCD
//#define PARAL_LCD

#define TS_RESCAN_TIME 10

#define MOT_TIM TIM8

#define WTC_ORIENTATION 1

#define FLOW_TIM TIM7
#define FLOW_TIM_IRQ TIM7_IRQn
#define FLOW_TIM_CLK LL_APB1_GRP1_PERIPH_TIM7
#endif /* __SETTINGS_H__ */
