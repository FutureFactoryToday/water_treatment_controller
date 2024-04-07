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
//                if((planner.currentStep+1) != NULL){
//                    showStepName();
//                    updateRemTime();
//                }
				TC_clearButtons();
				TC_addButton(&regenBut);
        drawFillCustomButton(25, 80, 200, 60, "СЛЕДУЮЩАЯ", &gImage_DROPBUT, LCD_COLOR_DARKBLUE, false);
				drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_WRENCHBUT_PHANTOM, LCD_COLOR_PHANTOMBLUE, false);
				shownStep = planner.currentStep;
				stepShow = true;
			}
		} else {
			if (stepShow == true){
				clearShownStep();
                //drawFillCustomButton(25, 80, 200, 60, "ПРОМЫВКА", &gImage_DROPBUT, LCD_COLOR_DARKBLUE, false);
				//drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_WRENCHBUT, LCD_COLOR_WHITEBLUE, false);
				TC_addButton(&menuBut);
				stepShow = false;
        createFrame();
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
			//drawFillButton(260, 200, 200, 60, "Контакты", true);
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
	
	drawMainStatusBar(144, 2305, 16);
	
	drawClock();
	
	/*Add Buttons*/
	TC_addButton(&regenBut);
	TC_addButton(&menuBut);
	
	enableClockDraw = true;
}


void updateRemTime(void){
	wtc_time_t remTime = intToWTCTime(planner.currentTask->startDateTime - getRTC());
	drawCustomTextLabel(355, 160, 100, 60, getFormatedTimeFromSource("mm:ss",&remTime),LCD_COLOR_BLACK,LCD_COLOR_GREEN);
}

void showStepName(void){
    int8_t poz_t = PC_pozNum(planner.currentStep->poz);
    drawCustomTextLabel(25, 160, 300, 60, ITEM_STEPS[poz_t],LCD_COLOR_BLACK,LCD_COLOR_GREEN);
}

void clearShownStep(void){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(25,160,450,61);
}