/**
  ******************************************************************************
  * @file           : Util.c
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
uint8_t numBuf[11] = {0};
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
uint16_t POWC (uint8_t a, uint8_t b){
	while(b !=0){a = a*a; b--;}
	return a;
}

uint8_t intToChar(uint8_t num){
	assert_param(num< 10);
	uint32_t modNum = num;
	if (num == 0){
		return 48;
	} else {
		return 48 + num;
	}
}

uint8_t* intToStr (uint32_t num){
	for(int i = 0; i <sizeof(numBuf); i++){
		numBuf[i] = 0;
	}
	uint32_t modNum = num;
	uint8_t ch = 0;
	uint32_t mod = 1000000000;
	if (num == 0){
		numBuf[0] = 48;
		return numBuf;
	}
	uint8_t i = 0;
	while(modNum < mod){
		mod /= 10;
	}
	if (mod == 0) {
		mod = 1;
	}
	
	while (modNum > 0 || mod > 0){
		while (modNum>=mod){
			ch++;
			modNum -= mod;
		}
		numBuf[i++] = ch + 48;
		ch = 0;
		mod /= 10;
//		if (mod == 0) {
//		mod = 1;
//		}
	}
	return numBuf;
}