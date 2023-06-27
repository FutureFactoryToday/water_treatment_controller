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
static button_t menuLines[STEP_PER_TASK_NUM-1];
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
	
	tempTask = pistonTasks[MAN_TASK_NUM];
	tempTask.step[0].poz = &pistonPositions.closedPosition;
	tempTask.step[1].poz = &pistonPositions.backwash;
	tempTask.step[2].poz = &pistonPositions.closedPosition;
	tempTask.step[3].poz = &pistonPositions.backwash;
	tempTask.step[4].poz = &pistonPositions.closedPosition;
	tempTask.step[5].poz = &pistonPositions.backwash;
	tempTask.step[0].secPause = 10;
	tempTask.step[1].secPause = 5;
	tempTask.step[2].secPause = 10;
	tempTask.step[3].secPause = 5;
	tempTask.step[4].secPause = 10;
	tempTask.step[5].secPause = 5;
	stepNum = 6;
//	if (tempTask == NULL){
//		stepNum = 0;
//	} else {
//		stepNum = sizeof(
//	}
	scroll_cnt = 0;
	createFrame();
	
	while (1){
					/*Buttons pressed*/
         if(retBut.isReleased == true){
             
            retBut.isReleased = false;
            return;
         }
				 if (addLine.isReleased == true){
					 //!!!!!!!!//
					 addLine.isReleased = false;
				 }
				 
				 if (addLine.isPressed == true){
					 uint8_t line = (stepNum < 4)? stepNum: stepNum%4;
					 drawFillButton(FIRST_CURSOR_POS_X + GAP,STATIC_LINE_Y + STATIC_LINE_SPASER*line + 2 , 200, 40, ITEM_MANUAL_SETTINGS[1], true);
					 addLine.isPressed = false;
				 }
				 for (uint8_t i = 0; i < stepNum ; i++){
					 if(lineTime[i].isPressed == true){
							drawDarkTextLabel(lineTime[i].x, lineTime[i].y, lineTime[i].xSize, lineTime[i].ySize, ITEM_STEPS[getPPStep(tempTask.step[i].poz)]);				 
						  lineTime[i].isPressed = false;
					 }
						
				 }
//         if(menuLines[0].isPressed == true){
//                //Make it blue
//            drawFillArcRec(menuLines[0].x, menuLines[0].y, menuLines[0].xSize, menuLines[0].ySize, LCD_COLOR_BLUE);
//            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[0].y + 9,ITEM_SERVICE_MENU[0],LEFT_MODE);
//            menuLines[0].isPressed = false;
//         }
//         if(menuLines[1].isPressed == true){
//                //Make it blue
//            drawFillArcRec(menuLines[1].x, menuLines[1].y, menuLines[1].xSize, menuLines[1].ySize, LCD_COLOR_BLUE);
//            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[1].y + 9,ITEM_SERVICE_MENU[1],LEFT_MODE);
//            menuLines[1].isPressed = false;
//         }
//         if(menuLines[2].isPressed == true){
//                //Make it blue
//            drawFillArcRec(menuLines[3].x, menuLines[2].y, menuLines[2].xSize, menuLines[2].ySize, LCD_COLOR_BLUE);
//            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[2].y + 9,ITEM_SERVICE_MENU[2],LEFT_MODE);
//            menuLines[2].isPressed = false;
//         }
//         if(menuLines[3].isPressed == true){
//                //Make it blue
//            drawFillArcRec(menuLines[3].x, menuLines[3].y, menuLines[3].xSize, menuLines[3].ySize, LCD_COLOR_BLUE);
//            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[3].y + 9,ITEM_SERVICE_MENU[3],LEFT_MODE);
//            menuLines[3].isPressed = false;
//         }
//         if(menuLines[4].isPressed == true){
//                //Make it blue
//            drawFillArcRec(menuLines[4].x, menuLines[4].y, menuLines[4].xSize, menuLines[4].ySize, LCD_COLOR_BLUE);
//            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[4].y + 9,ITEM_SERVICE_MENU[4],LEFT_MODE);
//            menuLines[4].isPressed = false;
//         }
//         if(menuLines[5].isPressed == true){
//                //Make it blue
//            drawFillArcRec(menuLines[5].x, menuLines[5].y, menuLines[5].xSize, menuLines[5].ySize, LCD_COLOR_BLUE);
//            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[5].y + 9,ITEM_SERVICE_MENU[5],LEFT_MODE);
//            menuLines[5].isPressed = false;
//         }
//         if(menuLines[6].isPressed == true){
//                //Make it blue
//            drawFillArcRec(menuLines[6].x, menuLines[6].y, menuLines[6].xSize, menuLines[6].ySize, LCD_COLOR_BLUE);
//            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//            BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[6].y + 9,ITEM_SERVICE_MENU[6],LEFT_MODE);
//            menuLines[6].isPressed = false;
//         }
         if(scrollUpBut.isPressed == true){
                //Make it blue
            scrollUpBut.isPressed = false;
         }
         if(scrollDwnBut.isPressed == true){
                //Make it blue
            scrollDwnBut.isPressed = false;
         }
        /*Buttons released*/
         if (retBut.isReleased == true){
            retBut.isReleased = false;
            return;
         }
//         if(menuLines[0].isReleased == true){
//            ShowFilterSelectionFrame();
//            menuLines[0].isReleased = false;
//            createFrame();
//         }
//         if(menuLines[1].isReleased == true){
//            ShowRegenPeriodServiceFrame(); 
//            menuLines[1].isReleased = false;
//            createFrame();
//         }
//         if(menuLines[2].isReleased == true){
//            ShowWashingTimeServiceFrame();
//            menuLines[2].isReleased = false;
//            createFrame();
//         }
//         if(menuLines[3].isReleased == true){
//            ShowQuantityCountServiceFrame();
//            menuLines[3].isReleased = false;
//            createFrame();
//         }
//         if(menuLines[4].isReleased == true){
//            ShowRegenServiceFrame();
//            menuLines[4].isReleased = false;
//            createFrame();
//         }
//         if(menuLines[5].isReleased == true){
//            ShowAdjustmentFrame();               
//            menuLines[5].isReleased = false;
//            createFrame();
//         }
//         if(menuLines[6].isReleased == true){
//            ShowAlarmNotiServiceFrame();   
//            menuLines[6].isReleased = false;
//            createFrame();
//         }
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
	
	drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_MANUAL_SETTINGS[0]);
	
	drawStatusBarEmpty();
	
	drawClock();
    	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	
	RefreshScrollBar();
	
//	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt],LEFT_MODE);
//	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 1],LEFT_MODE);
//	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 2],LEFT_MODE);
//	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_SERVICE_MENU[service_menu_frame_Scroll_cnt + 3],LEFT_MODE);
//    
//	/*Add buttons parameters*/
//	calcButParam();
//	/*Add buttons to Touch Controller*/
//	for (uint8_t i = 0; i < sizeof(menuLines[0]); i++){
//			TC_addButton(&menuLines[i]);
//	}
	TC_addButton(&retBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
//	
//	enableClockDraw = true;
}


void RefreshScrollBar(void)
{
	calcButParam();
	
	if (stepNum > 4){
		drawScrollButton(scroll_cnt == 0 ? 0 : (scroll_cnt == 3 ? 2 : 1));
	}
	for(uint8_t i = 0; i < stepNum && i < 4; i++){
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		drawFillArcRec(menuLines[scroll_cnt + i].x, menuLines[scroll_cnt + i].y, menuLines[scroll_cnt + i].xSize, menuLines[scroll_cnt + i].ySize, LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,STATIC_LINE_Y + STATIC_LINE_SPASER*i + 9,ITEM_STEPS[getPPStep(tempTask.step[i].poz)],LEFT_MODE);
		delMenuLines[scroll_cnt + i] = drawFillButton(SCROLLBAR_POS_X - 50,STATIC_LINE_Y + STATIC_LINE_SPASER*i + 2, 40, 40, "", false);
		lineTime[i] = drawTextLabel(FIRST_CURSOR_POS_X + 2*GAP + 200, STATIC_LINE_Y + STATIC_LINE_SPASER*i + 9, 100, 40, intToStr(tempTask.step[i].secPause));
	}
  if (stepNum < scroll_cnt + 4){
		uint8_t line = (stepNum < 4)? stepNum: stepNum%4;
		addLine = drawFillButton(FIRST_CURSOR_POS_X + GAP,STATIC_LINE_Y + STATIC_LINE_SPASER*line + 2 , 200, 40, ITEM_MANUAL_SETTINGS[1], false);
	}
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    
	drawStaticLines();
}

void calcButParam(){
	TC_clearButtons();
   
	//Setting for key "0"
	menuLines[scroll_cnt].x = FIRST_CURSOR_POS_X;
	menuLines[scroll_cnt].y = FIRST_CURSOR_POS_Y;
	menuLines[scroll_cnt].xSize = FIRST_CURSOR_SIZE_X;
	menuLines[scroll_cnt].ySize = FIRST_CURSOR_SIZE_Y;
	
	//Setting for key "1"
	menuLines[scroll_cnt + 1].x = SECOND_CURSOR_POS_X;
	menuLines[scroll_cnt + 1].y = SECOND_CURSOR_POS_Y;
	menuLines[scroll_cnt + 1].xSize = SECOND_CURSOR_SIZE_X;
	menuLines[scroll_cnt + 1].ySize = SECOND_CURSOR_SIZE_Y;
	
	//Setting for key "2"
	menuLines[scroll_cnt + 2].x = THRID_CURSOR_POS_X;
	menuLines[scroll_cnt + 2].y = THRID_CURSOR_POS_Y;
	menuLines[scroll_cnt + 2].xSize = THRID_CURSOR_SIZE_X;
	menuLines[scroll_cnt + 2].ySize = THRID_CURSOR_SIZE_Y;
	
	//Setting for key "3"
	menuLines[scroll_cnt + 3].x = FOURTH_CURSOR_POS_X;
	menuLines[scroll_cnt + 3].y = FOURTH_CURSOR_POS_Y;
	menuLines[scroll_cnt + 3].xSize = FOURTH_CURSOR_SIZE_X;
	menuLines[scroll_cnt + 3].ySize = FOURTH_CURSOR_SIZE_Y;
    
	for (uint8_t i = scroll_cnt; i < scroll_cnt + 4; i++){
		//TC_addButton(&menuLines[i]);
		TC_addButton(&delMenuLines[i]);
	}
	TC_addButton(&addLine);
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