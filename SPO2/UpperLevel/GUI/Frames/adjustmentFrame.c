/*Includes*/
#include "adjustmentFrame.h"

/*Macro and defines*/
#define LINE_NUM 5
/*Global parameters*/
static button_t menuLines[LINE_NUM];
static button_t playBut[LINE_NUM];
static uint8_t firstEl;

/*Local prototypes*/
static void createFrame(uint8_t *text);
static void RefreshScrollBar(void);
static void calcButParam();
static void markLine(uint8_t i);
void drawLine(uint8_t num, uint8_t * string, uint16_t time, bool touch);
uint32_t *pozPtr;
piston_poz_t tempPoz;

/*Code*/
uint8_t ShowAdjustmentFrame(){
	
	PC_Restart();
	tempPoz = sysParams.consts.pistonPositions;
	firstEl = 0;
	pozPtr = &tempPoz;
	createFrame(MODE_ADJUSTMENT);
	while(1) {
		if(goHome){
			 PC_GoToPoz(sysParams.consts.pistonPositions.rabPoz);
			return -1;
		}
		if(updateFlags.sec == true) {
			updateFlags.sec = false;
		}
		if(okBut.isReleased == true) {
			okBut.isReleased = false;
			sysParams.consts.pistonPositions = tempPoz;
			FP_SaveParam();
			 PC_GoToPoz(sysParams.consts.pistonPositions.rabPoz);
			return 0;
		}
		if(cancelBut.isReleased == true) {
			 PC_GoToPoz(sysParams.consts.pistonPositions.rabPoz);
			cancelBut.isReleased = false;
			return 0;
		}
		if(retBut.isReleased == true) {
			 PC_GoToPoz(sysParams.consts.pistonPositions.rabPoz);
			retBut.isReleased = false;
			return 0;
		}
		if(homeBut.isReleased == true) {
			homeBut.isReleased = false;
			 PC_GoToPoz(sysParams.consts.pistonPositions.rabPoz);
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
			if(playBut[i+firstEl].isReleased == true) {
				PC_GoToPoz(*(pozPtr+i+firstEl));
				//Make it blue
//				uint8_t* ptr = &tempEnable;
//				uint8_t tempResult = *ptr  ^ (0x01 << (i + firstEl));
//				*ptr = tempResult;
//				markLine(i);
				playBut[i+firstEl].isReleased = false;
			}
			if (menuLines[i+firstEl].isReleased == true){
				int32_t temp = ShowKeyboardFrame(0, 999);
				if (temp >= 0){
					*(pozPtr+i+firstEl) = temp;
				}
				menuLines[i+firstEl].isReleased = false;
				createFrame(MODE_ADJUSTMENT);
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
//	for(uint8_t i = 0; i < 4; i++) {
//		menuLines[i].x = FIRST_CURSOR_POS_X + 9;
//		menuLines[i].y = STATIC_LINE_Y + i * STATIC_LINE_SPASER + 9;
//		//menuLine[i].xSize = 250;
//		menuLines[i].ySize = 40;
//	}
	
	RefreshScrollBar();
	/*Add buttons parameters*/
}


void RefreshScrollBar(void) {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	calcButParam();
	drawMainWindow();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	WTC_FONT_t *oldFont = BSP_LCD_GetFont();
	BSP_LCD_SetFont( &Oxygen_Mono_20);
	for(uint8_t i = 0; i < 4; i++) {
		int8_t pozNum = i + firstEl;
		if (pozNum == 4) pozNum = 5;
		if (pozNum == 3){
			BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + STATIC_LINE_SPASER * i + 18, ITEM_STEPS[pozNum+1], LEFT_MODE);
			BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + STATIC_LINE_SPASER * i , ITEM_STEPS[pozNum], LEFT_MODE);
			
		} else {
			BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + STATIC_LINE_SPASER * i + 3, ITEM_STEPS[pozNum], LEFT_MODE);
		}
		//BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + i * STATIC_LINE_SPASER + 9, ITEM_STEPS[i + firstEl], LEFT_MODE);
		drawFillButton(menuLines[i + firstEl].x,menuLines[i + firstEl].y,menuLines[i + firstEl].xSize,menuLines[i + firstEl].ySize,intToStr(*(pozPtr + i + firstEl)),false);
		drawFillButton(playBut[i + firstEl].x,playBut[i + firstEl].y,playBut[i + firstEl].xSize,playBut[i + firstEl].ySize,"GO",false);
	}
	drawScrollButton(0);
	BSP_LCD_SetFont(oldFont);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	
	drawStaticLines();
	
}

void calcButParam() {
	TC_clearButtons();
	for(uint8_t i = 0; i < 4; i++) {
		menuLines[i + firstEl].x = SCROLLKEYUP_POS_X - 5 - 40 - 90;
		menuLines[i + firstEl].y = STATIC_LINE_Y + i * STATIC_LINE_SPASER + 3;
		menuLines[i + firstEl].xSize = 80;
		menuLines[i + firstEl].ySize = 40;
		
		playBut[i + firstEl].x = SCROLLKEYUP_POS_X - 5 - 40;
		playBut[i + firstEl].y = STATIC_LINE_Y + STATIC_LINE_SPASER * i + 3;
		playBut[i + firstEl].xSize = 40;
		playBut[i + firstEl].ySize = 40;
		TC_addButton(&playBut[i + firstEl]);
		TC_addButton(&menuLines[i + firstEl]);
	}
	TC_addButton(&okBut);
	TC_addButton(&cancelBut);
	TC_addButton(&retBut);
	TC_addButton(&homeBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
}