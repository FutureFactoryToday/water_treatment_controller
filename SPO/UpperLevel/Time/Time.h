/**
  ******************************************************************************
  * @file    TIME.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TIME_H_
#define _TIME_H_

/*Includes */
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

/*Public defines */
#define DEFAULT_TIME {2000, 1, 1,12,0,0}

typedef struct {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	bool isSecondSecHalf;
} time_t;
/*Global params*/

/*Prototypes */
void initTime();
void setTime (time_t time);
time_t* getTime ();
void RTC_Interrupt();
uint8_t* getFormatedTime(uint8_t* fStr);

uint8_t* getTimeString();

#endif /* __TIME_H__ */

