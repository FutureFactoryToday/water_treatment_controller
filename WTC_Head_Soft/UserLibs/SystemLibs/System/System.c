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
#define DEF_SERVICE_CODE 1234
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
sys_param_t sysParams;
/* Private function prototypes -----------------------------------------------*/
static void Start_ADC();
static void Start_RTC();
static void Load_Flash_Param();
static void Start_Logic();
/* Private user code ---------------------------------------------------------*/
void System_init(void){
	Start_ADC();
	Start_RTC();
	Load_Flash_Param();
	Start_Logic();
//	if (fp->isLoaded != 1){
//		sysParam.lang = DEF_SYST_CONFIG_LANG;
//		sysParam.SERVICE_CODE = DEF_SERVICE_CODE;
//		fp->needToSave = true;
//		fp->params.sysPar = sysParam;
//	} else {
//		sysParam = fp->params.sysPar;
//	}
//	sysParam.WORK_STATUS = WAIT;
}

void Start_ADC(){
	sysParams.vars.adc.adcCoef[Vbat] = 1/1.0;
	sysParams.vars.adc.adcCoef[_3V3] = 1/(10.0/(10.0+10.0));
	sysParams.vars.adc.adcCoef[_5V] = 1/(10.0/(10.0+10.0));
	sysParams.vars.adc.adcCoef[VrelDC] = 1/(10.0/(10.0+68.0));
	sysParams.vars.adc.adcCoef[Temp] = 1/1.0;
	sysParams.vars.adc.adcCoef[Vin] = 1/(10.0/(91.0+10.0));
	
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADCEx_Calibration_Start(&hadc3);
	
	HAL_ADC_Start_DMA(&hadc1,&sysParams.vars.adc.rawADC[Vbat],hadc1.Init.NbrOfConversion);
	HAL_ADC_Start_DMA(&hadc3,&sysParams.vars.adc.rawADC[Vin],hadc3.Init.NbrOfConversion);
}
void Start_RTC(){
	//Time_init();
}
void Load_Flash_Param(){
	
}
void Start_Logic(){
	sysParams.vars.error.all = 0;
	sysParams.vars.status.all = 0;
	HAL_TIM_Base_Start_IT(LOGIC_TIM);
}

void SYS_Logic_IT(void){
	/*Errors*/
	
	/*Status*/
	
	/*ADC count*/
	#ifndef NO_FLOAT
	sysParams.vars.adc.floatParam[Temp] = ((V25 - sysParams.vars.adc.rawADC[Temp]*LSB)/AVG_SLOPE) + 25;
	sysParams.vars.adc.floatParam[Vbat] = sysParams.vars.adc.rawADC[Vbat]*LSB/sysParams.vars.adc.adcCoef[Vbat];
	sysParams.vars.adc.floatParam[_3V3] = sysParams.vars.adc.rawADC[_3V3]*LSB/sysParams.vars.adc.adcCoef[_3V3];
	sysParams.vars.adc.floatParam[_5V] = sysParams.vars.adc.rawADC[_5V]*LSB/sysParams.vars.adc.adcCoef[_5V];
	sysParams.vars.adc.floatParam[VrelDC] = sysParams.vars.adc.rawADC[VrelDC]*LSB/sysParams.vars.adc.adcCoef[VrelDC];
	sysParams.vars.adc.floatParam[Vin] = sysParams.vars.adc.rawADC[Vin]*LSB/sysParams.vars.adc.adcCoef[Vin];
	#endif
}
