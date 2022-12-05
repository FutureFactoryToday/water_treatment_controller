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
uint32_t flowPeriod;
bool isOverFlow;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
//Flow period (time of one rotation)
uint32_t FM_getFlowPeriod(void){
	return  flowPeriod;
}
//Flow freq (int)
uint32_t FM_getFlowHzInt(void){
	return (uint32_t)1000/flowPeriod;
}
//Flow freq (float)
float FM_getFlowHzFloat(void){
	return 1000.0/flowPeriod;
}
//Flow speed scaled by coef
float FM_getFlowSpeedKoef(float coef){
	return (float)flowPeriod*coef;
}

void FM_Init(void){
	LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
	LL_TIM_InitTypeDef TIM_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(FLOW_TIM_CLK);

  /* TIM7 interrupt Init */
  NVIC_SetPriority(FLOW_TIM_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),14, 0));
  NVIC_EnableIRQ(FLOW_TIM_IRQ);
	
	GPIO_InitStruct.Pin = METER_INP_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTC, LL_GPIO_AF_EXTI_LINE10);
	
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_10;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
  LL_EXTI_Init(&EXTI_InitStruct);
	
	//„астота счета 1ћ√ц
	TIM_InitStruct.Prescaler = 18000;
  
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = UINT16_MAX;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV4;
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
		flowPeriod = LL_TIM_GetCounter(FLOW_TIM);
	}
	LL_TIM_SetCounter(FLOW_TIM,0);
}
void FM_OVF_Interrupt(void){
	isOverFlow = true;
	flowPeriod = 0;
}

