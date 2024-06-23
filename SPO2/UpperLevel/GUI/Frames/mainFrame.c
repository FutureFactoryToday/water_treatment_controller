#include "mainFrame.h"
#define NEXT_STEP_DELAY 2*10
uint8_t* FormatTime = "hh:mm";
int32_t remainingDays;
bool showDays;
uint8_t hwndMainFrameControl = 0;
int8_t startMainFrame = 1;
uint8_t* dayText;
uint8_t* timeText;
uint8_t *valText, *unitsText;
bool shownServiceMessage;
bool shownErrorMessage;
uint32_t shownStep;
static time_t displayedTime;
bool update;
bool stepShow, errorShown;
static button_t regenBut, menuBut, contactsBut;
static void createFrame(void);
void updateRemTime(void);
void showStepName(void);
void clearShownStep(void);
void showInOut(void);
void showMessage(void);

// void RefreshMainFrame(void);
extern uint8_t frameBuffer[];
static bool enableMenu, enableWash; 
uint32_t color, c; 

void ShowMainFrame(void) {
    goHome = false;
    stepShow = false;
    errorShown = false;
    shownServiceMessage = false;
    shownErrorMessage = false;
    enableMenu = true;
    enableWash = true;
    createFrame();

  while (1) {

    if (updateFlags.sec == true) {
      drawClock();
      drawMainStatusBar(144, 2305, 16);
      if (sysParams.consts.planerConsts.status == PL_WORKING) {
        updateRemTime();
      }
			if (sysParams.vars.status.flags.NeedService == 0){
				showInOut();
			}
      updateFlags.sec = false;
    }
    if (sysParams.consts.planerConsts.status == PL_WORKING) {
      if (*sysParams.vars.planer.currentStep->poz != shownStep) {
        shownStep = *sysParams.vars.planer.currentStep->poz;
        showStepName();

				enableMenu = false;
        drawFillCustomButton(regenBut.x, regenBut.y, regenBut.xSize, regenBut.ySize, "СЛЕДУЮЩАЯ", &gImage_DROPBUT,
                             LCD_COLOR_DARKBLUE, LCD_COLOR_WHITE, false);
        drawFillCustomButton(menuBut.x, menuBut.y, menuBut.xSize, menuBut.ySize, "МЕНЮ",
                             &gImage_WRENCHBUT_PHANTOM, LCD_COLOR_PHANTOMBLUE, LCD_COLOR_WHITE,
                             false);

        stepShow = true;
      }
    } else {
      if (stepShow == true) {
        clearShownStep();
        drawFillCustomButton(regenBut.x, regenBut.y, regenBut.xSize, regenBut.ySize, "ПРОМЫВКА", &gImage_DROPBUT,
                             LCD_COLOR_DARKBLUE, LCD_COLOR_WHITE, false);
        drawFillCustomButton(menuBut.x, menuBut.y, menuBut.xSize, menuBut.ySize, "МЕНЮ", &gImage_WRENCHBUT,
                             LCD_COLOR_WHITEBLUE, LCD_COLOR_WHITE, false);
        enableMenu = true;
        stepShow = false;
				shownStep = 0;
        // createFrame();
      }
			showMessage();
    }
    
    /*Button pressed*/
    if (enableWash && regenBut.isPressed == true){
			
			if (regenBut.pressCnt > NEXT_STEP_DELAY) {
				PL_planer(FORCE_START_NOW);
				// drawFillCustomButton(25, 80, 200, 60, "ПРОМЫВКА", &gImage_DROPBUT,
				// true);
				regenBut.pressCnt = 0;
				regenBut.isPressed = false;
			}
    }
		if (enableMenu && menuBut.isPressed == true){ 
			if (menuBut.drawPressed == false){
				drawFillCustomButton(menuBut.x, menuBut.y, menuBut.xSize, menuBut.ySize, "МЕНЮ",
                             &gImage_WRENCHBUT_PHANTOM, LCD_COLOR_PHANTOMBLUE, LCD_COLOR_WHITE,false);
				menuBut.drawPressed = true;
			}
			if (menuBut.pressCnt > NEXT_STEP_DELAY) {
				goHome = false;
				ShowMainMenuFrame();
				// drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_DROPBUT, true);
				menuBut.isPressed = false;
				createFrame();
			}
		}

    /*Buttons releases*/
    if (regenBut.isReleased == true ) {
      
      regenBut.isReleased = false;
      // createFrame();
    }
    if (menuBut.isReleased == true) {
      //ShowMainMenuFrame();
			if (enableMenu){
				drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_WRENCHBUT,
																	 LCD_COLOR_WHITEBLUE, LCD_COLOR_WHITE,false);
				menuBut.drawPressed = false;
			}
      menuBut.isReleased = false;
      //createFrame();
    }

  }
}

void createFrame(void) {
  goHome = false;
  stepShow = false;
  errorShown = false;
  shownServiceMessage = false;
  shownErrorMessage = false;
  TC_clearButtons();
  menuBut.drawPressed = false;
  drawMainBar(false, false, SMALL_LOGO_X, SMALL_LOGO_Y, " ");

  drawMainWindow();

  regenBut = drawFillCustomButton(25, 80, 200, 60, "ПРОМЫВКА", &gImage_DROPBUT,
                                  LCD_COLOR_DARKBLUE, LCD_COLOR_WHITE, false);
  menuBut = drawFillCustomButton(255, 80, 200, 60, "МЕНЮ", &gImage_WRENCHBUT,
                                 LCD_COLOR_WHITEBLUE, LCD_COLOR_WHITE, false);
  // contactsBut = drawTextLabel(260, 200, 200, 60, "Контакты");

  drawMainStatusBar(144, 2305, 16);

  drawClock();
  showInOut();
  /*Add Buttons*/
  TC_addButton(&regenBut);
  TC_addButton(&menuBut);

  enableClockDraw = true;
}
#define X_START 30
#define Y_START 145
#define X_SIZE 420
#define Y_SIZE 55
void showMessage(void){
	WTC_FONT_t *oldFont = BSP_LCD_GetFont();
	 BSP_LCD_SetFont(&Oxygen_Mono_20);
	if (sysParams.vars.status.flags.NeedService == 1){
		if (shownServiceMessage == false){
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			drawFillArcRec(X_START, 215, X_SIZE, Y_SIZE, LCD_COLOR_DARKYELLOW);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_SetBackColor(LCD_COLOR_DARKYELLOW);

			BSP_LCD_DisplayStringAt(X_START + 50, 215,"Необходимо провести сервисное", LEFT_MODE);
			uint32_t offset = BSP_LCD_DisplayStringAt(X_START + 70, 215 + 25,"обслуживание! +7", LEFT_MODE);
			BSP_LCD_DisplayStringAt(X_START + 70 + offset, 215 + 25,intToStr(sysParams.consts.ServicePhoneNumber), LEFT_MODE);
			shownServiceMessage = true;
		}
		BSP_LCD_SetFont(oldFont);
	} else {
		if (shownServiceMessage == true){
			drawFillArcRec(X_START, 215, X_SIZE, Y_SIZE, LCD_COLOR_WHITE);
			shownServiceMessage = false;
		}
	}		
	if ((sysParams.vars.error.flags.PistonFail == 1 || sysParams.vars.error.flags.MotorFail == 1)){
		if (!shownErrorMessage){
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			drawFillArcRec(X_START, Y_START, X_SIZE, Y_SIZE, LCD_COLOR_PALERED);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_SetBackColor(LCD_COLOR_PALERED);
			BSP_LCD_SetFont(&Oxygen_Mono_20);
			BSP_LCD_DisplayStringAt(X_START + 30, Y_START + Y_SIZE/4,"ОТСУТСТВИЕ ВРАЩЕНИЯ ШЕСТЕРНИ", LEFT_MODE);
			
			shownErrorMessage = true;
		}
		BSP_LCD_SetFont(oldFont);
	}	else {
		if (shownErrorMessage){
			drawFillArcRec(X_START, Y_START, X_SIZE, Y_SIZE, LCD_COLOR_WHITE);
			shownErrorMessage = false;
		}
	}
//	if (shownMessage != 0){
//		drawFillArcRec(X_START, Y_START, X_SIZE, Y_SIZE, LCD_COLOR_WHITE);
//		shownMessage = 0;
//	}
}
void showInOut(void) {
  uint8_t offset = X_START;

  //if (sysParams.vars.status.flags.ExternalCommandOn == 1) {
	if((!LL_GPIO_IsInputPinSet(DP_SWITCH_GPIO_Port, DP_SWITCH_Pin)&&!sysParams.vars.error.flags._5VPowerFail)){
		if (LL_RTC_TIME_Get(RTC)&0x01){
			drawCustomTextLabel(offset, 215, 60, 55, "ВХ1", LCD_COLOR_BLACK,
                        LCD_COLOR_YELLOW);
		} else {
			drawCustomTextLabel(offset, 215, 60, 55, "ВХ1", LCD_COLOR_WHITE,
                        LCD_COLOR_WHITE);
		}
  } else {
    drawCustomTextLabel(offset, 215, 60, 55, "ВХ1", LCD_COLOR_WHITE,
                        LCD_COLOR_WHITE);
  }
  offset += 60 + 20;
  if (sysParams.vars.status.flags.RelDCOn == 1) {
		if (LL_RTC_TIME_Get(RTC)&0x01){
			drawCustomTextLabel(offset, 215, 60, 55, "ВЫХ1", LCD_COLOR_BLACK,
                        LCD_COLOR_WHITEBLUE);
		} else {
			drawCustomTextLabel(offset, 215, 60, 55, "ВЫХ1", LCD_COLOR_WHITE,
                        LCD_COLOR_WHITE);
		}
  } else {
    drawCustomTextLabel(offset, 215, 60, 55, "ВЫХ1", LCD_COLOR_WHITE,
                        LCD_COLOR_WHITE);
  }
  offset += 60 + 20;
  if (sysParams.vars.status.flags.RelACOn == 1) {
		if (LL_RTC_TIME_Get(RTC)&0x01){
			drawCustomTextLabel(offset, 215, 60, 55, "ВЫХ2", LCD_COLOR_WHITE,
                        LCD_COLOR_BLUE);
		} else {
			drawCustomTextLabel(offset, 215, 60, 55, "ВЫХ2", LCD_COLOR_WHITE,
                        LCD_COLOR_WHITE);
		}
  } else {
    drawCustomTextLabel(offset, 215, 60, 55, "ВЫХ2", LCD_COLOR_WHITE,
                        LCD_COLOR_WHITE);
  }
}

void updateRemTime(void) {
//  wtc_time_t remTime =
//      intToWTCTime(sysParams.vars.planer.currentTask->remainingTime);
	uint32_t time;
	uint8_t* text;
	if (sysParams.vars.planer.currentTask->remainingTime > 60){
		time = sysParams.vars.planer.currentTask->remainingTime/60;
		text = " мин";
	} else {
		time = sysParams.vars.planer.currentTask->remainingTime;
		text = " сек";
	}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	drawFillArcRec(355, 145, 100, 60, LCD_COLOR_GREEN);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
	
	uint8_t offset = BSP_LCD_DisplayStringAt(400, 160, intToStr(time), RIGHT_MODE);
	BSP_LCD_DisplayStringAt(400, 160,text, LEFT_MODE);
//  drawCustomTextLabel(355, 145, 100, 60, intToStr(time),
//                      //getFormatedTimeFromSource("mm:ss", &remTime),
//                      LCD_COLOR_BLACK, LCD_COLOR_GREEN);
}

void showStepName(void) {
  int8_t pozNum = PC_pozNum(sysParams.vars.planer.currentStep->poz);
	if (pozNum == 4) pozNum = 5;
	if (pozNum == 3){
		drawCustom2TextLabel(25, 145, 300, 60, ITEM_STEPS[pozNum],ITEM_STEPS[pozNum+1], LCD_COLOR_BLACK, LCD_COLOR_GREEN);	
	} else {
		drawCustomTextLabel(25, 145, 300, 60, ITEM_STEPS[pozNum], LCD_COLOR_BLACK, LCD_COLOR_GREEN);
	}
 
}

void clearShownStep(void) {
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_FillRect(25, 145, 450, 61);
}