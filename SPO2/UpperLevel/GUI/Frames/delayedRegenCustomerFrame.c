#include "delayedRegenCustomerFrame.h"

//void ShowRemainingDays(void);

static uint16_t statusColor;
static button_t forceRegen; 
static void createFrame();
static void showRemeiningTime(void);

void ShowDelayedRegenCustFrame(void)
{
    createFrame();
	//uint8_t oldSec = getTime()->second - 1;
    while(1)
    {
        if (updateFlags.sec == true){
           drawClock(); drawMainStatusBar(144, 2305, 16);
					showRemeiningTime();
					
          updateFlags.sec = false;
        }    

        /*Buttons pressed*/ 
        if (forceRegen.isPressed == true){
            drawFillButton(80, 180, 200, 60, "Начать", true);
            
            forceRegen.isPressed = false;
        }

        /*Buttons releases*/
        if (retBut.isReleased == true){
            retBut.isReleased = false;
            return;
        }
        if (forceRegen.isReleased == true){
          drawFillButton(80, 180, 200, 60, "Начать", false);
					PL_planer(FORCE_START_NEAREST);
          forceRegen.isReleased = false;
        }
        
        
    }
}

void createFrame()
{
    TC_clearButtons();
    
    drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_FORCED_REGEN);
    
    drawMainWindow();
    
   BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);


		
	showRemeiningTime();
      
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    
    BSP_LCD_DrawLine(60, 145, 420, 145);
    
    forceRegen = drawFillButton(80, 180, 200, 60, "Начать", false);
    
    drawStatusBarLabel(ITEM_LOAD_TYPE[sysParams.consts.loadType]);
    
     drawClock(); drawMainStatusBar(144, 2305, 16);
    
    /*Add buttons parameters*/
   
	/*Add buttons to Touch Controller*/
	
		TC_addButton(&retBut);
    TC_addButton(&forceRegen);
    
    //enableClockDraw = true;
} 



void showRemeiningTime(void){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(70, 90, 480,50);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	if (sysParams.consts.planerConsts.status != PL_WORKING){
		BSP_LCD_DisplayStringAt(75, 90, "Регенерация через" ,LEFT_MODE);
	} else {
		BSP_LCD_DisplayStringAt(75, 90, "До следующего шага " ,LEFT_MODE);
	}
	uint8_t* text;
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	if (sysParams.vars.planer.currentTask == NULL || sysParams.consts.planerConsts.status == PL_NOT_SET){
		text = &PL_NOT_INITED;
		BSP_LCD_DisplayStringAt(315, 90, text ,LEFT_MODE);
		
	} else {
		wtc_time_t remain = timeRemain();
		if (remain.day > 0) {
			BSP_LCD_DisplayStringAt(325, 90, getFormatedTimeFromSource("DD",&remain) ,LEFT_MODE);
			BSP_LCD_DisplayStringAt(355, 90, "дн." ,LEFT_MODE);  
		} else {
			if (remain.hour > 0) {
			BSP_LCD_DisplayStringAt(325, 90, getFormatedTimeFromSource("hh",&remain) ,LEFT_MODE);
			BSP_LCD_DisplayStringAt(355, 90, "ч." ,LEFT_MODE);  
		} else {
			if (remain.minute > 0) {
			BSP_LCD_DisplayStringAt(325, 90, getFormatedTimeFromSource("mm",&remain) ,LEFT_MODE);
			BSP_LCD_DisplayStringAt(355, 90, "м." ,LEFT_MODE);  
		} else {
			if (remain.second > 0) {
			BSP_LCD_DisplayStringAt(325, 90, getFormatedTimeFromSource("ss",&remain) ,LEFT_MODE);
				BSP_LCD_DisplayStringAt(355, 90, "сек." ,LEFT_MODE);  
		} 
		}
		}
		}
	}
	switch(sysParams.consts.planerConsts.status){
			case (PL_NOT_SET):{
					statusColor = LCD_COLOR_RED;
					break;
			}
			case (PL_SET):{
					statusColor = LCD_COLOR_BLUE;
					break;
			}
			case (PL_WORKING):{
					statusColor = LCD_COLOR_GREEN;
					break;
			}
	}
	BSP_LCD_SetTextColor(statusColor);
	BSP_LCD_FillCircle(355, 210, 15);
}