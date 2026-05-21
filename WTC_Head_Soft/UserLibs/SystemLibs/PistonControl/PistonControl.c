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

extern uint8_t redraw;
uint32_t stallCnt;
uint32_t seek_cnt;
uint32_t stallTime;

bool fitstInt;
bool oldOpticInt;
int8_t opticCnt;
uint32_t start, stop;
uint32_t lastPoz;
int32_t deltaPoz;


#define OPTIC_DELAY 10
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void PC_OpticTest(){
	if (opticCnt > 0){
			opticCnt--;
	}
	if (oldOpticInt !=sysParams.vars.pcParams.opticInt){
		opticCnt = OPTIC_DELAY;
		oldOpticInt = sysParams.vars.pcParams.opticInt;
	} else {
		if (opticCnt == 0 && sysParams.vars.pcParams.opticInt == true){
			opticCnt = -1;
			if (MOT_GetControl().DIR == OUT){
				sysParams.vars.pcParams.curPoz--;
			} else {
				sysParams.vars.pcParams.curPoz++;
			}
		}
	}
}

void PC_Control(void){

	
		//!!!!!!ЗАГЛУШКА!!!!!!//
//	if (sysParams.vars.pcParams.workStatus == PC_ERROR){
//		sysParams.vars.pcParams.workStatus = PC_READY;
//	}
	//!!!!!!ЗАГЛУШКА!!!!!!//
	
	if (sysParams.vars.pcParams.workStatus == PC_ERROR){
		MOT_Stop();
		return;
	}
	deltaPoz = sysParams.vars.pcParams.curPoz - lastPoz;
	if (deltaPoz > 10){
		//MOT_Stop();
	}
	if (sysParams.vars.pcParams.autoControl == true){
	//Need to go?
		if (sysParams.vars.pcParams.curPoz != sysParams.vars.pcParams.destPoz){
			//Stop->Start
			if (sysParams.vars.pcParams.workStatus == PC_READY){
				//Set DIR
				if (sysParams.vars.pcParams.curPoz>sysParams.vars.pcParams.destPoz){
					MOT_SetDir(OUT);
				} else {
					MOT_SetDir(IN);
				}
				//Set stall time
				if (sysParams.vars.pcParams.calibration){
					stallTime = STALL_TIME;
				} else {
					stallTime = STALL_TIME;
				}
				if (sysParams.vars.pcParams.workStatus == PC_READY){
					sysParams.vars.pcParams.workStatus = PC_IN_PROCESS;
				}
				sysParams.vars.pcParams.destComplete = false;
				MOT_Start();
				lastPoz = -1;
			}
			
			if (deltaPoz == 0){
				stallTime--;
				if (stallTime == 0){
					stallTime = 1;
					MOT_Stop();
					if (sysParams.vars.pcParams.calibration){
						sysParams.vars.pcParams.workStatus = PC_READY;
					} else {
						sysParams.vars.pcParams.workStatus = PC_ERROR;
					}
				}
			} else {
				stallTime = STALL_TIME;
			} 
			
			if (abs(sysParams.vars.pcParams.destPoz - sysParams.vars.pcParams.curPoz) < 5){
				MOT_SetSpeed(MAX_SPEED/2);
			}
		
			
		} else {
			//Destination complete
		
				sysParams.vars.pcParams.destComplete = true;
				MOT_Stop();
				sysParams.vars.pcParams.workStatus = PC_READY;
		 }
	}

	lastPoz = sysParams.vars.pcParams.curPoz;
}
pc_calib_result_t PC_AUTO_CALIBRATE(void){
	pc_calib_result_t result = SKIPPED;
	if (sysParams.vars.pcParams.workStatus == PC_READY){
		sysParams.vars.pcParams.maxPoz = FULL_LENGTH*2;
		sysParams.vars.pcParams.minPoz = -FULL_LENGTH*2;
		result = PASSED;
		PC_GoToPoz(20);
		LL_mDelay(500);
		while (sysParams.vars.pcParams.workStatus == PC_IN_PROCESS);
		sysParams.vars.pcParams.workStatus = PC_READY;
		sysParams.vars.pcParams.calibration = true;
		PC_GoToPozWithSpeed(- (FULL_LENGTH + 100), 100);
		//Ждем пока сработает контроль или SEEK_TIME секунд
		while (sysParams.vars.pcParams.workStatus == PC_IN_PROCESS && seek_cnt++ < SEEK_TIME*1000){
			LL_mDelay(1);
		}
		if (seek_cnt >= SEEK_TIME*1000){
			result = NO_MIN;
		}
		
		sysParams.vars.pcParams.destPoz = sysParams.vars.pcParams.minPoz = sysParams.vars.pcParams.curPoz = 0;
		sysParams.vars.pcParams.calibration = false;
		
//		seek_cnt = 0;
//		
//		PC_GoToPoz(FULL_LENGTH + 100);
//		sysParams.vars.pcParams.workStatus = PC_SEEK_ZERO;
//		//Ждем пока сработает контроль или SEEK_TIME секунд
//		while (sysParams.vars.pcParams.workStatus == PC_SEEK_ZERO 
//			&& seek_cnt++ < 2 * SEEK_TIME*1000){
//			LL_mDelay(1);
//		}
//		if (seek_cnt > 2 * SEEK_TIME*1000){
//			if (result == NO_MIN){
//				result = NO_MIN_MAX;
//			} else {
//				result = NO_MAX;
//			}
//			
//		}
//		MOT_Stop();
//		sysParams.vars.pcParams.maxPoz = sysParams.vars.pcParams.curPoz;
		sysParams.vars.pcParams.maxPoz = FULL_LENGTH;
		
//		if (result != NO_MIN_MAX && 
//			(mod(sysParams.vars.pcParams.maxPoz - sysParams.vars.pcParams.minPoz) < PISTON_MOVE_MIN || sysParams.vars.pcParams.maxPoz < sysParams.vars.pcParams.minPoz)){
//				result = STALL;
//		}

		
//		sysParams.vars.pcParams.maxPoz += mod(sysParams.vars.pcParams.minPoz);
//		sysParams.vars.pcParams.curPoz += mod(sysParams.vars.pcParams.minPoz);
//		sysParams.vars.pcParams.minPoz = 0;
     if (result == PASSED){
			 
			 PC_GoToPoz(pistonPositions.rabPoz);
			
		}
			
	}
	return result;
}

void PC_GoToPoz (int32_t dest){
	sysParams.vars.pcParams.workStatus = PC_READY;
	PC_GoToPozWithSpeed(dest, MAX_SPEED);
}
void PC_GoToPozWithSpeed (int32_t dest, uint8_t speed){
	if (dest != sysParams.vars.pcParams.curPoz){
		sysParams.vars.pcParams.destPoz = dest;
	}
	MOT_SetSpeed(speed);
	PC_Control();
}

pc_params_t* PC_GetParams (void){
	return &sysParams.vars.pcParams;
}


int16_t PC_GetCurPoz(void){
	int16_t val = sysParams.vars.pcParams.curPoz;
	return val;
}
void PC_Init(void){
	sysParams.vars.pcParams.workStatus = PC_READY;
	stallCnt = 0;
	sysParams.vars.pcParams.curPoz = 0;
	sysParams.vars.pcParams.autoControl = true;
	MOT_Init(MOT_TIM);
//	LL_TIM_EnableCounter(PISTON_CONTROL_TIM);
//	LL_TIM_ClearFlag_UPDATE(PISTON_CONTROL_TIM);
//	LL_TIM_EnableIT_UPDATE(PISTON_CONTROL_TIM);
//	LL_TIM_EnableCounter(OPTIC_DELAY_TIM);
//	LL_TIM_ClearFlag_UPDATE(OPTIC_DELAY_TIM);
//	LL_TIM_EnableIT_UPDATE(OPTIC_DELAY_TIM);
	sysParams.vars.pcParams.calibResult = PC_AUTO_CALIBRATE();
	if (sysParams.vars.pcParams.calibResult != PASSED){
		sysParams.vars.pcParams.workStatus = PC_ERROR;
		
	}
    //sysParams.vars.pcParams.workStatus = PC_READY;
}

volatile  uint32_t intCnt = 0;
void PC_OpticSensInterrupt(void){
	uint32_t delt = 0;
	intCnt++;
	if (!fitstInt){
		stallTime = 500;
	} else {
		 fitstInt = false;
	}
	stallCnt = 0;
	
	if (MOT_GetControl().DIR == OUT){
		sysParams.vars.pcParams.curPoz++;
		delt = destination - sysParams.vars.pcParams.curPoz;
	}else {
		sysParams.vars.pcParams.curPoz--;
		delt = sysParams.vars.pcParams.curPoz - destination;
	}
	
	if (delt < 20){
		MOT_SetSpeed(80);
		MOT_Start();
	}
	if (delt < 2){
		MOT_Stop();
		sysParams.vars.pcParams.workStatus = PC_READY;
		return;
	}
}
void PC_Restart (void){
	if ( sysParams.vars.pcParams.workStatus == PC_ERROR){
		sysParams.vars.pcParams.workStatus = PC_READY;
	}
}
bool PC_isBusy(){
	return sysParams.vars.pcParams.workStatus == PC_IN_PROCESS;
}

piston_position_enum_t PC_pozNum (uint32_t* poz){
	uint32_t* ptr = &pistonPositions;
	uint8_t size = sizeof(pistonPositions)/sizeof(uint32_t);
	for (uint8_t i = 0; i < size; i++){
		if (poz == ptr++){
			return i;
		}
	}
	return -1;
}

