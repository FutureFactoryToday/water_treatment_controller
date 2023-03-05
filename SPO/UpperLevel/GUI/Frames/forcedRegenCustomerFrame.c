#include "forcedRegenCustomerFrame.h"
void RefreshForcedRegenCustFrame(void);

//int8_t hwndForcedRegenCustFrameControl = 0;
uint16_t statusColor;
static button_t forceRegen; 
static void createFrame();

void ShowForcedRegenCustFrame(void)
{
    createFrame();
	//uint8_t oldSec = getTime()->second - 1;
    while(1)
    {
        if (updateFlags.sec == true){
            drawClock();
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
        if (updateFlags.sec){
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
            BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
            BSP_LCD_FillCircle(355, 210, 15);
			updateFlags.sec = false;
		} 

        /*Buttons pressed*/ 
        if (forceRegen.isPressed == true){
            drawFillButton(80, 180, 200, 60, "Начать", true);
            PL_Planner(FORCE_START_NOW);
            forceRegen.isPressed = false;
        }

        /*Buttons releases*/
        if (retBut.isReleased == true){
            retBut.isReleased = false;
            return;
        }
        if (forceRegen.isReleased == true){
            drawFillButton(80, 180, 200, 60, "Начать", false);
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
	BSP_LCD_DisplayStringAt(75, 90, "Регенерация через" ,LEFT_MODE);
    BSP_LCD_DisplayStringAt(315, 90, intToStr(5) ,LEFT_MODE);
    BSP_LCD_DisplayStringAt(345, 90, "дней" ,LEFT_MODE);    
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    
    BSP_LCD_DrawLine(60, 145, 420, 145);
    
    forceRegen = drawFillButton(80, 180, 200, 60, "Начать", false);
    
    drawStatusBarLabel("Обезжелезивание");
    
    drawClock();
    
    /*Add buttons parameters*/
   
	/*Add buttons to Touch Controller*/
	
	TC_addButton(&retBut);
    TC_addButton(&forceRegen);
    
    //enableClockDraw = true;
} 

//void RefreshForcedRegenCustFrame(void)
//{
//    //Static refresh
//	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//	BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
//	BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
//	
//	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//	BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
//	
//	BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
//	
//	BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
//	
//	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,MODE_FORCED_REGEN,LEFT_MODE);
//	
//	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//	BSP_LCD_FillRect(KEY_REGEN_FAST_X,KEY_REGEN_FAST_Y,KEY_REGEN_FAST_SIZE_X, KEY_REGEN_FAST_SIZE_Y);
//	BSP_LCD_FillRect(KEY_REGEN_DELAY_X,KEY_REGEN_DELAY_Y,KEY_REGEN_DELAY_SIZE_X, KEY_REGEN_DELAY_SIZE_Y);
//	
//	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	BSP_LCD_DisplayStringAt(KEY_REGEN_FAST_X+KEY_REGEN_FAST_SIZE_X/2, KEY_REGEN_FAST_TEXT_Y, FAST_REGEN, CENTER_MODE);
//	BSP_LCD_DisplayStringAt(KEY_REGEN_DELAY_X+KEY_REGEN_DELAY_SIZE_X/2, KEY_REGEN_DELAY_TEXT_Y, DELAYED_REGEN, CENTER_MODE);
//		
//	
//}