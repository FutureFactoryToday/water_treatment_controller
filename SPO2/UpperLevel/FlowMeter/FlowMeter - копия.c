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
bool oldPinVal;
bool newPulse;
filter_t flowFilter;
uint32_t waterFilterDelayCnt;
uint8_t successfulCnt;
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
	float res = (float)(FLOW_TIM_FREQ/sysParams.vars.flowCnt);
	res *= DEF_FLOW_COEF;
	return res;
}
uint32_t FM_getFlowMeterVal(void){
	return sysParams.consts.waterQuantaty;
}
void FM_incFlowMeter(void){
	if (sysParams.consts.planerConsts.status != PL_WORKING){
		float water = FM_getFlowSpeed();
		water *= DEF_VAL_COEF;
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
	
	//Частота счета 1МГц
	TIM_InitStruct.Prescaler = (FLOW_TIM_TAKT_FREQ/FLOW_TIM_FREQ) - 1;
  
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 71;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(FLOW_TIM, &TIM_InitStruct);
	LL_TIM_DisableARRPreload(FLOW_TIM);
  LL_TIM_SetTriggerOutput(FLOW_TIM, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(FLOW_TIM);
	LL_TIM_SetCounter(FLOW_TIM,0);
	LL_TIM_EnableIT_UPDATE(FLOW_TIM);
	
	LL_TIM_EnableCounter(FLOW_TIM);
	
	waterFilterDelayCnt = 0;
	successfulCnt = 0;
	newPulse = false;
}
#define DEF_WATER_DELAY_CNT 3
void FM_Sense_Interrupt(void){
	if (newPulse){
		sysParams.vars.flowCnt = 0;
	}
	newPulse = true;
	LL_TIM_SetCounter(FLOW_TIM,0);
	LL_TIM_ClearFlag_UPDATE(FLOW_TIM);
//	if (!newPulse){
//		newPulse = true;
//		oldPinVal = LL_GPIO_IsInputPinSet(METER_IRQ_GPIO_Port, METER_IRQ_Pin);
//		waterFilterDelayCnt = DEF_WATER_DELAY_CNT;
//	}
	
}

void FM_Input_Filter(void){
//	if (newPulse){
//		if (waterFilterDelayCnt){
//			waterFilterDelayCnt--;
//		} else {
//			if (oldPinVal == LL_GPIO_IsInputPinSet(METER_IRQ_GPIO_Port, METER_IRQ_Pin)){
//				successfulCnt++;
//				if (successfulCnt >= 3){
//					FM_Inc_Water();
//					newPulse = false;
//					return;
//				}
//				waterFilterDelayCnt = DEF_WATER_DELAY_CNT;
//			} else {
//				newPulse = false;
//			}
//		}
//	}
}
static uint32_t oldSec;
void FM_Inc_Water(void){
	if (sysParams.vars.error.flags._5VPowerFail != true){
		sysParams.vars.flowImpulseCnt++;
		if (oldSec != LL_RTC_TIME_Get(RTC)){
			float tempVal = sysParams.vars.flowImpulseCnt/60.0;
			sysParams.vars.flowCnt = tempVal*0.0641;
			sysParams.consts.maxWaterUsage = MAX(sysParams.consts.maxWaterUsage,sysParams.vars.flowCnt);
		}
		oldSec = LL_RTC_TIME_Get(RTC);
	} else {
		sysParams.vars.flowCnt = 0;
	}
}

void FM_OVF_Interrupt(void){
	if (newPulse){
		FM_Inc_Water();
		newPulse = false;
	}
//	isOverFlow = true;
//	sysParams.vars.flowCnt = 0;
	
}

