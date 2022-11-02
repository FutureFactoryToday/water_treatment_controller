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

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
sys_param_t sysParam;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void System_init(void){
	if (fp->isLoaded != 1){
		sysParam.lang = DEF_SYST_CONFIG_LANG;
		sysParam.SERVIVE_CODE = DEF_SERVIVE_CODE;
		fp->needToSave = true;
		fp->params.sysPar = sysParam;
	} else {
		sysParam = fp->params.sysPar;
	}
}