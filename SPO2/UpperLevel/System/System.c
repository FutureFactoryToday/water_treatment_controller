/**
  ******************************************************************************
  * @file           : System.c
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
#include "System.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
sys_param_t sysParams;
uint32_t externalSignalCnt;
bool oldExternalSignal;
extern uint32_t resetCounter;
/* Private function prototypes -----------------------------------------------*/
static void Start_ADC();
static void Start_RTC();
static void Load_Flash_Param();
static void Start_Logic();
void Load_Default_Values(void);
/* Private user code ---------------------------------------------------------*/

void SYS_init(void){
	__enable_irq();
	sysParams.vars = (sys_var_t){0};
	Start_Logic();
	FP_Init();
	Start_ADC();
	initGUI();
	Load_Flash_Param();	
	#ifdef CLEAR_LOG
	FP_ClearLog();
	sysParams.consts.storedEntryNum = 0;
	sysParams.consts.storedDayValueNum = 0;
	sysParams.consts.storedWashNum = 0;
	#endif
	LOG_Init();
	PC_Init();
	PL_Init();
	FM_Init();
	RELAY_Init();
	Time_init();
	resetCounter = 0;
	FP_SaveParam();
	sysParams.vars.status.flags.DebugMode = 1;
	LL_SYSTICK_EnableIT();
}
void Start_ADC(){
	sysParams.vars.adc.adcCoef[Vbat] = 1/0.877;
	sysParams.vars.adc.adcCoef[_3V3] = 1/(10.0/(10.0+10.0));
	sysParams.vars.adc.adcCoef[_5V] = 1/(10.0/(10.0+10.0));
	sysParams.vars.adc.adcCoef[VrelDC] = 1/(10.0/(10.0+68.0));
	sysParams.vars.adc.adcCoef[Temp] = 1/1.0;
	sysParams.vars.adc.adcCoef[Vin] = 1/(10.0/(91.0+10.0));
	
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADCEx_Calibration_Start(&hadc3);
	
	HAL_ADC_Start_DMA(&hadc1,&sysParams.vars.adc.rawADC[Vbat],hadc1.Init.NbrOfConversion);
	HAL_ADC_Start_DMA(&hadc3,&sysParams.vars.adc.rawADC[Vin],hadc3.Init.NbrOfConversion);
	LL_DMA_DisableIT_HT(DMA2,LL_DMA_CHANNEL_5);
}
void Load_Flash_Param(){

	FP_GetParam();
	if (sysParams.vars.status.flags.StoredParamsLoaded == 1 /*&& resetCounter < RESET_COUNTER_LIM*/){
		sysParams.consts = fp->params.sysParConsts;
		sysParams.consts.planerConsts.currentStepNum = 0;
		
		uint8_t taskNum = 0;
		sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].step[taskNum++].poz = &sysParams.consts.pistonPositions.backwash;
		sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].step[taskNum++].poz = &sysParams.consts.pistonPositions.forwardWash;
		sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].step[taskNum].poz = NULL;
		
		
		
		//Softening
		taskNum = 0;
		sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum++].poz = &sysParams.consts.pistonPositions.backwash;
		sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum++].poz = &sysParams.consts.pistonPositions.saltering;
		sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum++].poz = &sysParams.consts.pistonPositions.forwardWash;
		sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum++].poz = &sysParams.consts.pistonPositions.filling;
		sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum].poz = NULL;
		
		} else {
		Load_Default_Values();
		FP_ClearLog();
		sysParams.consts.storedDayValueNum = 0;
		sysParams.consts.storedEntryNum = 0;
		sysParams.consts.storedWashNum = 0;
	}
}

void Load_Default_Values(void){
	sysParams.consts = (sys_const_t){0};
	
	sysParams.consts.adcLimit[Vbat] = 1.8;
	sysParams.consts.adcLimit[_3V3] = 2.0;
	sysParams.consts.adcLimit[_5V] = 4.0;
	sysParams.consts.adcLimit[VrelDC] = 22;
	sysParams.consts.adcLimit[Temp] = 100.0;
	sysParams.consts.adcLimit[Vin] = 13.0;
	
	sysParams.consts.adcLimitDelt[Vbat] = 1.1;
	sysParams.consts.adcLimitDelt[_3V3] = 1.1;
	sysParams.consts.adcLimitDelt[_5V] = 1.1;
	sysParams.consts.adcLimitDelt[VrelDC] = 1.1;
	sysParams.consts.adcLimitDelt[Temp] = 0.9;
	sysParams.consts.adcLimitDelt[Vin] = 1.1;
	
	sysParams.consts.maxMotorSpeedPercent = DEF_MAX_MOT_SPEED_PERCENT;
	sysParams.consts.minMotorSpeedPercent = DEF_MIN_MOT_SPEED_PERCENT;
	
	sysParams.consts.ServicePinCode = DEF_SERVICE_CODE;
	
	sysParams.consts.pistonPositions.rabPoz = DEF_WORK_POS; //–аб–еж
	sysParams.consts.pistonPositions.forwardWash = DEF_FORWARD_POS;
	sysParams.consts.pistonPositions.backwash = DEF_BACKWASH_POS; //обр пром
	sysParams.consts.pistonPositions.saltering = DEF_SALTERING_POS;
	sysParams.consts.pistonPositions.filling = DEF_FILLING_POS;
	
	sysParams.consts.pistonStallDelay = DEF_WAIT_STALL_TIME_MS;
	sysParams.consts.pistonSeekTime = DEF_SEEK_TIME_SECONDS;
	
	sysParams.consts.loadType = DEF_LOAD_TYPE;
	//Planner
	//Filtration
	sysParams.consts.planerConsts.currentTaskNum = REGENERATION_TASK_NUM;
	
	sysParams.consts.planerConsts.currentStepNum = 0;
	sysParams.consts.planerConsts.status = PL_NOT_SET;
	sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].startDateTime = 0;
	sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].remainingTime = getRTC() + DEF_TASK_RESTART_HOURS*60*60;
	sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].restartDateTime = DEF_TASK_RESTART_HOURS*60*60;// hours * 60 min * 60 sec
	uint8_t taskNum = 0;
	sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].step[taskNum].poz = &sysParams.consts.pistonPositions.backwash;
	sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 14*60;
	
	sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].step[taskNum].poz = &sysParams.consts.pistonPositions.forwardWash;
	sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 8*60;
	
	sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].step[taskNum].poz = NULL;
	sysParams.consts.planerConsts.planerTasks[REGENERATION_TASK_NUM].step[taskNum++].secPause = 0; 	
	
	
	//Softening
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].remainingTime = 0;
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].startDateTime = getRTC() + DEF_TASK_RESTART_HOURS*60*60;
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].restartDateTime = DEF_TASK_RESTART_HOURS*60*60;
	taskNum = 0;
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &sysParams.consts.pistonPositions.backwash;
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 8*60;
	
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &sysParams.consts.pistonPositions.saltering;
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 60*60;
	
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &sysParams.consts.pistonPositions.forwardWash;
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 6*60; 
	
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum].poz = &sysParams.consts.pistonPositions.filling;
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 1*SALT_COEF + 1; 
		
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum].poz = NULL;
	sysParams.consts.planerConsts.planerTasks[SOFTENING_TASK_NUM].step[taskNum++].secPause = 0; 	
	
	
	//copyTasksToFlash();
	
	sysParams.vars.planer.currentStep = sysParams.vars.planer.currentTask->step;
	sysParams.consts.planerConsts.status = PL_NOT_SET;
	sysParams.consts.planerConsts.preferedTimeForWash = (wtc_time_t)DEF_TASK_PREF_TIME_TO_START;
	sysParams.consts.planerConsts.monthBetweenService = DEF_TASK_MONTH_BETWEN_SERV;
	sysParams.consts.planerConsts.lastService = 0;
	sysParams.consts.planerConsts.startType = DEF_FILTER_START_COND;
	sysParams.consts.planerConsts.filtroCycle = DEF_FILTR_CYCLE;
	sysParams.consts.planerConsts.filtroReserve = DEF_FILTER_RESERVE;
	sysParams.consts.waterFromLastFilter = 0;
	
	sysParams.consts.loadType = DEF_LOAD_TYPE;
	sysParams.vars.planer.cycleCnt = 0;
	sysParams.consts.sysVersion = SYSTEM_PO_VERSION;
	sysParams.consts.waterQuantaty = 0;
	
	sysParams.consts.ExternalCommandType = EXTERNAL_START;
	
	sysParams.consts.dcRelay.workType = HALT;
	sysParams.consts.dcRelay.pozEnable = (relay_enable_t){0};
	sysParams.consts.acRelay.pozEnable = (relay_enable_t){0};
	
	sysParams.consts.impulseWeight = DEF_IMPULSE_WEIGHT;
	sysParams.consts.ServicePhoneNumber = DEF_PHONE_NUMBER;
}

void Start_Logic(){
	sysParams.vars.error.all = 0;
	sysParams.vars.status.all = 0;
	sysParams.vars.status.flags.WaterInLiters = 1;
	LL_TIM_ClearFlag_UPDATE(LOGIC_TIM);
	LL_TIM_EnableIT_UPDATE(LOGIC_TIM);
	LL_TIM_EnableCounter(LOGIC_TIM);
}

void SYS_Logic_IT(void){
	/*ADC count*/
	//#ifndef NO_FLOAT
	sysParams.vars.adc.floatParam[Temp] = ((V25 - sysParams.vars.adc.rawADC[Temp]*LSB)/AVG_SLOPE) + 25;
	sysParams.vars.adc.floatParam[Vbat] = sysParams.vars.adc.rawADC[Vbat]*LSB*sysParams.vars.adc.adcCoef[Vbat];
	sysParams.vars.adc.floatParam[_3V3] = sysParams.vars.adc.rawADC[_3V3]*LSB*sysParams.vars.adc.adcCoef[_3V3];
	sysParams.vars.adc.floatParam[_5V] = sysParams.vars.adc.rawADC[_5V]*LSB*sysParams.vars.adc.adcCoef[_5V];
	sysParams.vars.adc.floatParam[VrelDC] = sysParams.vars.adc.rawADC[VrelDC]*LSB*sysParams.vars.adc.adcCoef[VrelDC];
	sysParams.vars.adc.floatParam[Vin] = sysParams.vars.adc.rawADC[Vin]*LSB*sysParams.vars.adc.adcCoef[Vin];
	
	/*Errors*/		
	float limit = sysParams.consts.adcLimit[Temp];
	if (sysParams.vars.error.flags.TempFail == 1){
		limit *= sysParams.consts.adcLimit[Temp]*sysParams.consts.adcLimitDelt[Temp];
	}
	if(sysParams.vars.adc.floatParam[Temp] > sysParams.consts.adcLimit[Temp]){
		sysParams.vars.error.flags.TempFail = 1;
	} else {
		sysParams.vars.error.flags.TempFail = 0;
	}
	
	limit = sysParams.consts.adcLimit[Vbat];
	if (sysParams.vars.error.flags.BatteryFail == 1){
		limit *= sysParams.consts.adcLimit[Vbat]*sysParams.consts.adcLimitDelt[Vbat];
	}
	if(sysParams.vars.adc.floatParam[Vbat] < sysParams.consts.adcLimit[Vbat]){
		sysParams.vars.error.flags.BatteryFail = 1;
	} else {
		sysParams.vars.error.flags.BatteryFail = 0;
	}
	
	limit = sysParams.consts.adcLimit[_5V];
	if (sysParams.vars.error.flags._5VPowerFail == 1){
		limit *= sysParams.consts.adcLimit[_5V]*sysParams.consts.adcLimitDelt[_5V];
	}
	if(sysParams.vars.adc.floatParam[_5V] < sysParams.consts.adcLimit[_5V]){
		sysParams.vars.error.flags._5VPowerFail = 1;
	} else {
		sysParams.vars.error.flags._5VPowerFail = 0;
	}
	
	limit = sysParams.consts.adcLimit[VrelDC];
	if (sysParams.vars.error.flags.RelPowerFail == 1){
		limit *= sysParams.consts.adcLimit[VrelDC]*sysParams.consts.adcLimitDelt[VrelDC];
	}
	if(sysParams.vars.adc.floatParam[VrelDC] < sysParams.consts.adcLimit[VrelDC]){
		sysParams.vars.error.flags.RelPowerFail = 1;
	} else {
		sysParams.vars.error.flags.RelPowerFail = 0;
	}
	
	limit = sysParams.consts.adcLimit[Vin];
	if (sysParams.vars.error.flags.mainPowerFail == 1){
		limit *= sysParams.consts.adcLimit[Vin]*sysParams.consts.adcLimitDelt[Vin];
	}
	if(sysParams.vars.adc.floatParam[Vin] < sysParams.consts.adcLimit[Vin]){
		sysParams.vars.error.flags.mainPowerFail = 1;
	} else {
		sysParams.vars.error.flags.mainPowerFail = 0;
	}
	
	
	
	/*Status*/
	//ExCom On?
	if (sysParams.vars.error.flags._5VPowerFail == false){
		bool externalSignal = !LL_GPIO_IsInputPinSet(DP_SWITCH_GPIO_Port, DP_SWITCH_Pin);
		
		//On->On
		if (oldExternalSignal == externalSignal){
			if (externalSignalCnt == 0){
				sysParams.vars.status.flags.ExternalCommandOn = externalSignal;
			} else {
				externalSignalCnt--;
			}
			//Off->On
		} else {
			if (sysParams.consts.ExternalCommandType == EXTERNAL_START){
				externalSignalCnt = DEF_EXTERNAL_COM_EX_START_DELAY;
			} else {
				externalSignalCnt = DEF_EXTERNAL_COM_ENABLE_WASH_DELAY;
			}
		}
		oldExternalSignal = externalSignal;
	}
	//Output DC
	RELAY_DC_CYCLE();
	//Putput AC
	RELAY_AC_CYCLE();
	
	
	sysParams.vars.status.flags.RelACOn = !LL_GPIO_IsInputPinSet(REL_AC_FB_GPIO_Port,REL_AC_FB_Pin);
	sysParams.vars.status.flags.RelDCOn = !LL_GPIO_IsInputPinSet(REL_DC_FB_GPIO_Port,REL_DC_FB_Pin);
	
	if (sysParams.vars.status.flags.RelACOn == LL_GPIO_IsOutputPinSet(REL_AC_ON_GPIO_Port,REL_AC_ON_Pin)){
		sysParams.vars.error.flags.RelayACFail = 0;
	} else {
		sysParams.vars.error.flags.RelayACFail = 1;
	}
	
	if (sysParams.vars.status.flags.RelDCOn == LL_GPIO_IsOutputPinSet(REL_DC_ON_GPIO_Port,REL_DC_ON_Pin)){
		sysParams.vars.error.flags.RelayDCFail = 0;
	} else {
		sysParams.vars.error.flags.RelayDCFail = 1;
	}
	
	time_t now = LL_RTC_TIME_Get(RTC);
	if (sysParams.consts.planerConsts.monthBetweenService > 0){
		if (now > sysParams.consts.planerConsts.lastService + sysParams.consts.planerConsts.monthBetweenService*30*24*60*60){
			sysParams.vars.status.flags.NeedService = 1;
		}
	}
	//#endif
}