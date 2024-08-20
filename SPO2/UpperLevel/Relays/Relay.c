/*Includes*/
#include "main.h"

/*Macro and defines*/
#define CYCLE_HZ 100
#define TARGET_HZ 10
#define PULSE_DURATION_SECONDS 60
/*Global parameters*/

/*Local prototypes*/
static uint32_t oldWater;
static planer_status_t oldStatus;
uint32_t oldPoz;
bool pulse ;
/*Code*/
void RELAY_Init(void){
	LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
	oldWater = (uint32_t)sysParams.consts.waterQuantaty;
	pulse = false;
	oldStatus =	sysParams.consts.planerConsts.status;
	oldPoz = sysParams.vars.pistonParams.curPoz;
}
void RELAY_DC_ChangeType(dc_relay_work_t type){
	RELAY_Init();
	sysParams.consts.dcRelay.workType = type;
}
void RELAY_DC_CYCLE(void){
	switch(sysParams.consts.dcRelay.workType){
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
			
//				if (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.rabPoz && 
//					sysParams.consts.dcRelay.pozEnable.rabPoz == 1){
//						LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
//						return;
//					} else {
//						LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
//					}
//				if (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.forwardWash && 
//					sysParams.consts.dcRelay.pozEnable.forwardWash == 1){
//						LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
//						return;
//					} else {
//						LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
//					}
//				if (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.backwash && 
//					sysParams.consts.dcRelay.pozEnable.backwash == 1){
//						LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
//						return;
//					} else {
//						LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
//					}
//				if (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.saltering && 
//					sysParams.consts.dcRelay.pozEnable.saltering == 1){
//						LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
//						return;
//					} else {
//						LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
//					}
//				if (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.filling && 
//					sysParams.consts.dcRelay.pozEnable.filling == 1){
//						LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
//						return;
//					} else {
//						LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
//					}
//				}
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
					
					if (sysParams.consts.waterQuantaty - oldWater > sysParams.consts.impulseWeight){
						LL_GPIO_SetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
						sysParams.vars.dcRelayCnt = CYCLE_HZ/TARGET_HZ;
						oldWater = sysParams.consts.waterQuantaty;
					} 
				} else {
					LL_GPIO_ResetOutputPin(REL_DC_ON_GPIO_Port, REL_DC_ON_Pin);
				}
				break;
		}
		case (NEIGHBOR):{
			//Conditions
			if (sysParams.consts.planerConsts.currentTaskNum == SOFTENING_TASK_NUM){
				if (sysParams.vars.pistonParams.curPoz == sysParams.consts.pistonPositions.filling){
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
//		if (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.rabPoz && 
//			sysParams.consts.acRelay.pozEnable.rabPoz == 1){
//				LL_GPIO_SetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
//				return;
//			} else {
//				LL_GPIO_ResetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
//			}
//		if (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.forwardWash && 
//			sysParams.consts.acRelay.pozEnable.forwardWash == 1){
//				LL_GPIO_SetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
//				return;
//			} else {
//				LL_GPIO_ResetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
//			}
//		if (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.backwash && 
//			sysParams.consts.acRelay.pozEnable.backwash == 1){
//				LL_GPIO_SetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
//				return;
//			} else {
//				LL_GPIO_ResetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
//			}
//		if (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.saltering && 
//			sysParams.consts.acRelay.pozEnable.saltering == 1){
//				LL_GPIO_SetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
//				return;
//			} else {
//				LL_GPIO_ResetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
//			}
//		if (*sysParams.vars.planer.currentStep->poz == sysParams.consts.pistonPositions.filling && 
//			sysParams.consts.acRelay.pozEnable.filling == 1){
//				LL_GPIO_SetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
//				return;
//			} else {
//				LL_GPIO_ResetOutputPin(REL_AC_ON_GPIO_Port, REL_AC_ON_Pin);
//			}
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
			}
}