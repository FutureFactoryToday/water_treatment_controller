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
bool PL_isRunnig;
/* Private function prototypes -----------------------------------------------*/
void PL_ProceedStep(void);
/*---------------------------------------------*/
void PL_Init(){
	currentStep = NULL;
	PL_isRunnig = false;
	if (fp->isLoaded != 1){
		wtc_time_t zeroTime = {0};
		pl_dayWashTime = zeroTime; 
		pl_nightWashTime = zeroTime; 
		
		for (uint16_t task = 0; task < TASK_NUM; task++){	
			pistonTasks[task].restartDateTime = zeroTime;
			pistonTasks[task].startDateTime = zeroTime;
			for (uint16_t step = 0; step < STEP_PER_TASK_NUM; step++){
				pistonTasks[task].step[step].poz = NULL;
				pistonTasks[task].step[step].secPause = 0;
			}
		}
		
		copyTasksToFlash();
		chosenTask = NULL;
		
		fp->needToSave = true;		
	} else {
		copyTasksFromFlash();
		chosenTask = fp->params.chosenTask;
		#ifdef TESTS
		pistonTasks[0].restartDateTime = (wtc_time_t)DEF_TASK_RESTART;
		chosenTask = &pistonTasks[0];
		
		pistonTasks[0].step[0].poz = &pistonPositions.backwash;
		pistonTasks[0].step[0].secPause = 10;
		
		pistonTasks[0].step[1].poz = &pistonPositions.filling;
		pistonTasks[0].step[1].secPause = 10;
		
		pistonTasks[0].step[2].poz = &pistonPositions.closedPosition;
		pistonTasks[0].step[2].secPause = 10;		
		#endif
		PL_Planner(START_NORMAL);
	}
}


void PL_Planner (planner_control_type_t startType){

	if (chosenTask != NULL){
		if (!isZeroDateTime(&chosenTask->restartDateTime)){
				if (!PL_isRunnig){
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
		PL_isRunnig = true;
		PC_GoToPoz(*currentStep->poz);
		currentStepDateTime = *addSec(&currentStepDateTime,currentStep->secPause);
		setAlarm(&currentStepDateTime,PL_ProceedStep);
		currentStep++;
	} else {
		PL_isRunnig = false;
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
}

void copyOneTaskFromFlash(uint16_t task){
//	pistonTasks[task].restartDateTime = fp->params.pistonTasks[task].restartDateTime;
//	pistonTasks[task].startDateTime = fp->params.pistonTasks[task].startDateTime;
//	pistonTasks[task].totalLineCnt = fp->params.pistonTasks[task].totalLineCnt;
	pistonTasks[task] = fp->params.pistonTasks[task];
}
