/**
  ******************************************************************************
  * @file    System.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/*Includes */
#include "main.h"

/*Public defines */
#define DEF_SYST_CONFIG_LANG ENGLISH
#define DEF_SYST_CONFIG_LCD_TYPE 1
#define DEF_SYST_CONFIG_LCD_ROTATION 1

typedef enum{
	ENGLISH,
	RUSSIAN
} language_t;

typedef struct{
	uint32_t lang;
	uint32_t LCD_TYPE;
	uint32_t LCD_ROTATION;
} sys_param_t;

extern sys_param_t sysParam;
/*Global params*/

/*Prototypes */
void System_init(void);

#endif /* __SYSTEM_H__ */

