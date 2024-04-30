/**
  ******************************************************************************
  * @file           : sysParams.consts.planerConsts.c
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

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

uint8_t tasksCnt;

time_t timeOfNextStep;
uint32_t oldSec;
/* Private function prototypes -----------------------------------------------*/
void PL_ProceedStep(void);
uint8_t findLastElement(piston_task_t* task);
time_t setPreferedTime(time_t time);
/*---------------------------------------------*/
void PL_Init(){
	sysParams.vars.planer.cycleCnt = 0;
	sysParams.vars.planer.cycled = false;
	if (sysParams.consts.planerConsts.currentTaskNum >= 3){
		sysParams.consts.planerConsts.currentTaskNum = 0;
	}
	if (sysParams.consts.planerConsts.currentStepNum >= STEP_PER_TASK_NUM){
		sysParams.consts.planerConsts.currentStepNum = 0;
	}
	sysParams.vars.planer.currentTask = &sysParams.consts.planerConsts.planerTasks[sysParams.consts.planerConsts.currentTaskNum];
	sysParams.vars.planer.currentStep = &sysParams.consts.planerConsts.planerTasks[sysParams.consts.planerConsts.currentTaskNum].step[sysParams.consts.planerConsts.currentStepNum];
	if (sysParams.vars.status.flags.PistonInited == 1)
	sysParams.vars.status.flags.PlanerInited = 1;
	if (sysParams.vars.status.flags.StoredParamsLoaded == 1){
		if (sysParams.consts.planerConsts.status == PL_WORKING){
			PC_GoToPoz(*(sysParams.vars.planer.currentStep->poz));
		}
	}
}

void PL_planer (planer_control_type_t startType){
	if (sysParams.vars.planer.currentTask != NULL &&
		sysParams.vars.error.flags.PistonFail == 0){
		if (sysParams.consts.planerConsts.status == PL_FINISHED || 
				sysParams.consts.planerConsts.status == PL_SET){
					switch (startType){
						case START_NORMAL:{
							if (sysParams.vars.planer.currentTask->startDateTime >= getRTC()){
								sysParams.vars.planer.currentStep = sysParams.vars.planer.currentTask->step;
								sysParams.consts.planerConsts.status = PL_SET;
							} else {
								if (sysParams.vars.planer.currentTask->restartDateTime > 0){
								
									sysParams.vars.planer.currentTask->startDateTime = getRTC() + sysParams.vars.planer.currentTask->restartDateTime;
									
									sysParams.vars.planer.currentTask->startDateTime = setPreferedTime(sysParams.vars.planer.currentTask->startDateTime);
									
									sysParams.vars.planer.currentStep = sysParams.vars.planer.currentTask->step;
									
									sysParams.consts.planerConsts.currentStepNum = 0;
									
									sysParams.consts.planerConsts.status = PL_SET;
									
								}
							}
							break;
						}
						case FORCE_START_NOW:{
							sysParams.vars.planer.currentTask->startDateTime = getRTC();
							sysParams.vars.planer.currentStep = sysParams.vars.planer.currentTask->step;
							sysParams.consts.planerConsts.currentStepNum = 0;
							sysParams.consts.planerConsts.status = PL_SET;
							PL_Interrupt();
							break;
						}
						case FORCE_START_NEAREST:{
							sysParams.vars.planer.currentTask->startDateTime = getRTC();
							sysParams.vars.planer.currentTask->startDateTime = setPreferedTime(sysParams.vars.planer.currentTask->startDateTime);
							sysParams.vars.planer.currentStep = sysParams.vars.planer.currentTask->step;
							sysParams.consts.planerConsts.currentStepNum = 0;
							sysParams.consts.planerConsts.status = PL_SET;
							break;
						}
					}
					FP_SaveParam();
					return;
				} else {
					if (startType == FORCE_START_NEAREST || startType == FORCE_START_NOW){
						sysParams.vars.planer.currentTask->remainingTime = 0;
					}		}
	} else {
		sysParams.consts.planerConsts.status = PL_FINISHED;
	}
	
}

time_t setPreferedTime(time_t time){
	uint32_t addDay = 0;
	struct tm tempTime = *localtime(&time);
	if (sysParams.consts.planerConsts.preferedTimeForWash.hour < tempTime.tm_hour){
		addDay = 24*60*60;
	} else {
		if (sysParams.consts.planerConsts.preferedTimeForWash.hour == tempTime.tm_hour) {
			if (sysParams.consts.planerConsts.preferedTimeForWash.minute <= tempTime.tm_min){
				addDay = 24*60*60;
			}
		}
	}
	tempTime.tm_hour = sysParams.consts.planerConsts.preferedTimeForWash.hour;
	tempTime.tm_min = sysParams.consts.planerConsts.preferedTimeForWash.minute;
	addDay += mktime(&tempTime);
	return addDay;
}
void PL_Interrupt(){
	if (sysParams.vars.error.flags.PistonFail == 1){
		sysParams.consts.planerConsts.status = PL_FINISHED;
		sysParams.consts.planerConsts.currentStepNum = 0;
		sysParams.vars.planer.currentTask = &sysParams.consts.planerConsts.planerTasks[sysParams.consts.planerConsts.currentTaskNum];
		sysParams.vars.planer.currentStep = &sysParams.consts.planerConsts.planerTasks[sysParams.consts.planerConsts.currentTaskNum].step[sysParams.consts.planerConsts.currentStepNum];
		return;
	}
	if (sysParams.vars.status.flags.PlanerInited == 1){
		uint32_t remTime = sysParams.vars.planer.currentTask->remainingTime;
		if(remTime && oldSec != LL_RTC_TIME_Get(RTC)){
			sysParams.vars.planer.currentTask->remainingTime--;
			oldSec = LL_RTC_TIME_Get(RTC);
		}
		if (sysParams.consts.planerConsts.status == PL_SET &&
			sysParams.vars.planer.currentTask->startDateTime < getRTC()){
			sysParams.consts.planerConsts.status = PL_WORKING;
			PC_GoToPoz(*(sysParams.vars.planer.currentStep->poz));
			sysParams.vars.planer.currentTask->remainingTime = sysParams.vars.planer.currentStep->secPause;
			oldSec = LL_RTC_TIME_Get(RTC);
			return;
		}
		if(sysParams.consts.planerConsts.status == PL_WORKING){
			if (sysParams.vars.planer.currentTask->remainingTime == 0){
					sysParams.vars.planer.currentStep++;
					sysParams.consts.planerConsts.currentStepNum++;
				if(sysParams.vars.planer.currentStep->poz == NULL){
					sysParams.consts.planerConsts.status = PL_FINISHED;
					PC_GoToPoz(sysParams.consts.pistonPositions.rabPoz);
					PL_planer(START_NORMAL);
				} else {
					PC_GoToPoz(*(sysParams.vars.planer.currentStep->poz));
					sysParams.vars.planer.currentTask->remainingTime = sysParams.vars.planer.currentStep->secPause;
				}
			}
		}
		if(sysParams.consts.planerConsts.status == PL_FINISHED){
			PC_GoToPoz(sysParams.consts.pistonPositions.rabPoz);
		}
		oldSec = LL_RTC_TIME_Get(RTC);
	}
}

void copyTasksToFlash (void){
	#if VERSION == 1
	for (uint16_t task = 0; task < TASK_NUM; task++){
		copyOneTaskToFlash(task);
	}
	#else 
	//fp->params.sysParams.vars.planer = sysParams.vars.planer;
	#endif
}

void copyTasksFromFlash(void){
	#if VERSION == 1
		for (uint16_t task = 0; task < TASK_NUM; task++){
		copyOneTaskFromFlash(task);
	#else 
	//sysParams.vars.planer = fp->params.sysParams.vars.planer;
	#endif
}


wtc_time_t timeRemain (void){
	return intToWTCTime(sysParams.vars.planer.currentTask->remainingTime);
}

bool PL_addTaskLine(piston_task_t* task,task_line_t tl){
	uint8_t lastEl = findLastElement(task);
	if (lastEl < STEP_PER_TASK_NUM - 1){
		task->step[lastEl] = tl;
		return true;
	}
	return false;
}

bool PL_deleteTaskLine(piston_task_t* task, uint8_t line){
	uint8_t lastEl = findLastElement(task);
	if (line < STEP_PER_TASK_NUM - 1 && line < lastEl){
		for(uint8_t i = 0; i < lastEl - line; i++){
			task->step[line + i] = task->step[line + i + 1];
		}
	}
}

bool PL_modTaskLine(piston_task_t* task, uint8_t line, task_line_t tl){
	uint8_t lastEl = findLastElement(task);
	if (line < lastEl){
		task->step[lastEl] = tl;
		return true;
	}
	return false;
}

uint8_t findLastElement(piston_task_t* task){
	uint8_t pozN = 0;
	while(task->step[pozN].poz != NULL){
		pozN++;
	}
	return pozN;
}

uint8_t PL_getCurrentTaskNum(void){
	for(uint8_t i = 0; i < sizeof(sysParams.consts.planerConsts.planerTasks)/sizeof(piston_task_t);i++){
		if (sysParams.vars.planer.currentTask == &sysParams.consts.planerConsts.planerTasks[i]) 
			return i;
	}
	
}