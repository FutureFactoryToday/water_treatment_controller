/**
  ******************************************************************************
  * @file    Service.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SERVICE_H_
#define _SERVICE_H_

/*Includes */
#include "main.h"

/*Public defines */
#define TOUCH_CALIB_CNT 1
/*Global params*/

/*Prototypes */
void SERV_TS_CALIB(void);
uint8_t SERV_TS_TEST (int16_t kXe,int16_t kYe,int16_t bXe,int16_t bYe);
#endif /* __SERVICE_H__ */

