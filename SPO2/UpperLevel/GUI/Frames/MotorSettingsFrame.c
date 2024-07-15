/*Includes*/
#include "MotorSettingsFrame.h"

/*Macro and defines*/
#define LINE_NUM 2
/*Global parameters*/
static button_t menuLines[LINE_NUM];
static uint32_t tempVals[LINE_NUM];
/*Local prototypes*/
static void createFrame();
static void RefreshScrollBar(void);
static void calcButParam();
static void markLine(uint8_t i);
void drawLine(uint8_t num, uint8_t * string, uint16_t time, bool touch);
/*Code*/
uint8_t ShowMotorSettings(){
	
	tempVals[0] = sysParams.consts.maxMotorSpeedPercent;
	tempVals[1] = sysParams.consts.minMotorSpeedPercent;
	createFrame();
	while(1) {
		if(goHome){
			return -1;
		}
		if(updateFlags.sec == true) {
			updateFlags.sec = false;
		}
		if(okBut.isReleased == true) {
			okBut.isReleased = false;
			sysParams.consts.maxMotorSpeedPercent = tempVals[0];
			sysParams.consts.minMotorSpeedPercent = tempVals[1];
			FP_SaveParam();
			return 0;
		}
		if(cancelBut.isReleased == true) {
			cancelBut.isReleased = false;
			return 0;
		}
		if(retBut.isReleased == true) {
			retBut.isReleased = false;
			return 0;
		}
		if(homeBut.isReleased == true) {
			homeBut.isReleased = false;
			goHome = true;
		}
		
		if(menuLines[0].isReleased == true) {
			menuLines[0].isReleased = false;
			uint32_t temp = ShowKeyboardFrame(1,100);
			if (temp > 0){
				tempVals[0] = temp;
			}
			createFrame();
		}
		if(menuLines[1].isReleased == true) {
			menuLines[1].isReleased = false;
			uint32_t temp = ShowKeyboardFrame(1,100);
			if (temp > 0){
				tempVals[1] = temp;
			}
			createFrame();
		}
		
		if(homeBut.isReleased == true) {
			homeBut.isReleased = false;
			goHome = true;
		}
//		if(scrollUpBut.isReleased == true) {
//			if(firstEl > 0) {
//				firstEl--;
//				RefreshScrollBar();
//			}
//			scrollUpBut.isReleased = false;
//		}
//		if(scrollDwnBut.isReleased == true) {
//			if(firstEl < (sizeof(piston_poz_t)/sizeof(uint32_t)) - 4) {
//				firstEl++;
//				RefreshScrollBar();
//			}
//			scrollDwnBut.isReleased = false;
//		}
//		for (uint8_t i = 0; i < LINE_NUM; i++){
//			if(checkBox[i].isPressed == true) {
//				//Make it blue
//				uint8_t* ptr = &tempEnable;
//				uint8_t tempResult = *ptr  ^ (0x01 << (i + firstEl));
//				*ptr = tempResult;
//				markLine(i);
//				checkBox[i].isPressed = false;
//			}
			
//		}
		
	}
}


/* Private user code ---------------------------------------------------------*/
void createFrame() {
	TC_clearButtons();
	drawMainWindow();
	//BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_MOTOR_SETTINGS[0]);
	drawStatusBarOkCancel();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	uint32_t xOff = 300;
	for(uint8_t i = 0; i < LINE_NUM; i++) {
		BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + i * STATIC_LINE_SPASER + 9, ITEM_MOTOR_SETTINGS[i+1], LEFT_MODE);
		menuLines[i].xSize = 150;
		menuLines[i].ySize = 40;
		menuLines[i].x = BSP_LCD_GetXSize() - 5 - menuLines[i].xSize;
		menuLines[i].y = STATIC_LINE_Y + STATIC_LINE_SPASER * i + 3;
		
		drawFillButton(menuLines[i].x, menuLines[i] .y, menuLines[i].xSize, menuLines[i].ySize, intToStr(tempVals[i]), false);
	}
	calcButParam();
	//RefreshScrollBar();
	/*Add buttons parameters*/
}

//void markLine(uint8_t i) {
//	bool checked;
//	char *status;
//	
//	uint8_t* ptr = &tempEnable;
//	bool tempResult = *ptr  & (0x01 << (i + firstEl));
//	checked = (tempResult) ? true : false;
//	status = (tempResult) ? "X" : "";
//	checkBox[i] = drawFillButton(checkBox[i].x, checkBox[i] .y, checkBox[i].xSize, checkBox[i].ySize, status, checked);
//	
//}

//void RefreshScrollBar(void) {
//	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//	drawMainWindow();
//	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	WTC_FONT_t *oldFont = BSP_LCD_GetFont();
//	BSP_LCD_SetFont( &Oxygen_Mono_20);
//	for(uint8_t i = 0; i < LINE_NUM; i++) {
//		menuLines[i].xSize = 18 + BSP_LCD_DisplayStringAt(menuLines[i].x, menuLines[i].y, ITEM_STEPS[i + firstEl], LEFT_MODE);
//		markLine(i);
//	}
//	drawScrollButton(0);
//	BSP_LCD_SetFont(oldFont);
//	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	
//	
//	drawStaticLines();
//	
//}

void calcButParam() {
	TC_clearButtons();
	for(uint8_t i = 0; i < LINE_NUM; i++) {
//		mark[i].x = SCROLLKEYUP_POS_X - 5 - 40;
//		checkBox[i].y = STATIC_LINE_Y + STATIC_LINE_SPASER * i + 3;
//		checkBox[i].xSize = 40;
//		checkBox[i].ySize = 40;
		TC_addButton(&menuLines[i]);
	}
	TC_addButton(&okBut);
	TC_addButton(&cancelBut);
	TC_addButton(&retBut);
	TC_addButton(&homeBut);
//	TC_addButton(&scrollUpBut);
//	TC_addButton(&scrollDwnBut);
}