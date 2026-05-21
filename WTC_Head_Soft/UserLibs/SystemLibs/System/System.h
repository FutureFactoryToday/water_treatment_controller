/**
  ******************************************************************************
  * @file    System.h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/*Includes */
#include "main.h"

#include "uC_Settings.h"
#include "System_Settings.h"

#include "adc.h"
#include "crc.h"
#include "dma.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "FlashParams\FlashParam.h"
#include "Time/Time.h"
#include "PistonControl/PistonControl.h"
#include "Planner/Planner.h"
#include "Logic/WTC_Logic.h"

/*Public defines */
#define MANUAL_CONTROL 0
#define AUTO_CONTROL 1


/*Public typedef*/
typedef enum {
	Vbat = 0,
	_3V3,
	_5V,
	VrelDC,
	Temp,
	Vin,
} adc_volts_poz_num_t;

typedef struct{
	unsigned mainPowerFail:1;
	unsigned BatteryFail:1;
	unsigned _5VPowerFail:1;
	unsigned RelPowerFail:1;
	unsigned TempFail:1;
	unsigned PistonStallFail:1;
	unsigned RelayDCFail:1;
	unsigned RelayACFail:1;
	unsigned TFTFail:1;
	unsigned TouchFail:1;
	unsigned FRAMFail:1;
	unsigned RAMFail:1;
	unsigned Drive1Fail:1;
	unsigned Drive2Fail:1;
} sys_error_flag_bits_t;

typedef union{
	sys_error_flag_bits_t flags;
	uint32_t all;
} sys_error_flags_t;


typedef struct{
	unsigned RelDCOn:1;
	unsigned RelACOn:1;
	unsigned MotorOn:1;
	unsigned FlashParamLoaded:1;
	unsigned NewDataToStore:1;
	unsigned NewLogEntry:1;
	unsigned CurrentPistonPosition:3;
	unsigned ManualControl:1;
	unsigned PCConnected:1;
	unsigned FRAMInited:1;
	unsigned EEPROMInited:1;
} sys_status_flag_bits_t;

typedef union{
	sys_status_flag_bits_t flags;
	uint32_t all;
} sys_status_flags_t;

typedef struct{
	uint32_t ServicePinCode;
	uint32_t maxMotorSpeedPercent;
	piston_poz_t pistonPositions;
	uint32_t pistonStallDelay;
	
} sys_const_t;

typedef struct {
	uint16_t rawADC[Vin+1];
	float adcCoef[Vin+1];
	float floatParam[Vin+1];
}adc_params;

typedef struct{
	sys_status_flags_t status;
	sys_error_flags_t error;
	adc_params adc;
	wtc_time_t sysTime;
	pc_params_t pistonParams;
} sys_var_t;

typedef struct{
	sys_var_t vars;
	sys_const_t consts;
} sys_param_t;

extern sys_param_t sysParams;
/*Global params*/

/*Prototypes */
void SYS_init(void);
void SYS_Logic_IT(void);

#endif /* __SYSTEM_H__ */

