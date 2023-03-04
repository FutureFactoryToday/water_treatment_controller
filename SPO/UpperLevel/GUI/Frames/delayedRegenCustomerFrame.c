#include "delayedRegenCustomerFrame.h"

//void ShowRemainingDays(void);

static void createFrame();

void ShowDelayedRegenCustFrame(void)
{
	createFrame();
	while(1)
	{
		if (updateFlags.sec == true){
			 //ShowRemainingDays();
            if (chosenTask == NULL || 
            isZeroDateTime(&chosenTask->startDateTime) || 
            compareDateTime(&chosenTask->startDateTime, getTime())<=0) {
                BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
                BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
                BSP_LCD_DisplayStringAt(DELAYED_REGEN_VALUE_BOX_X + 60, DELAYED_REGEN_VALUE_BOX_Y + 12, PL_NOT_INITED, CENTER_MODE);
            }
            else{
                uint8_t remainingDays = countDaysBetween(getTime(), &chosenTask->startDateTime);
                BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
                BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
                BSP_LCD_DisplayStringAt(DELAYED_REGEN_VALUE_BOX_X + 60, DELAYED_REGEN_VALUE_BOX_Y + 12, intToStr(remainingDays) ,CENTER_MODE);
            }
            updateFlags.sec = false;
		}
		if(retBut.isPressed == true){
            retBut.isPressed = false;
			return;
        }
	}
}
//void ShowRemainingDays(void){
//	    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//	    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//    BSP_LCD_FillRect(DELAYED_REGEN_VALUE_BOX_X,DELAYED_REGEN_VALUE_BOX_Y, DELAYED_REGEN_VALUE_BOX_SIZE_X, DELAYED_REGEN_VALUE_BOX_SIZE_Y);
//    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//    BSP_LCD_DrawRect(DELAYED_REGEN_VALUE_BOX_X, DELAYED_REGEN_VALUE_BOX_Y, DELAYED_REGEN_VALUE_BOX_SIZE_X, DELAYED_REGEN_VALUE_BOX_SIZE_Y);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	if (chosenTask == NULL || 
//			isZeroDateTime(&chosenTask->startDateTime) || 
//			compareDateTime(&chosenTask->startDateTime, getTime())<=0){
//				
//				BSP_LCD_DisplayStringAt(DELAYED_REGEN_VALUE_X, DELAYED_REGEN_VALUE_Y, PL_NOT_INITED, LEFT_MODE);
//			} else {
//				uint8_t remainingDays = countDaysBetween(getTime(), &chosenTask->startDateTime);//*decDateTime(&chosenTask->startDateTime,getTime());
//				BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//				BSP_LCD_DisplayStringAt(DELAYED_REGEN_VALUE_X, DELAYED_REGEN_VALUE_Y, intToStr(remainingDays), LEFT_MODE);
//			
//			}
//}
void createFrame(void)
{
    TC_clearButtons();
    
    drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_DELAYED_REGEN);
    
    drawMainWindow();
    
    drawTextLabel(DELAYED_REGEN_VALUE_BOX_X, DELAYED_REGEN_VALUE_BOX_Y, DELAYED_REGEN_VALUE_BOX_SIZE_X, DELAYED_REGEN_VALUE_BOX_SIZE_Y,"");
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(250, DELAYED_REGEN_VALUE_BOX_Y + 10, "День(Дни)" ,LEFT_MODE);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    
    drawStatusBarEmpty();
    
    drawClock();
    
    /*Add buttons parameters*/
   
	/*Add buttons to Touch Controller*/
	
	TC_addButton(&retBut);
    
    enableClockDraw = true;
}