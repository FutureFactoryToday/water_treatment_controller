#include "regenPeriodServiceFrame.h"

static void createFrame(void);
static button_t restartTextArea;
static uint16_t daysBetweenRegen;
static uint8_t* text;
void ShowRegenPeriodServiceFrame(void)
{
	if (sysParams.vars.planer.currentTask != NULL){
		daysBetweenRegen = intToWTCTime(sysParams.vars.planer.currentTask->restartDateTime).day;
	}
	createFrame();
	while(1)
	{
        if (updateFlags.sec == true){
            //drawClock(); drawMainStatusBar(144, 2305, 16);
            updateFlags.sec = false;
        }
     
		if(okBut.isReleased == true){	
			if (sysParams.vars.planer.currentTask != NULL){
				sysParams.vars.planer.currentTask->restartDateTime = daysBetweenRegen*24*60*60;
				FP_SaveParam();
			}
			okBut.isReleased = false;
			return;
		}       
		
		if(restartTextArea.isReleased == true){
			if (sysParams.vars.planer.currentTask != NULL){  
				uint16_t result = ShowKeyboardFrame(1,999);
				if (result > 0 ) {
					daysBetweenRegen = result;
					createFrame();
				}
			}
			restartTextArea.isReleased = false;
			
		}
		if(restartTextArea.isReleased == true){
			if (sysParams.vars.planer.currentTask != NULL){
				drawDarkTextLabel(BSP_LCD_GetXSize()/2 - 30, BSP_LCD_GetYSize()/2 - 40, 60, 40, text);
			}
			restartTextArea.isReleased = false;
		}
		if (retBut.isReleased == true){
			retBut.isReleased = false;
			return;
		}
		if (cancelBut.isReleased == true){
			cancelBut.isReleased = false;
			return;
		}
	}
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_REGEN_PERIOD);
	
	drawStatusBarOkCancel();
	
	
	if (sysParams.vars.planer.currentTask == NULL){
		text = &PL_NOT_INITED;
	} else {
		text = intToStr(daysBetweenRegen);
	}
	
	restartTextArea = drawTextLabel(BSP_LCD_GetXSize()/2 - 30, BSP_LCD_GetYSize()/2 - 40, 60, 40, text);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2 + 10, DAY_BETWEEN_REGEN, CENTER_MODE);
	BSP_LCD_SetFont(&Oxygen_Mono_24);

	
	TC_addButton(&retBut);
	TC_addButton(&okBut);
	TC_addButton(&restartTextArea);
	TC_addButton(&cancelBut);
	
	 drawClock(); drawMainStatusBar(144, 2305, 16);
	//enableClockDraw = true;
}
