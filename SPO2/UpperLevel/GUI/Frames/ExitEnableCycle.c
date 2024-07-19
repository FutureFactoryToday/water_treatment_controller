/*Includes*/
#include "ExitEnableCycle.h"

/*Macro and defines*/
#define LINE_NUM 4
/*Global parameters*/
static button_t menuLines[LINE_NUM];
static button_t checkBox[LINE_NUM];
static uint8_t firstEl;
relay_enable_t tempEnable;
/*Local prototypes*/
static void createFrame(uint8_t *text);
static void RefreshScrollBar(void);
static void calcButParam();
static void markLine(uint8_t i);
void drawLine(uint8_t num, uint8_t * string, uint16_t time, bool touch);
/*Code*/
uint8_t ShowOutputEnableChoice(uint8_t* text, relay_t* relay){
	tempEnable = relay->pozEnable;
	firstEl = 0;
	createFrame(text);
	while(1) {
		if(goHome){
			return -1;
		}
		if(updateFlags.sec == true) {
			updateFlags.sec = false;
		}
		if(okBut.isReleased == true) {
			okBut.isReleased = false;
			relay->pozEnable = tempEnable;
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
		if(scrollUpBut.isReleased == true) {
			if(firstEl > 0) {
				firstEl--;
				RefreshScrollBar();
			}
			scrollUpBut.isReleased = false;
		}
		if(scrollDwnBut.isReleased == true) {
			if(firstEl < (sizeof(piston_poz_t)/sizeof(uint32_t)) - 4) {
				firstEl++;
				RefreshScrollBar();
			}
			scrollDwnBut.isReleased = false;
		}
		for (uint8_t i = 0; i < LINE_NUM; i++){
			if(checkBox[i].isPressed == true) {
				//Make it blue
				uint8_t* ptr = &tempEnable;
				uint8_t tempResult = *ptr  ^ (0x01 << (i + firstEl));
				*ptr = tempResult;
				markLine(i);
				checkBox[i].isPressed = false;
			}
			
		}
		
	}
}


/* Private user code ---------------------------------------------------------*/
void createFrame(uint8_t *text) {
	TC_clearButtons();
	//BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, text);
	drawStatusBarOkCancel();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	for(uint8_t i = 0; i < 4; i++) {
		menuLines[i].x = FIRST_CURSOR_POS_X + 9;
		menuLines[i].y = STATIC_LINE_Y + i * STATIC_LINE_SPASER + 9;
		//menuLine[i].xSize = 250;
		menuLines[i].ySize = 40;
	}
	calcButParam();
	RefreshScrollBar();
	/*Add buttons parameters*/
}

void markLine(uint8_t i) {
	bool checked;
	char *status;
	
	uint8_t* ptr = &tempEnable;
	bool tempResult = *ptr  & (0x01 << (i + firstEl));
	checked = (tempResult) ? true : false;
	status = (tempResult) ? "X" : "";
	checkBox[i] = drawFillButton(checkBox[i].x, checkBox[i] .y, checkBox[i].xSize, checkBox[i].ySize, status, checked);
	
}

void RefreshScrollBar(void) {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	drawMainWindow();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	WTC_FONT_t *oldFont = BSP_LCD_GetFont();
	BSP_LCD_SetFont( &Oxygen_Mono_20);
	for(uint8_t i = 0; i < LINE_NUM; i++) {
		int8_t pozNum = i + firstEl;
		if (pozNum == 4) pozNum = 5;
		if (pozNum == 3){
			menuLines[i].xSize = 18 + BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + STATIC_LINE_SPASER * i + 18, ITEM_STEPS[pozNum+1], LEFT_MODE);
			menuLines[i].xSize = 18 + BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + STATIC_LINE_SPASER * i , ITEM_STEPS[pozNum], LEFT_MODE);
			
		} else {
			menuLines[i].xSize = 18 + BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + STATIC_LINE_SPASER * i + 3, ITEM_STEPS[pozNum], LEFT_MODE);
		}
		//menuLines[i].xSize = 18 + BSP_LCD_DisplayStringAt(menuLines[i].x, menuLines[i].y, ITEM_STEPS[i + firstEl], LEFT_MODE);
		markLine(i);
	}
	drawScrollButton(0);
	BSP_LCD_SetFont(oldFont);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	
	drawStaticLines();
	
}

void calcButParam() {
	TC_clearButtons();
	for(uint8_t i = 0; i < LINE_NUM; i++) {
		checkBox[i].x = SCROLLKEYUP_POS_X - 5 - 40;
		checkBox[i].y = STATIC_LINE_Y + STATIC_LINE_SPASER * i + 3;
		checkBox[i].xSize = 40;
		checkBox[i].ySize = 40;
		TC_addButton(&checkBox[i]);
	}
	TC_addButton(&okBut);
	TC_addButton(&cancelBut);
	TC_addButton(&retBut);
	TC_addButton(&homeBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
}