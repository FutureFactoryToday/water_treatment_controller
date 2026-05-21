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
uint16_t POWC (uint32_t a, uint8_t b){
	uint32_t res = a;
	if (b == 0) return 1;
	while(b !=1){b--; res = res*a; }
	return res;
}

uint32_t mod(int32_t a){
	return (a<0)? -a : a;
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

uint8_t* intToStr (int32_t num){
	for(int i = 0; i <sizeof(numBuf); i++){
		numBuf[i] = 0;
	}
	
	uint8_t ch = 0;
	uint32_t mod = 1000000000;
	if (num == 0){
		numBuf[0] = 48;
		return numBuf;
	}
	uint8_t i = 0;
	if (num < 0)
	{
		numBuf[i++] = '-';
		num = num*(-1);
	}
	uint32_t modNum = num;
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
int32_t MAX(int32_t a, int32_t b){
	return (a>b)?a:b;
}
