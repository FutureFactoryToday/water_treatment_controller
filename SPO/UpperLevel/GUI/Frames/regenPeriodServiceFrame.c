#include "regenPeriodServiceFrame.h"

static void createFrame(void);
static button_t restartTextArea;
static uint16_t daysBetweenRegen;
static uint8_t* text;
void ShowRegenPeriodServiceFrame(void)
{
	if (chosenTask != NULL){
		daysBetweenRegen = chosenTask->restartDateTime.day;
	}
	createFrame();
	while(1)
	{ 
		if(okBut.isReleased == true){	
			if (chosenTask != NULL){
				chosenTask->restartDateTime.day = daysBetweenRegen;
				copyTasksToFlash();			
				fp->needToSave = 1;
				FP_SaveParam();
			}
			okBut.isReleased = false;
			return;
		}       
		
		if(restartTextArea.isReleased == true){
			if (chosenTask != NULL){  
				uint16_t result = ShowKeyboardFrame(1,999);
				if (result > 0 ) {
					daysBetweenRegen = result;
					createFrame();
				}
			}
			restartTextArea.isReleased = false;
			
		}
		if(restartTextArea.isReleased == true){
			if (chosenTask != NULL){
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
	drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_REGEN_PERIOD);
	
	drawStatusBarOkCancel();
	
	
	if (chosenTask == NULL){
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
	
	drawClock();
	enableClockDraw = true;
}
