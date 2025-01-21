#include "historyGeneralInfoFrame.h"

uint8_t history_general_info_frame_Scroll_cnt = 0;
uint8_t history_general_info_frame_was_Scroll = 0;
int8_t hwndHistoryGeneralInfoFrameControl = 0;
int8_t startHistoryGeneralInfoFrame = 0;

static button_t menuLines[5]; 
static void createFrame();
static void calcButParam();

int ShowHistoryGeneralInfoFrame(void)
{
    history_general_info_frame_Scroll_cnt = 0;
		/*Static create*/
		createFrame();
    while(1)
    {
		 if(updateFlags.sec == true){
            drawClock();
            drawMainStatusBar(144, 2305, 16);
            updateFlags.sec = false;
            sysParams.vars.frameWDTTim = SOFT_WDT_TIM_VAL_DEF; 
         }
			/*Buttons pressed*/
         if(retBut.isPressed == true){
            retBut.isPressed = false;
         }
//         if(menuLines[0].isPressed == true){
//                //Make it blue
//                drawFillArcRec(menuLines[0].x, menuLines[0].y, menuLines[0].xSize, menuLines[0].ySize, LCD_COLOR_BLUE);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[0].y + 9,ITEM_GENERAL_INFO_MENU[0],LEFT_MODE);
//                menuLines[0].isPressed = false;
//         }
//         if(menuLines[1].isPressed == true){
//                //Make it blue
//                drawFillArcRec(menuLines[1].x, menuLines[1].y, menuLines[1].xSize, menuLines[1].ySize, LCD_COLOR_BLUE);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[1].y + 9,ITEM_GENERAL_INFO_MENU[1],LEFT_MODE);
//                menuLines[1].isPressed = false;
//         }
//         if(menuLines[2].isPressed == true){
//                //Make it blue
//                drawFillArcRec(menuLines[2].x, menuLines[2].y, menuLines[2].xSize, menuLines[2].ySize, LCD_COLOR_BLUE);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[2].y + 9,ITEM_GENERAL_INFO_MENU[2],LEFT_MODE);
//                menuLines[2].isPressed = false;
//         }
//         if(menuLines[3].isPressed == true){
//                //Make it blue
//                drawFillArcRec(menuLines[3].x, menuLines[3].y, menuLines[3].xSize, menuLines[3].ySize, LCD_COLOR_BLUE);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[3].y + 9,ITEM_GENERAL_INFO_MENU[3],LEFT_MODE);
//                menuLines[3].isPressed = false;
//         }
//         if(menuLines[4].isPressed == true){
//                //Make it blue
//                drawFillArcRec(menuLines[4].x, menuLines[4].y, menuLines[4].xSize, menuLines[4].ySize, LCD_COLOR_BLUE);
//                BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//                BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,menuLines[4].y + 9,ITEM_GENERAL_INFO_MENU[4],LEFT_MODE);
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
            goHome = true;
         }
		 if (goHome){
			return -1;
		 }
//         if(menuLines[0].isReleased == true){
//                menuLines[0].isReleased = false;
//                createFrame();
//         }
//         if(menuLines[1].isReleased == true){
//                menuLines[1].isReleased = false;
//                createFrame();
//         }
//         if(menuLines[2].isReleased == true){
//                menuLines[2].isReleased = false;
//                createFrame();
//         }
//         if(menuLines[3].isReleased == true){
//                menuLines[3].isReleased = false;
//                createFrame();
//         }
	}
}
void createFrame(void){
    if (goHome) return;
    
    drawMainBar(true, true, SMALL_LOGO_X, SMALL_LOGO_Y, MODE_HISTORY_GENERAL_INFO);
    
    drawMainWindow();
    
    //drawScrollButton(menu_frame_Scroll_cnt == 0 ? 0 : (menu_frame_Scroll_cnt == 1 ? 2 : 1));
    
    drawMainStatusBar(144, 2305, 16);
    //drawStatusBarEmpty();
    
    drawClock();
    drawMainStatusBar(144, 2305, 16);
    
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_DrawHLine(STATIC_LINE_X, STATIC_LINE_Y, 448);
	BSP_LCD_DrawHLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER, 448);
	BSP_LCD_DrawHLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER*2, 448);
	BSP_LCD_DrawHLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER*3, 448);
	BSP_LCD_DrawHLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER*4, 448);
    
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_GENERAL_INFO_MENU[history_general_info_frame_Scroll_cnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_GENERAL_INFO_MENU[history_general_info_frame_Scroll_cnt + 1],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_GENERAL_INFO_MENU[history_general_info_frame_Scroll_cnt + 2],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_GENERAL_INFO_MENU[history_general_info_frame_Scroll_cnt + 3],LEFT_MODE);
    
	
	
  uint16_t offsetFirst = BSP_LCD_DisplayStringAt(250,FIRST_CURSOR_POS_Y + 9,intToStr(sysParams.consts.overallWorkingTime/3600),LEFT_MODE);
	
	uint32_t water = (uint32_t)(sysParams.consts.waterQuantaty/1000.0);
	if (water > MAX_OVERALL_WATER_SHOWN_M3)
	{
		water = MAX_OVERALL_WATER_SHOWN_M3;
	}
	uint32_t waterToPrint = 0;
	
	uint16_t offsetSecond = 0;
	uint32_t mod = 100000000;
	uint8_t poz = 0;
	if (water <= 0){
		offsetSecond = BSP_LCD_DisplayStringAt(250,SECOND_CURSOR_POS_Y + 9,intToStr(0),LEFT_MODE);
	} else {
		while (mod > 0){
			waterToPrint = water/mod;
			if (poz == 0){
				if (waterToPrint > 0){
					offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9,intToStr(waterToPrint),LEFT_MODE);
					poz++;
				}
			} else {
				offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9,intToStr(waterToPrint),LEFT_MODE);
				poz++;
			}
			if (poz > 0 && (mod == 1000 || mod == 1000000)){
				offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9," ",LEFT_MODE);
			}
			water -= waterToPrint*mod;
			mod /= 10;
		}
	}
		
//		if (water >= 1000000){
//			waterToPrint = water/1000000;
//			offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9,intToStr(waterToPrint),LEFT_MODE);
//			offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9," ",LEFT_MODE);
//		}
//		water -= waterToPrint*1000000;
//		waterToPrint = 0;
//		if (water >= 1000 ){
//			waterToPrint = water/1000;
//			offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9,intToStr(waterToPrint),LEFT_MODE);
//			offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9," ",LEFT_MODE);
//		} else {
//			if (offsetSecond > 0){
//				offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9,"000",LEFT_MODE);
//			}
//		}
//		water -= waterToPrint*1000;
//		waterToPrint = 0;
//		if (water >= 1){
//			waterToPrint = water;
//			offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9,intToStr(waterToPrint),LEFT_MODE);
////			offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9," ",LEFT_MODE);
//		} else {
//			offsetSecond += BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9,"000",LEFT_MODE);
//		}
//	}
	
	
	
	//offsetSecond = BSP_LCD_DisplayStringAt(250,SECOND_CURSOR_POS_Y + 9,intToStr(water),LEFT_MODE);
	uint16_t offsetThrid = BSP_LCD_DisplayStringAt(250,THRID_CURSOR_POS_Y + 9,intToStr(sysParams.consts.overallWashNum),LEFT_MODE);
	uint16_t offsetFour = BSP_LCD_DisplayStringAt(250,FOURTH_CURSOR_POS_Y + 9,intToStr(sysParams.consts.sysVersion),LEFT_MODE);
    
    BSP_LCD_DisplayStringAt(250 + offsetFirst,FIRST_CURSOR_POS_Y + 9," часов",LEFT_MODE);
	BSP_LCD_DisplayStringAt(250 + offsetSecond,SECOND_CURSOR_POS_Y + 9," м^3",LEFT_MODE);
	BSP_LCD_DisplayStringAt(250 + offsetThrid,THRID_CURSOR_POS_Y + 9," раз",LEFT_MODE);
	BSP_LCD_DisplayStringAt(250 + offsetFour,FOURTH_CURSOR_POS_Y + 9," ",LEFT_MODE);
  
	/*Add buttons parameters*/
    calcButParam();
}

//void RefreshScrollBarMenuFrame()
//{       
//    if(history_menu_frame_was_Scroll == 1 || history_menu_frame_was_Scroll == 2){
//        calcButParam();
//        
//        drawScrollButton(history_menu_frame_Scroll_cnt == 0 ? 0 : (history_menu_frame_Scroll_cnt == 1 ? 2 : 1));
//        
//        drawFillArcRec(menuLines[history_menu_frame_Scroll_cnt].x, menuLines[history_menu_frame_Scroll_cnt].y, menuLines[history_menu_frame_Scroll_cnt].xSize, menuLines[history_menu_frame_Scroll_cnt].ySize, LCD_COLOR_WHITE);
//        drawFillArcRec(menuLines[history_menu_frame_Scroll_cnt + 1].x, menuLines[history_menu_frame_Scroll_cnt + 1].y, menuLines[history_menu_frame_Scroll_cnt + 1].xSize, menuLines[history_menu_frame_Scroll_cnt + 1].ySize, LCD_COLOR_WHITE);
//        drawFillArcRec(menuLines[history_menu_frame_Scroll_cnt + 2].x, menuLines[history_menu_frame_Scroll_cnt + 2].y, menuLines[history_menu_frame_Scroll_cnt + 2].xSize, menuLines[history_menu_frame_Scroll_cnt + 2].ySize, LCD_COLOR_WHITE);
//        drawFillArcRec(menuLines[history_menu_frame_Scroll_cnt + 3].x, menuLines[history_menu_frame_Scroll_cnt + 3].y, menuLines[history_menu_frame_Scroll_cnt + 3].xSize, menuLines[history_menu_frame_Scroll_cnt + 3].ySize, LCD_COLOR_WHITE);
//        
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FIRST_CURSOR_POS_Y + 9,ITEM_GENERAL_INFO_MENU[history_menu_frame_Scroll_cnt],LEFT_MODE);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,SECOND_CURSOR_POS_Y + 9,ITEM_GENERAL_INFO_MENU[history_menu_frame_Scroll_cnt + 1],LEFT_MODE);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,THRID_CURSOR_POS_Y + 9,ITEM_GENERAL_INFO_MENU[history_menu_frame_Scroll_cnt + 2],LEFT_MODE);
//        BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X + 9,FOURTH_CURSOR_POS_Y + 9,ITEM_GENERAL_INFO_MENU[history_menu_frame_Scroll_cnt + 3],LEFT_MODE);
//        
//        drawStaticLines();
//        
//        history_menu_frame_was_Scroll = 0;
//    }
//}

void calcButParam()
{
    TC_clearButtons();
   
        //Setting for key "0"
    menuLines[history_general_info_frame_Scroll_cnt].x = FIRST_CURSOR_POS_X;
    menuLines[history_general_info_frame_Scroll_cnt].y = FIRST_CURSOR_POS_Y;
    menuLines[history_general_info_frame_Scroll_cnt].xSize = FIRST_CURSOR_SIZE_X;
    menuLines[history_general_info_frame_Scroll_cnt].ySize = FIRST_CURSOR_SIZE_Y;
		
		//Setting for key "1"
    menuLines[history_general_info_frame_Scroll_cnt + 1].x = SECOND_CURSOR_POS_X;
    menuLines[history_general_info_frame_Scroll_cnt + 1].y = SECOND_CURSOR_POS_Y;
    menuLines[history_general_info_frame_Scroll_cnt + 1].xSize = SECOND_CURSOR_SIZE_X;
    menuLines[history_general_info_frame_Scroll_cnt + 1].ySize = SECOND_CURSOR_SIZE_Y;
    
		//Setting for key "2"
    menuLines[history_general_info_frame_Scroll_cnt + 2].x = THRID_CURSOR_POS_X;
    menuLines[history_general_info_frame_Scroll_cnt + 2].y = THRID_CURSOR_POS_Y;
    menuLines[history_general_info_frame_Scroll_cnt + 2].xSize = THRID_CURSOR_SIZE_X;
    menuLines[history_general_info_frame_Scroll_cnt + 2].ySize = THRID_CURSOR_SIZE_Y;
    
		//Setting for key "3"
    menuLines[history_general_info_frame_Scroll_cnt + 3].x = FOURTH_CURSOR_POS_X;
    menuLines[history_general_info_frame_Scroll_cnt + 3].y = FOURTH_CURSOR_POS_Y;
    menuLines[history_general_info_frame_Scroll_cnt + 3].xSize = FOURTH_CURSOR_SIZE_X;
    menuLines[history_general_info_frame_Scroll_cnt + 3].ySize = FOURTH_CURSOR_SIZE_Y;
    
    for (uint8_t i = history_general_info_frame_Scroll_cnt; i < history_general_info_frame_Scroll_cnt + 4; i++){
			TC_addButton(&menuLines[i]);
	}
	TC_addButton(&retBut);
	TC_addButton(&scrollUpBut);
	TC_addButton(&scrollDwnBut);
    TC_addButton(&homeBut);
    
}