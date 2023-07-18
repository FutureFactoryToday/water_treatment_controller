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
#define MAX_SPEED 100
#define MIN_SPEED 60
#define MOT_PWM_FREQ 10000
#define MAX_PRESC UINT16_MAX
#define FORWARD_CHANNEL LL_TIM_CHANNEL_CH2 //AIN1
#define REVERSE_CHANNEL LL_TIM_CHANNEL_CH3 //AIN2
typedef enum {
	SIMPLE = 0,
	PWM
} mot_control_type_t;

typedef struct {
    unsigned INITED: 1;
    unsigned START: 1;
    unsigned DIR: 1;
    unsigned TYPE: 1;
} mot_control_t;

/*Global params*/


/*Prototypes */
void MOT_Start(void);
void MOT_Stop(void);
void MOT_SetDir(uint8_t dir);
void MOT_SetSpeed(uint8_t speed);

void MOT_Init(mot_control_type_t type, TIM_TypeDef *TIM);
void MOT_SetControlType(mot_control_type_t type);

mot_control_t MOT_GetControl(void);

void MOT_TEST(void);

#endif /* __MOTOR_H__ */

