#ifndef __uC_Settings__
#define __uC_Settings__

/*Includes*/
#include "main.h"
/*Pinout*/
#define Vbat_ADC_Pin LL_GPIO_PIN_0
#define Vbat_ADC_GPIO_Port GPIOC
#define V3v3_ADC_Pin LL_GPIO_PIN_1
#define V3v3_ADC_GPIO_Port GPIOC
#define Vpwr_ADC_Pin LL_GPIO_PIN_2
#define Vpwr_ADC_GPIO_Port GPIOC
#define V5v_ADC_Pin LL_GPIO_PIN_3
#define V5v_ADC_GPIO_Port GPIOC
#define TFT_RES_Pin LL_GPIO_PIN_0
#define TFT_RES_GPIO_Port GPIOA
#define TFT_CS_Pin LL_GPIO_PIN_1
#define TFT_CS_GPIO_Port GPIOA
#define SELF_RES_Pin LL_GPIO_PIN_2
#define SELF_RES_GPIO_Port GPIOA
#define SD_CS_Pin LL_GPIO_PIN_3
#define SD_CS_GPIO_Port GPIOA
#define TOUCH_RES_Pin LL_GPIO_PIN_4
#define TOUCH_RES_GPIO_Port GPIOA
#define DRV_1_FB_Pin LL_GPIO_PIN_5
#define DRV_1_FB_GPIO_Port GPIOA
#define TOUCH_IRQ_Pin LL_GPIO_PIN_6
#define TOUCH_IRQ_GPIO_Port GPIOA
#define DRV_2_FB_Pin LL_GPIO_PIN_7
#define DRV_2_FB_GPIO_Port GPIOA
#define TFT_DATA_COM_Pin LL_GPIO_PIN_4
#define TFT_DATA_COM_GPIO_Port GPIOC
#define Vrel_ADC_Pin LL_GPIO_PIN_5
#define Vrel_ADC_GPIO_Port GPIOC
#define DRV_IN2_Pin LL_GPIO_PIN_0
#define DRV_IN2_GPIO_Port GPIOB
#define DRV_IN1_Pin LL_GPIO_PIN_1
#define DRV_IN1_GPIO_Port GPIOB
#define DP_SWITCH_Pin LL_GPIO_PIN_2
#define DP_SWITCH_GPIO_Port GPIOB
#define TOUCH_SCL_Pin LL_GPIO_PIN_10
#define TOUCH_SCL_GPIO_Port GPIOB
#define TOUCH_SDA_Pin LL_GPIO_PIN_11
#define TOUCH_SDA_GPIO_Port GPIOB
#define TFT_SCK_Pin LL_GPIO_PIN_13
#define TFT_SCK_GPIO_Port GPIOB
#define TFT_MISO_Pin LL_GPIO_PIN_14
#define TFT_MISO_GPIO_Port GPIOB
#define TFT_MOSI_Pin LL_GPIO_PIN_15
#define TFT_MOSI_GPIO_Port GPIOB
#define TFT_BL_Pin LL_GPIO_PIN_6
#define TFT_BL_GPIO_Port GPIOC
#define REL_DC_FB_Pin LL_GPIO_PIN_7
#define REL_DC_FB_GPIO_Port GPIOC
#define REL_AC_FB_Pin LL_GPIO_PIN_8
#define REL_AC_FB_GPIO_Port GPIOC
#define REL_DC_ON_Pin LL_GPIO_PIN_9
#define REL_DC_ON_GPIO_Port GPIOC
#define REL_AC_ON_Pin LL_GPIO_PIN_8
#define REL_AC_ON_GPIO_Port GPIOA
#define OPTIC_IRQ_Pin LL_GPIO_PIN_11
#define OPTIC_IRQ_GPIO_Port GPIOA
#define ILED_Pin LL_GPIO_PIN_12
#define ILED_GPIO_Port GPIOA
#define METER_IRQ_Pin LL_GPIO_PIN_15
#define METER_IRQ_GPIO_Port GPIOA
#define FRAM_HOLD_Pin LL_GPIO_PIN_10
#define FRAM_HOLD_GPIO_Port GPIOC
#define MEM_CS_Pin LL_GPIO_PIN_11
#define MEM_CS_GPIO_Port GPIOC
#define MEM_RES_Pin LL_GPIO_PIN_12
#define MEM_RES_GPIO_Port GPIOC
#define MEM_SCK_Pin LL_GPIO_PIN_3
#define MEM_SCK_GPIO_Port GPIOB
#define MEM_MISO_Pin LL_GPIO_PIN_4
#define MEM_MISO_GPIO_Port GPIOB
#define MEM_MOSI_Pin LL_GPIO_PIN_5
#define MEM_MOSI_GPIO_Port GPIOB
#define MEM_WP_Pin LL_GPIO_PIN_6
#define MEM_WP_GPIO_Port GPIOB
#define FRAM_CS_Pin LL_GPIO_PIN_7
#define FRAM_CS_GPIO_Port GPIOB
#define BOOT_Pin LL_GPIO_PIN_8
#define BOOT_GPIO_Port GPIOB
#define FRAM_FP_Pin LL_GPIO_PIN_9
#define FRAM_FP_GPIO_Port GPIOB

/*Periph Usage*/
	/*ADC*/
//#define 

	/*TIM*/
#define MOT_TIM &htim3
#define PISTON_CONTROL_TIM &htim11
#define OPTIC_DELAY_TIM &htim13
#define BL_TIM &htim8
#define DELAY_TIM &htim14

	/*SPI*/
	
	/*I2C*/
	
	/*UART*/
//#define 
#endif //__uC_Settings__