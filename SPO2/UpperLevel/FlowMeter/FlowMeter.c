/**
  ******************************************************************************
  * @file           : FlowMeter.c
  * @brief          : 
  ******************************************************************************
  * @attention
  *
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
bool isOverFlow;
filter_t flowFilter;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
//Flow period (time of one rotation)
uint32_t FM_getFlowPeriod(void){
	return  sysParams.vars.flowCnt;
}
//Flow freq (int)
uint32_t FM_getFlowHzInt(void){
	if (sysParams.vars.flowCnt == 0){
		 return 0;
	}
	return (uint32_t)FLOW_TIM_FREQ/sysParams.vars.flowCnt;
}
//Flow freq (float)
float FM_getFlowHzFloat(void){
	if (sysParams.vars.flowCnt == 0){
		 return 0;
	}
	return FLOW_TIM_FREQ/sysParams.vars.flowCnt;
}
//Flow speed scaled by coef
float FM_getFlowSpeed(void){
	if (sysParams.vars.flowCnt == 0){
		 return 0;
	}
	return (FLOW_TIM_FREQ/sysParams.vars.flowCnt)*DEF_FLOW_COEF;
}
uint32_t FM_getFlowMeterVal(void){
	return sysParams.consts.waterQuantaty;
}
void FM_incFlowMeter(void){
	sysParams.consts.waterQuantaty += (uint32_t)FM_getFlowSpeed()*DEF_VAL_COEF;
}
void FM_Init(void){
	LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
	LL_TIM_InitTypeDef TIM_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	flowFilter = *initFilterStruct(&flowFilter,0,128);
	
	//Частота счета 1МГц
	TIM_InitStruct.Prescaler = FLOW_TIM_TAKT_FREQ/FLOW_TIM_FREQ;
  
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = UINT16_MAX;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(FLOW_TIM, &TIM_InitStruct);
	LL_TIM_DisableARRPreload(FLOW_TIM);
  LL_TIM_SetTriggerOutput(FLOW_TIM, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(FLOW_TIM);
	
	LL_TIM_EnableIT_UPDATE(FLOW_TIM);
	
	LL_TIM_EnableCounter(FLOW_TIM);
}

void FM_Sense_Interrupt(void){
if (isOverFlow){
		isOverFlow = false;
	} else {
		sysParams.vars.flowCnt = filter(&flowFilter,LL_TIM_GetCounter(FLOW_TIM));
		//flowPeriod = LL_TIM_GetCounter(FLOW_TIM);//filter(&flowFilter,LL_TIM_GetCounter(FLOW_TIM));
	}
	LL_TIM_SetCounter(FLOW_TIM,0);
}
void FM_OVF_Interrupt(void){
	isOverFlow = true;
	sysParams.vars.flowCnt = 0;
}

