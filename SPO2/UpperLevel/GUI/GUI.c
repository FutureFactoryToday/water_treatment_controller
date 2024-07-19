/**
  ******************************************************************************
  * @file           : GUI.c
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
#include "PistonControl\PistonControl.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

button_t retBut = {RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y,0,0,0,0}, 
okBut = {OK_X,OK_Y,100,50,0,0,0,0}, cancelBut = {CANCEL_X,CANCEL_Y,100,50,0,0,0,0}, 
scrollUpBut = {UP_ARROW_POS_X,UP_ARROW_POS_Y,UP_ARROW_SIZE_X,UP_ARROW_SIZE_Y,0,0,0,0}, 
scrollDwnBut = {DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y,0,0,0,0}, 
homeBut = {HOME_BUT_X,HOME_BUT_Y,40,60,0,0,0,0};


TS_StateTypeDef tsState;
uint32_t noTouchDelay;
uint8_t dropBut;
uint8_t wrenchBut;
uint8_t pageBut;
uint8_t redraw = 0;
uint8_t frame = 0;
//uint8_t wasScroll = 0;
uint8_t itemIndex;
update_flag_t updateFlags;
bool enableClockDraw = false;
bool goHome;
uint8_t* hour = "hh";
uint8_t* minute = "mm";

char* ITEM_MENU_DROP[] = { "SERVICE", "REGENERATION", "FILTERING" };
char* ITEM_MENU_WRENCH[] = { "LANGUAGE", "SET TIME", "RESET" };
char* ITEM_MENU_PAGE[] = { "ERROR LIST", "DIAGRAM", "COUNTER" };

char* ITEM_MENU_SERVICE[] = { "ADJUSTMENT", "FEED RAPID", "CALIBRATE" };
char* ITEM_MENU_REGENERATION[] = { "BACKWASH", "RINSE", "DOWNFLOW BRINE", "UPFLOW BRINE", "FILL/REGENERANT REFILL", "SOFTENING/FILTERING" };
char* ITEM_MENU_FILTERING[] = { "aaa", "sss", "ddd" };

/* Private function prototypes -----------------------------------------------*/

void DrawOpticStatus(void);
/* Private user code ---------------------------------------------------------*/
void initGUI(void){
	uint16_t offset;
	uint16_t VersHigh, VersLow;
 	redraw = 0;
	if (BSP_LCD_Init() == LCD_OK){
		sysParams.vars.status.flags.TFTInited = 1;
	} else {
		sysParams.vars.error.flags.TFTFail = 1;
	}
	BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
	sysParams.vars.status.flags.TouchInited = 1;
	BSP_LCD_Clear(LCD_COLOR_DARKBLUE);
	BSP_LCD_DrawBitmap(0,0,&LOGO);

	BSP_LCD_SetFont(&Oxygen_Mono_24);
    
	BSP_LCD_SetBackColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(160, 220, "ГОЛОВА КМ1", LEFT_MODE);
	offset = 110;
	offset += BSP_LCD_DisplayStringAt(offset, 255, "МОЗГИ версия ПО ", LEFT_MODE);
	VersHigh = MAIN_VERSION;//(0xFFFF0000&sysParams.consts.sysVersion)>>16;
	VersLow = SUB_VERSION;//(0xFFFE&sysParams.consts.sysVersion)>>1;
	offset += BSP_LCD_DisplayStringAt(offset, 255, intToStr(VersHigh), LEFT_MODE);
	offset += BSP_LCD_DisplayStringAt(offset, 255, ".", LEFT_MODE);
	offset += BSP_LCD_DisplayStringAt(offset, 255, intToStr(VersLow), LEFT_MODE);
	BSP_BL_Control(100);  
	sysParams.vars.status.flags.TFTInited = 1;
	frame = 0;
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	offset += BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, 285, "Загрузка настроек и иниацилизация", CENTER_MODE);
	itemIndex = 0;
	LL_mDelay(2000);
}




uint8_t isInRectangle (uint16_t x, uint16_t y, uint16_t xS, uint16_t yS, uint16_t xSize, uint16_t ySize){
	
	return x < xS+xSize && x > xS && y < yS+ySize && y > yS;
}
