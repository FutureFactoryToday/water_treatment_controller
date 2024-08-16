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
#include "Motor/Motor.h"

/*Public defines */
//Направление движения штока
#define OUT 1
#define IN 0

//#define STALL_TIME 500 //мс
#define LONG_STALL_TIME 1600
#define FULL_LENGTH 560 //обороты
//#define SEEK_TIME 30 //сек
#define PISTON_MOVE_MIN 100 //обороты
#define SPEED 37.7 //37,9 //Оборотов/сек при полном напряжении

typedef enum {
	 PC_ERROR = 1,
	 PC_IN_PROCESS,
	 PC_READY,
	 PC_SEEK_ZERO,
} pc_work_status_t;

typedef enum {
	PASSED = 1,
	STALL,
	NO_MIN,
	NO_MAX,
	NO_MIN_MAX,
	SKIPPED
} pc_calib_result_t;

typedef struct {
	pc_calib_result_t calibResult;
	pc_work_status_t workStatus;
	int16_t destPoz;
	int16_t curPoz;
	int32_t maxPoz;
	int32_t minPoz;
	uint32_t stallTime;
	motor_struct_t mot;
	bool opticInt;
	bool autoControl;
	bool destComplete;
	bool calibration;
} pc_params_t;

typedef struct {
	uint32_t rabPoz;                                //???????? ?????????
	uint32_t forwardWash;                                      //???????? ????????
	uint32_t backwash;                                  //???????????
	uint32_t saltering;                                       //??????????
	uint32_t filling;    
} piston_poz_t;

/*Global params*/
extern uint32_t intPoz;
extern int8_t opticCnt;
/*Prototypes */
void PC_Init(void);
void PC_GoToPozWithSpeed (int32_t dest, uint8_t speed);
void PC_GoToPoz (int32_t dest);
void PC_OpticSensInterrupt(void);
pc_params_t* PC_GetParams(void);
int16_t PC_GetCurPoz(void);
void PC_Control(void);
//Если калибровка прошла успещно вернется 2, иначе что-то не нашли
pc_calib_result_t PC_AUTO_CALIBRATE(bool first);
void PC_Stop(void);
void PC_Restart (void);
bool PC_isBusy();
int8_t PC_pozNum (uint32_t* poz);
void PC_OpticTest();
#endif /* __PISTON_CONTROL_H__ */

