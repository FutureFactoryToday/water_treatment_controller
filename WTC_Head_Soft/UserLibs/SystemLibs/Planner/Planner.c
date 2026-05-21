/**
  ******************************************************************************
  * @file           : Planner.c
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
#include "Planner.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
planer_t planner;
uint8_t tasksCnt;
bool firstStep, cycled;
time_t timeOfNextStep;
uint32_t cycleCnt;
/* Private function prototypes -----------------------------------------------*/
void PL_ProceedStep(void);
uint8_t findLastElement(piston_task_t* task);
time_t setPreferedTime(time_t time);
/*---------------------------------------------*/
void PL_Init(){
	planner.currentStep = NULL;
	cycleCnt = 0;
	firstStep = true;
	cycled = false;
	planner.status = PL_FINISHED;
	if (fp->isLoaded != 1){
		wtc_time_t zeroTime = {0};
		
		//Filtration
		planner.currentTask = &planner.pistonTasks[REGENERATION_TASK_NUM];
		planner.currentTaskNum = REGENERATION_TASK_NUM;
		planner.pistonTasks[REGENERATION_TASK_NUM].restartDateTime = DEF_TASK_RESTART_HOURS*60*60;// hours * 60 min * 60 sec
		uint8_t taskNum = 0;
		planner.pistonTasks[REGENERATION_TASK_NUM].step[taskNum].poz = &pistonPositions.backwash;
		planner.pistonTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 14*60;
		
		planner.pistonTasks[REGENERATION_TASK_NUM].step[taskNum].poz = &pistonPositions.forwardWash;
		planner.pistonTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 8*60;
		
		planner.pistonTasks[REGENERATION_TASK_NUM].step[taskNum].poz = &pistonPositions.rabPoz;
		planner.pistonTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 5; //На всякий случай	
		
		planner.pistonTasks[REGENERATION_TASK_NUM].step[taskNum].poz = NULL;
		planner.pistonTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 0; 	
		
		
		//Softening
		planner.pistonTasks[SOFTENING_TASK_NUM].restartDateTime = DEF_TASK_RESTART_HOURS*60*60;
		taskNum = 0;
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.backwash;
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 8*60;
		
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.saltering;
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 60*60;
		
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.forwardWash;
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 6*60; 
		
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.filling;
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 6*60; 
		
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.rabPoz;
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 5; //На всякий случай	
		
		planner.pistonTasks[REGENERATION_TASK_NUM].step[taskNum].poz = NULL;
		planner.pistonTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 0; 	
		
		
		//copyTasksToFlash();
		
		planner.preferedTimeForWash = zeroTime; 
		planner.currentStep = planner.currentTask->step;
		planner.status = PL_FINISHED;
		planner.preferedTimeForWash = (wtc_time_t)DEF_TASK_PREF_TIME_TO_START;
		planner.monthBetweenService = DEF_TASK_MONTH_BETWEN_SERV;
		planner.waterBeforeRegen = DEF_WATER_VAL;
		planner.lastService = 0;
		planner.loadType = DEF_LOAD_TYPE;
		planner.cycleCnt = 0;
		
		//fp->params.planner = planner;
		
		//fp->needToSave = true;		
	} else {
		//planner = fp->params.planner;
		planner.currentTask = &planner.pistonTasks[planner.currentTaskNum];
		planner.status = PL_FINISHED;
		//PL_Planner(START_NORMAL);
	}
}


void PL_Planner (planner_control_type_t startType){
	if (planner.currentTask != NULL){
		if (planner.status == PL_FINISHED){
					switch (startType){
						case START_NORMAL:{
							if (planner.currentTask->startDateTime >= getRTC()){
								planner.currentStep = planner.currentTask->step;
								planner.status = PL_SET;
							} else {
								if (planner.currentTask->restartDateTime > 0){
								
									planner.currentTask->startDateTime = getRTC() + planner.currentTask->restartDateTime;
									
									planner.currentTask->startDateTime = setPreferedTime(planner.currentTask->startDateTime);
									
									planner.currentStep = planner.currentTask->step;
									planner.status = PL_SET;
								}
							}
							break;
						}
						case FORCE_START_NOW:{
							planner.currentTask->startDateTime = getRTC();
							planner.currentStep = planner.currentTask->step;
							planner.status = PL_SET;
							break;
						}
						case FORCE_START_NEAREST:{
							planner.currentTask->startDateTime = getRTC();
							planner.currentTask->startDateTime = setPreferedTime(planner.currentTask->startDateTime);
							planner.currentStep = planner.currentTask->step;
							planner.status = PL_SET;
							break;
						}
					}
					firstStep = false;
					return;
				} else {
					if (startType == FORCE_START_NEAREST || startType == FORCE_START_NOW){
						planner.currentTask->startDateTime = getRTC();
					}
		}
	}
	
}

time_t setPreferedTime(time_t time){
	uint32_t addDay = 0;
	struct tm tempTime = *localtime(&time);
	if (planner.preferedTimeForWash.hour < tempTime.tm_hour){
		addDay = 24*60*60;
	} else {
		if (planner.preferedTimeForWash.hour == tempTime.tm_hour) {
			if (planner.preferedTimeForWash.minute <= tempTime.tm_min){
				addDay = 24*60*60;
			}
		}
	}
	tempTime.tm_hour = planner.preferedTimeForWash.hour;
	tempTime.tm_min = planner.preferedTimeForWash.minute;
	addDay += mktime(&tempTime);
	return addDay;
}
void PL_Interrupt(){
	if (planner.status == PL_SET || planner.status == PL_WORKING){
		if (planner.currentTask->startDateTime < getRTC()){
			if (planner.status == PL_WORKING){
				planner.currentStep++;
			}
			planner.status = PL_WORKING;
			
			
			if(planner.currentStep->poz == NULL){
				planner.status = PL_FINISHED;
				PL_Planner(START_NORMAL);
				
			} else {
				PC_GoToPoz(*(planner.currentStep->poz));
				planner.currentTask->startDateTime += planner.currentStep->secPause;
			}
		}
	}
}

void copyTasksToFlash (void){

	//fp->params.planner = planner;

}

void copyTasksFromFlash(void){

	//planner = fp->params.planner;

}


wtc_time_t timeRemain (void){
	wtc_time_t tempTime = {0};
	
	uint32_t remTime = planner.currentTask->startDateTime - getRTC();
	tempTime = intToWTCTime(remTime);

	return tempTime;
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
	for(uint8_t i = 0; i < sizeof(planner.pistonTasks)/sizeof(piston_task_t);i++){
		if (planner.currentTask == &planner.pistonTasks[i]) 
			return i;
	}
	
}