#include "daysBetweenRegenCustomerFrame.h"

static void createFrame();

void ShowDaysBetweenRegenCustFrame(void)
{
	createFrame();
    while(1)
    {
        if (updateFlags.sec == true){
          drawClock(); 
					drawMainStatusBar(144, 2305, 16);
          updateFlags.sec = false;
        }
        if (updateFlags.sec == true){
					if(sysParams.vars.planer.currentTask == NULL){
							BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
							BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
							BSP_LCD_DisplayStringAt(DBR_VALUE_BOX_X + 60, DBR_VALUE_BOX_Y + 12, PL_NOT_INITED, CENTER_MODE);
					}
					else{
							BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
							BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
							BSP_LCD_DisplayStringAt(DBR_VALUE_BOX_X + 60, DBR_VALUE_BOX_Y + 12, intToStr(intToWTCTime(sysParams.vars.planer.currentTask->restartDateTime).day), CENTER_MODE);
					}
					updateFlags.sec = false;
        }
        if(retBut.isReleased == true){
            retBut.isReleased = false;
            return;
        }
    }
}

void createFrame(void)
{
    TC_clearButtons();
    
    drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_DAYS_BETWEEN_REGEN);
    
    drawMainWindow();
    
    drawTextLabel(DBR_VALUE_BOX_X, DBR_VALUE_BOX_Y, DBR_VALUE_BOX_SIZE_X, DBR_VALUE_BOX_SIZE_Y,"");
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(250, DBR_VALUE_BOX_Y + 10, "День(Дни)" ,LEFT_MODE);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    
    drawStatusBarEmpty();
    
     drawClock(); drawMainStatusBar(144, 2305, 16);
    
    /*Add buttons parameters*/
   
	/*Add buttons to Touch Controller*/
	
	TC_addButton(&retBut);
    
    //enableClockDraw = true;
}



