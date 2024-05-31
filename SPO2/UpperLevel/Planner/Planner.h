/**
  ******************************************************************************
  * @file    Planer.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _planer_H_
#define _planer_H_

#define VERSION 2
/*Includes */
#include "main.h"

/*Public defines */
#define NAME_LENGTH 12
#define STEP_PER_TASK_NUM 10
#define TASK_NUM 3

#define REGENERATION_TASK_NUM 0
#define SOFTENING_TASK_NUM 1
#define MAN_TASK_NUM 2

#define DEF_TASK_NUM 0

#define START_DELAY_PAUSE 5

/*Piston position and pause to form tasks*/
typedef struct {
	uint32_t* poz;
	uint32_t secPause;
}task_line_t;

typedef struct {
	task_line_t step[STEP_PER_TASK_NUM];
	time_t restartDateTime;                //дни между регенерациями
	time_t startDateTime;                   //время первого запуска
	uint32_t remainingTime;
} piston_task_t;

typedef enum {
	//INTERRUPT_CALL = 0,
	START_NORMAL = 1,
	FORCE_START_NOW,
	FORCE_START_NEAREST
} planer_control_type_t;

typedef enum {
	PL_NOT_SET = 1,
	PL_SET,
	PL_WORKING
} planer_status_t;

typedef struct{
	piston_task_t *currentTask;
	task_line_t *currentStep;
	uint32_t cycleCnt;
	bool cycled;
	uint32_t noWaterUsageCnt;
}planer_t;

typedef enum {
	BY_DAY,
	BY_HOUR,
	DELAYED,
	IMMEDIATELY,
} start_type_t;

typedef struct{
	start_type_t startType; 							//+
	uint32_t filtroCycle; 								//+
	uint8_t filtroReserve;								//+
	time_t lastService;										//+
	//uint32_t waterBeforeRegen;						//+
	wtc_time_t preferedTimeForWash;				//+
	uint32_t monthBetweenService;					//+
	piston_task_t planerTasks[TASK_NUM];
	uint32_t currentTaskNum;
	planer_status_t status;
	uint32_t currentStepNum;
} planer_consts;

/*Global params*/

/*Prototypes */

void PL_Init(void);

void PL_planer (planer_control_type_t startType);

void PL_Interrupt();
void copyOneTaskToFlash (uint16_t task);
void copyOneTaskFromFlash(uint16_t task);
void copyTasksToFlash (void);
void copyTasksFromFlash(void);
wtc_time_t timeRemain (void);

bool PL_deleteTaskLine(piston_task_t* task, uint8_t line);
bool PL_addTaskLine(piston_task_t* task,task_line_t tl);
bool PL_modTaskLine(piston_task_t* task, uint8_t line, task_line_t tl);

uint8_t PL_getCurrentTaskNum(void);

#endif /* _sysParams.vars.planer_H_ */
