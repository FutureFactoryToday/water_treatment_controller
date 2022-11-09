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
typedef struct {
	
} pc_struct_t;

volatile static stored_offsets_params stored_offsets_p ={0};
stored_offsets_params* op = &stored_offsets_p;
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
int32_t curPoz;
int32_t destination;
int32_t minPoz;
int32_t maxPoz;
pc_status_t status;
extern uint8_t redraw;
uint32_t stall_cnt;
uint32_t seek_cnt;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void PC_Control(void){
	if (status == PC_IN_PROCESS){//если едем
		//∆дем STALL_TIME мсек на упоре
		if (stall_cnt++ >= STALL_TIME){
			MOT_Stop();
			status = PC_ERROR;
			stall_cnt--;
		} else {
			
		}
	}
	if (status == PC_SEEK_ZERO){//если едем
		//∆дем STALL_TIME мсек на упоре
		if (stall_cnt++ >= STALL_TIME){
			MOT_Stop();
			status = PC_COMPLETE;
			stall_cnt--;
		} else {
			
		}	
	}
}
uint8_t PC_AUTO_CALIBRATE(void){
	uint8_t result = 2;
	if (status == PC_COMPLETE){
		status = PC_SEEK_ZERO;
		seek_cnt == 0;
		PC_GoToPoz(- (FULL_LENGTH + 100));
		//∆дем пока сработает контроль или SEEK_TIME секунд
		while (status == PC_SEEK_ZERO || seek_cnt++ < SEEK_TIME*1000){
			LL_mDelay(1);
		}
		if (seek_cnt >= SEEK_TIME*1000){
			result--;
		}
		MOT_Stop();
		
		minPoz = curPoz+5;
		status = PC_SEEK_ZERO;
		seek_cnt == 0;
		PC_GoToPoz(FULL_LENGTH + 100);
		//∆дем пока сработает контроль или SEEK_TIME секунд
		while (status == PC_SEEK_ZERO || seek_cnt++ < SEEK_TIME*1000){
			LL_mDelay(1);
		}
		if (seek_cnt >= SEEK_TIME*1000){
			result--;
		}
		MOT_Stop();
		maxPoz = curPoz-5;
	}
	return result;
}
void PC_GoToPoz (uint32_t dest){
	if (curPoz == dest){
		status = PC_COMPLETE;
		return;
	}
	destination = dest;
	
	if (curPoz<dest){
		MOT_SetDir(OUT);
	} else {
		MOT_SetDir(IN);
	}
	MOT_SetSpeed(MAX_SPEED);
	status = PC_IN_PROCESS;
	MOT_Start();
}

uint32_t PC_GetCurPoz (void){
	return curPoz;
}

pc_status_t PC_GetStatus(void){
	return status;
}

void PC_Init(void){
//	flash_params_t* params = FP_GetFromFlash();
//	if (*params != NULL) {
//		curPoz = params->lastPistonPoz;
//	} else {
//		curPoz = 0;
//	}
	status = PC_COMPLETE;
	stall_cnt = 0;
	curPoz = 0;
	MOT_Init(PWM,MOT_TIM);
	PC_AUTO_CALIBRATE();
}
void PC_OpticSensInterrupt(void){
	redraw = 1;
	uint32_t delt = 0;
	if (MOT_GetControl().DIR == OUT){
		curPoz++;
		delt = destination - curPoz;
	}else {
		curPoz--;
		delt = curPoz - destination;
	}
	
	if (delt < 20){
		MOT_SetSpeed(80);
		MOT_Start();
	}
	if (delt == 0){
		MOT_Stop();
		status = PC_COMPLETE;
		return;
	}
//	if (curPoz == 0 || curPoz == UINT32_MAX){
//		MOT_Stop();
//		status = PC_ERROR;
//	}
}