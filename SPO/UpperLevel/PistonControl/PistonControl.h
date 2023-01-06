/**
  ******************************************************************************
  * @file    PistonControl.h
  * @brief   This file contains all the function prototypes for
  *          the PistonControl.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PISTON_CONTROL_H_
#define _PISTON_CONTROL_H_

/*Includes */
#include "main.h"

/*Public defines */
//Направление движения штока
#define OUT 1
#define IN 0

#define STALL_TIME 500 //мс
#define FULL_LENGTH 10000 //обороты
#define SEEK_TIME 10 //сек
#define PISTON_MOVE_MIN 100 //обороты
#define SPEED 37.7 //37,9 //Оборотов/сек при полном напряжении
typedef enum {
	 PC_ERROR,
	 PC_IN_PROCESS,
	 PC_READY,
	 PC_SEEK_ZERO,
} pc_work_status_t;
typedef enum {
	OK,
	STALL,
	NO_MIN,
	NO_MAX,
	NO_MIN_MAX,
	SKIPPED
} pc_calib_result_t;

typedef struct {
	pc_calib_result_t calibResult;
	pc_work_status_t workStatus;
	int32_t curPoz;
	int32_t maxPoz;
	int32_t minPoz;
} pc_params_t;


/*Global params*/

/*Prototypes */
void PC_Init(void);
void PC_GoToPoz (int32_t dest);
void PC_OpticSensInterrupt(void);
pc_params_t* PC_GetParams(void);
void PC_Control(void);
//Если калибровка прошла успещно вернется 2, иначе что-то не нашли
pc_calib_result_t PC_AUTO_CALIBRATE(void);
void PC_Stop(void);
void PC_Restart (void);
#endif /* __PISTON_CONTROL_H__ */

