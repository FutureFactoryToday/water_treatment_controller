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

/*Includes */
#include "main.h"

/*Public defines */
#define NAME_LENGTH 12
#define STEP_PER_TASK_NUM 10
#define TASK_NUM 3

#define DEF_TASK_RESTART {0,0,30,0,0,0}
#define DEF_TASK_LAST_START
#define DEF_TASK_TOTAL_LINE 4
#define DEF_WATER_VAL 150
#define DEF_MONTH_SERV 3

#define REGENERATION_TASK_NUM 0
#define SOFTENING_TASK_NUM 1
#define MAN_TASK_NUM 2

#define DEF_TASK_NUM 0

#define START_DELAY_PAUSE 3

/*Piston position and pause to form tasks*/
typedef struct {
	uint32_t* poz;
	uint32_t secPause;
}task_line_t;

typedef struct {
	task_line_t step[STEP_PER_TASK_NUM];
	wtc_time_t restartDateTime;                //дни между регенерациями
	wtc_time_t startDateTime;                   //время первого запуска
} piston_task_t;

typedef enum {
	START_NORMAL = 1,
	FORCE_START_NOW,
	FORCE_START_NEAREST
} planner_control_type_t;
typedef enum {
	PL_WAITING = 1,
	PL_ALARM_SET,
	PL_FORCED_ALARM_SET,
	PL_WORKING
} planer_status_t;
/*Global params*/
extern piston_task_t pistonTasks[TASK_NUM], *chosenTask;
extern wtc_time_t pl_dayWashTime, pl_nightWashTime;
extern planer_status_t PL_status;
extern uint32_t monthBetweenService;
extern uint32_t waterBeforeRegen;
extern wtc_time_t lastService;
extern uint32_t loadType;
/*Prototypes */

void PL_Init(void);

void PL_Planner (planner_control_type_t startType);

void copyOneTaskToFlash (uint16_t task);
void copyOneTaskFromFlash(uint16_t task);
void copyTasksToFlash (void);
void copyTasksFromFlash(void);
wtc_time_t timeRemain (void);
#endif /* _PLANNER_H_ */
