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
uint32_t stallCnt;
uint32_t seek_cnt;
uint32_t stallTime;
piston_poz_t pistonPositions;
bool fitstInt;
uint32_t start, stop;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void PC_Control(void){

	if (pcParams.workStatus == PC_IN_PROCESS){//если едем
		//Ждем STALL_TIME мсек на упоре
		if (stallCnt++ >= stallTime){
			MOT_Stop();
			pcParams.workStatus = PC_ERROR;
			stallCnt--;
		} else {
		
		}
	}
	if (pcParams.workStatus == PC_SEEK_ZERO){//если едем
		//Ждем STALL_TIME мсек на упоре
		if (stallCnt++ >= stallTime){
			MOT_Stop();
			pcParams.workStatus = PC_READY;
			stallCnt--;
		} else {
		
		}	
	}
}
pc_calib_result_t PC_AUTO_CALIBRATE(void){
	pc_calib_result_t result = SKIPPED;
	if (pcParams.workStatus == PC_READY){
		pcParams.maxPoz = FULL_LENGTH*2;
		pcParams.minPoz = -FULL_LENGTH*2;
		result = PASSED;
		seek_cnt = 0;
		stallTime = LONG_STALL_TIME;
		PC_GoToPoz(20);
		while (pcParams.workStatus == PC_IN_PROCESS);
		stallTime = 1500;
		pcParams.workStatus = PC_SEEK_ZERO;
		PC_GoToPozWithSpeed(- (FULL_LENGTH + 100), 80);
		//Ждем пока сработает контроль или SEEK_TIME секунд
		while (pcParams.workStatus == PC_IN_PROCESS && seek_cnt++ < SEEK_TIME*1000){
			LL_mDelay(1);
		}
		if (seek_cnt >= SEEK_TIME*1000){
			result = NO_MIN;
		}
		MOT_Stop();
		
		pcParams.minPoz = pcParams.curPoz = 0;
//		seek_cnt = 0;
//		
//		PC_GoToPoz(FULL_LENGTH + 100);
//		pcParams.workStatus = PC_SEEK_ZERO;
//		//Ждем пока сработает контроль или SEEK_TIME секунд
//		while (pcParams.workStatus == PC_SEEK_ZERO 
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
//		pcParams.maxPoz = pcParams.curPoz;
		pcParams.maxPoz = FULL_LENGTH;
		
//		if (result != NO_MIN_MAX && 
//			(mod(pcParams.maxPoz - pcParams.minPoz) < PISTON_MOVE_MIN || pcParams.maxPoz < pcParams.minPoz)){
//				result = STALL;
//		}

		
//		pcParams.maxPoz += mod(pcParams.minPoz);
//		pcParams.curPoz += mod(pcParams.minPoz);
//		pcParams.minPoz = 0;
     if (result == PASSED){
			 #ifdef newPositions
			 PC_GoToPoz(pistonPositions.rabPoz);
			 #else
				PC_GoToPoz(pistonPositions.closedPosition);
			#endif
			 LL_mDelay(100);
			 while( pcParams.workStatus == PC_IN_PROCESS);
		}
			
	}
	return result;
}

void PC_GoToPoz (int32_t dest){
	PC_GoToPozWithSpeed(dest, MAX_SPEED);
}
void PC_GoToPozWithSpeed (int32_t dest, uint8_t speed){
	stallTime = LONG_STALL_TIME;
	fitstInt = true;
		//!!!!!!ЗАГЛУШКА!!!!!!//
	if (PC_ERROR){
		pcParams.workStatus = PC_READY;
	}
	//!!!!!!ЗАГЛУШКА!!!!!!//
	stallCnt = 0;
	if (pcParams.workStatus == PC_ERROR){
		return;
	}
	if (pcParams.curPoz == dest){
		pcParams.workStatus = PC_READY;
		return;
	}

	destination = dest;
	
	if (pcParams.curPoz<dest){
		MOT_SetDir(OUT);
	} else {
		MOT_SetDir(IN);
	}
	MOT_SetSpeed(speed);
	pcParams.workStatus = PC_IN_PROCESS;
	MOT_Start();
}

pc_params_t* PC_GetParams (void){
	return &pcParams;
}


void PC_Init(void){
	pcParams.workStatus = PC_READY;
	stallCnt = 0;
	pcParams.curPoz = 0;
	
	if (fp->isLoaded != 1){
		#ifndef newPositions
		pistonPositions.closedPosition = DEF_CLOSED_POS;
		pistonPositions.backwash = DEF_BACKWASH_POS;
		pistonPositions.regeneration = DEF_REGENERATION_POS;
		pistonPositions.filling = DEF_FILLING_POS;
		pistonPositions.softening = DEF_SOFTENNING_POS;
		pistonPositions.flushing = DEF_FLUSHING_POS;
		pistonPositions.rabPoz = DEF_FILTERING_POS;
		#else
		pistonPositions.rabPoz = DEF_WORK_POS; //РабРеж
		pistonPositions.forwardWash = DEF_FORWARD_POS;
		pistonPositions.backwash = DEF_BACKWASH_POS; //обр пром
		pistonPositions.saltering = DEF_SALTERING_POS;
		pistonPositions.filling = DEF_FILLING_POS;
		
		#endif
		fp->params.pistonPositions = pistonPositions;
		fp->needToSave = 1;
	} else {
		pistonPositions = fp->params.pistonPositions;
	}
	MOT_Init(PWM,MOT_TIM);
	pcParams.calibResult = PC_AUTO_CALIBRATE();
	if (!pcParams.calibResult == PASSED){
		pcParams.workStatus = PC_ERROR;
		MOT_Stop();
	}
    //pcParams.workStatus = PC_READY;
}

uint32_t start;
void PC_OpticSensInterrupt(void){
	uint32_t delt = 0;
	if (!fitstInt){
		stallTime = 500;
	} else {
		 fitstInt = false;
	}
	stallCnt = 0;
	
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
	if (delt < 2){
		MOT_Stop();
		pcParams.workStatus = PC_READY;
		return;
	}
}
void PC_Restart (void){
	if ( pcParams.workStatus == PC_ERROR){
		pcParams.workStatus = PC_READY;
	}
}
bool PC_isBusy(){
	return pcParams.workStatus == PC_IN_PROCESS;
}

int8_t PC_pozNum (uint32_t* poz){
	uint32_t* ptr = &pistonPositions;
	uint8_t size = sizeof(pistonPositions)/sizeof(uint32_t);
	for (uint8_t i = 0; i < size; i++){
		if (poz == ptr++){
			return i;
		}
	}
	return -1;
}