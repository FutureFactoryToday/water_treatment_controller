#include "mainFrame.h"
uint8_t* FormatTime = "hh:mm";
int32_t remainingDays;
bool showDays;
uint8_t hwndMainFrameControl = 0;
int8_t startMainFrame = 1;
uint8_t* dayText;
uint8_t* timeText;
uint8_t* valText, *unitsText;
task_line_t *shownStep;
static time_t displayedTime;
bool update;
bool stepShow;
static button_t regenBut, menuBut, contactsBut; 
static void createFrame (void);
void updateRemTime(void);
void showStepName(void);
void clearShownStep(void);
//void RefreshMainFrame(void);

void ShowMainFrame(void)
{
	stepShow = false;
//	dayText = ITEM_MAIN_FRAME[DELAY_REGEN_UNITS];
//	timeText = ITEM_MAIN_FRAME[TIME_UNITS];
	//shownStep = planner.currentStep;
	createFrame();
	
	while(1)
	{		
		if (updateFlags.sec == true){
				drawClock();
			if (planner.status == PL_WORKING){
				updateRemTime();
			}
				updateFlags.sec = false;
		}
		if (planner.status == PL_WORKING){
			if (planner.currentStep != shownStep){
				TC_clearButtons();
				TC_addButton(&regenBut);
				drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_WRENCHBUT, LCD_COLOR_WHITE, false);
				showStepName();
				updateRemTime();
				shownStep = planner.currentStep;
				stepShow = true;
			}
		} else {
			if (stepShow == true){
				clearShownStep();
				drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_WRENCHBUT, LCD_COLOR_WHITEBLUE, false);
				TC_addButton(&menuBut);
				stepShow = false;
			}
		}
		
		
		/*Button pressed*/
        if (regenBut.isPressed == true){
			//drawFillCustomButton(25, 80, 200, 60, "ПРОМЫВКА", &gImage_DROPBUT, true);
			regenBut.isPressed = false;
		}
		if (menuBut.isPressed == true){
			//drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_DROPBUT, true);
			menuBut.isPressed = false;
		}
     if (contactsBut.isPressed == true){
			drawFillButton(260, 200, 200, 60, "Контакты", true);
			contactsBut.isPressed = false;
		}
       
        
		/*Buttons releases*/
    if (regenBut.isReleased == true){
			PL_Planner(FORCE_START_NOW);
			regenBut.isReleased = false;
			createFrame();
		}
		if (menuBut.isReleased == true){

      ShowMainMenuFrame();
			menuBut.isReleased = false;
			createFrame();
		}
        if (contactsBut.isReleased == true){
            ShowAlarmNotiServiceFrame();   
			contactsBut.isReleased = false;
            createFrame();
		}
	}
}

void createFrame (void){
	TC_clearButtons();
	
	drawMainBar(false, false, SMALL_LOGO_X, SMALL_LOGO_Y, " ");
	
	drawMainWindow();
	
	regenBut = drawFillCustomButton(25, 80, 200, 60, "ПРОМЫВКА", &gImage_DROPBUT, LCD_COLOR_DARKBLUE, false);
	menuBut = drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_WRENCHBUT, LCD_COLOR_WHITEBLUE, false);
	//contactsBut = drawTextLabel(260, 200, 200, 60, "Контакты");
	
	drawMainStatusBar(144, 2305, 15);
	
	drawClock();
	
	/*Add buttons settings*/
	
	/*Add Buttons*/
	TC_addButton(&regenBut);
	TC_addButton(&menuBut);
  //TC_addButton(&contactsBut);
	
	enableClockDraw = true;
}


void updateRemTime(void){
	wtc_time_t remTime = intToWTCTime(planner.currentTask->startDateTime - getRTC());
	
	drawCustomTextLabel(235,160,100, 60, getFormatedTimeFromSource("hh:mm",&remTime),LCD_COLOR_BLACK,LCD_COLOR_GREEN);
}

void showStepName(void){
	drawCustomTextLabel(25, 160, 200, 60, ITEM_STEPS[PC_pozNum(planner.currentStep->poz)],LCD_COLOR_BLACK,LCD_COLOR_GREEN);
}

void clearShownStep(void){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(25,160,310,61);
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
//		if (planner.currentTask == NULL || isZeroDateTime(&planner.currentTask->startDateTime) || compareDateTime(&planner.currentTask->startDateTime, getTime())<=0){
//			BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//			if (unitsText != dayText){
//					unitsText = dayText;
//					update = true;
//				}
//			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//			BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_VALUE_X, DELAY_REGEN_STATUS_VALUE_Y, PL_NOT_INITED, LEFT_MODE);
//		} else {
//			remainingDays = countDaysBetween(getTime(), &planner.currentTask->startDateTime);//*decDateTime(&planner.currentTask->startDateTime,getTime());
//			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//			if (!equalDate(&planner.currentTask->startDateTime,getTime())){
//				BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_VALUE_X, DELAY_REGEN_STATUS_VALUE_Y, intToStr(remainingDays), LEFT_MODE);
//			} else {
//				BSP_LCD_DisplayStringAt(DELAY_REGEN_STATUS_VALUE_X, DELAY_REGEN_STATUS_VALUE_Y, getFormatedTimeFromSource("hh:mm:ss",decDateTime(&planner.currentTask->startDateTime,getTime())), LEFT_MODE);	
//			}
//			BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//			if (!equalDate(&planner.currentTask->startDateTime,getTime())){
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