/**
  ******************************************************************************
  * @file    .h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MCP3421_H_
#define _MCP3421_H_

/*Includes */
	
	#include "main.h"

/*Public defines */
	#define MCP_ADR 0xD0 // 1101 + 000 ? 001 ? 010 ? 011 ? 100? 101 ? 110 ? 111

	
/*Global params*/
	extern uint32_t ADC_VAL;
/*Prototypes */
	void MCP_READ_DATA(void);
	uint8_t INIT_MCP(void);
	uint32_t MCP_GET_DATA(void);
	//Callback функция
	void MCP_TRANSFORM_DATA (void);
#endif /* __MCP3421_H__ */

