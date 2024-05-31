#include "alarmNotiFrame.h"

uint32_t X_START = 115;
uint32_t Y_START = 120;
uint32_t X_SIZE = 250;
uint32_t Y_SIZE = 60;

int8_t hwndAlarmNotiServiceFrameControl = 0;
int8_t startAlarmNotiFrame = 0;
uint64_t phone;
static void createFrame(void);
static button_t phoneNumber;

void ShowAlarmNotiServiceFrame(void) {
  phone = sysParams.consts.ServicePhoneNumber;
  createFrame();
  while (1) {
		
    if (homeBut.isReleased == true) {
      homeBut.isReleased = false;
      goHome = true;
    }
    if (goHome) {
      return;
    }
//    if (updateFlags.sec == true) {
//      drawClock();
//      drawMainStatusBar(144, 2305, 16);
//      updateFlags.sec = false;
//    }
    if (retBut.isReleased == true) {
      retBut.isReleased = false;
      return;
    }

    if (phoneNumber.isPressed == true) {
      phoneNumber.isPressed = false;
    }
    if (phoneNumber.isReleased == true) {
      uint64_t temp = ShowKeyboardFrame(1, 9999999999);
      if (temp > 0) {
				phone = temp;
      }
      phoneNumber.isReleased = false;
      createFrame();
    }
    if (okBut.isReleased) {
      sysParams.consts.ServicePhoneNumber = phone;
      FP_SaveParam();
      okBut.isReleased = false;
      return;
    }
    if (cancelBut.isReleased) {
      cancelBut.isReleased = false;
      return;

    }
  }
}

void createFrame(void) {
  TC_clearButtons();
  //Static refresh
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_ALARM_NOTI);
  drawStatusBarOkCancel();

  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  drawFillArcRec(X_START, Y_START, X_SIZE, Y_SIZE, LCD_COLOR_PHANTOMBLUE);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_PHANTOMBLUE);
  uint8_t offset = 0;
  offset = BSP_LCD_DisplayStringAt(X_START + 45, Y_START + Y_SIZE / 4, "+7-", LEFT_MODE);
  BSP_LCD_DisplayStringAt(X_START + 45 + offset, Y_START + Y_SIZE / 4, intToStr(phone), LEFT_MODE);
  phoneNumber.x = X_START;
  phoneNumber.y = Y_START;
  phoneNumber.xSize = X_SIZE;
  phoneNumber.ySize = Y_SIZE;

  //BSP_LCD_DrawBitmap(LIST_X, LIST_Y, &list);

  //plug
  //	BSP_LCD_SetFont(&Oxygen_Mono_20);
  //	
  //	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  //	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  //	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, 100, NOTI_STRING_1, CENTER_MODE);
  //	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, 130, NOTI_STRING_2, CENTER_MODE);
  //	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, 160, NOTI_STRING_3, CENTER_MODE);
  //	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2, 190, NOTI_STRING_4, CENTER_MODE);

  //	BSP_LCD_SetFont(&Oxygen_Mono_24);

  /*Add buttons settings*/

  /*Add Buttons*/
  TC_addButton( & retBut);
  TC_addButton( & phoneNumber);
  TC_addButton( & okBut);
  TC_addButton( & cancelBut);
  TC_addButton( & homeBut);
  //enableClockDraw = true;
}