#include "widgets.h"

void drawFillButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t radius, uint16_t* label, uint16_t color, bool isTouch)
{
    if(isTouch)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    }
    else
    {
        BSP_LCD_SetTextColor(color);
        BSP_LCD_SetBackColor(color);
    }
    if(radius != 0)
    {
       BSP_LCD_FillRect(xPos, yPos + radius, xSize + 1, ySize - radius * 2);
       BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
        
       BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
       BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
       BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
       BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
    }
    else
    {
        BSP_LCD_FillRect(xPos, yPos, xSize, ySize);
    }
    
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 18, label, CENTER_MODE);
}

void drawTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t radius, uint16_t* label, uint16_t color1, uint16_t color2)
{
    if(radius != 0)
    {
       BSP_LCD_SetTextColor(color1);
       BSP_LCD_FillRect(xPos, yPos + radius, xSize + 1, ySize - radius * 2);
       BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
        
       BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
       BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
       BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
       BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
       
        
       BSP_LCD_SetTextColor(color2);
       BSP_LCD_FillRect(xPos + 1, yPos + radius + 1, xSize - 1, ySize - radius * 2 - 2);
       BSP_LCD_FillRect(xPos + radius + 1, yPos + 1, xSize - radius * 2 - 2, ySize - 1);
        
       BSP_LCD_FillCircle(xPos + radius + 1, yPos + radius + 1, radius);
       BSP_LCD_FillCircle(xPos + radius + 1, (yPos + ySize) - radius - 1, radius);
       BSP_LCD_FillCircle((xPos + xSize) - radius - 1, (yPos + ySize) - radius - 1, radius);
       BSP_LCD_FillCircle((xPos + xSize) - radius - 1, yPos + radius + 1, radius);
    }
    else
    {
        BSP_LCD_FillRect(xPos, yPos, xSize, ySize);
    }
    BSP_LCD_SetBackColor(color2);
    BSP_LCD_SetTextColor(color1);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 18, label, CENTER_MODE);
}

void drawMainBar(bool returnBut, uint16_t xPosLogo, uint16_t yPosLogo, uint16_t* label)
{
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
    
    BSP_LCD_DrawBitmap(xPosLogo, yPosLogo ,&Logo);
    
    if(returnBut)
        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 20, RETURN_BUT_POS_Y + 11 ,&gImage_RETURNARROW);
    
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y ,label, LEFT_MODE);
}

void drawStatusBarOkCancel()
{
    BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);

    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(CANCEL_X, CANCEL_Y, CANCEL, LEFT_MODE);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(OK_X, OK_Y, OK, LEFT_MODE);

}

void drawStatusBarSave(uint16_t* label)
{
    BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);

    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(SAVE_X,SAVE_Y,SAVE,LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(TEXT_X, TEXT_Y ,label, LEFT_MODE);
}


void drawScrollButton (uint16_t scPos)
{
   uint16_t scrollPos = scPos * 45;
   BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
    
   BSP_LCD_FillRect(SCROLLBAR_POS_X, SCROLLBAR_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_SIZE_X + 1, SCROLLBAR_SIZE_Y - SCROLLBAR_RADIUS * 2);
   BSP_LCD_FillRect(SCROLLBAR_POS_X + SCROLLBAR_RADIUS, SCROLLBAR_POS_Y, SCROLLBAR_SIZE_X - SCROLLBAR_RADIUS * 2, SCROLLBAR_SIZE_Y + 1);
    
   BSP_LCD_FillCircle(SCROLLBAR_POS_X + SCROLLBAR_RADIUS, SCROLLBAR_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle(SCROLLBAR_POS_X + SCROLLBAR_RADIUS, (SCROLLBAR_POS_Y + SCROLLBAR_SIZE_Y) - SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle((SCROLLBAR_POS_X + SCROLLBAR_SIZE_X) - SCROLLBAR_RADIUS, (SCROLLBAR_POS_Y + SCROLLBAR_SIZE_Y) - SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle((SCROLLBAR_POS_X + SCROLLBAR_SIZE_X) - SCROLLBAR_RADIUS, SCROLLBAR_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);

   BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 12, UP_ARROW_POS_Y + 5 ,&gImage_ARROWUP);
   BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 12, DOWN_ARROW_POS_Y + 25 ,&gImage_ARROWDOWN);
    
    
   BSP_LCD_SetTextColor(LCD_COLOR_WHITE); 
    
   BSP_LCD_FillRect(SCROLLBAR_CURSOR_POS_X, SCROLLBAR_CURSOR_POS_Y + SCROLLBAR_CURSOR_RADIUS + scrollPos, SCROLLBAR_CURSOR_SIZE_X + 1, SCROLLBAR_CURSOR_SIZE_Y - SCROLLBAR_CURSOR_RADIUS * 2);
   BSP_LCD_FillRect(SCROLLBAR_CURSOR_POS_X + SCROLLBAR_CURSOR_RADIUS, SCROLLBAR_CURSOR_POS_Y + scrollPos, SCROLLBAR_CURSOR_SIZE_X - SCROLLBAR_CURSOR_RADIUS * 2, SCROLLBAR_CURSOR_SIZE_Y + 1);
    
   BSP_LCD_FillCircle(SCROLLBAR_CURSOR_POS_X + SCROLLBAR_CURSOR_RADIUS, SCROLLBAR_CURSOR_POS_Y + SCROLLBAR_CURSOR_RADIUS + scrollPos, SCROLLBAR_CURSOR_RADIUS);
   BSP_LCD_FillCircle(SCROLLBAR_CURSOR_POS_X + SCROLLBAR_CURSOR_RADIUS, (SCROLLBAR_CURSOR_POS_Y + SCROLLBAR_CURSOR_SIZE_Y) - SCROLLBAR_CURSOR_RADIUS + scrollPos, SCROLLBAR_CURSOR_RADIUS);
   BSP_LCD_FillCircle((SCROLLBAR_CURSOR_POS_X + SCROLLBAR_CURSOR_SIZE_X) - SCROLLBAR_CURSOR_RADIUS, (SCROLLBAR_CURSOR_POS_Y + SCROLLBAR_CURSOR_SIZE_Y) - SCROLLBAR_CURSOR_RADIUS + scrollPos, SCROLLBAR_CURSOR_RADIUS);
   BSP_LCD_FillCircle((SCROLLBAR_CURSOR_POS_X + SCROLLBAR_CURSOR_SIZE_X) - SCROLLBAR_CURSOR_RADIUS, SCROLLBAR_CURSOR_POS_Y + SCROLLBAR_CURSOR_RADIUS + scrollPos, SCROLLBAR_CURSOR_RADIUS);
}