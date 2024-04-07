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
#define DEF_SYST_CONFIG_LANG RUSSIAN
#define DEF_SYST_CONFIG_LCD_TYPE 1
#define DEF_SYST_CONFIG_LCD_ROTATION 1
#define DEF_SERVICE_CODE 1234

typedef enum{
	ENGLISH,
	RUSSIAN
} language_t;

typedef enum{
	WORK = 1,
	WAIT,
	SERVICE
}system_work_status_t;

typedef struct{
	uint32_t lang;
	uint32_t LCD_TYPE;
	uint32_t SYS_VERSION;
	uint32_t SERVICE_CODE;
	uint32_t WORK_STATUS;
} sys_param_t;

extern sys_param_t sysParam;
/*Global params*/

/*Prototypes */
void System_init(void);

#endif /* __SYSTEM_H__ */

