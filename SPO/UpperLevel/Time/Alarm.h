/**
  ******************************************************************************
  * @file    Alarm.h
  * @brief   This file contains all the function prototypes for
  *          the Alarm.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ALARM_H_
#define _ALARM_H_

/*Includes */
#include "main.h"

/*Public defines */

/*Global params*/

/*Prototypes */
void setAlarm(wtc_time_t* time, void (*func)(void));
void ALARM_INTERRUPT();
#endif /* __ALARM_H__ */

