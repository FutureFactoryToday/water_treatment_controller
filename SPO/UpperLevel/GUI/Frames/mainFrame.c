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
void RefreshMainFrame(void);

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
			 
			serviceBut.isPressed = false;
		}
		if (customerBut.isPressed == true){
			 
			customerBut.isPressed = false;
		}
	
	}
}

void createFrame (void){
	TC_clearButtons();
	
//	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//	BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
//	BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
	
//	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//	BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
//	
//	BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&Logo);
    drawMainBar(false, 190, 5, " ");
    
    drawFillButton(20, 80, 200, 60, 20, "Пользователь", LCD_COLOR_WHITEBLUE, false);
	drawFillButton(260, 80, 200, 60, 20, "Инженер", LCD_COLOR_WHITEBLUE, false);
    
    drawStatusBarSave(" ");
	
//	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//	BSP_LCD_FillRect(DELAY_REGEN_VALUE_BOX_X,DELAY_REGEN_VALUE_BOX_Y, DELAY_REGEN_VALUE_BOX_SIZE_X, DELAY_REGEN_VALUE_BOX_SIZE_Y * 3);
//	
//	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//	BSP_LCD_DrawRect(DELAY_REGEN_VALUE_BOX_X, DELAY_REGEN_VALUE_BOX_Y, DELAY_REGEN_VALUE_BOX_SIZE_X, DELAY_REGEN_VALUE_BOX_SIZE_Y);
//	BSP_LCD_DrawRect(SPEED_VALUE_BOX_X, SPEED_VALUE_BOX_Y, SPEED_VALUE_BOX_SIZE_X, SPEED_VALUE_BOX_SIZE_Y);
//	BSP_LCD_DrawRect(TIME_VALUE_BOX_X, TIME_VALUE_BOX_Y, TIME_VALUE_BOX_SIZE_X, TIME_VALUE_BOX_SIZE_Y);
//	BSP_LCD_DrawRect(DELAY_REGEN_VALUE_BOX_X - 1, DELAY_REGEN_VALUE_BOX_Y - 1, DELAY_REGEN_VALUE_BOX_SIZE_X + 2, TIME_VALUE_BOX_SIZE_Y*3+2);
//	
//	
//	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	
//	BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y, ITEM_MAIN_FRAME[MODE_SOFTENING_CYCLE], LEFT_MODE);
//	BSP_LCD_DisplayStringAt(MODE_MENU_X, MODE_MENU_Y, ITEM_MAIN_FRAME[MODE_MENU], LEFT_MODE);
//	
//	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//	BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_TEXT_X, DELAY_REGEN_STATUS_TEXT_Y, ITEM_MAIN_FRAME[DELAY_REGEN], LEFT_MODE);
//	BSP_LCD_DisplayStringAt(SPEED_STATUS_TEXT_X, SPEED_STATUS_TEXT_Y, ITEM_MAIN_FRAME[SPEED], LEFT_MODE);
//	BSP_LCD_DisplayStringAt(TIME_STATUS_TEXT_X, TIME_STATUS_TEXT_Y, ITEM_MAIN_FRAME[TIME], LEFT_MODE);
//	
//	
//	BSP_LCD_DisplayStringAt(SPEED_STATUS_UNITS_X, SPEED_STATUS_UNITS_Y, ITEM_MAIN_FRAME[SPEED_UNITS], LEFT_MODE);
//	BSP_LCD_DisplayStringAt(TIME_STATUS_UNITS_X , TIME_STATUS_UNITS_Y, ITEM_MAIN_FRAME[TIME_UNITS], LEFT_MODE);
	
	/*Add buttons settings*/
    serviceBut.x = 260;
    serviceBut.y = 80;
    serviceBut.xSize = 200;
    serviceBut.ySize = 60;
    
    customerBut.x = 20;
    customerBut.y = 80;
    customerBut.xSize = 200;
    customerBut.ySize = 60;
	
	/*Add Buttons*/
	TC_addButton(&serviceBut);
	TC_addButton(&customerBut);
	
	enableClockDraw = true;
}

void RefreshMainFrame(void)
{
    //Static refresh
    
    //Dinamic refres
	
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(DELAY_REGEN_VALUE_BOX_X+1, DELAY_REGEN_VALUE_BOX_Y+1, DELAY_REGEN_VALUE_BOX_SIZE_X-2, DELAY_REGEN_VALUE_BOX_SIZE_Y-2);
		
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		if (chosenTask == NULL || isZeroDateTime(&chosenTask->startDateTime) || compareDateTime(&chosenTask->startDateTime, getTime())<=0){
			BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
			if (unitsText != dayText){
					unitsText = dayText;
					update = true;
				}
			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
			BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_VALUE_X, DELAY_REGEN_STATUS_VALUE_Y, PL_NOT_INITED, LEFT_MODE);
		} else {
			remainingDays = countDaysBetween(getTime(), &chosenTask->startDateTime);//*decDateTime(&chosenTask->startDateTime,getTime());
			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
			if (!equalDate(&chosenTask->startDateTime,getTime())){
				BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_VALUE_X, DELAY_REGEN_STATUS_VALUE_Y, intToStr(remainingDays), LEFT_MODE);
			} else {
				BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_VALUE_X, DELAY_REGEN_STATUS_VALUE_Y, getFormatedTimeFromSource("hh:mm:ss",decDateTime(&chosenTask->startDateTime,getTime())), LEFT_MODE);	
			}
			BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
			if (!equalDate(&chosenTask->startDateTime,getTime())){
				if (unitsText != dayText){
					unitsText = dayText;
					update = true;
				}
			}else {
				if (unitsText != timeText){
					unitsText = timeText;
					update = true;
				}
			}
		}
		if (update){
			BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
			BSP_LCD_FillRect(DELAY_REGEN_STATUS_UNITS_X, DELAY_REGEN_STATUS_UNITS_Y, BSP_LCD_GetXSize() - DELAY_REGEN_STATUS_UNITS_X, BSP_LCD_GetFont()->height);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_UNITS_X, DELAY_REGEN_STATUS_UNITS_Y, unitsText, LEFT_MODE);
			update = false;
		}
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(SPEED_VALUE_BOX_X+1, SPEED_VALUE_BOX_Y+1, SPEED_VALUE_BOX_SIZE_X-2, SPEED_VALUE_BOX_SIZE_Y-2);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_DisplayStringAt(SPEED_STATUS_VALUE_X, SPEED_STATUS_VALUE_Y, intToStr((uint32_t)FM_getFlowSpeed()), LEFT_MODE); 
    
        
}



void TranslateMainFrameMSG (void)
{
    BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        if (isInRectangle(tsState.X,tsState.Y,STATUSBAR_POS_X,STATUSBAR_POS_Y,100,TOP_BOT_LINE_WIDTH) )
        {
           hwndMainFrameControl = 1;
        }        
    }
}