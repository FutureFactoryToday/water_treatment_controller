/**
  ******************************************************************************
  * @file           : Service.c
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
#include "Service/Service.h"
/* Private includes ----------------------------------------------------------*/
//#include "FlashParams/FlashParam.h"
/* Private typedef -----------------------------------------------------------*/
typedef struct{
	uint16_t x;
	uint16_t y;
} coord_t;
/* Private define ------------------------------------------------------------*/
#define TEXT_X 50
#define TEXT_Y 50
#define TEXT_WIDTH 16
#define CROSS_WIDTH 21
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
extern TS_StateTypeDef tsState;
extern uint32_t touchDelay;
extern int16_t kX;
extern int16_t kY;
extern int16_t bX;
extern int16_t bY;
/* Private function prototypes -----------------------------------------------*/
void SERV_PRINT_TOUCH_INFO(void);

/* Private user code ---------------------------------------------------------*/
void SERV_TS_CALIB(void){
	bool exit = 0;
	
	int32_t kX;
	int32_t kY;
	int32_t bX;
	int32_t bY;
	
	coord_t calibCoord[4] = {0};
	coord_t calibCross[4] = {{10,10},{470,10},{10,310},{470,310}};
	uint8_t tCnt = 0, step = 0;
	int16_t old_kX = kX, old_kY = kY, old_bX = bX, old_bY = bY;
	
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	
	WTC_FONT_t *oldFont = BSP_LCD_GetFont();
	BSP_LCD_SetFont(&Oxygen_Mono_8);
	SERV_PRINT_TOUCH_INFO();
	
	BSP_LCD_DrawHLine(calibCross[step].x-CROSS_WIDTH/2,calibCross[step].y,CROSS_WIDTH);
	BSP_LCD_DrawVLine(calibCross[step].x,calibCross[step].y-CROSS_WIDTH/2,CROSS_WIDTH);
	
	while (!exit){
		LL_mDelay(10);
		BSP_TS_GetState(&tsState);
		
		if (touchDelay == 0 && tsState.TouchDetected == 1 ){
			touchDelay = 300;
			SERV_PRINT_TOUCH_INFO();
		
			calibCoord[step].x = (tCnt == 0)?tsState.X_t : (calibCoord[step].x + tsState.X_t)/2;
			calibCoord[step].y = (tCnt == 0)?tsState.Y_t : (calibCoord[step].y + tsState.Y_t)/2;
			
			if (++tCnt == TOUCH_CALIB_CNT){
				step++;
				if (step > 3){
					kX = (calibCross[3].x - calibCross[0].x)*MOD;
					kX = kX/(calibCoord[3].x - calibCoord[0].x);
					kY = ((calibCross[3].y - calibCross[0].y)*MOD)/(calibCoord[3].y - calibCoord[0].y);
					bX = calibCross[0].x - (kX*calibCoord[0].x)/MOD;
					bY = calibCross[0].y - (kY*calibCoord[0].y)/MOD;
					
				} else {
					BSP_LCD_Clear(LCD_COLOR_WHITE);
					SERV_PRINT_TOUCH_INFO();
					BSP_LCD_DrawHLine(calibCross[step].x-CROSS_WIDTH/2,calibCross[step].y,CROSS_WIDTH);
					BSP_LCD_DrawVLine(calibCross[step].x,calibCross[step].y-CROSS_WIDTH/2,CROSS_WIDTH);
					tCnt = 0;
				}
			}
			
		}
		if (step > 3){
			switch(SERV_TS_TEST(kX,kY,bX,bY)){
				case (0): {
					tCnt = 0;
					step = 0;
					break;
				}	
				case (1): {
					BSP_TS_SetCalibCoef((int16_t)kX, (int16_t)kY, (int16_t)bX, (int16_t)bY);

					stored_ts_conf_t newConf = {0};
					newConf.bX = (uint32_t) bX;
					newConf.kX = (uint32_t) kX;
					newConf.bY = (uint32_t) bY;
					newConf.kY = (uint32_t) kY;
					fp->params.ts_conf = newConf;
					fp->needToSave = true;
					exit = true;
					break;
				}
				case (2): {
					BSP_TS_SetCalibCoef(old_kX, old_kY, old_bX, old_bY);
					exit = true;
					break;
				}
			}
		}
	}
}

uint8_t SERV_TS_TEST(int16_t kXe,int16_t kYe,int16_t bXe,int16_t bYe){
	
	WTC_FONT_t *oldFont = BSP_LCD_GetFont();
	uint16_t oldBCol = BSP_LCD_GetBackColor();
	uint16_t oldTCol = BSP_LCD_GetTextColor();
	
	BSP_LCD_SetFont(&Oxygen_Mono_12);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	DrawButton(BSP_LCD_GetXSize()/2 - 80, BSP_LCD_GetYSize() - 40, 40, 40, 0, "RETRY"); 
	DrawButton(BSP_LCD_GetXSize()/2 - 20, BSP_LCD_GetYSize() - 40, 40, 40, 0, "SAVE"); 
	DrawButton(BSP_LCD_GetXSize()/2 + 20, BSP_LCD_GetYSize() - 40, 40, 40, 0, "EXIT");
	SERV_PRINT_TOUCH_INFO();
	
	
	BSP_TS_SetCalibCoef((int16_t)kXe, (int16_t)kYe, (int16_t)bXe, (int16_t)bYe);
	while (1){
		LL_mDelay(10);
		BSP_TS_GetState(&tsState);
		if (touchDelay == 0 && tsState.TouchDetected == 1 ){
			touchDelay = 300;
			SERV_PRINT_TOUCH_INFO();
			if (isInRectangle(tsState.X, tsState.Y,BSP_LCD_GetXSize()/2 - 80, BSP_LCD_GetYSize() - 40, 40, 40)){
				return 0;
			}
			if (isInRectangle(tsState.X, tsState.Y,BSP_LCD_GetXSize()/2 - 20, BSP_LCD_GetYSize() - 40, 40, 40)){
				return 1;
			}
			if (isInRectangle(tsState.X, tsState.Y,BSP_LCD_GetXSize()/2 + 20, BSP_LCD_GetYSize() - 40, 40, 40)){
				return 2;
			}
		}
	}
	
	BSP_LCD_SetFont(oldFont);
	BSP_LCD_SetBackColor(oldBCol);
	BSP_LCD_SetTextColor(oldTCol);
}

void SERV_PRINT_TOUCH_INFO(void){
	uint16_t oldCol = BSP_LCD_GetTextColor();
	
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(TEXT_X, TEXT_Y, TEXT_WIDTH*4,TEXT_WIDTH*4);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(TEXT_X,TEXT_Y,"X_t: ",LEFT_MODE);
	BSP_LCD_DisplayStringAt(TEXT_X+25,TEXT_Y,intToStr(tsState.X_t),LEFT_MODE);
	BSP_LCD_DisplayStringAt(TEXT_X,TEXT_Y+TEXT_WIDTH,"Y_t: ",LEFT_MODE);
	BSP_LCD_DisplayStringAt(TEXT_X+25,TEXT_Y+TEXT_WIDTH,intToStr(tsState.Y_t),LEFT_MODE);
			
	BSP_LCD_DisplayStringAt(TEXT_X,TEXT_Y+TEXT_WIDTH*2,"X_d: ",LEFT_MODE);
	BSP_LCD_DisplayStringAt(TEXT_X+25,TEXT_Y+TEXT_WIDTH*2,intToStr(tsState.X),LEFT_MODE);
	BSP_LCD_DisplayStringAt(TEXT_X,TEXT_Y+TEXT_WIDTH*3,"Y_d: ",LEFT_MODE);
	BSP_LCD_DisplayStringAt(TEXT_X+25,TEXT_Y+TEXT_WIDTH*3,intToStr(tsState.Y),LEFT_MODE);
	
	BSP_LCD_SetTextColor(oldCol);
}