/**
  ******************************************************************************
  * @file           : Optic.c
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
#include "Optic.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint32_t opticCnt = 0;
uint8_t opticStatus = 1;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void initOptic(){
	opticCnt = 0;
	opticStatus = 1;
}

void opticInterrupt(void){
	if (opticStatus == 1 && !LL_GPIO_IsInputPinSet(OPT_SENS_GPIO_Port,OPT_SENS_Pin)){
		
		opticCnt++;
		if (opticCnt > 10000)
		{
			opticCnt = 0;
		}
		opticStatus = 0;
	} else {
		opticStatus = 1;
	}
	
}