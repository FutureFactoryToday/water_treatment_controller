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

typedef enum {
	 PC_ERROR,
	 PC_IN_PROCESS,
	 PC_COMPLETE,
} pc_status_t;
/*Global params*/

/*Prototypes */
void PC_Init(void);
void PC_GoToPoz (uint32_t dest);
uint32_t PC_GetCurPoz (void);
void initPistonControl(void);
void PC_OpticSensInterrupt(void);
pc_status_t PC_GetStatus(void);
#endif /* __PISTON_CONTROL_H__ */

