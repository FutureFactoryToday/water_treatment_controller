/**
  ******************************************************************************
  * @file           : MOTOR.c
  * @brief          : 
  ******************************************************************************
  * @attention
  *
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Motor.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void MOT_FORWARD(void){
	LL_GPIO_SetOutputPin(AIN2_GPIO_Port, AIN2_Pin);
	LL_GPIO_SetOutputPin(BIN2_GPIO_Port, BIN2_Pin);
	
	LL_GPIO_ResetOutputPin(AIN1_GPIO_Port, AIN1_Pin);
	LL_GPIO_ResetOutputPin(BIN1_GPIO_Port, BIN1_Pin);
	
}
void MOT_BRAKE(void){
	LL_GPIO_ResetOutputPin(AIN2_GPIO_Port, AIN2_Pin);
	LL_GPIO_ResetOutputPin(BIN2_GPIO_Port, BIN2_Pin);
}
void MOT_REVERSE(void){
	LL_GPIO_SetOutputPin(AIN2_GPIO_Port, AIN2_Pin);
	LL_GPIO_SetOutputPin(BIN2_GPIO_Port, BIN2_Pin);
	
	LL_GPIO_SetOutputPin(AIN1_GPIO_Port, AIN1_Pin);
	LL_GPIO_SetOutputPin(BIN1_GPIO_Port, BIN1_Pin);
}


void MOT_TEST(void){
	MOT_BRAKE();
	LL_mDelay(100);
	MOT_FORWARD();
	LL_mDelay(5000);
	MOT_REVERSE();
	LL_mDelay(5000);
	MOT_BRAKE();
}