/**
  ******************************************************************************
  * @file    Planner.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PLANNER_H_
#define _PLANNER_H_

#define VERSION 2
/*Includes */
#include "main.h"

/*Public defines */
#define NAME_LENGTH 12
#define STEP_PER_TASK_NUM 10
#define TASK_NUM 3

#define DEF_TASK_RESTART_HOURS 150
#define DEF_TASK_PREF_TIME_TO_START {0,0,0,0,0,0}
#define DEF_TASK_LAST_START
#define DEF_TASK_TOTAL_LINE 4
#define DEF_WATER_VAL 150
#define DEF_TASK_MONTH_BETWEN_SERV 3
#define DEF_LOAD_TYPE 0

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
} piston_task_t;

typedef enum {
	//INTERRUPT_CALL = 0,
	START_NORMAL = 1,
	FORCE_START_NOW,
	FORCE_START_NEAREST
} planner_control_type_t;

typedef enum {
	PL_FINISHED = 1,
	PL_SET,
	PL_WORKING
} planer_status_t;

typedef struct{
	piston_task_t pistonTasks[TASK_NUM];
	piston_task_t *currentTask;
	task_line_t *currentStep;
	planer_status_t status;
	wtc_time_t preferedTimeForWash;
	uint32_t monthBetweenService;
	uint32_t waterBeforeRegen;
	wtc_time_t lastService;
	uint32_t loadType;
	uint32_t cycleCnt;
}planer_t;
/*Global params*/
extern bool cycled;
extern uint32_t cycleCnt;
extern planer_t planner;
/*Prototypes */

void PL_Init(void);

void PL_Planner (planner_control_type_t startType);

void PL_Interrupt();
void copyOneTaskToFlash (uint16_t task);
void copyOneTaskFromFlash(uint16_t task);
void copyTasksToFlash (void);
void copyTasksFromFlash(void);
wtc_time_t timeRemain (void);

bool PL_deleteTaskLine(piston_task_t* task, uint8_t line);
bool PL_addTaskLine(piston_task_t* task,task_line_t tl);
bool PL_modTaskLine(piston_task_t* task, uint8_t line, task_line_t tl);


#endif /* _PLANNER_H_ */
