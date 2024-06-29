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
#define FIL_DEPTH 8
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
bool isOverFlow;
filter_t flowFilter;
bool oldMeterInt;
int16_t flowMeterCnt;
uint32_t timVal;
uint32_t filBuf[FIL_DEPTH];
uint8_t filPtr;
uint64_t filResult;
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
	return (float)FLOW_TIM_FREQ/sysParams.vars.flowCnt;
}
//Flow speed scaled by coef
float FM_getFlowSpeed(void){
	if (sysParams.vars.flowCnt == 0){
		 return 0;
	}
	float res = FM_getFlowHzFloat();
	res /= DEF_FLOW_COEF;
	return res;
}
uint32_t FM_getFlowMeterVal(void){
	return sysParams.consts.waterQuantaty;
}
void FM_incFlowMeter(void){
	if (sysParams.consts.planerConsts.status != PL_WORKING){
		float water = FM_getFlowSpeed();
		sysParams.consts.waterQuantaty += water;
		sysParams.consts.dayWaterUsage += water;
		sysParams.consts.waterFromLastFilter += water;
	}
}
void FM_Init(void){
	LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
	LL_TIM_InitTypeDef TIM_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	flowFilter = *initFilterStruct(&flowFilter,0,8);
	for (uint8_t i = 0; i < FIL_DEPTH; i++){
		filBuf[i] = LL_TIM_GetAutoReload(FLOW_TIM);
	}
	filPtr = 0;
	filResult = 0;
	//Частота счета 1МГц
	TIM_InitStruct.Prescaler = FLOW_TIM_TAKT_FREQ/FLOW_TIM_FREQ;
  
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = UINT16_MAX;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(FLOW_TIM, &TIM_InitStruct);
	LL_TIM_DisableARRPreload(FLOW_TIM);
  LL_TIM_SetTriggerOutput(FLOW_TIM, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(FLOW_TIM);
	LL_TIM_SetCounter(FLOW_TIM,0);
	LL_TIM_EnableIT_UPDATE(FLOW_TIM);
	
	LL_TIM_EnableCounter(FLOW_TIM);
}

void FM_Sense_Interrupt(void){
if (isOverFlow){
		isOverFlow = false;
		sysParams.vars.flowImpulseCnt = 0;
	} else {
		if (sysParams.vars.error.flags._5VPowerFail != true){
			sysParams.vars.flowImpulseCnt++;
			if (LL_TIM_GetCounter(FLOW_TIM) < 72){
				LL_TIM_SetCounter(FLOW_TIM,0);
				LL_TIM_ClearFlag_UPDATE(FLOW_TIM);
				return;
			}
			
			 
//			filter(&flowFilter,LL_TIM_GetCounter(FLOW_TIM));
//			if (flowFilter.filtered){
//				sysParams.vars.flowCnt = flowFilter.fvalue;
//			}
			filBuf[filPtr++] = LL_TIM_GetCounter(FLOW_TIM);
			if (filPtr >= FIL_DEPTH){
				filPtr = 0;
			}
			filResult = 0;
			for (uint8_t i = 0; i < FIL_DEPTH; i++){
				filResult += filBuf[i];
				
			}
			filResult /= FIL_DEPTH;
			sysParams.vars.flowCnt = filResult;
			sysParams.consts.maxWaterUsage = MAX(sysParams.consts.maxWaterUsage,sysParams.vars.flowCnt);
			LL_TIM_SetCounter(FLOW_TIM,0);
			LL_TIM_ClearFlag_UPDATE(FLOW_TIM);
			//flowPeriod = LL_TIM_GetCounter(FLOW_TIM);//filter(&flowFilter,LL_TIM_GetCounter(FLOW_TIM));
		} else {
			sysParams.vars.flowCnt = 0;
		}
		
	}
	LL_TIM_SetCounter(FLOW_TIM,0);
}
void FM_OVF_Interrupt(void){
	isOverFlow = true;
	sysParams.vars.flowCnt = 0;//filter(&flowFilter,0);
}
#define FLOW_METER_DELAY 20
void FM_Meter_Test(void){
	if (flowMeterCnt > 0){
		flowMeterCnt--;
	}
	if (oldMeterInt != sysParams.vars.status.flags.FlowMeterInt){
		flowMeterCnt = FLOW_METER_DELAY;
		oldMeterInt = sysParams.vars.status.flags.FlowMeterInt;
	} else {
		if (flowMeterCnt == 0 && sysParams.vars.status.flags.FlowMeterInt == true){
			flowMeterCnt = -1;
			FM_Sense_Interrupt();
		}
	}
}
