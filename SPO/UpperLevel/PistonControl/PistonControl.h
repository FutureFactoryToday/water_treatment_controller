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
#define STALL_TIME 500
#define FULL_LENGTH 10000
#define SEEK_TIME 10

typedef enum {
	 PC_ERROR,
	 PC_IN_PROCESS,
	 PC_COMPLETE,
	 PC_SEEK_ZERO,
} pc_status_t;

typedef struct {
	uint32_t closedPosition;                                //Закрытое положение
	
	uint32_t backwash;                                      //Обратная промывка
	uint32_t regeneration;                                  //Регенерация
	uint32_t filling;                                       //Заполнение
    uint32_t softening;                                     //Умягчение
    uint32_t flushing;                                      //Промывка
    uint32_t filtering;                                     //Фильтрация
	
} stored_offsets_params;

extern stored_offsets_params* op;

extern int32_t curPoz;

/*Global params*/

/*Prototypes */
void PC_Init(void);
void PC_GoToPoz (uint32_t dest);
uint32_t PC_GetCurPoz (void);
void initPistonControl(void);
void PC_OpticSensInterrupt(void);
pc_status_t PC_GetStatus(void);
void PC_Control(void);
//Если калибровка прошла успещно вернется 2, иначе что-то не нашли
uint8_t PC_AUTO_CALIBRATE(void);
void PC_Stop(void);
#endif /* __PISTON_CONTROL_H__ */

