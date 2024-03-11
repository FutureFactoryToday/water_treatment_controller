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
static uint8_t stepNum;
//static button_t menuLines[STEP_PER_TASK_NUM-1];
static button_t delMenuLines[STEP_PER_TASK_NUM-1];
static button_t lineTime[STEP_PER_TASK_NUM-1];
static button_t addLine;
static uint8_t scroll_cnt;
/* Private function prototypes -----------------------------------------------*/
static void createFrame();
static void RefreshScrollBar(void);
static void calcButParam();
static int8_t getPPStep(uint32_t* poz);
/* Private user code ---------------------------------------------------------*/
void ShowManualFilterSettings(){
	
	tempTask = planner.pistonTasks[MAN_TASK_NUM];

    while(tempTask.step[stepNum].poz != NULL)
    {
        stepNum++;
    }
	scroll_cnt = 0;
	createFrame();
	
	while (1){
         if (updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
         }
         /*Buttons pressed*/         
         if (addLine.isPressed == true){
             if (stepNum < 7){
                 //uint8_t line = (stepNum < 4)? stepNum: stepNum%4;
                 drawFillButton(SCROLLBAR_POS_X - 51, 124 ,40, 83, "+", true);
                 addLine.isPressed = false;
             }
         }
         for (uint8_t i = 0; i < stepNum && i < 4 ; i++){
             if(lineTime[i].isPressed == true){
                  drawDarkTextLabel(4*GAP + 118, STATIC_LINE_Y + STATIC_LINE_SPASER*i + 3, 80, 39, intToStr(tempTask.step[scroll_cnt + i].secPause / 60));                 
                  lineTime[i].isPressed = false;
             }
         }
         if(scrollUpBut.isPressed == true){
                //Make it blue
            scrollUpBut.isPressed = false;
         }
         if(scrollDwnBut.isPressed == true){
                //Make it blue
            scrollDwnBut.isPressed = false;
         }
         /*Buttons released*/
         if(okBut.isReleased == true){
            okBut.isReleased = false;

            planner.pistonTasks[MAN_TASK_NUM] = tempTask;
            fp->params.planner.pistonTasks[MAN_TASK_NUM] = planner.pistonTasks[MAN_TASK_NUM];
			fp->needToSave = 1;
			FP_SaveParam();
			return;
		 }
         if (retBut.isReleased == true){
            retBut.isReleased = false;
            return;
         }
         if (addLine.isReleased == true){
             if (stepNum < 7){
                 drawFillButton(SCROLLBAR_POS_X - 51, 124 ,40, 83, "+", false);
                 
                 task_line_t _tl;
                 _tl.poz = ShowStepsFrame();
                 _tl.secPause = 300;
                 if(PL_addTaskLine(&tempTask, _tl))
                 {
                    copyTasksToFlash();
                    stepNum++;
                 }
                 addLine.isReleased = false;
                 createFrame();
            }
         }
         for (uint8_t i = 0; i < stepNum && i < 4 ; i++){
             if(lineTime[i].isReleased == true){
                 uint8_t tempRes = ShowKeyboardFrame(1,150);
                 if (tempRes > 0){
                     tempTask.step[scroll_cnt + i].secPause = tempRes * 60;
                 }
                 lineTime[i].isReleased = false;
                 createFrame();
             }
         }
         for (uint8_t i = 0; i < stepNum && i < 4 ; i++){
             if (delMenuLines[i].isReleased == true){
                if(PL_deleteTaskLine(&tempTask, scroll_cnt + i))
                {
                    stepNum--;
                    if(scroll_cnt > 0) scroll_cnt--;
                }
                delMenuLines[i].isReleased = false;
                createFrame();
             }
         }
         if(scrollUpBut.isReleased == true){
            if(scroll_cnt > 0) scroll_cnt--;
            RefreshScrollBar();
            scrollUpBut.isReleased = false;
         }
         if(scrollDwnBut.isReleased == true){
            if(scroll_cnt < 3) scroll_cnt++;
            RefreshScrollBar();
            scrollDwnBut.isReleased = false;
         } 
	}
}


void createFrame(){
	TC_clearButtons();

	BSP_LCD_Clear(LCD_COLOR_WHITE);
	
	drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_MANUAL_SETTINGS[0]);
	
    drawStatusBarOkCancel();
	
	drawClock();
    	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	RefreshScrollBar();
    /*Add buttons parameters*/
    calcButParam();
}


void RefreshScrollBar(void)
{
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(FIRST_CURSOR_POS_X + 9, STATIC_LINE_Y + 3, 320, 177);
	if (stepNum > 4){
		drawScrollButton(scroll_cnt == 0 ? 0 : (scroll_cnt == (stepNum - 4) ? 2 : 1));
	}
	for(uint8_t i = 0; i < stepNum && i < 4; i++){
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
		BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,STATIC_LINE_Y + STATIC_LINE_SPASER*i + 3,ITEM_STEPS[getPPStep(tempTask.step[scroll_cnt + i].poz)],LEFT_MODE);
		lineTime[i] = drawTextLabel(4*GAP + 118, STATIC_LINE_Y + STATIC_LINE_SPASER*i + 3, 80, 39, intToStr(tempTask.step[scroll_cnt + i].secPause / 60));
        delMenuLines[i] = drawFillButton(SCROLLBAR_POS_X - 101,STATIC_LINE_Y + STATIC_LINE_SPASER*i + 3, 40, 40, "-", false);
	}
    if (stepNum < 7){
        addLine = drawFillButton(SCROLLBAR_POS_X - 51, 125 ,40, 83, "+", false);
    }
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    
	drawStaticLines();
}

void calcButParam(){
	TC_clearButtons();
    
	for (uint8_t i = 0; i < scroll_cnt + 4; i++){
		TC_addButton(&delMenuLines[i]);
	}
    for (uint8_t i = 0; i < scroll_cnt + 4; i++){
		TC_addButton(&lineTime[i]);
	}
	TC_addButton(&addLine);
    TC_addButton(&okBut);
	TC_addButton(&retBut);
	if (stepNum > 4){
		TC_addButton(&scrollUpBut);
		TC_addButton(&scrollDwnBut);
	}
}

int8_t getPPStep(uint32_t* poz){
	uint32_t* ptr = &pistonPositions;
	uint8_t end = sizeof(pistonPositions)/sizeof(uint32_t);
	for(uint8_t i = 0; i < end; i++){
		if (ptr == poz){
			return i;
		}
		ptr++;
	}
	return -1;
}

button_t drawDelButton(uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label, bool isTouch){
	button_t but = drawFillButton(xPos, yPos, xSize, ySize,  label, isTouch);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(xPos + 3, yPos  + ySize/2 - 3,xSize - 6, 6);  
	BSP_LCD_FillRect(xPos + xSize/2 - 3, yPos - 3,6, ySize - 6);
}

button_t drawAddButton(uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label, bool isTouch){
	button_t but = drawFillButton(xPos, yPos, xSize, ySize,  label, isTouch);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(xPos + 3, yPos  + ySize/2 - 3,xSize - 6, 6); 
}