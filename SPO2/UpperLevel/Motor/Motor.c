/**
  ******************************************************************************
  * @file           : MOTOR.c
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
#include "Motor.h"
#include "System/System.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#if FORWARD_CHANNEL == REVERSE_CHANNEL
#error "Check motor channel settings!"
#endif

#if FORWARD_CHANNEL == LL_TIM_CHANNEL_CH3 //BIN1
#define setForwardSpeed(sp)        LL_TIM_OC_SetCompareCH3(sysParams.vars.pistonParams.mot.tim, sp)
#define setReverseSpeed(sp)        LL_TIM_OC_SetCompareCH4(sysParams.vars.pistonParams.mot.tim, sp);
#else
#define setForwardSpeed(sp)        LL_TIM_OC_SetCompareCH4(mot.tim, sp)
#define setReverseSpeed(sp)        LL_TIM_OC_SetCompareCH3(mot.tim, sp);
#endif
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void MOT_Forward(void);

void MOT_Brake(void);

void MOT_Coast(void);

void MOT_Reverse(void);

void initTim(void);

void setDrvMode(mot_control_type_t type);

void initMotGPIO(void);

/* Private user code ---------------------------------------------------------*/
void MOT_Forward(void) {
    if (sysParams.vars.pistonParams.mot.control.TYPE == SIMPLE) {
        LL_GPIO_SetOutputPin(DRV_IN2_GPIO_Port, DRV_IN2_Pin);
        LL_GPIO_ResetOutputPin(DRV_IN1_GPIO_Port, DRV_IN1_Pin);
    } else {
        setReverseSpeed(sysParams.vars.pistonParams.mot.settings.max + 1);
        setForwardSpeed(sysParams.vars.pistonParams.mot.settings.max - sysParams.vars.pistonParams.mot.settings.pwm);
    }

}

void MOT_Brake(void) {
    if (sysParams.vars.pistonParams.mot.control.TYPE == SIMPLE) {
        LL_GPIO_ResetOutputPin(DRV_IN2_GPIO_Port, DRV_IN2_Pin);
    } else {
        setForwardSpeed(sysParams.vars.pistonParams.mot.settings.max + 1);
        setReverseSpeed(sysParams.vars.pistonParams.mot.settings.max + 1);
    }
}

void MOT_Coast(void) {
    if (sysParams.vars.pistonParams.mot.control.TYPE == SIMPLE) {
        return;
    } else {
        setForwardSpeed(0);
        setReverseSpeed(0);
    }
}

void MOT_Reverse(void) {
    if (sysParams.vars.pistonParams.mot.control.TYPE == SIMPLE) {
        LL_GPIO_SetOutputPin(DRV_IN2_GPIO_Port, DRV_IN2_Pin);
        LL_GPIO_SetOutputPin(DRV_IN1_GPIO_Port, DRV_IN1_Pin);
    } else {
        setReverseSpeed(sysParams.vars.pistonParams.mot.settings.max - sysParams.vars.pistonParams.mot.settings.pwm);
        setForwardSpeed(sysParams.vars.pistonParams.mot.settings.max + 1);
    }
}

void MOT_Start(void) {
   if (sysParams.vars.error.flags.mainPowerFail != 1 ||
				sysParams.vars.error.flags.MotorFail != 1) {
        if (sysParams.vars.pistonParams.mot.control.DIR == 0) {
            MOT_Forward();
        } else {
            MOT_Reverse();
        }
        sysParams.vars.pistonParams.mot.control.START = 1;
    }
}

void MOT_Stop(void) {
    if (sysParams.vars.pistonParams.mot.control.START == 1) {
        MOT_Brake();
        sysParams.vars.pistonParams.mot.control.START = 0;
    }
}

void MOT_SetDir(uint8_t dir) {
	if (dir == sysParams.vars.pistonParams.mot.control.DIR){
		return;
	}
	else {
		sysParams.vars.pistonParams.mot.control.DIR = dir;
	}
    
    if (sysParams.vars.pistonParams.mot.control.START == 1) {
        MOT_Stop();
        MOT_Start();
    }
}

void MOT_Init(mot_control_type_t type, TIM_TypeDef *TIM) {
    sysParams.vars.pistonParams.mot.control.DIR = 0;
    sysParams.vars.pistonParams.mot.control.START = 0;
    sysParams.vars.pistonParams.mot.control.TYPE = type;
    sysParams.vars.pistonParams.mot.tim = TIM;
    if (type == PWM) {
        initTim();
    }
    initMotGPIO();

    MOT_SetSpeed(MAX_SPEED);
    sysParams.vars.pistonParams.mot.control.INITED = 1;
    setDrvMode(type);
    LL_TIM_CC_EnableChannel(sysParams.vars.pistonParams.mot.tim, FORWARD_CHANNEL);
    LL_TIM_CC_EnableChannel(sysParams.vars.pistonParams.mot.tim, REVERSE_CHANNEL);
    LL_TIM_EnableAllOutputs(sysParams.vars.pistonParams.mot.tim);
    LL_TIM_EnableCounter(sysParams.vars.pistonParams.mot.tim);
}


void setDrvMode(mot_control_type_t type) {
    if (type == SIMPLE) {
//        LL_GPIO_SetOutputPin(DRV_MODE_GPIO_Port, DRV_MODE_Pin);
    } else {
//        LL_GPIO_ResetOutputPin(DRV_MODE_GPIO_Port, DRV_MODE_Pin);
    }
}

void MOT_SetSpeed(uint8_t speed) {
    if (speed > MAX_SPEED) {
        speed = MAX_SPEED;
    }
		if (speed < MIN_SPEED){
			speed = MIN_SPEED;
		}
    sysParams.vars.pistonParams.mot.speed = speed;
    if (sysParams.vars.pistonParams.mot.control.TYPE == PWM) {
        uint32_t temp;
        temp = sysParams.vars.pistonParams.mot.settings.max / MAX_SPEED;
        temp = temp * speed;
        sysParams.vars.pistonParams.mot.settings.pwm = temp;
    }
		if (sysParams.vars.pistonParams.mot.control.START == 1){
			MOT_Start();
		}
}

void initMotGPIO(void) {
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

//    GPIO_InitStruct.Pin = DRV_MODE_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//    LL_GPIO_Init(DRV_MODE_GPIO_Port, &GPIO_InitStruct);

    if (sysParams.vars.pistonParams.mot.control.TYPE == SIMPLE) {
        GPIO_InitStruct.Pin = DRV_IN1_Pin | DRV_IN2_Pin;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        LL_GPIO_Init(DRV_IN1_GPIO_Port, &GPIO_InitStruct);
        LL_GPIO_ResetOutputPin(DRV_IN2_GPIO_Port, DRV_IN2_Pin);
        LL_GPIO_SetOutputPin(DRV_IN1_GPIO_Port, DRV_IN1_Pin);
//        LL_GPIO_SetOutputPin(DRV_MODE_GPIO_Port, DRV_MODE_Pin);
    } else {
        GPIO_InitStruct.Pin = DRV_IN1_Pin | DRV_IN2_Pin;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        LL_GPIO_Init(DRV_IN1_GPIO_Port, &GPIO_InitStruct);
//        LL_GPIO_ResetOutputPin(DRV_MODE_GPIO_Port, DRV_MODE_Pin);
    }
}

void initTim(void) {
    uint32_t temp = 0;
    sysParams.vars.pistonParams.mot.settings.presc = 0;

    sysParams.vars.pistonParams.mot.settings.timFreq = SystemCoreClock;

    sysParams.vars.pistonParams.mot.settings.freq = MOT_PWM_FREQ;

    sysParams.vars.pistonParams.mot.settings.min = 0;

    temp = sysParams.vars.pistonParams.mot.settings.timFreq / sysParams.vars.pistonParams.mot.settings.freq;

    sysParams.vars.pistonParams.mot.settings.max = temp - 1;

    LL_TIM_InitTypeDef timSet;
    LL_TIM_OC_InitTypeDef pwmSet;

    LL_TIM_StructInit(&timSet);
    LL_TIM_OC_StructInit(&pwmSet);

    timSet.Prescaler = sysParams.vars.pistonParams.mot.settings.presc;
    timSet.CounterMode = LL_TIM_COUNTERMODE_UP;
    timSet.Autoreload = sysParams.vars.pistonParams.mot.settings.max;
    timSet.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    timSet.RepetitionCounter = 0;

    pwmSet.OCMode = LL_TIM_OCMODE_PWM1;
    pwmSet.OCState = LL_TIM_OCSTATE_ENABLE;
    pwmSet.CompareValue = sysParams.vars.pistonParams.mot.settings.max + 1;
    pwmSet.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    pwmSet.OCIdleState = LL_TIM_OCIDLESTATE_HIGH;

    LL_TIM_Init(sysParams.vars.pistonParams.mot.tim, &timSet);

    LL_TIM_OC_Init(sysParams.vars.pistonParams.mot.tim, FORWARD_CHANNEL, &pwmSet);
    LL_TIM_OC_Init(sysParams.vars.pistonParams.mot.tim, REVERSE_CHANNEL, &pwmSet);


    LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_TIM_DisableARRPreload(sysParams.vars.pistonParams.mot.tim);

    LL_TIM_SetClockSource(sysParams.vars.pistonParams.mot.tim, LL_TIM_CLOCKSOURCE_INTERNAL);

    LL_TIM_OC_DisableFast(sysParams.vars.pistonParams.mot.tim, FORWARD_CHANNEL);
    LL_TIM_OC_DisableFast(sysParams.vars.pistonParams.mot.tim, REVERSE_CHANNEL);

    LL_TIM_SetTriggerOutput(sysParams.vars.pistonParams.mot.tim, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(sysParams.vars.pistonParams.mot.tim);

    TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_DISABLE;
    TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_DISABLE;
    TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
    TIM_BDTRInitStruct.DeadTime = 0;
    TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
    TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_DISABLE;
    LL_TIM_BDTR_Init(sysParams.vars.pistonParams.mot.tim, &TIM_BDTRInitStruct);

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
}
void MOT_ChangeDir(){

	MOT_SetDir(!sysParams.vars.pistonParams.mot.control.DIR);
}
mot_control_t MOT_GetControl(void) {
    return sysParams.vars.pistonParams.mot.control;
}

void MOT_TEST(void) {
    MOT_Brake();
    LL_mDelay(100);
    MOT_Forward();
    LL_mDelay(5000);
    MOT_Reverse();
    LL_mDelay(5000);
    MOT_Brake();
}