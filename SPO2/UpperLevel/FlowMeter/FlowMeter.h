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
#define DEF_FLOW_COEF 15.6 //imp/litr
#define DEF_VAL_COEF 1/60.0f
#define FLOW_TIM_TAKT_FREQ 72000000Ul
#define FLOW_TIM_FREQ 10000Ul

/*Global params*/
extern uint32_t waterFilterDelayCnt;
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
void FM_Inc_Water(void);
void FM_Input_Filter(void);
void FM_Meter_Test(void);
#endif /* __FLOW_METER_H__ */

