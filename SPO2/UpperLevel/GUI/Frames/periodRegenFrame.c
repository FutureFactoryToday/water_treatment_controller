#include "periodRegenFrame.h"

static void createFrame();
static button_t periodRegenBut;
static button_t timeBeforeRegenBut;
static piston_task_t tempTask;
static uint8_t periodRegen, timeBeforeRegen;

int ShowPeriodRegenCustFrame(void) {
	tempTask = *sysParams.vars.planer.currentTask;
  createFrame();
  while (1) {
    if (updateFlags.sec == true) {
      // drawClock(); drawMainStatusBar(144, 2305, 16);
      updateFlags.sec = false;
    }
    //Released
    if (periodRegenBut.isReleased == true) {
      int32_t tempData = ShowKeyboardFrame(1, 99);
      if (tempData >= 0) {
        if (sysParams.consts.planerConsts.startType == BY_DAY ||
         sysParams.consts.planerConsts.startType == UNIVERSAL) {
					tempTask. restartDateTime = tempData * 60 * 60 * 24;
        }
        if (sysParams.consts.planerConsts.startType == BY_HOUR) {
					tempTask. restartDateTime = tempData * 60 * 60;
        }
      }
      createFrame();
      periodRegenBut.isReleased = false;
    }
    if (timeBeforeRegenBut.isReleased == true) {
      int32_t tempData = ShowKeyboardFrame(1, 999);
      if (tempData >= 0) {
				if (sysParams.consts.planerConsts.startType == BY_DAY ||
         sysParams.consts.planerConsts.startType == UNIVERSAL) {
					 bool addDay = false;
					 time_t tempRaw = getRTC() + tempData * 60 * 60 * 24;
					 struct tm timeSt = *localtime(&tempRaw); 
					 if (timeSt.tm_hour > sysParams.consts.planerConsts.preferedTimeForWash.hour){
						 addDay = true;
					 } else {
						 if (timeSt.tm_hour == sysParams.consts.planerConsts.preferedTimeForWash.hour &&
							 timeSt.tm_min > sysParams.consts.planerConsts.preferedTimeForWash.minute){
								 addDay = true;
							 }
					 }
					 timeSt.tm_hour = sysParams.consts.planerConsts.preferedTimeForWash.hour;
					 timeSt.tm_min = sysParams.consts.planerConsts.preferedTimeForWash.minute;
					 tempRaw = mktime(&timeSt);
					 if (addDay) tempRaw += 60*60*24;
          tempTask. startDateTime = tempRaw;
        }
        if (sysParams.consts.planerConsts.startType == BY_HOUR) {
					tempTask. startDateTime = getRTC() + tempData * 60 * 60;
        }
        
      }

      createFrame();
      timeBeforeRegenBut.isReleased = false;
    }
    if (retBut.isReleased == true) {
      retBut.isReleased = false;
      return 0;
    }
    if (homeBut.isReleased == true) {
      homeBut.isReleased = false;
      goHome = true;
    }
    if (goHome) {
      return -1;
    }
    if (okBut.isReleased == true) {
      okBut.isReleased = false;
			sysParams.vars.planer.currentTask->startDateTime = tempTask.startDateTime;
			sysParams.vars.planer.currentTask->restartDateTime = tempTask.restartDateTime;
      return 0;
    }
    if (cancelBut.isReleased == true) {
      cancelBut.isReleased = false;
      return 0;
    }
  }
}

void createFrame() {
  TC_clearButtons();
  //Static refresh
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, PERIOD_REGEN);

  drawStatusBarOkCancel();

  BSP_LCD_SetFont( & Oxygen_Mono_24);
  if (sysParams.consts.planerConsts.startType == BY_DAY ||
    sysParams.consts.planerConsts.startType == UNIVERSAL) {
    periodRegenBut = drawLightTextLabel(BSP_LCD_GetXSize() / 2 + 50, BSP_LCD_GetYSize() / 2 - 65, 100, 60, intToStr(tempTask. restartDateTime / (60 * 60 * 24)));
  }
  if (sysParams.consts.planerConsts.startType == BY_HOUR) {
    periodRegenBut = drawLightTextLabel(BSP_LCD_GetXSize() / 2 + 50, BSP_LCD_GetYSize() / 2 - 65, 100, 60, intToStr(tempTask. restartDateTime / (60 * 60)));
  }
  int32_t deltTime = tempTask. startDateTime - getRTC();
  uint32_t remTime = 0;
  if (deltTime >= 0) {
    if (sysParams.consts.planerConsts.startType == BY_HOUR) {
      remTime = deltTime / (60 * 60);
    }
    if (sysParams.consts.planerConsts.startType == BY_DAY ||
      sysParams.consts.planerConsts.startType == UNIVERSAL) {
      remTime = deltTime / (60 * 60 * 24);
    }
    timeBeforeRegenBut = drawLightTextLabel(BSP_LCD_GetXSize() / 2 + 50, BSP_LCD_GetYSize() / 2 + 25, 100, 60, intToStr(remTime));
  } else {
    timeBeforeRegenBut = drawLightTextLabel(BSP_LCD_GetXSize() / 2 + 50, BSP_LCD_GetYSize() / 2 + 25, 100, 60, "NaN");

  }

  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  if (sysParams.consts.planerConsts.startType == BY_DAY ||
    sysParams.consts.planerConsts.startType == UNIVERSAL) {
    BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 + 180, BSP_LCD_GetYSize() / 2 - 50, "Д", LEFT_MODE);
    BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 + 180, BSP_LCD_GetYSize() / 2 + 40, "Д", LEFT_MODE);
  }
  if (sysParams.consts.planerConsts.startType == BY_HOUR) {
    BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 + 180, BSP_LCD_GetYSize() / 2 - 50, "Ч", LEFT_MODE);
    BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 + 180, BSP_LCD_GetYSize() / 2 + 40, "Ч", LEFT_MODE);
  }
  
  BSP_LCD_SetFont( & Oxygen_Mono_20);
  BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 - 190, BSP_LCD_GetYSize() / 2 - 60, "Период проведения", LEFT_MODE);
  BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 - 190, BSP_LCD_GetYSize() / 2 - 36, "промывки", LEFT_MODE);
  BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 - 190, BSP_LCD_GetYSize() / 2 + 30, "Оставшееся время", LEFT_MODE);
  BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 - 190, BSP_LCD_GetYSize() / 2 + 54, "до начала промывки", LEFT_MODE);

  TC_addButton( & periodRegenBut);
  TC_addButton(&timeBeforeRegenBut);
  TC_addButton( & retBut);
  TC_addButton( & homeBut);
  TC_addButton( & okBut);
  TC_addButton( & cancelBut);
}