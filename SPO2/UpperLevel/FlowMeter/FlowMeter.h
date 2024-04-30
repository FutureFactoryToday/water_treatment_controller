/**
  ******************************************************************************
  * @file    FlowMeter.h
  * @brief   This file contains all the function prototypes for
  *          the FlowMeter.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FLOW_METER_H_
#define _FLOW_METER_H_

/*Includes */
#include "main.h"

/*Public defines */
#define DEF_FLOW_COEF 1.0 //m^3/(rot/s) 
#define DEF_VAL_COEF 0.001
#define FLOW_TIM_TAKT_FREQ 72000000Ul
#define FLOW_TIM_FREQ 1000000Ul

/*Global params*/

/*Prototypes */
//Flow period (time of one rotation)
uint32_t FM_getFlowPeriod(void);
//Flow freq (int)
uint32_t FM_getFlowHzInt(void);
//Flow freq (float)
float FM_getFlowHzFloat(void);
//Flow speed scaled by coef
float FM_getFlowSpeed(void);

uint32_t FM_getFlowMeterVal(void);
void FM_Init(void);
void FM_Sense_Interrupt(void);
void FM_OVF_Interrupt(void);
void FM_incFlowMeter(void);

#endif /* __FLOW_METER_H__ */

