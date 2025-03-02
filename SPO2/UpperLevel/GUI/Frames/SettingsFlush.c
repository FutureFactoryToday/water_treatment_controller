#include "SettingsFlush.h"

static void createFrame();


int ShowSettingsFlushFrame(void)
{

    createFrame();
    while(1)
    {
        if (updateFlags.sec == true){
             
          updateFlags.sec = false; 
					sysParams.vars.frameWDTTim = SOFT_WDT_TIM_VAL_DEF; 
        }
        //Pressed
        
        //Released
        if(retBut.isReleased == true) {
            retBut.isReleased = false;
            return 0;
        }
        if(cancelBut.isReleased == true) {
            cancelBut.isReleased = false;
            return 0;
        }
        if (homeBut.isReleased == true){
					homeBut.isReleased = false;
					goHome = true;
				}
				if (goHome){
					return -1;
				}
       
        if (okBut.isReleased == true){
					BSP_LCD_Clear(LCD_COLOR_WHITEBLUE);
					BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
					BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
	
					BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2,ITEM_SETTINGS_FLUSH[4],CENTER_MODE);
					
          Load_Default_Values();
					sysParams.vars.frameWDTTim = SOFT_WDT_TIM_VAL_DEF*3; 
          FP_SaveParam();
					while(1);
          okBut.isReleased = false;
          return 0;
        }
			
			}
}

void createFrame()
{
	TC_clearButtons();
	//Static refresh
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_SETTINGS_FLUSH[0]);
	
	drawStatusBarOkCancelCustom(ITEM_SETTINGS_FLUSH[2],ITEM_SETTINGS_FLUSH[3]);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2,ITEM_SETTINGS_FLUSH[1],CENTER_MODE);
	TC_addButton(&retBut);
  TC_addButton(&homeBut);
  TC_addButton(&okBut);	
	TC_addButton(&cancelBut);
}
