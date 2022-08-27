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
typedef struct {
	unsigned START:1;
	unsigned DIR:1;
} mot_status_t;
/*Prototypes */
void MOT_START(void);
void MOT_STOP(void);
void MOT_CHANGE_DIR(void);
void initMot(void);

void MOT_TEST(void);
#endif /* __MOTOR_H__ */

