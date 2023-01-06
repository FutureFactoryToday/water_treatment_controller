/**
  ******************************************************************************
  * @file           : PistonControl.c
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
#include "Motor/Motor.h"
#include <math.h>
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

int32_t destination;
int32_t minPoz;
int32_t maxPoz;
pc_params_t pcParams;
extern uint8_t redraw;
uint32_t stall_cnt;
uint32_t seek_cnt;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void PC_Control(void){
	if (pcParams.workStatus == PC_IN_PROCESS){//если едем
		//∆дем STALL_TIME мсек на упоре
		if (stall_cnt++ >= STALL_TIME){
			MOT_Stop();
			pcParams.workStatus = PC_ERROR;
			stall_cnt--;
		} else {
			
		}
	}
	if (pcParams.workStatus == PC_SEEK_ZERO){//если едем
		//∆дем STALL_TIME мсек на упоре
		if (stall_cnt++ >= STALL_TIME){
			MOT_Stop();
			pcParams.workStatus = PC_READY;
			stall_cnt--;
		} else {
			
		}	
	}
}
pc_calib_result_t PC_AUTO_CALIBRATE(void){
	pc_calib_result_t result = SKIPPED;
	if (pcParams.workStatus == PC_READY){
		pcParams.maxPoz = FULL_LENGTH*2;
		pcParams.minPoz = -FULL_LENGTH*2;
		result = OK;
		seek_cnt == 0;
		PC_GoToPoz(- (FULL_LENGTH + 100));
		pcParams.workStatus = PC_SEEK_ZERO;
		//∆дем пока сработает контроль или SEEK_TIME секунд
		while (pcParams.workStatus == PC_SEEK_ZERO && seek_cnt++ < SEEK_TIME*1000){
			LL_mDelay(1);
		}
		if (seek_cnt >= SEEK_TIME*1000){
			result = NO_MIN;
		}
		MOT_Stop();
		
		pcParams.minPoz = pcParams.curPoz+5;
		
		seek_cnt = 0;
		PC_GoToPoz(FULL_LENGTH + 100);
		pcParams.workStatus = PC_SEEK_ZERO;
		//∆дем пока сработает контроль или SEEK_TIME секунд
		while (pcParams.workStatus == PC_SEEK_ZERO && seek_cnt++ < SEEK_TIME*1000){
			LL_mDelay(1);
		}
		if (seek_cnt >= SEEK_TIME*1000){
			if (result == NO_MIN){
				result = NO_MIN_MAX;
			} else {
				result = NO_MAX;
			}
			
		}
		MOT_Stop();
		pcParams.maxPoz = pcParams.curPoz-5;

		if (mod(maxPoz - minPoz) < PISTON_MOVE_MIN || maxPoz < minPoz){
				result = STALL;
		}

		if (result == OK){
			PC_GoToPoz(minPoz);
			pcParams.curPoz = 0;
		}
	}
	return result;
}
void PC_GoToPoz (int32_t dest){
	stall_cnt = 0;
	if (pcParams.workStatus = PC_ERROR){
		return;
	}
	if (pcParams.curPoz == dest){
		pcParams.workStatus = PC_READY;
		return;
	}
	if (dest > pcParams.maxPoz || dest < pcParams.minPoz){
		//pcParams.workStatus = PC_ERROR;
		//return;
	}
	destination = dest;
	
	if (pcParams.curPoz<dest){
		MOT_SetDir(OUT);
	} else {
		MOT_SetDir(IN);
	}
	MOT_SetSpeed(MAX_SPEED);
	pcParams.workStatus = PC_IN_PROCESS;
	MOT_Start();
}

pc_params_t* PC_GetParams (void){
	return &pcParams;
}


void PC_Init(void){
	pcParams.workStatus = PC_READY;
	stall_cnt = 0;
	pcParams.curPoz = 0;
	MOT_Init(PWM,MOT_TIM);
	//pcParams.calibResult = PC_AUTO_CALIBRATE();
	if (pcParams.calibResult == OK){
		pcParams.workStatus = PC_READY;
	} else {
		//pcParams.workStatus = PC_ERROR;
	}
    pcParams.workStatus = PC_READY;
}

void PC_OpticSensInterrupt(void){
	redraw = 1;
	uint32_t delt = 0;
	stall_cnt = 0;
	if (MOT_GetControl().DIR == OUT){
		pcParams.curPoz++;
		delt = destination - pcParams.curPoz;
	}else {
		pcParams.curPoz--;
		delt = pcParams.curPoz - destination;
	}
	
	if (delt < 20){
		MOT_SetSpeed(80);
		MOT_Start();
	}
	if (delt == 0){
		MOT_Stop();
		pcParams.workStatus = PC_READY;
		return;
	}
}
void PC_Restart (void){
	pcParams.workStatus = PC_READY;
}