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
#define SUB_VERSION 2
#define NEED_TO_UPDATE 1

#define SYSTEM_PO_VERSION (MAIN_VERSION << 16) + (SUB_VERSION << 1) + NEED_TO_UPDATE

#define UTF-8
//SPI 
#define SPI_LCD

/*LCD TYPE*/
#define ST7796S

#define LSB 3.3/4096

#define AVG_SLOPE 4.3

#define V25 1.43

#define DEF_SERVICE_CODE 1234
#define DEF_MAX_MOT_SPEED_PERCENT 100
#define DEF_WAIT_STALL_TIME_MS 100
#define DEF_SEEK_TIME_SECONDS 30
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

#define DEF_LOAD_TYPE 0

#define DEFAULT_TIME {2024, 03, 01,12,0,0}

#define FLASH_SECTORS 3
#endif /* __SETTINGS_H__ */
