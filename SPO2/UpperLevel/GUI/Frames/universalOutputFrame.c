#include "universalOutputFrame.h"
uint8_t universal_Output_Scroll_cnt = 0;
uint8_t universal_Output_frame_was_Scroll = 0;
int8_t hwndUniversalOutputFrameControl = 0;
int8_t startUniversalOutputFrame = 0;

static button_t menuLines[5]; 
static void createFrame();
static void calcButParam();

int ShowUniversalOutputFrame(void)
{
    universal_Output_Scroll_cnt = 0;
		/*Static create*/
		createFrame();
    while(1)
    {
		 if(updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
         }
			/*Buttons pressed*/
         if(retBut.isPressed == true){
            retBut.isPressed = false;
         }
         if(menuLines[0].isPressed == true){
                //Make it blue
                drawFillArcRec(menuLines[0].x, menuLines[0].y, menuLines[0].xSize, menuLines[0].ySize, LCD_COLOR_BLUE);
                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[0].y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[0],LEFT_MODE);
                menuLines[0].isPressed = false;
         }
         if(menuLines[1].isPressed == true){
                //Make it blue
                drawFillArcRec(menuLines[1].x, menuLines[1].y, menuLines[1].xSize, menuLines[1].ySize, LCD_COLOR_BLUE);
                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[1].y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[1],LEFT_MODE);
                menuLines[1].isPressed = false;
         }
         if(menuLines[2].isPressed == true){
                //Make it blue
                drawFillArcRec(menuLines[2].x, menuLines[2].y, menuLines[2].xSize, menuLines[2].ySize, LCD_COLOR_BLUE);
                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[2].y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[2],LEFT_MODE);
                menuLines[2].isPressed = false;
         }
         if(menuLines[3].isPressed == true){
                //Make it blue
                drawFillArcRec(menuLines[3].x, menuLines[3].y, menuLines[3].xSize, menuLines[3].ySize, LCD_COLOR_BLUE);
                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[3].y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[3],LEFT_MODE);
                menuLines[3].isPressed = false;
         }
//         if(menuLines[4].isPressed == true){
//                //Make it blue
//                drawFillArcRec(menuLines[4].x, menuLines[4].y, menuLines[4].xSize, menuLines[4].ySize, LCD_COLOR_BLUE);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[4].y + 9,ITEM_MENU[4],LEFT_MODE);
//                menuLines[4].isPressed = false;
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
             return 0;
         }
         if (homeBut.isReleased == true){
             homeBut.isReleased = false;
             return 1;
         }
         if(menuLines[0].isReleased == true){
                //if(TSF_showFrame() == 1) return 1;
                menuLines[0].isReleased = false;
                createFrame();
         }
         if(menuLines[1].isReleased == true){
                //if(ShowWashTimCustFrame() == 1) return 1;
                menuLines[1].isReleased = false;
                createFrame();
         }
         if(menuLines[2].isReleased == true){
                //if(ShowPeriodRegenCustFrame() == 1) return 1;
                menuLines[2].isReleased = false;
                createFrame();
         }
         if(menuLines[3].isReleased == true){
                //if(ShowFilterCycleCustFrame() == 1) return 1;
                menuLines[3].isReleased = false;
                createFrame();
         }
//         if(menuLines[4].isReleased == true){
//                ShowRegenPeriodServiceFrame();
//                menuLines[4].isReleased = false;
//                createFrame();
//         }
//         if(scrollUpBut.isReleased == true){
//                if(menu_frame_Scroll_cnt > 0){ menu_frame_Scroll_cnt--;
//                    menu_frame_was_Scroll = 1;
//                    RefreshScrollBarMenuFrame();
//                }
//                scrollUpBut.isReleased = false;
//         }
//         if(scrollDwnBut.isReleased == true){
//                if(menu_frame_Scroll_cnt < 1){ menu_frame_Scroll_cnt++;
//                    menu_frame_was_Scroll = 2;
//                    RefreshScrollBarMenuFrame();
//                }
//                scrollDwnBut.isReleased = false;
//         }   
	}
}
void createFrame(void){
    
    drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, ITEM_UNIVERSAL_OUTPUT_FRAME[4]);
    
    drawMainWindow();
    
    //drawScrollButton(menu_frame_Scroll_cnt == 0 ? 0 : (menu_frame_Scroll_cnt == 1 ? 2 : 1));
    
    //drawStatusBarEmpty();
    drawMainStatusBar(144, 2305, 16);
    
    drawClock();
    
    drawStaticLines();
    
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[universal_Output_Scroll_cnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[universal_Output_Scroll_cnt + 1],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[universal_Output_Scroll_cnt + 2],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[universal_Output_Scroll_cnt + 3],LEFT_MODE);
  
	/*Add buttons parameters*/
    calcButParam();
}

//void RefreshScrollBarMenuFrame()
//{       
//    if(universal_Output_frame_was_Scroll == 1 || universal_Output_frame_was_Scroll == 2){
//        calcButParam();
//        
//        drawScrollButton(universal_Output_Scroll_cnt == 0 ? 0 : (universal_Output_Scroll_cnt == 1 ? 2 : 1));
//        
//        drawFillArcRec(menuLines[universal_Output_Scroll_cnt].x, menuLines[universal_Output_Scroll_cnt].y, menuLines[universal_Output_Scroll_cnt].xSize, menuLines[universal_Output_Scroll_cnt].ySize, LCD_COLOR_WHITE);
//        drawFillArcRec(menuLines[universal_Output_Scroll_cnt + 1].x, menuLines[universal_Output_Scroll_cnt + 1].y, menuLines[universal_Output_Scroll_cnt + 1].xSize, menuLines[universal_Output_Scroll_cnt + 1].ySize, LCD_COLOR_WHITE);
//        drawFillArcRec(menuLines[universal_Output_Scroll_cnt + 2].x, menuLines[universal_Output_Scroll_cnt + 2].y, menuLines[universal_Output_Scroll_cnt + 2].xSize, menuLines[universal_Output_Scroll_cnt + 2].ySize, LCD_COLOR_WHITE);
//        drawFillArcRec(menuLines[universal_Output_Scroll_cnt + 3].x, menuLines[universal_Output_Scroll_cnt + 3].y, menuLines[universal_Output_Scroll_cnt + 3].xSize, menuLines[universal_Output_Scroll_cnt + 3].ySize, LCD_COLOR_WHITE);
//        
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[universal_Output_Scroll_cnt],LEFT_MODE);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[universal_Output_Scroll_cnt + 1],LEFT_MODE);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[universal_Output_Scroll_cnt + 2],LEFT_MODE);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_UNIVERSAL_OUTPUT_FRAME[universal_Output_Scroll_cnt + 3],LEFT_MODE);
//        
//        drawStaticLines();
//        
//        universal_Output_frame_was_Scroll = 0;
//    }
//}

void calcButParam()
{
    TC_clearButtons();
   
        //Setting for key "0"
    menuLines[universal_Output_Scroll_cnt].x = FIRST_CURSOR_POS_X;
    menuLines[universal_Output_Scroll_cnt].y = FIRST_CURSOR_POS_Y;
    menuLines[universal_Output_Scroll_cnt].xSize = FIRST_CURSOR_SIZE_X;
    menuLines[universal_Output_Scroll_cnt].ySize = FIRST_CURSOR_SIZE_Y;
		
		//Setting for key "1"
    menuLines[universal_Output_Scroll_cnt + 1].x = SECOND_CURSOR_POS_X;
    menuLines[universal_Output_Scroll_cnt + 1].y = SECOND_CURSOR_POS_Y;
    menuLines[universal_Output_Scroll_cnt + 1].xSize = SECOND_CURSOR_SIZE_X;
    menuLines[universal_Output_Scroll_cnt + 1].ySize = SECOND_CURSOR_SIZE_Y;
    
		//Setting for key "2"
    menuLines[universal_Output_Scroll_cnt + 2].x = THRID_CURSOR_POS_X;
    menuLines[universal_Output_Scroll_cnt + 2].y = THRID_CURSOR_POS_Y;
    menuLines[universal_Output_Scroll_cnt + 2].xSize = THRID_CURSOR_SIZE_X;
    menuLines[universal_Output_Scroll_cnt + 2].ySize = THRID_CURSOR_SIZE_Y;
    
		//Setting for key "3"
    menuLines[universal_Output_Scroll_cnt + 3].x = FOURTH_CURSOR_POS_X;
    menuLines[universal_Output_Scroll_cnt + 3].y = FOURTH_CURSOR_POS_Y;
    menuLines[universal_Output_Scroll_cnt + 3].xSize = FOURTH_CURSOR_SIZE_X;
    menuLines[universal_Output_Scroll_cnt + 3].ySize = FOURTH_CURSOR_SIZE_Y;
    
    for (uint8_t i = universal_Output_Scroll_cnt; i < universal_Output_Scroll_cnt + 4; i++){
			TC_addButton(&menuLines[i]);
	}
	TC_addButton(&retBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
    TC_addButton(&homeBut);
    
}