/**
 ******************************************************************************
 * @file           : ManualFilteringSettings.c
 * @brief          : 
 ******************************************************************************
 * @attention
 *
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ManualFilteringSettings.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define STEP_PER_TASK_NUM 10
//typedef struct {
//	task_line_t step[STEP_PER_TASK_NUM];
//	wtc_time_t restartDateTime;                //дни между регенерациями
//	wtc_time_t startDateTime;                   //время первого запуска
//} piston_task_t;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static piston_task_t tempTask;
static button_t menuLines[4];
static button_t delMenuLines[4];
static button_t lineTime[4];
static button_t addLine;
static uint8_t scroll_cnt;
static uint8_t firstEl, taskSize;
static bool modif;
/* Private function prototypes -----------------------------------------------*/
static void createFrame();
static void RefreshScrollBar(void);
static void calcButParam();
void drawLine(uint8_t num, uint8_t * string, uint16_t time, bool touch);
button_t drawEmptyLine(uint8_t num, bool touch);
/* Private user code ---------------------------------------------------------*/
int ShowManualFilterSettings(piston_task_t baseTask, bool modable) {
	firstEl = 0;
	taskSize = 0;
	tempTask = baseTask;
	modif = modable;
	while(tempTask.step[taskSize].poz != NULL) {
		taskSize++;
	}
	createFrame();
	while(1) {
		if(updateFlags.sec == true) {
			updateFlags.sec = false;
		}
		if(scrollUpBut.isPressed == true) {
			//Make it blue
			scrollUpBut.isPressed = false;
		}
		if(scrollDwnBut.isPressed == true) {
			//Make it blue
			scrollDwnBut.isPressed = false;
		}
		/*Buttons released*/
		if(okBut.isReleased == true) {
			okBut.isReleased = false;
			baseTask = tempTask;
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
		if(goHome) {
			return -1;
		}
		if(modif == true) {
			if(addLine.isReleased == true) {
				if(taskSize < STEP_PER_TASK_NUM) {
					task_line_t _tl;
					_tl.poz = ShowStepsFrame();
					_tl.secPause = 0;
					if(PL_addTaskLine( & tempTask, _tl)) {
						taskSize++;
					}
					addLine.isReleased = false;
					createFrame();
				}
			}
			for(uint8_t i = 0; i < (taskSize - firstEl) && i < 4; i++) {
				if(menuLines[i].isReleased == true) {
					task_line_t _tl = tempTask.step[i + firstEl];
					_tl.poz = ShowStepsFrame();
					PL_modTaskLine( & tempTask, i + firstEl, _tl);
					menuLines[i].isReleased = false;
					createFrame();
				}
			}
		}
		for(uint8_t i = 0; i < (taskSize - firstEl) && i < 4; i++) {
			if(lineTime[i].isReleased == true) {
				int32_t tempRes = ShowKeyboardFrame(0, 999);
				if(tempRes >= 0) {
					tempTask.step[i + firstEl].secPause = tempRes * 60;
				}
				lineTime[i].isReleased = false;
				createFrame();
			}
		}
		if(modif == true) {
			for(uint8_t i = 0; i < (taskSize - firstEl) && i < 4; i++) {
				if(delMenuLines[i].isReleased == true) {
					if(PL_deleteTaskLine( & tempTask, i + firstEl)) {
						taskSize--;
					}
					delMenuLines[i].isReleased = false;
					createFrame();
				}
			}
		}
		if(scrollUpBut.isReleased == true) {
			if(firstEl > 0) {
				firstEl--;
				RefreshScrollBar();
			}
			scrollUpBut.isReleased = false;
		}
		if(scrollDwnBut.isReleased == true) {
			if(firstEl < 4) {
				firstEl++;
				RefreshScrollBar();
			}
			scrollDwnBut.isReleased = false;
		}
	}
}
void createFrame() {
	TC_clearButtons();
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_MANUAL_SETTINGS[0]);
	drawStatusBarOkCancel();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	RefreshScrollBar();
	/*Add buttons parameters*/
}
void RefreshScrollBar(void) {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	drawMainWindow();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	WTC_FONT_t * oldFont = BSP_LCD_GetFont();
	BSP_LCD_SetFont( & Oxygen_Mono_20);
	for(uint8_t i = 0; i < 4; i++) {
		if(i < taskSize - firstEl) {
			uint8_t step = firstEl + i;
			drawLine(i, ITEM_STEPS[PC_pozNum(tempTask.step[step].poz)], tempTask.step[step].secPause, false);
		} else {
			if(taskSize < STEP_PER_TASK_NUM) {
				drawEmptyLine(i, modif);
			}
			break;
		}
	}
	drawScrollButton(0);
	BSP_LCD_SetFont(oldFont);
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	drawStaticLines();
	calcButParam();
}
#define SEC_COL 290
#define THIRD_COL SEC_COL + 80
void drawLine(uint8_t num, uint8_t * string, uint16_t time, bool touch) {
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + STATIC_LINE_SPASER * num + 3, string, LEFT_MODE);
	menuLines[num] = (button_t) {
		FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + STATIC_LINE_SPASER * num + 3, 200, STATIC_LINE_SPASER
	};
	lineTime[num] = drawTextLabel(SEC_COL, STATIC_LINE_Y + STATIC_LINE_SPASER * num + 3, 80, 39, intToStr(time / 60));
	delMenuLines[num] = drawFillButton(THIRD_COL, STATIC_LINE_Y + STATIC_LINE_SPASER * num + 3, 40, 40, "-", false);
}
button_t drawEmptyLine(uint8_t num, bool touch) {
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	if(modif == true) {
		BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + STATIC_LINE_SPASER * num + 3, ITEM_MANUAL_SETTINGS[1], LEFT_MODE);
	}
	addLine.x = FIRST_CURSOR_POS_X + 9;
	addLine.y = STATIC_LINE_Y + STATIC_LINE_SPASER * num + 3;
	addLine.xSize = 200;
	addLine.ySize = STATIC_LINE_SPASER;
}
void calcButParam() {
	TC_clearButtons();
	for(uint8_t i = 0; i < (taskSize - firstEl) && i < 4; i++) {
		TC_addButton( & lineTime[i]);
		if(modif == true) {
			TC_addButton( & delMenuLines[i]);
			TC_addButton( & menuLines[i]);
		}
	}
	if(taskSize - firstEl < 4) {
		if(modif == true) {
			TC_addButton( & addLine);
		}
	}
	TC_addButton( & okBut);
	TC_addButton( & cancelBut);
	TC_addButton( & retBut);
	TC_addButton( & homeBut);
	if(taskSize > 3) {
		TC_addButton( & scrollUpBut);
		TC_addButton( & scrollDwnBut);
	}
}
button_t drawDelButton(uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t * label, bool isTouch) {
	button_t but = drawFillButton(xPos, yPos, xSize, ySize, label, isTouch);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(xPos + 3, yPos + ySize / 2 - 3, xSize - 6, 6);
	BSP_LCD_FillRect(xPos + xSize / 2 - 3, yPos - 3, 6, ySize - 6);
}
button_t drawAddButton(uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t * label, bool isTouch) {
	button_t but = drawFillButton(xPos, yPos, xSize, ySize, label, isTouch);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(xPos + 3, yPos + ySize / 2 - 3, xSize - 6, 6);
}