#include "forcedRegenCustomerFrame.h"
void RefreshForcedRegenCustFrame(void);

//int8_t hwndForcedRegenCustFrameControl = 0;
static uint16_t statusColor;
static button_t forceRegen; 
wtc_time_t remain;
static void createFrame();
static void showRemeiningTime(void);
void ShowForcedRegenCustFrame(void)
{
    createFrame();
	//uint8_t oldSec = getTime()->second - 1;
    while(1)
    {
        if (updateFlags.sec == true){
          drawClock();
					showRemeiningTime();
					
          updateFlags.sec = false;
        }
//        if(redraw)
//        {
//            RefreshForcedRegenCustFrame();
//            redraw = 0;
//        }
//				if (oldSec != getTime()->second){
//					switch(PL_status){
//						case (PL_WAITING):{
//							statusColor = LCD_COLOR_RED;
//							 break;
//						}
//						case (PL_ALARM_SET):{
//							statusColor = LCD_COLOR_BLUE;
//							break;
//						}
//						case (PL_WORKING):{
//							statusColor = LCD_COLOR_GREEN;
//							 break;
//						}
//						case (PL_FORCED_ALARM_SET):{
//							statusColor = LCD_COLOR_YELLOW;
//							 break;
//						}
//					}
//					BSP_LCD_SetTextColor(statusColor);
//					BSP_LCD_FillRect(PL_STATUS_X,PL_STATUS_Y,PL_STATUS_SIZE_X, PL_STATUS_SIZE_Y);
//				}

//        TranslateForcedRegenCustFrameMSG();
//        
//        if(hwndForcedRegenCustFrameControl == 20) return;
//				if(hwndForcedRegenCustFrameControl == 30){
//					hwndForcedRegenCustFrameControl = 0;
//					PL_Planner(FORCE_START_NOW);
//				}
//				if(hwndForcedRegenCustFrameControl == 40){
//					hwndForcedRegenCustFrameControl = 0;
//					PL_Planner(FORCE_START_NEAREST);
//				}
      

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
						PL_Planner(FORCE_START_NOW);
            forceRegen.isReleased = false;
        }
        
        
    }
}

void createFrame()
{
    TC_clearButtons();
    
    drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_FORCED_REGEN);
    
    drawMainWindow();
    
   BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);


		
	showRemeiningTime();
      
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    
    BSP_LCD_DrawLine(60, 145, 420, 145);
    
    forceRegen = drawFillButton(80, 180, 200, 60, "Начать", false);
    
    drawStatusBarLabel(ITEM_LOAD_TYPE[loadType]);
    
    drawClock();
    
    /*Add buttons parameters*/
   
	/*Add buttons to Touch Controller*/
	
		TC_addButton(&retBut);
    TC_addButton(&forceRegen);
    
    //enableClockDraw = true;
} 



void showRemeiningTime(void){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(70, 90, 400,50);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	if (PL_status != PL_WORKING){
		BSP_LCD_DisplayStringAt(75, 90, "Регенерация через" ,LEFT_MODE);
	} else {
		BSP_LCD_DisplayStringAt(75, 90, "До следующего шага " ,LEFT_MODE);
	}
	uint8_t* text;
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	if (chosenTask == NULL || PL_status == PL_WAITING){
		text = &PL_NOT_INITED;
		BSP_LCD_DisplayStringAt(315, 90, text ,LEFT_MODE);
		
	} else {
		remain = timeRemain();
		if (remain.day > 0) {
			BSP_LCD_DisplayStringAt(325, 90, getFormatedTimeFromSource("DD",&remain) ,LEFT_MODE);
			BSP_LCD_DisplayStringAt(355, 90, " дн." ,LEFT_MODE);  
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
	switch(PL_status){
                case (PL_WAITING):{
                    statusColor = LCD_COLOR_RED;
                    break;
                }
                case (PL_ALARM_SET):{
                    statusColor = LCD_COLOR_BLUE;
                    break;
                }
                case (PL_WORKING):{
                    statusColor = LCD_COLOR_GREEN;
                    break;
                }
                case (PL_FORCED_ALARM_SET):{
                    statusColor = LCD_COLOR_YELLOW;
                    break;
                }
            }
            BSP_LCD_SetTextColor(statusColor);
            BSP_LCD_FillCircle(355, 210, 15);
}