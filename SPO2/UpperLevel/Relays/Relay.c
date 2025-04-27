/*Includes*/
#include "main.h"

/*Macro and defines*/
#define CYCLE_HZ 100
#define TARGET_HZ 10
#define PULSE_DURATION_SECONDS 60
/*Global parameters*/

/*Local prototypes*/
static uint32_t oldWaterDC, oldWaterAC;
static planer_status_t oldStatus;
static uint32_t waterStartTime;
uint32_t oldPoz;
bool pulse ;
/*Code*/
void DC_RELAY_Init(void){
	LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
	oldWaterDC = (uint32_t)sysParams.consts.waterQuantaty;
	pulse = false;
	oldStatus =	sysParams.consts.planerConsts.status;
	oldPoz = sysParams.vars.pistonParams.curPoz;
}

void AC_RELAY_Init(void){
	LL_GPIO_ResetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
}
void RELAY_DC_ChangeType(dc_relay_work_t type){
	DC_RELAY_Init();
	sysParams.consts.dcRelay.workType = type;
}
void RELAY_DC_CYCLE(void){
	switch(sysParams.consts.dcRelay.workType){
		case (MANUAL_ON):{
			//LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
			break;
		}
		case (HALT):{
			LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
			break;
		}
		case (WASH):{
			if (sysParams.consts.planerConsts.status == PL_WORKING){
				bool dcOn = false;
				dcOn |= (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.rabPoz && 
					sysParams.consts.dcRelay.pozEnable.rabPoz == 1);
				
				dcOn |= (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.forwardWash && 
					sysParams.consts.dcRelay.pozEnable.forwardWash == 1);
				dcOn |= (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.backwash && 
					sysParams.consts.dcRelay.pozEnable.backwash == 1);
				dcOn |= (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.saltering && 
					sysParams.consts.dcRelay.pozEnable.saltering == 1);
				dcOn |= (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.filling && 
					sysParams.consts.dcRelay.pozEnable.filling == 1);
				
				if (dcOn){
					LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
				} else {
					LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
				}
			} else {
					LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
				}
			

			break;
		}
	
		case (PULSE):{
				if (sysParams.consts.planerConsts.status != PL_WORKING){
					if (LL_GPIO_IsOutputPinSet(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin)){
						if (sysParams.vars.dcRelayCnt){
							sysParams.vars.dcRelayCnt--;
						} else {
							LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
							return;
						}
					}
					
					if (sysParams.consts.waterQuantaty - oldWaterDC > sysParams.consts.impulseWeight){
						LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
						sysParams.vars.dcRelayCnt = CYCLE_HZ/TARGET_HZ;
						oldWaterDC = sysParams.consts.waterQuantaty;
					} 
				} else {
					LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
				}
				break;
		}
		case (NEIGHBOR):{
			//Conditions
			if (sysParams.consts.planerConsts.currentTaskNum == SOFTENING_TASK_NUM){
				if (sysParams.vars.pistonParams.destComplete == true && sysParams.vars.pistonParams.curPoz == sysParams.consts.pistonPositions.filling){
					if (oldPoz != sysParams.consts.pistonPositions.filling){
						pulse = true;
					} 
				} //else {
					//pulse = false;
				//}
				oldPoz = sysParams.vars.pistonParams.curPoz;
			} else {
				if (sysParams.consts.planerConsts.status != PL_WORKING){
					if (oldStatus == PL_WORKING){
						pulse = true;
					}
				} //else {
//					pulse = false;
//				}
				
			}
			
			//Pulse formation
			if (pulse && !LL_GPIO_IsOutputPinSet(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin)){
				sysParams.vars.dcRelayCnt =  CYCLE_HZ*PULSE_DURATION_SECONDS;
				LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
			} else {
				if (sysParams.vars.dcRelayCnt){
					sysParams.vars.dcRelayCnt--;
				} else {
					pulse = false;
					LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
				}
			}
			break;
		}
		default: break;
	}
	oldStatus = sysParams.consts.planerConsts.status;
}
void RELAY_AC_CYCLE(void){

	switch(sysParams.consts.acRelay.workType){
		case (MANUAL_ON_AC):{
			//LL_GPIO_SetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
			break;
		}
		case (COMPRESSOR_AC):{
			float speed = FM_getFlowSpeed()*60;
			if (speed > 0){
				if (waterStartTime == 0){
					waterStartTime = sysParams.vars.rtcTime;
				} else {
					if (sysParams.vars.rtcTime - waterStartTime > DELAY_FOR_COMPRESSOR_START){
						LL_GPIO_SetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
					}
				}
			} else {
				waterStartTime = 0;
				LL_GPIO_ResetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
			}
			break;
		}
		case (WASH_AC):{
			if (sysParams.consts.planerConsts.status == PL_WORKING){
				bool acOn = false;
				acOn |= (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.rabPoz && 
					sysParams.consts.acRelay.pozEnable.rabPoz == 1);
				
				acOn |= (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.forwardWash && 
					sysParams.consts.acRelay.pozEnable.forwardWash == 1);
				acOn |= (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.backwash && 
					sysParams.consts.acRelay.pozEnable.backwash == 1);
				acOn |= (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.saltering && 
					sysParams.consts.acRelay.pozEnable.saltering == 1);
				acOn |= (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.filling && 
					sysParams.consts.acRelay.pozEnable.filling == 1);
				
				if (acOn){
					LL_GPIO_SetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
				} else {
					LL_GPIO_ResetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
				}
			} else {
				LL_GPIO_ResetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
			}				
			break;
		}
		default:{
			
		}
	}
}