#include "mainFrame.h"
uint8_t* FormatTime = "hh:mm";
int32_t remainingDays;
bool showDays;
uint8_t hwndMainFrameControl = 0;
int8_t startMainFrame = 1;
uint8_t* dayText;
uint8_t* timeText;
uint8_t* valText, *unitsText;
bool update;
static button_t serviceBut, customerBut; 
static void createFrame (void);
//void RefreshMainFrame(void);

void ShowMainFrame(void)
{
	dayText = ITEM_MAIN_FRAME[DELAY_REGEN_UNITS];
	timeText = ITEM_MAIN_FRAME[TIME_UNITS];
	
	createFrame();
	
	while(1)
	{		

		/*Buttons releases*/
		if (serviceBut.isReleased == true){
			if (PIN_showFrame() == 1){
				ShowServiceMenuFrame();
			}				
			serviceBut.isReleased = false;
			createFrame();
		}
		if (customerBut.isReleased == true){
			ShowMenuFrame(); 
			customerBut.isReleased = false;
			createFrame();
		}
		/*Button pressed*/
		if (serviceBut.isPressed == true){
			drawFillButton(260, 80, 200, 60, "Инженер", true);
			serviceBut.isPressed = false;
		}
		if (customerBut.isPressed == true){
			drawFillButton(20, 80, 200, 60, "Пользователь", true);
			customerBut.isPressed = false;
		}
	
	}
}

void createFrame (void){
	TC_clearButtons();
	
    drawMainBar(false, 190, 5, " ");
    
    drawMainWindow();
    
    customerBut = drawFillButton(20, 80, 200, 60, "Пользователь", false);
	serviceBut = drawFillButton(260, 80, 200, 60, "Инженер", false);
    
    drawStatusBarEmpty();
    
    drawClock();
	
	/*Add buttons settings*/
	
	/*Add Buttons*/
	TC_addButton(&serviceBut);
	TC_addButton(&customerBut);
	
	enableClockDraw = true;
}

//void RefreshMainFrame(void)
//{
//    //Static refresh
//    
//    //Dinamic refres
//	
//    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//		BSP_LCD_FillRect(DELAY_REGEN_VALUE_BOX_X+1, DELAY_REGEN_VALUE_BOX_Y+1, DELAY_REGEN_VALUE_BOX_SIZE_X-2, DELAY_REGEN_VALUE_BOX_SIZE_Y-2);
//		
//		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//		if (chosenTask == NULL || isZeroDateTime(&chosenTask->startDateTime) || compareDateTime(&chosenTask->startDateTime, getTime())<=0){
//			BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//			if (unitsText != dayText){
//					unitsText = dayText;
//					update = true;
//				}
//			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//			BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_VALUE_X, DELAY_REGEN_STATUS_VALUE_Y, PL_NOT_INITED, LEFT_MODE);
//		} else {
//			remainingDays = countDaysBetween(getTime(), &chosenTask->startDateTime);//*decDateTime(&chosenTask->startDateTime,getTime());
//			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//			if (!equalDate(&chosenTask->startDateTime,getTime())){
//				BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_VALUE_X, DELAY_REGEN_STATUS_VALUE_Y, intToStr(remainingDays), LEFT_MODE);
//			} else {
//				BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_VALUE_X, DELAY_REGEN_STATUS_VALUE_Y, getFormatedTimeFromSource("hh:mm:ss",decDateTime(&chosenTask->startDateTime,getTime())), LEFT_MODE);	
//			}
//			BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//			if (!equalDate(&chosenTask->startDateTime,getTime())){
//				if (unitsText != dayText){
//					unitsText = dayText;
//					update = true;
//				}
//			}else {
//				if (unitsText != timeText){
//					unitsText = timeText;
//					update = true;
//				}
//			}
//		}
//		if (update){
//			BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//			BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//			BSP_LCD_FillRect(DELAY_REGEN_STATUS_UNITS_X, DELAY_REGEN_STATUS_UNITS_Y, BSP_LCD_GetXSize() - DELAY_REGEN_STATUS_UNITS_X, BSP_LCD_GetFont()->height);
//			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//			BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_UNITS_X, DELAY_REGEN_STATUS_UNITS_Y, unitsText, LEFT_MODE);
//			update = false;
//		}
//    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//		BSP_LCD_FillRect(SPEED_VALUE_BOX_X+1, SPEED_VALUE_BOX_Y+1, SPEED_VALUE_BOX_SIZE_X-2, SPEED_VALUE_BOX_SIZE_Y-2);
//		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//		BSP_LCD_DisplayStringAt(SPEED_STATUS_VALUE_X, SPEED_STATUS_VALUE_Y, intToStr((uint32_t)FM_getFlowSpeed()), LEFT_MODE); 
//    
//        
//}



//void TranslateMainFrameMSG (void)
//{
//    BSP_TS_GetState(&tsState);
//	if (touchDelay == 0 && tsState.TouchDetected == 1)
//    {
//        touchDelay = 100;
//        if (isInRectangle(tsState.X,tsState.Y,STATUSBAR_POS_X,STATUSBAR_POS_Y,100,TOP_BOT_LINE_WIDTH) )
//        {
//           hwndMainFrameControl = 1;
//        }        
//    }
//}