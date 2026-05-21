/**
  ******************************************************************************
  * @file    Optic.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _OPTIC_H_
#define _OPTIC_H_

/*Includes */
#include "main.h"

/*Public defines */

/*Global params*/
extern uint32_t opticCnt;
extern uint8_t opticStatus;
/*Prototypes */

void opticInterrupt(void);
void initOptic(void);

#endif /* __OPTIC_H__ */

