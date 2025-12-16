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

//#define PROMEI //#if defined (MARCO) ... #endif //#if defined (MARCO) ...#else... #endif //#if defined (MARCO) ...#elif defined (MACRO)... #endif
#define GEYSER
//#define GEYSER_MAIN_LOGO

#define MAIN_VERSION 1
#define SUB_VERSION 34
#define TEST_NUM 1

#define ENABLE_MEM_READ

#define SYSTEM_PO_VERSION (MAIN_VERSION *100) + (SUB_VERSION) 

#define UTF_8
//SPI 
#define SPI_LCD

/*LCD TYPE*/
#define ST7796S

#define LSB 3.3/4096

#define SALT_COEF 90.349

#define AVG_SLOPE 4.3

#define V25 1.43

#define NO_TOUCH_DELAY_VALUE 60

#define MAX_FRAM_ADR 			0x7FF

#define MAX_RAM_ADDRESS 0xFFFFFF

#define DAYS_TO_STORE 90
#define ERROR_SECTOR_ADDR 0x000000
#define WATER_USAGE_SECTOR_ADDR	MAX_RAM_ADDRESS - DAYS_TO_STORE*sizeof(log_data_t) //0xFFF5DF
#define WATER_QUANT_SECTOR_ADDR WATER_USAGE_SECTOR_ADDR - DAYS_TO_STORE*sizeof(log_data_t) // 0xFFEBBF
#define WASH_SECTOR_ADDR WATER_QUANT_SECTOR_ADDR/2 //0x7FF5DF

#define DEF_SCREEN_SAVE_BL_VALUE 0

#define DEF_BL_VALUE 80
#define DEF_SCREEN_SAVE_DELAY_VALUE 120 //sec*msec
#define RESET_COUNTER_LIM 5

#define MAX_OVERALL_WATER_SHOWN_L 999999999

#define DEF_SERVICE_CODE 1408
#define DEF_MAX_MOT_SPEED_PERCENT 50
#define DEF_MIN_MOT_SPEED_PERCENT 50
#define DEF_WAIT_STALL_TIME_MS 100
#define DEF_SEEK_TIME_SECONDS 35
#define newPositions

#define DEF_WORK_POS 20//10;//+ //                               //???????? ?????????
#define	DEF_BACKWASH_POS 261//261;  //                                   //???????? ????????
#define	DEF_FORWARD_POS 500//525; //+                                      //??????????
#define	DEF_SALTERING_POS 415//415 //
#define	DEF_FILLING_POS 105; //

#define DEF_TASK_RESTART_HOURS 150
#define DEF_TASK_PREF_TIME_TO_START {0,0,0,0,0,0}
#define DEF_TASK_LAST_START
#define DEF_TASK_TOTAL_LINE 4
#define DEF_WATER_VAL 150
#define DEF_TASK_MONTH_BETWEN_SERV 12
#define DEF_LOAD_TYPE 0
#define DEF_FILTER_START_COND UNIVERSAL //Ver. 1.29 from 05.10.2025 BY_DAY
#define DEF_FILTR_CYCLE 1500
#define DEF_FILTER_RESERVE 20
#define DEF_NO_WATER_CNT_LIMIT 60*10*100 //60sec*10min*100Hz

#define DEF_EXTERNAL_COM_ENABLE_WASH_DELAY 100*3 //100Hz*3sec
#define DEF_EXTERNAL_COM_EX_START_DELAY 100*10 //100Hz*10sec

#define DEFAULT_TIME {2025,8,01,12,0,0}

#if defined (GEYSER)
	#define DEF_PHONE_NUMBER 78126050055
#else
	#define DEF_PHONE_NUMBER 79876543210
#endif

#define DEF_IMPULSE_WEIGHT 1
#define FLASH_SECTORS 3

#define UART_LOG_Q_SIZE 20

#define SOFT_WDT_TIM_VAL_DEF 500

#define DEF_BY_DAY_RESTART 5*24*60*60 //5day*24h*60min*60sec
#define DEF_BY_HOUR_RESTART 12*60*60 //12h*60min*60sec
#define DEF_UNIVERSAL_TIME_RESTART 5*24*60*60 //5day*24h*60min*60sec
#define DEF_UNIVERSAL_WATER_RESTART 3000
#define DEF_IMMEDIATELY_WATER_RESTART 3000
#define DEF_DELAYED_RESTART 3000

#define DELAY_FOR_COMPRESSOR_START 3

#define RAB_POZ_DELAY 2
#endif /* __SETTINGS_H__ */
