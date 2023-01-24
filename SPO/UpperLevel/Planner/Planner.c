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
piston_task_t pistonTasks[TASK_NUM], *chosenTask;
uint8_t tasksCnt;
wtc_time_t pl_dayWashTime = {0}, pl_nightWashTime = {0}, currentStepDateTime;
task_line_t *currentStep;
planer_status_t PL_status;
/* Private function prototypes -----------------------------------------------*/
void PL_ProceedStep(void);
/*---------------------------------------------*/
void PL_Init(){
	currentStep = NULL;
	PL_status = PL_WAITING;
	if (fp->isLoaded != 1){
		wtc_time_t zeroTime = {0};
		pl_dayWashTime = zeroTime; 
		pl_nightWashTime = zeroTime; 
		
//		for (uint16_t task = 0; task < TASK_NUM; task++){	
//			pistonTasks[task].restartDateTime = zeroTime;
//			pistonTasks[task].startDateTime = zeroTime;
//			for (uint16_t step = 0; step < STEP_PER_TASK_NUM; step++){
//				pistonTasks[task].step[step].poz = NULL;
//				pistonTasks[task].step[step].secPause = 0;
//			}
//		}
		
		//Filtration
		chosenTask = &pistonTasks[REGENERATION_TASK_NUM];
		pistonTasks[REGENERATION_TASK_NUM].restartDateTime = (wtc_time_t)DEF_TASK_RESTART;
		chosenTask = &pistonTasks[0];
		uint8_t taskNum = 0;
		pistonTasks[REGENERATION_TASK_NUM].step[taskNum].poz = &pistonPositions.backwash;
		pistonTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 14*60;
		
		pistonTasks[REGENERATION_TASK_NUM].step[taskNum].poz = &pistonPositions.filtering;
		pistonTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 8*60;
		
		pistonTasks[REGENERATION_TASK_NUM].step[taskNum].poz = &pistonPositions.closedPosition;
		pistonTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 5; //На всякий случай	
		
		pistonTasks[REGENERATION_TASK_NUM].step[taskNum].poz = NULL;
		pistonTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 0; 	
		
		
		//Softening
		pistonTasks[SOFTENING_TASK_NUM].restartDateTime = (wtc_time_t)DEF_TASK_RESTART;
		taskNum = 0;
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.backwash;
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 8*60;
		
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.softening;
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 60*60;
		
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.backwash;
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 10*60; 	
		
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.filtering;
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 6*60; 
		
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.flushing;
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 6*60; 
		
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &pistonPositions.closedPosition;
		pistonTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 5; //На всякий случай	
		
		pistonTasks[REGENERATION_TASK_NUM].step[taskNum].poz = NULL;
		pistonTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 0; 	
		
		copyTasksToFlash();
		fp->params.chosenTaskNum = REGENERATION_TASK_NUM;
		fp->needToSave = true;		
	} else {
		copyTasksFromFlash();
		chosenTask = &pistonTasks[fp->params.chosenTaskNum];
		PL_Planner(START_NORMAL);
	}
}


void PL_Planner (planner_control_type_t startType){

	if (chosenTask != NULL){
		if (!isZeroDateTime(&chosenTask->restartDateTime)){
				if (PL_status == PL_WAITING){
					switch (startType){
						case START_NORMAL:{
							if(!isZeroDateTime(&chosenTask->startDateTime)) {
								if (compareDateTime(&chosenTask->startDateTime, getTime()) < 0){
									chosenTask->startDateTime = *addDate(&chosenTask->startDateTime,&chosenTask->restartDateTime);
								}
								currentStepDateTime = chosenTask->startDateTime;
								currentStepDateTime = *addSec(&currentStepDateTime,START_DELAY_PAUSE);
							} else {
								return;
							}
							break;
						}
						case FORCE_START_NOW:{
							currentStepDateTime = *addSec(getTime(), START_DELAY_PAUSE);		
							break;
						}
						case FORCE_START_NEAREST:{
							currentStepDateTime = *getTime();
							currentStepDateTime = *setTime(&currentStepDateTime, &chosenTask->restartDateTime);
							if (compareDateTime(&currentStepDateTime, getTime()) < 0){
								currentStepDateTime = *addDay(&currentStepDateTime,1);
							}								
							break;
						}
				}
				
				currentStep = &chosenTask->step[0];	
				setAlarm(&currentStepDateTime,PL_ProceedStep);
				PL_status=PL_ALARM_SET;
			
			} else {
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
void PL_ProceedStep(void){
	if (currentStep->poz != NULL){
		PL_status = PL_WORKING;
		uint32_t poz = *(currentStep->poz);
		PC_GoToPoz(poz);
		currentStepDateTime = *addSec(&currentStepDateTime,currentStep->secPause);
		setAlarm(&currentStepDateTime,PL_ProceedStep);
		currentStep++;
	} else {
		PL_status = PL_WAITING;
		redraw = 1;
		chosenTask->startDateTime = *addDate(getTime(), &chosenTask->restartDateTime);
		chosenTask->startDateTime = *setTime(&chosenTask->startDateTime,&chosenTask->restartDateTime);
		PL_Planner(START_NORMAL);
	}
}

void copyTasksToFlash (void){
	for (uint16_t task = 0; task < TASK_NUM; task++){
		copyOneTaskToFlash(task);
	}
}

void copyTasksFromFlash(void){
		for (uint16_t task = 0; task < TASK_NUM; task++){
		copyOneTaskFromFlash(task);
	}
}

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
