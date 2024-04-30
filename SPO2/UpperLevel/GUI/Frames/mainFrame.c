#include "mainFrame.h"
uint8_t* FormatTime = "hh:mm";
int32_t remainingDays;
bool showDays;
uint8_t hwndMainFrameControl = 0;
int8_t startMainFrame = 1;
uint8_t* dayText;
uint8_t* timeText;
uint8_t* valText, *unitsText;
uint32_t shownStep;
static time_t displayedTime;
bool update;
bool stepShow, errorShown;
static button_t regenBut, menuBut, contactsBut; 
static void createFrame (void);
void updateRemTime(void);
void showStepName(void);
void clearShownStep(void);
void showInOut(void);
//void RefreshMainFrame(void);

void ShowMainFrame(void)
{
	goHome = false;
	stepShow = false;
	errorShown = false;
//	dayText = ITEM_MAIN_FRAME[DELAY_REGEN_UNITS];
//	timeText = ITEM_MAIN_FRAME[TIME_UNITS];
	//shownStep = sysParams.consts.planerConsts.currentStep;
	createFrame();
	
	while(1)
	{		
		if (updateFlags.sec == true){
			 drawClock(); drawMainStatusBar(144, 2305, 16);
			if (sysParams.consts.planerConsts.status == PL_WORKING){
				updateRemTime();
				drawMainStatusBar(0, 0, 0);
			}
			updateFlags.sec = false;
		}
		if (sysParams.consts.planerConsts.status == PL_WORKING){
			if (*sysParams.vars.planer.currentStep->poz != shownStep){
				shownStep = *sysParams.vars.planer.currentStep->poz;
				showStepName();
//				if((sysParams.vars.planer.currentStep+1) != NULL){
//						showStepName();
//						updateRemTime();
//				}
				TC_clearButtons();
				TC_addButton(&regenBut);
        drawFillCustomButton(25, 80, 200, 60, "СЛЕДУЮЩАЯ", &gImage_DROPBUT, LCD_COLOR_DARKBLUE, false);
				drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_WRENCHBUT_PHANTOM, LCD_COLOR_PHANTOMBLUE, false);
				
				stepShow = true;
			}
		} else {
			if (stepShow == true){
				clearShownStep();
        drawFillCustomButton(25, 80, 200, 60, "ПРОМЫВКА", &gImage_DROPBUT, LCD_COLOR_DARKBLUE, false);
				drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_WRENCHBUT, LCD_COLOR_WHITEBLUE, false);
				TC_addButton(&menuBut);
				stepShow = false;
        //createFrame();
			}
		}
		showInOut();
		if ((sysParams.vars.error.flags.PistonFail == 1 ||
			sysParams.vars.error.flags.MotorFail == 1) &&
				errorShown == false){
					clearShownStep();
					drawCustomTextLabel(70, 145, 350, 60, "Заклинивание двигателя клапана",LCD_COLOR_BLACK,LCD_COLOR_PALERED);
					errorShown = true;
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
			PL_planer(FORCE_START_NOW);
			regenBut.isReleased = false;
			//createFrame();
		}
		if (menuBut.isReleased == true){
      ShowMainMenuFrame();
			menuBut.isReleased = false;
			createFrame();
		}
//        if (contactsBut.isReleased == true){
//            ShowAlarmNotiServiceFrame();   
//			contactsBut.isReleased = false;
//            createFrame();
//		}
	}
}

void createFrame (void){
	goHome = false;
	goHome = false;
	stepShow = false;
	errorShown = false;
	TC_clearButtons();
	
	drawMainBar(false, false, SMALL_LOGO_X, SMALL_LOGO_Y, " ");
	
	drawMainWindow();
	
	regenBut = drawFillCustomButton(25, 80, 200, 60, "ПРОМЫВКА", &gImage_DROPBUT, LCD_COLOR_DARKBLUE, false);
	menuBut = drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_WRENCHBUT, LCD_COLOR_WHITEBLUE, false);
	//contactsBut = drawTextLabel(260, 200, 200, 60, "Контакты");
	
	drawMainStatusBar(144, 2305, 16);
	
	drawClock(); drawMainStatusBar(144, 2305, 16);
	showInOut();
	/*Add Buttons*/
	TC_addButton(&regenBut);
	TC_addButton(&menuBut);
	
	enableClockDraw = true;
}

void showInOut(void){
	uint8_t offset = 25;
	
		if(sysParams.vars.status.flags.ExternalCommandOn == 1){
			drawCustomTextLabel(offset, 215, 60, 60, "ВХ1",LCD_COLOR_BLACK,LCD_COLOR_YELLOW);
		}else{
			drawCustomTextLabel(offset, 215, 60, 60, "ВХ1",LCD_COLOR_WHITE,LCD_COLOR_WHITE);
		}
		offset += 60+20;
		if(sysParams.vars.status.flags.RelDCOn == 1){
			drawCustomTextLabel(offset, 215, 60, 60, "ВЫХ1",LCD_COLOR_BLACK,LCD_COLOR_WHITEBLUE);
		}else{
			drawCustomTextLabel(offset, 215, 60, 60, "ВЫХ1",LCD_COLOR_WHITE,LCD_COLOR_WHITE);
		}
		offset += 60+20;
		if(sysParams.vars.status.flags.RelACOn == 1){
			drawCustomTextLabel(offset, 215, 60, 60, "ВЫХ2",LCD_COLOR_WHITE,LCD_COLOR_BLUE);
		}else{
			drawCustomTextLabel(offset, 215, 60, 60, "ВЫХ2",LCD_COLOR_WHITE,LCD_COLOR_WHITE);
		}
}
void updateRemTime(void){
	wtc_time_t remTime = intToWTCTime(sysParams.vars.planer.currentTask->remainingTime);
	drawCustomTextLabel(355, 145, 100, 60, getFormatedTimeFromSource("mm:ss",&remTime),LCD_COLOR_BLACK,LCD_COLOR_GREEN);
}

void showStepName(void){
    int8_t poz_t = PC_pozNum(sysParams.vars.planer.currentStep->poz);
    drawCustomTextLabel(25, 145, 300, 60, ITEM_STEPS[poz_t],LCD_COLOR_BLACK,LCD_COLOR_GREEN);
}

void clearShownStep(void){
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(25,145,450,61);
}