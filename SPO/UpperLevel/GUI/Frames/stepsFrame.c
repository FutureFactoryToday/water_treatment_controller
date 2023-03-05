#include "stepsFrame.h"

uint8_t steps_frame_Scroll_cnt = 0;
uint8_t steps_frame_was_Scroll = 0;

int8_t startStepsFrame = 0;

int8_t stepsFrameResult = 0;
int8_t stepResult = -1;

static void createFrame(void);
static void calcButParam();
static button_t menuLines[6];
int8_t ShowStepsFrame(void)
{
	steps_frame_Scroll_cnt = 0;
	startStepsFrame = 1;
	stepsFrameResult = 0;
	stepResult = 0;
	while(1)
	{     
        if(menuLines[0].isPressed == true){
                //Make it blue
           drawFillArcRec(menuLines[0].x, menuLines[0].y, menuLines[0].xSize, menuLines[0].ySize, LCD_COLOR_BLUE);
           BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
           BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
           BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[0].y + 9,ITEM_STEPS[0],LEFT_MODE);
           menuLines[0].isPressed = false;
        }
        if(menuLines[1].isPressed == true){
                //Make it blue
           drawFillArcRec(menuLines[1].x, menuLines[1].y, menuLines[1].xSize, menuLines[1].ySize, LCD_COLOR_BLUE);
           BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
           BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
           BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[1].y + 9,ITEM_STEPS[1],LEFT_MODE);
           menuLines[1].isPressed = false;
        }
        if(menuLines[2].isPressed == true){
                //Make it blue
           drawFillArcRec(menuLines[3].x, menuLines[2].y, menuLines[2].xSize, menuLines[2].ySize, LCD_COLOR_BLUE);
           BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
           BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
           BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[2].y + 9,ITEM_STEPS[2],LEFT_MODE);
           menuLines[2].isPressed = false;
        }
        if(menuLines[3].isPressed == true){
                //Make it blue
           drawFillArcRec(menuLines[3].x, menuLines[3].y, menuLines[3].xSize, menuLines[3].ySize, LCD_COLOR_BLUE);
           BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
           BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
           BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[3].y + 9,ITEM_STEPS[3],LEFT_MODE);
           menuLines[3].isPressed = false;
        }
        if(menuLines[4].isPressed == true){
                //Make it blue
           drawFillArcRec(menuLines[4].x, menuLines[4].y, menuLines[4].xSize, menuLines[4].ySize, LCD_COLOR_BLUE);
           BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
           BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
           BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[4].y + 9,ITEM_STEPS[4],LEFT_MODE);
           menuLines[4].isPressed = false;
        }
        if(menuLines[5].isPressed == true){
                //Make it blue
           drawFillArcRec(menuLines[5].x, menuLines[5].y, menuLines[5].xSize, menuLines[5].ySize, LCD_COLOR_BLUE);
           BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
           BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
           BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[5].y + 9,ITEM_STEPS[5],LEFT_MODE);
           menuLines[5].isPressed = false;
        }
				if(menuLines[6].isPressed == true){
                //Make it blue
           drawFillArcRec(menuLines[6].x, menuLines[6].y, menuLines[6].xSize, menuLines[6].ySize, LCD_COLOR_BLUE);
           BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
           BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
           BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[6].y + 9,ITEM_STEPS[6],LEFT_MODE);
           menuLines[6].isPressed = false;
        }

        
		if(retBut.isReleased == true)
		{
			retBut.isReleased == false;
			return 0;
		}
		if(okBut.isReleased == true)
		{
			okBut.isReleased == false;
			return stepResult;
		}
		if(menuLines[0].isReleased == true)
		{
			stepResult = 1;
			menuLines[0].isReleased = false;
		}
		if(menuLines[1].isReleased == true)
		{
			stepResult = 2;
			menuLines[1].isReleased = false;
		}
		if(menuLines[2].isReleased == true)
		{
			stepResult = 3;
			menuLines[2].isReleased = false;
		}
		if(menuLines[3].isReleased == true)
		{
			stepResult = 4;
			menuLines[3].isReleased = false;
		}
		if(menuLines[4].isReleased == true)
		{
			stepResult = 5;
			menuLines[4].isReleased = false;
		}
		if(menuLines[5].isReleased == true)
		{
			stepResult = 6;
			menuLines[5].isReleased = false;
		}
		if(menuLines[6].isReleased == true)
		{
			stepResult = 7;
			menuLines[6].isReleased = false;
		}
        if(scrollUpBut.isReleased == true){
           if(steps_frame_Scroll_cnt > 0){ steps_frame_Scroll_cnt--;
               steps_frame_was_Scroll = 1;
               RefreshScrollBarStepsFrame();
           }
           scrollUpBut.isReleased = false;
        }
        if(scrollDwnBut.isReleased == true){
           if(steps_frame_Scroll_cnt < 2){ steps_frame_Scroll_cnt++;
               steps_frame_was_Scroll = 2;
               RefreshScrollBarStepsFrame();
           }
           scrollDwnBut.isReleased = false;
        } 
   }
}

void createFrame(void)
{
    drawMainBar(true, SMALL_LOGO_X, SMALL_LOGO_Y, STEPS_LIST);
    
    drawMainWindow();
    
    drawScrollButton(steps_frame_Scroll_cnt == 0 ? 0 : (steps_frame_Scroll_cnt == 2 ? 2 : 1));
    
    drawStatusBarOkCancel();
    
    drawClock();
    
    drawStaticLines();	
	
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 1],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 2],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 3],LEFT_MODE);
    
	/*Add buttons parameters*/
	calcButParam();
	/*Add buttons to Touch Controller*/
//	for (uint8_t i = 0; i < sizeof(menuLines[0]); i++){
//			TC_addButton(&menuLines[i]);
//	}
//	TC_addButton(&retBut);
//	TC_addButton(&scrollUpBut);
//	TC_addButton(&scrollDwnBut);
	
	enableClockDraw = true;
}

void RefreshScrollBarStepsFrame()
{       
    if(steps_frame_was_Scroll == 1 || steps_frame_was_Scroll == 2){
        calcButParam();
    
        drawScrollButton(steps_frame_Scroll_cnt == 0 ? 0 : (steps_frame_Scroll_cnt == 2 ? 2 : 1));
        
        drawFillArcRec(menuLines[steps_frame_Scroll_cnt].x, menuLines[steps_frame_Scroll_cnt].y, menuLines[steps_frame_Scroll_cnt].xSize, menuLines[steps_frame_Scroll_cnt].ySize, LCD_COLOR_WHITE);
        drawFillArcRec(menuLines[steps_frame_Scroll_cnt + 1].x, menuLines[steps_frame_Scroll_cnt + 1].y, menuLines[steps_frame_Scroll_cnt + 1].xSize, menuLines[steps_frame_Scroll_cnt + 1].ySize, LCD_COLOR_WHITE);
        drawFillArcRec(menuLines[steps_frame_Scroll_cnt + 2].x, menuLines[steps_frame_Scroll_cnt + 2].y, menuLines[steps_frame_Scroll_cnt + 2].xSize, menuLines[steps_frame_Scroll_cnt + 2].ySize, LCD_COLOR_WHITE);
        drawFillArcRec(menuLines[steps_frame_Scroll_cnt + 3].x, menuLines[steps_frame_Scroll_cnt + 3].y, menuLines[steps_frame_Scroll_cnt + 3].xSize, menuLines[steps_frame_Scroll_cnt + 3].ySize, LCD_COLOR_WHITE);
        
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt],LEFT_MODE);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 1],LEFT_MODE);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 2],LEFT_MODE);
        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_STEPS[steps_frame_Scroll_cnt + 3],LEFT_MODE);
        
        drawStaticLines();
        
        steps_frame_was_Scroll = 0;
    }
    
}

void calcButParam()
{    
    TC_clearButtons();
   
        //Setting for key "0"
    menuLines[steps_frame_Scroll_cnt].x = FIRST_CURSOR_POS_X;
    menuLines[steps_frame_Scroll_cnt].y = FIRST_CURSOR_POS_Y;
    menuLines[steps_frame_Scroll_cnt].xSize = FIRST_CURSOR_SIZE_X;
    menuLines[steps_frame_Scroll_cnt].ySize = FIRST_CURSOR_SIZE_Y;
		
		//Setting for key "1"
    menuLines[steps_frame_Scroll_cnt + 1].x = SECOND_CURSOR_POS_X;
    menuLines[steps_frame_Scroll_cnt + 1].y = SECOND_CURSOR_POS_Y;
    menuLines[steps_frame_Scroll_cnt + 1].xSize = SECOND_CURSOR_SIZE_X;
    menuLines[steps_frame_Scroll_cnt + 1].ySize = SECOND_CURSOR_SIZE_Y;
    
		//Setting for key "2"
    menuLines[steps_frame_Scroll_cnt + 2].x = THRID_CURSOR_POS_X;
    menuLines[steps_frame_Scroll_cnt + 2].y = THRID_CURSOR_POS_Y;
    menuLines[steps_frame_Scroll_cnt + 2].xSize = THRID_CURSOR_SIZE_X;
    menuLines[steps_frame_Scroll_cnt + 2].ySize = THRID_CURSOR_SIZE_Y;
    
		//Setting for key "3"
    menuLines[steps_frame_Scroll_cnt + 3].x = FOURTH_CURSOR_POS_X;
    menuLines[steps_frame_Scroll_cnt + 3].y = FOURTH_CURSOR_POS_Y;
    menuLines[steps_frame_Scroll_cnt + 3].xSize = FOURTH_CURSOR_SIZE_X;
    menuLines[steps_frame_Scroll_cnt + 3].ySize = FOURTH_CURSOR_SIZE_Y;
    
    for (uint8_t i = steps_frame_Scroll_cnt; i < steps_frame_Scroll_cnt + 4; i++){
			TC_addButton(&menuLines[i]);
	}
	TC_addButton(&retBut);
  TC_addButton(&okBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
}
