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

#define MAIN_VERSION 1
#define SUB_VERSION 6
#define NEED_TO_UPDATE 0

#define SYSTEM_PO_VERSION (MAIN_VERSION << 16) + (SUB_VERSION << 1) + NEED_TO_UPDATE

#define UTF-8
//SPI 
#define SPI_LCD

/*LCD TYPE*/
#define ST7796S

#define LSB 3.3/4096

#define SALT_COEF 90.349

#define AVG_SLOPE 4.3

#define V25 1.43

#define NO_TOUCH_DELAY_VALUE 60

#define RESET_COUNTER_LIM 5

#define DEF_SERVICE_CODE 1234
#define DEF_MAX_MOT_SPEED_PERCENT 100
#define DEF_WAIT_STALL_TIME_MS 100
#define DEF_SEEK_TIME_SECONDS 35
#define newPositions

#define DEF_WORK_POS 5;//+ //                               //???????? ?????????
#define	DEF_BACKWASH_POS 261;  //                                   //???????? ????????
#define	DEF_FORWARD_POS 500; //+                                      //??????????
#define	DEF_SALTERING_POS 415 //
#define	DEF_FILLING_POS 105; //

#define DEF_TASK_RESTART_HOURS 150
#define DEF_TASK_PREF_TIME_TO_START {0,0,0,0,0,0}
#define DEF_TASK_LAST_START
#define DEF_TASK_TOTAL_LINE 4
#define DEF_WATER_VAL 150
#define DEF_TASK_MONTH_BETWEN_SERV 3
#define DEF_LOAD_TYPE 0
#define DEF_FILTER_START_COND BY_DAY
#define DEF_FILTR_CYCLE 1500
#define DEF_FILTER_RESERVE 20
#define DEF_NO_WATER_CNT_LIMIT 60*10*100 //60sec*10min*100Hz

#define DEF_EXTERNAL_COM_ENABLE_WASH_DELAY 100*3 //100Hz*3sec
#define DEF_EXTERNAL_COM_EX_START_DELAY 100*10 //100Hz*10sec

#define DEFAULT_TIME {2024, 03, 01,12,0,0}

#define DEF_PHONE_NUMBER 9876543210

#define DEF_IMPULSE_WEIGHT 1
#define FLASH_SECTORS 3


#endif /* __SETTINGS_H__ */
