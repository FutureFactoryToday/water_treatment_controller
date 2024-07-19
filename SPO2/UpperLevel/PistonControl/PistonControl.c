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
uint32_t seek_cnt;

bool firstInt;
bool oldOpticInt;
int8_t opticCnt;
uint32_t start, stop;
uint32_t lastPoz;
int32_t deltaPoz;
uint32_t intPoz;

#define OPTIC_DELAY 10
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void PC_OpticTest(){
	if (oldOpticInt !=sysParams.vars.pistonParams.opticInt){
		opticCnt = OPTIC_DELAY;
		oldOpticInt = sysParams.vars.pistonParams.opticInt;
	} else {
		if (opticCnt == 0 && sysParams.vars.pistonParams.opticInt == true){
			opticCnt = -1;
			if (MOT_GetControl().DIR == OUT){
				sysParams.vars.pistonParams.curPoz--;
			} else {
				sysParams.vars.pistonParams.curPoz++;
			}
		}
	}
}

void PC_Control(void){
		//!!!!!!ЗАГЛУШКА!!!!!!//
//	if (sysParams.vars.pistonParams.workStatus == PC_ERROR){
//		sysParams.vars.pistonParams.workStatus = PC_READY;
//	}
	//!!!!!!ЗАГЛУШКА!!!!!!//
	if (sysParams.vars.status.flags.PistonInited == 0){
		return;
	}
	if (sysParams.vars.error.flags.mainPowerFail){
		sysParams.vars.error.flags.PistonFail = 1;
	}
	if (sysParams.vars.error.flags.PistonFail == 1 || 
			sysParams.vars.error.flags.mainPowerFail == 1 ||
			sysParams.vars.error.flags.MotorFail == 1){
				
		sysParams.vars.pistonParams.workStatus = PC_ERROR;		
		MOT_Stop();
		return;
				
	}
	deltaPoz = sysParams.vars.pistonParams.curPoz - lastPoz;
	if (deltaPoz > 10){
		//MOT_Stop();
	}
	if (sysParams.vars.pistonParams.autoControl == true){
	//Need to go?
		if (sysParams.vars.pistonParams.curPoz != sysParams.vars.pistonParams.destPoz){
			//Stop->Start
			if (sysParams.vars.pistonParams.workStatus == PC_READY){
				//Set DIR
				if (sysParams.vars.pistonParams.curPoz>sysParams.vars.pistonParams.destPoz){
					MOT_SetDir(OUT);
				} else {
					MOT_SetDir(IN);
				}
				//Set stall time
				sysParams.vars.pistonParams.stallTime = sysParams.consts.pistonStallDelay;
				if (sysParams.vars.pistonParams.workStatus == PC_READY){
					sysParams.vars.pistonParams.workStatus = PC_IN_PROCESS;
				}
				sysParams.vars.pistonParams.destComplete = false;
				MOT_Start();
				lastPoz = -1;
			}
			
			if (deltaPoz == 0){
				sysParams.vars.pistonParams.stallTime--;
				if (sysParams.vars.pistonParams.stallTime == 0){
					sysParams.vars.pistonParams.stallTime = 1;
					MOT_Stop();
					if (sysParams.vars.pistonParams.calibration){
						sysParams.vars.pistonParams.workStatus = PC_READY;
					} else {
						sysParams.vars.pistonParams.workStatus = PC_ERROR;
						sysParams.vars.error.flags.PistonFail = 1;
						sysParams.vars.error.flags.PistonStallFail = 1;
					}
				}
			} else {
				sysParams.vars.pistonParams.stallTime = sysParams.consts.pistonStallDelay;
			} 
			
			if (abs(sysParams.vars.pistonParams.destPoz - sysParams.vars.pistonParams.curPoz) < 5){
				//uint32_t speed = (MAX_SPEED*6)/10;
				MOT_SetSpeed(MIN_SPEED);
			}
		
			
		} else {
			//Destination complete
		
				sysParams.vars.pistonParams.destComplete = true;
				MOT_Stop();
				sysParams.vars.pistonParams.workStatus = PC_READY;
		 }
	}

	lastPoz = sysParams.vars.pistonParams.curPoz;
}
pc_calib_result_t PC_AUTO_CALIBRATE(void){
	pc_calib_result_t result = SKIPPED;
	if (sysParams.vars.pistonParams.workStatus == PC_READY){
		sysParams.vars.pistonParams.maxPoz = FULL_LENGTH*2;
		sysParams.vars.pistonParams.minPoz = -FULL_LENGTH*2;
		result = PASSED;
		sysParams.vars.status.flags.PistonInited = 1;
		PC_GoToPoz(20);
		while (sysParams.vars.pistonParams.workStatus == PC_IN_PROCESS);
		if (sysParams.vars.error.flags.PistonFail == 1){
			MOT_Stop();
			result = STALL;
		} else{
			sysParams.vars.pistonParams.workStatus = PC_READY;
			sysParams.vars.pistonParams.calibration = true;
			PC_GoToPozWithSpeed(- (FULL_LENGTH + 100), 100);
			//Ждем пока сработает контроль или SEEK_TIME секунд
			while (sysParams.vars.pistonParams.workStatus == PC_IN_PROCESS && seek_cnt++ < sysParams.consts.pistonSeekTime*1000){
				LL_mDelay(1);
			}
			if (seek_cnt >= sysParams.consts.pistonSeekTime*1000){
				result = NO_MIN;
			}
			
			sysParams.vars.pistonParams.destPoz = sysParams.vars.pistonParams.minPoz = sysParams.vars.pistonParams.curPoz = 0;
			sysParams.vars.pistonParams.calibration = false;
			
			sysParams.vars.pistonParams.maxPoz = FULL_LENGTH;
			
		}
		if (result == PASSED){
			PC_GoToPoz(sysParams.consts.pistonPositions.rabPoz);
			sysParams.vars.status.flags.PistonInited = 1;
		} else {
			sysParams.vars.status.flags.PistonInited = 0;
			sysParams.vars.error.flags.PistonFail = 1;
		}
			
	}
	return result;
}

void PC_GoToPoz (int32_t dest){
	if(sysParams.vars.status.flags.PistonInited == 1 &&
		sysParams.vars.error.flags.PistonFail == 0){
		sysParams.vars.pistonParams.workStatus = PC_READY;
		PC_GoToPozWithSpeed(dest, MAX_SPEED);
	}
}
void PC_GoToPozWithSpeed (int32_t dest, uint8_t speed){
	if (dest != sysParams.vars.pistonParams.curPoz){
		sysParams.vars.pistonParams.destPoz = dest;
	}
	MOT_SetSpeed(speed);
	PC_Control();
}

pc_params_t* PC_GetParams (void){
	return &sysParams.vars.pistonParams;
}


int16_t PC_GetCurPoz(void){
	int16_t val = sysParams.vars.pistonParams.curPoz;
	return val;
}
void PC_Init(void){
	intPoz = 0;
	
	if (sysParams.vars.error.flags.mainPowerFail == 0){
		sysParams.vars.pistonParams.workStatus = PC_READY;
		sysParams.vars.pistonParams.curPoz = 0;
		sysParams.vars.pistonParams.autoControl = true;
		MOT_Init(PWM,MOT_TIM);
		
		LL_TIM_EnableCounter(PISTON_CONTROL_TIM);
		LL_TIM_ClearFlag_UPDATE(PISTON_CONTROL_TIM);
		LL_TIM_EnableIT_UPDATE(PISTON_CONTROL_TIM);
		LL_TIM_EnableCounter(OPTIC_DELAY_TIM);
		LL_TIM_ClearFlag_UPDATE(OPTIC_DELAY_TIM);
		LL_TIM_EnableIT_UPDATE(OPTIC_DELAY_TIM);
		

		sysParams.vars.pistonParams.calibResult = PC_AUTO_CALIBRATE();
		
		if (sysParams.vars.pistonParams.calibResult != PASSED){
			sysParams.vars.pistonParams.workStatus = PC_ERROR;
		}
		
	} else {
		sysParams.vars.pistonParams.workStatus = PC_ERROR;
		sysParams.vars.pistonParams.curPoz = 0;
		sysParams.vars.pistonParams.autoControl = true;
		sysParams.vars.error.flags.PistonFail = 1;
		sysParams.vars.error.flags.MotorFail = 1;
	}
}

volatile  uint32_t intCnt = 0;
void PC_OpticSensInterrupt(void){
	uint32_t delt = 0;
	intCnt++;
	if (!firstInt){
		sysParams.vars.pistonParams.stallTime = sysParams.consts.pistonStallDelay*5;
	} else {
		 firstInt = false;
	}
	
	if (MOT_GetControl().DIR == OUT){
		sysParams.vars.pistonParams.curPoz++;
		delt = destination - sysParams.vars.pistonParams.curPoz;
	}else {
		sysParams.vars.pistonParams.curPoz--;
		delt = sysParams.vars.pistonParams.curPoz - destination;
	}
	
	if (delt < 20){
		MOT_SetSpeed(80);
		MOT_Start();
	}
	if (delt < 2){
		MOT_Stop();
		sysParams.vars.pistonParams.workStatus = PC_READY;
		return;
	}
}
void PC_Restart (void){
	if ( sysParams.vars.pistonParams.workStatus == PC_ERROR){
		sysParams.vars.pistonParams.workStatus = PC_READY;
	}
}
bool PC_isBusy(){
	return sysParams.vars.pistonParams.workStatus == PC_IN_PROCESS;
}

int8_t PC_pozNum (uint32_t* poz){
	uint32_t* ptr = &sysParams.consts.pistonPositions;
	uint8_t size = sizeof(sysParams.consts.pistonPositions)/sizeof(uint32_t);
	for (uint8_t i = 0; i < size; i++){
		if (poz == ptr++){
			return i;
		}
	}
	return -1;
}

