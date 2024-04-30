#include "forcedRegenCustomerFrame.h"
void RefreshForcedRegenCustFrame(void);

//int8_t hwndForcedRegenCustFrameControl = 0;
static uint16_t statusColor;
static button_t forceRegen, cycledRegen; 
wtc_time_t remain;
static void createFrame();
static void showRemeiningTime(void);
int ShowForcedRegenCustFrame(void)
{
    createFrame();
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
				if (cycledRegen.isPressed == true){
					uint8_t* text = (sysParams.vars.planer.cycled)?"ON":"OFF";
					drawFillButton(cycledRegen.x, cycledRegen.y, cycledRegen.xSize, cycledRegen.ySize, text, sysParams.vars.planer.cycled);
					cycledRegen.isPressed = false;
				}

        /*Buttons releases*/
        if (retBut.isReleased == true){
            retBut.isReleased = false;
            return 0;
        }
        if (forceRegen.isReleased == true){
            drawFillButton(80, 180, 200, 60, "Начать", false);
						PL_planer(FORCE_START_NOW);
            forceRegen.isReleased = false;
        }
				if (cycledRegen.isReleased == true){
					sysParams.vars.planer.cycled = !sysParams.vars.planer.cycled;
					uint8_t* text = (sysParams.vars.planer.cycled)?"ON":"OFF";
					drawFillButton(cycledRegen.x, cycledRegen.y, cycledRegen.xSize, cycledRegen.ySize, text, sysParams.vars.planer.cycled);
					
					
					cycledRegen.isReleased = false;
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
		BSP_LCD_DisplayStringAt(400, 140, "Цикл",LEFT_MODE);
		showRemeiningTime();
      
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    
    BSP_LCD_DrawLine(60, 145, 420, 145);
    
    forceRegen = drawFillButton(80, 180, 200, 60, "Начать", false);
		uint8_t* text = (sysParams.vars.planer.cycled)?"ON":"OFF";
    cycledRegen = drawFillButton(400, 180, 60, 60, text, sysParams.vars.planer.cycled);
    drawStatusBarLabel(ITEM_FILTER_SELECTION[PL_getCurrentTaskNum()]);
    
     drawClock(); drawMainStatusBar(144, 2305, 16);
    
    /*Add buttons parameters*/
   
	/*Add buttons to Touch Controller*/
	
	TC_addButton(&retBut);
    TC_addButton(&cycledRegen);
    TC_addButton(&forceRegen);
    
    //enableClockDraw = true;
} 



void showRemeiningTime(void){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(70, 90, 400,50);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	if (sysParams.consts.planerConsts.status != PL_WORKING){
	
		BSP_LCD_DisplayStringAt(75, 90, "Запуск через" ,LEFT_MODE);
		
		
	} else {
		uint8_t* text;
		uint8_t stepNum = PC_pozNum ((sysParams.vars.planer.currentStep-1)->poz);
		if (stepNum >= 0) {
			text = ITEM_STEPS[stepNum];
		}
		//BSP_LCD_DisplayStringAt(75, 90, "До " ,LEFT_MODE);
		BSP_LCD_DisplayStringAt(75, 90, text ,LEFT_MODE);
	}
	uint8_t* text;
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	if (sysParams.vars.planer.currentTask == NULL || sysParams.consts.planerConsts.status == PL_FINISHED){
		text = &PL_NOT_INITED;
		BSP_LCD_DisplayStringAt(315, 90, text ,LEFT_MODE);
		
	} else {
		remain = timeRemain();
		if (remain.month > 0) {
			BSP_LCD_DisplayStringAt(325, 90, intToStr(remain.month) ,LEFT_MODE);
			BSP_LCD_DisplayStringAt(355, 90, " мес." ,LEFT_MODE);  
		}
			else if(remain.day > 0) {
			BSP_LCD_DisplayStringAt(325, 90, getFormatedTimeFromSource("DD",&remain) ,LEFT_MODE);
			BSP_LCD_DisplayStringAt(355, 90, " дн." ,LEFT_MODE);  
		} else if (remain.hour > 0) {
			BSP_LCD_DisplayStringAt(325, 90, getFormatedTimeFromSource("hh",&remain) ,LEFT_MODE);
			BSP_LCD_DisplayStringAt(355, 90, "ч." ,LEFT_MODE);  
		} else if (remain.minute > 0) {
			BSP_LCD_DisplayStringAt(325, 90, getFormatedTimeFromSource("mm",&remain) ,LEFT_MODE);
			BSP_LCD_DisplayStringAt(355, 90, "м." ,LEFT_MODE);  
		} else if (remain.second >= 0) {
			BSP_LCD_DisplayStringAt(325, 90, getFormatedTimeFromSource("ss",&remain) ,LEFT_MODE);
			BSP_LCD_DisplayStringAt(355, 90, "сек." ,LEFT_MODE);  
		}
	}
	BSP_LCD_DisplayStringAt(400, 240, intToStr(sysParams.vars.planer.cycleCnt),LEFT_MODE);
	switch(sysParams.consts.planerConsts.status){
        case (PL_FINISHED):{
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