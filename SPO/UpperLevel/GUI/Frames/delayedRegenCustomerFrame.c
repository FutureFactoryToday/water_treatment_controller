#include "delayedRegenCustomerFrame.h"

void ShowRemainingDays(void);

static void createFrame();

void ShowDelayedRegenCustFrame(void)
{
	createFrame();
	while(1)
	{
		if (updateFlags.sec == true){
			 ShowRemainingDays();
		}
		if(retBut.isPressed == true){
			return;
    }
	}
}
void ShowRemainingDays(void){
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(DELAYED_REGEN_VALUE_BOX_X,DELAYED_REGEN_VALUE_BOX_Y, DELAYED_REGEN_VALUE_BOX_SIZE_X, DELAYED_REGEN_VALUE_BOX_SIZE_Y);
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawRect(DELAYED_REGEN_VALUE_BOX_X, DELAYED_REGEN_VALUE_BOX_Y, DELAYED_REGEN_VALUE_BOX_SIZE_X, DELAYED_REGEN_VALUE_BOX_SIZE_Y);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	if (chosenTask == NULL || 
			isZeroDateTime(&chosenTask->startDateTime) || 
			compareDateTime(&chosenTask->startDateTime, getTime())<=0){
				
				BSP_LCD_DisplayStringAt(DELAYED_REGEN_VALUE_X, DELAYED_REGEN_VALUE_Y, PL_NOT_INITED, LEFT_MODE);
			} else {
				uint8_t remainingDays = countDaysBetween(getTime(), &chosenTask->startDateTime);//*decDateTime(&chosenTask->startDateTime,getTime());
				BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(DELAYED_REGEN_VALUE_X, DELAYED_REGEN_VALUE_Y, intToStr(remainingDays), LEFT_MODE);
			
			}
}
void createFrame(void)
{
	TC_clearButtons();
    //Static refresh
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
    
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
    
    BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
    
    BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
    
    BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_DELAYED_REGEN,LEFT_MODE);
    
//    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//    BSP_LCD_FillRect(DELAYED_REGEN_VALUE_BOX_X,DELAYED_REGEN_VALUE_BOX_Y, DELAYED_REGEN_VALUE_BOX_SIZE_X, DELAYED_REGEN_VALUE_BOX_SIZE_Y);
//    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//    BSP_LCD_DrawRect(DELAYED_REGEN_VALUE_BOX_X, DELAYED_REGEN_VALUE_BOX_Y, DELAYED_REGEN_VALUE_BOX_SIZE_X, DELAYED_REGEN_VALUE_BOX_SIZE_Y);
//    
//    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//    BSP_LCD_DisplayStringAt(DELAYED_REGEN_VALUE_X, DELAYED_REGEN_VALUE_Y, intToStr(pistonTasks[REGENERATION_TASK_NUM].restartDateTime.day), LEFT_MODE);
//    
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(DELAYED_REGEN_VALUE_X + 80, DELAYED_REGEN_VALUE_Y, DAY_BEFORE_REGEN, LEFT_MODE);
    BSP_LCD_SetFont(&Oxygen_Mono_24);
		
		enableClockDraw = true;
		TC_addButton(&retBut);
}

