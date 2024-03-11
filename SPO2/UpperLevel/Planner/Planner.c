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
//		for (uint16_t task = 0; task < TASK_NUM; task++){	
//			pistonTasks[task].restartDateTime = zeroTime;
//			pistonTasks[task].startDateTime = zeroTime;
//			for (uint16_t step = 0; step < STEP_PER_TASK_NUM; step++){
//				pistonTasks[task].step[step].poz = NULL;
//				pistonTasks[task].step[step].secPause = 0;
//			}
//		}
		
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
		
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.backwash;
		planner.pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 10*60; 	
		
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
		
		fp->params.planner = planner;
		
		fp->needToSave = true;		
	} else {
		planner = fp->params.planner;
		planner.currentTask = &planner.pistonTasks[planner.currentTaskNum];
		planner.status = PL_FINISHED;
		//PL_Planner(START_NORMAL);
	}
}


void PL_Planner (planner_control_type_t startType){
	#if VERSION == 1
	if (ct != NULL){
		if (!isZeroDateTime(&ct->restartDateTime)){
				if (!forced){
					switch (startType){
						case START_NORMAL:{
							
							if(!isZeroDateTime(&ct->startDateTime)) {
								if (compareDateTime(&ct->startDateTime, getTime()) < 0){
									ct->startDateTime = *addDate(&ct->startDateTime,&ct->restartDateTime);
								}
								currentStepDateTime = ct->startDateTime;
								currentStepDateTime = *addSec(&currentStepDateTime,START_DELAY_PAUSE);
								status=PL_ALARM_SET;
							} else {
								return;
							}
							break;
						}
						case FORCE_START_NOW:{
							currentStepDateTime = *addSec(getTime(), START_DELAY_PAUSE);
							status=PL_FORCED_ALARM_SET;
							forced = true;
							break;
						}
						case FORCE_START_NEAREST:{
							currentStepDateTime = *getTime();
							currentStepDateTime = *setTime(&currentStepDateTime, &ct->restartDateTime);
							forced = true;
							if (compareDateTime(&currentStepDateTime, getTime()) < 0){
								currentStepDateTime = *addDay(&currentStepDateTime,1);
							}	
							status=PL_FORCED_ALARM_SET;							
							break;
						}
				}
				
				currentStep = &ct->step[0];	
				setAlarm(&currentStepDateTime,PL_ProceedStep);
				
			
			} else {
				if (!PC_isBusy()){
					switch (startType){
							case START_NORMAL:{
								break;
							}
							case FORCE_START_NOW:
							case FORCE_START_NEAREST:{
								stopAlarm();
								PL_ProceedStep();				
								break;
							}
					}
				}
			}
		}
	}
	#else
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
	
							
	#endif
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
			planner.status = PL_WORKING;
			PC_GoToPoz(*(planner.currentStep->poz));
			
			if(planner.currentStep->poz == NULL){
				planner.status = PL_FINISHED;
				PL_Planner(START_NORMAL);
				return;
			} else {
				planner.currentTask->startDateTime += planner.currentStep->secPause;
				
			}
			planner.currentStep++;
		}
	}
}

#if VERSION == 1
void PL_ProceedStep(void){
	if (currentStep->poz != NULL){
		status = PL_WORKING;
		uint32_t poz = *(currentStep->poz);
		PC_GoToPoz(poz);
		currentStepDateTime = *getTime();
		currentStepDateTime = *addSec(&currentStepDateTime,currentStep->secPause);
		setAlarm(&currentStepDateTime,PL_ProceedStep);
		currentStep++;
	} 
	if (currentStep->poz == NULL){
		status = PL_WAITING;
		cycleCnt++;
		if(cycled){
			forced = false;
			PL_Planner(FORCE_START_NOW);
		} else {
			ct->startDateTime = *addDate(getTime(), &ct->restartDateTime);
			ct->startDateTime = *setTime(&ct->startDateTime,&ct->restartDateTime);
			copyTasksToFlash();
			fp->needToSave = 1;
			forced = false;
			FP_SaveParam();
			PL_Planner(START_NORMAL);
		}
		
	}
}
#endif
void copyTasksToFlash (void){
	#if VERSION == 1
	for (uint16_t task = 0; task < TASK_NUM; task++){
		copyOneTaskToFlash(task);
	}
	#else 
	fp->params.planner = planner;
	#endif
}

void copyTasksFromFlash(void){
	#if VERSION == 1
		for (uint16_t task = 0; task < TASK_NUM; task++){
		copyOneTaskFromFlash(task);
	#else 
	planner = fp->params.planner;
	#endif
}

#if VERSION == 1
void copyOneTaskToFlash (uint16_t task){
//	fp->params.pistonTasks[task].restartDateTime = pistonTasks[task].restartDateTime;
//	fp->params.pistonTasks[task].startDateTime = pistonTasks[task].startDateTime;
//	fp->params.pistonTasks[task].totalLineCnt = pistonTasks[task].totalLineCnt;
	fp->params.pistonTasks[task] = pistonTasks[task];
	for(uint8_t stepNum = 0; stepNum < STEP_PER_TASK_NUM; stepNum++){
		if (pistonTasks[task].step[stepNum].poz == NULL){
			fp->params.pistonTasks[task].step[stepNum].poz = NULL;
		} else {
			uint32_t curAdr = (uint32_t)pistonTasks[task].step[stepNum].poz;
			uint32_t baseAdr = (uint32_t)&pistonPositions;
			fp->params.pistonTasks[task].step[stepNum].poz = (uint32_t*)((curAdr - baseAdr )/4 + 1);
			}
		}
}

void copyOneTaskFromFlash(uint16_t task){
//	pistonTasks[task].restartDateTime = fp->params.pistonTasks[task].restartDateTime;
//	pistonTasks[task].startDateTime = fp->params.pistonTasks[task].startDateTime;
//	pistonTasks[task].totalLineCnt = fp->params.pistonTasks[task].totalLineCnt;
	pistonTasks[task] = fp->params.pistonTasks[task];
	uint32_t *ptr = &pistonPositions;
	for(uint8_t stepNum = 0; stepNum < STEP_PER_TASK_NUM; stepNum++){
		if (fp->params.pistonTasks[task].step[stepNum].poz == NULL){
			pistonTasks[task].step[stepNum].poz = NULL;
		} else {
			pistonTasks[task].step[stepNum].poz = (ptr +(uint32_t)(fp->params.pistonTasks[task].step[stepNum].poz) - 1);
		}
	}
}
#endif


wtc_time_t timeRemain (void){
	wtc_time_t tempTime = {0};
	#if VERSION == 1
	if (currentStepDateTime.month != getTime()->month){
		tempTime.month = currentStepDateTime.month - getTime()->month;
	} else if (currentStepDateTime.day != getTime()->day) {
		tempTime.day = currentStepDateTime.day - getTime()->day;
	} else if (currentStepDateTime.hour != getTime()->hour){
		tempTime.hour = currentStepDateTime.hour - getTime()->hour;
	} else if (currentStepDateTime.minute != getTime()->minute){
		tempTime.minute = currentStepDateTime.minute - getTime()->minute;
	} else if (currentStepDateTime.second != getTime()->second){
		tempTime.second = currentStepDateTime.second - getTime()->second;
	}
	#else
	uint32_t remTime = planner.currentTask->startDateTime - getRTC();
	tempTime = intToWTCTime(remTime);
	#endif
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