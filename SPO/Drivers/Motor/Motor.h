/**
  ******************************************************************************
  * @file    MOTOR.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MOTOR_H_
#define _MOTOR_H_

/*Includes */
#include "main.h"

/*Public defines */

/*Global params*/

/*Prototypes */
void MOT_FORWARD(void);
void MOT_BRAKE(void);
void MOT_REVERSE(void);

void MOT_TEST(void);
#endif /* __MOTOR_H__ */

