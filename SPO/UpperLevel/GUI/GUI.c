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
update_flag_t updateFlags;


uint8_t* hour = "hh";
uint8_t* minute = "mm";

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
    
    //ShowMainFrame();
}
uint32_t neededPoz = 0;

void translateMessage(void){
	BSP_TS_GetState(&tsState);
	if (touchDelay == 0 && wasTouch())
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
   
    //intToStr(opticCnt);
}

void drawClock(void){
	BSP_LCD_SetFont(&Oxygen_Mono_24);
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
	uint16_t yTextStart = ySize/2+y-font->height/2;
	
	//SP_LCD_DrawPixel(xTextStart, yTextStart, LCD_COLOR_RED);
	//BSP_LCD_DrawPixel(xSize/2+x, ySize/2+y, LCD_COLOR_RED);
	
	BSP_LCD_DisplayStringAt(xTextStart,yTextStart,text,CENTER_MODE);
}