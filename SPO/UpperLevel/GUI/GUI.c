/**
  ******************************************************************************
  * @file           : GUI.c
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
#include "main.h"
#include "PistonControl\PistonControl.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TS_StateTypeDef tsState;
uint32_t touchDelay;
uint8_t dropBut;
uint8_t wrenchBut;
uint8_t pageBut;
uint8_t redraw = 0;
uint8_t frame = 0;
//uint8_t wasScroll = 0;
uint8_t itemIndex;
char* ITEM_MENU_DROP[] = { "SERVICE", "REGENERATION", "FILTERING" };
char* ITEM_MENU_WRENCH[] = { "LANGUAGE", "SET TIME", "RESET" };
char* ITEM_MENU_PAGE[] = { "ERROR LIST", "DIAGRAM", "COUNTER" };

char* ITEM_MENU_SERVICE[] = { "ADJUSTMENT", "FEED RAPID", "CALIBRATE" };
char* ITEM_MENU_REGENERATION[] = { "BACKWASH", "RINSE", "DOWNFLOW BRINE", "UPFLOW BRINE", "FILL/REGENERANT REFILL", "SOFTENING/FILTERING" };
char* ITEM_MENU_FILTERING[] = { "aaa", "sss", "ddd" };
/* Private function prototypes -----------------------------------------------*/

void DrawOpticStatus(void);
/* Private user code ---------------------------------------------------------*/
void initGUI(void){
	
	redraw = 0;
	BSP_LCD_Init();
	BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_DrawBitmap((ILI9486_LCD_PIXEL_HEIGHT-150)/2,(ILI9486_LCD_PIXEL_WIDTH-150)/2,&LOGO);
	//LL_mDelay(1000);
    
    BSP_LCD_SetFont(&Oxygen_Mono_24);
    
    frame = 0;
   // wasScroll = 0;
    
    itemIndex = 0;
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    //ShowMainFrame();
}
uint32_t neededPoz = 0;

void translateMessage(void){
	BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && tsState.TouchDetected == 1)
    {
        touchDelay = 100;
        switch(frame)
        {
            case 0:
            {
                if (isInRectangle(tsState.X,tsState.Y,DROP_BUT_X,DROP_BUT_Y,DROP_BUT_X_SIZE,DROP_BUT_Y_SIZE) )
                {
                    if (dropBut == 0)
                    {
                        dropBut = 1;
                        frame = 1;
                    } 
                }
                if (isInRectangle(tsState.X,tsState.Y,WRENCH_BUT_X,WRENCH_BUT_Y,DROP_BUT_X_SIZE,DROP_BUT_Y_SIZE) )
                {
                    if (wrenchBut == 0) 
                    {
                        wrenchBut = 1;
                        frame = 2;
                    } 
                }
                if (isInRectangle(tsState.X,tsState.Y,PAGE_BUT_X,PAGE_BUT_Y,DROP_BUT_X_SIZE,DROP_BUT_X_SIZE) )
                {
                    if (pageBut == 0) 
                    {
                        pageBut = 1;
                        frame = 3;
                    } 
                }   
                break;
            }
            case 1:
            {
                if (isInRectangle(tsState.X,tsState.Y,FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y))
                {
                    frame = 11;
                }   
                if (isInRectangle(tsState.X,tsState.Y,SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y))
                {
                    frame = 12;
                }   
                if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y))
                {
                    frame = 0;
                }
                break;
            }
            
            case 2:
            {
                if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y))
                {
                    frame = 0;
                }
                break;
            }
            
            case 3:
            {  
                if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y))
                {
                    frame = 0;
                }
                break;
            }

            case 11:
            {
                if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y))
                {
                    frame = 1;
                }
                break;
            }
            case 12:
            {
                if (isInRectangle(tsState.X,tsState.Y,RETURN_BUT_POS_X,RETURN_BUT_POS_Y,RETURN_BUT_SIZE_X,RETURN_BUT_SIZE_Y))
                {
                    frame = 1;
                }
                if (isInRectangle(tsState.X,tsState.Y,UP_ARROW_POS_X,UP_ARROW_POS_Y,UP_ARROW_SIZE_X,UP_ARROW_SIZE_Y))
                {
                    //if(wasScroll > 0) wasScroll--;
                }
                if (isInRectangle(tsState.X,tsState.Y,DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y))
                {
                    //if(wasScroll < 2) wasScroll++;
                }
                break;
            }
        }
		
		  
	}    
    //refresh();
   
    //intToStr(opticCnt);
}

//void refresh(void)
//{
//    if(frame == 1)
//    {
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(0,TOP_BOT_LINE_WIDTH,BSP_LCD_GetXSize(),BSP_LCD_GetYSize() - 2*TOP_BOT_LINE_WIDTH);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 13,ITEM_MENU_DROP[0],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 13,ITEM_MENU_DROP[1],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 13,ITEM_MENU_DROP[2],LEFT_MODE);
//        
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//        
//        BSP_LCD_DrawRect(FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//           
//        BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
//            
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
//        BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);

//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_DisplayStringAt(TOP_BOT_LINE_WIDTH,18,"MODE",LEFT_MODE);
//        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(UP_ARROW_POS_X,UP_ARROW_POS_Y, UP_ARROW_SIZE_X, UP_ARROW_SIZE_Y);
//        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y);
//        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
//    }
//    
//    if(frame == 2)
//    {
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(0,TOP_BOT_LINE_WIDTH,BSP_LCD_GetXSize(),BSP_LCD_GetYSize() - 2*TOP_BOT_LINE_WIDTH);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 13,ITEM_MENU_WRENCH[0],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 13,ITEM_MENU_WRENCH[1],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 13,ITEM_MENU_WRENCH[2],LEFT_MODE);
//        
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//        
//        BSP_LCD_DrawRect(FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//           
//        BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
//            
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
//        BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);

//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_DisplayStringAt(TOP_BOT_LINE_WIDTH,18,"SETTINGS",LEFT_MODE);
//        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(UP_ARROW_POS_X,UP_ARROW_POS_Y, UP_ARROW_SIZE_X, UP_ARROW_SIZE_Y);
//        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y);
//        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
//    }
//    if(frame == 3)
//    {
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(0,TOP_BOT_LINE_WIDTH,BSP_LCD_GetXSize(),BSP_LCD_GetYSize() - 2*TOP_BOT_LINE_WIDTH);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 13,ITEM_MENU_PAGE[0],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 13,ITEM_MENU_PAGE[1],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 13,ITEM_MENU_PAGE[2],LEFT_MODE);
//        
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//        
//        BSP_LCD_DrawRect(FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//           
//        BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
//            
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
//        BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);

//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_DisplayStringAt(TOP_BOT_LINE_WIDTH,18,"NOTIFICATIONS",LEFT_MODE);
//        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(UP_ARROW_POS_X,UP_ARROW_POS_Y, UP_ARROW_SIZE_X, UP_ARROW_SIZE_Y);
//        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y);
//        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
//    }
//    if(frame == 11)
//    {
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(0,TOP_BOT_LINE_WIDTH,BSP_LCD_GetXSize(),BSP_LCD_GetYSize() - 2*TOP_BOT_LINE_WIDTH);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 13,ITEM_MENU_SERVICE[0],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 13,ITEM_MENU_SERVICE[1],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 13,ITEM_MENU_SERVICE[2],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//           
//        BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
//            
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
//        BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);

//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_DisplayStringAt(TOP_BOT_LINE_WIDTH,18,"SERVICE",LEFT_MODE);
//        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11,&gImage_RETURNARROW);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(UP_ARROW_POS_X,UP_ARROW_POS_Y, UP_ARROW_SIZE_X, UP_ARROW_SIZE_Y);
//        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y);
//        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
//    }
//    if(frame == 12)
//    {
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(0,TOP_BOT_LINE_WIDTH,BSP_LCD_GetXSize(),BSP_LCD_GetYSize() - 2*TOP_BOT_LINE_WIDTH);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y,FIRST_CURSOR_SIZE_X,FIRST_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,FIRST_CURSOR_POS_Y + 13,ITEM_MENU_REGENERATION[wasScroll],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(SECOND_CURSOR_POS_X,SECOND_CURSOR_POS_Y,SECOND_CURSOR_SIZE_X,SECOND_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,SECOND_CURSOR_POS_Y + 13,ITEM_MENU_REGENERATION[wasScroll + 1],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(THRID_CURSOR_POS_X,THRID_CURSOR_POS_Y,THRID_CURSOR_SIZE_X,THRID_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,THRID_CURSOR_POS_Y + 13,ITEM_MENU_REGENERATION[wasScroll + 2],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//            
//        BSP_LCD_DrawRect(FOURTH_CURSOR_POS_X,FOURTH_CURSOR_POS_Y,FOURTH_CURSOR_SIZE_X,FOURTH_CURSOR_SIZE_Y);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(16,FOURTH_CURSOR_POS_Y + 13,ITEM_MENU_REGENERATION[wasScroll + 3],LEFT_MODE);
//            
//        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//           
//        BSP_LCD_DrawRect(SCROLLBAR_POS_X,SCROLLBAR_POS_Y,SCROLLBAR_SIZE_X,SCROLLBAR_SIZE_Y);
//            
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
//        BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);

//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_DisplayStringAt(TOP_BOT_LINE_WIDTH,18,"REGENERATION",LEFT_MODE);
//        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11,&gImage_RETURNARROW);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(UP_ARROW_POS_X,UP_ARROW_POS_Y, UP_ARROW_SIZE_X, UP_ARROW_SIZE_Y);
//        BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 15 ,&gImage_ARROWUP);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(DOWN_ARROW_POS_X,DOWN_ARROW_POS_Y,DOWN_ARROW_SIZE_X,DOWN_ARROW_SIZE_Y);
//        BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 15 ,&gImage_ARROWDOWN);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_FillRect(SCROLLBAR_CURSOR_POS_X, SCROLLBAR_CURSOR_POS_Y, SCROLLBAR_CURSOR_SIZE_X, SCROLLBAR_CURSOR_SIZE_Y);
//        
//        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y) + (wasScroll == 0 ? 0 : wasScroll * 40), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
//        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 5) + (wasScroll == 0 ? 0 : wasScroll * 40), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
//        BSP_LCD_FillRect(SCROLLBAR_CURSOR_SLIDER_POS_X,(SCROLLBAR_CURSOR_SLIDER_POS_Y + 10) + (wasScroll == 0 ? 0 : wasScroll * 40), SCROLLBAR_CURSOR_SLIDER_SIZE_X, SCROLLBAR_CURSOR_SLIDER_SIZE_Y);
//    }
//    
//    if(frame == 0)
//    {
//        BSP_LCD_Clear(LCD_COLOR_WHITE);
//        BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
//        BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
//        BSP_LCD_DrawBitmap(SMALL_LOGO_X, SMALL_LOGO_Y ,&gImage_SMALL_LOGO);
//    
//        BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//        BSP_LCD_DisplayStringAt(MODE_TEXT_X, MODE_TEXT_Y,MODE_SOFTENING_CYCLE,LEFT_MODE);
//        
//        //DrawButton(DROP_BUT_X, DROP_BUT_Y, DROP_BUT_X_SIZE, DROP_BUT_Y_SIZE, 1, DROP_BUT_FIRST_TEXT);
//        BSP_LCD_DrawBitmap(DROP_BUT_X, DROP_BUT_Y ,&gImage_DROPBUT);
//        dropBut = 0;
//	
//        //DrawButton(WRENCH_BUT_X, WRENCH_BUT_Y, DROP_BUT_X_SIZE, DROP_BUT_Y_SIZE, 1, WRENCH_BUT_FIRST_TEXT);
//        BSP_LCD_DrawBitmap(WRENCH_BUT_X, WRENCH_BUT_Y ,&gImage_WRENCHBUT);
//        wrenchBut = 0;
//	
//        //DrawButton(PAGE_BUT_X, DROP_BUT_Y, DROP_BUT_X_SIZE, DROP_BUT_Y_SIZE, 1, PAGE_BUT_TEXT);
//        BSP_LCD_DrawBitmap(PAGE_BUT_X, PAGE_BUT_Y ,&gImage_PAGEBUT);
//        pageBut = 0;
//    }
//    
//    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
//    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
//    BSP_LCD_FillRect(TIME_POS_X,TIME_POS_Y, TIME_SIZE_X, TIME_SIZE_Y);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//    BSP_LCD_DisplayStringAt(TIME_POS_X + 16,TIME_POS_Y + 18,intToStr(frame),CENTER_MODE);
//}
//void DrawOpticStatus(void){
//	if (opticStatus == 1){
//		BSP_LCD_SetTextColor(LCD_COLOR_RED);
//	} else {
//		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
//	}
//	BSP_LCD_FillCircle(SENS_STATUS_CIRC_X, SENS_STATUS_CIRC_Y,10);
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//}

//void DrawOpticStatus(void){
//	if (opticStatus == 1){
//		BSP_LCD_SetTextColor(LCD_COLOR_RED);
//	} else {
//		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
//	}
//	BSP_LCD_FillCircle(SENS_STATUS_CIRC_X, SENS_STATUS_CIRC_Y,10);
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//}

void drawClock(void){
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	BSP_LCD_DisplayStringAt(HOUR_X, CLOCK_Y, getFormatedTime("hh"),LEFT_MODE);
	BSP_LCD_DisplayStringAt(MINUTE_X, CLOCK_Y, getFormatedTime("mm"),LEFT_MODE);
	if (getTime()->second % 2){
		BSP_LCD_DisplayStringAt(DIV_X, CLOCK_Y, getFormatedTime(" "),LEFT_MODE);
		
	} else {
		BSP_LCD_DisplayStringAt(DIV_X, CLOCK_Y, ":",LEFT_MODE);
	}
}


uint8_t isInRectangle (uint16_t x, uint16_t y, uint16_t xS, uint16_t yS, uint16_t xSize, uint16_t ySize){
	
	return x < xS+xSize && x > xS && y < yS+ySize && y > yS;
}
void DrawButton(uint16_t x, uint16_t y, uint16_t xSize, uint16_t ySize, uint8_t isPushed, uint8_t* text, WTC_FONT_t* font){
	if (isPushed == 1)
	{
		BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
		BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	}
	else 
    {
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
		BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
	}
	BSP_LCD_FillRect(x,y,xSize,ySize);
	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(font);
	
	uint32_t size = 0, xsize = 0; 
    uint8_t  *ptr = text;
  
  /* Get the text size */
  while (*ptr++) size ++ ;
	
	uint16_t xTextStart = xSize/2+x;
	uint16_t yTextStart = ySize/2+(y-12);
	
	//SP_LCD_DrawPixel(xTextStart, yTextStart, LCD_COLOR_RED);
	//BSP_LCD_DrawPixel(xSize/2+x, ySize/2+y, LCD_COLOR_RED);
	
	BSP_LCD_DisplayStringAt(xTextStart,yTextStart,text,CENTER_MODE);
}