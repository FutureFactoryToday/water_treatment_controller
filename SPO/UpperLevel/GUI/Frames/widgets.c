#include "widgets.h"

void drawFillButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t radius, uint16_t* label, uint16_t color, WTC_FONT_t* font, bool isTouch)
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
    
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 18, label, CENTER_MODE);
}

void drawTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t radius, uint16_t* label, uint16_t color1, uint16_t color2, WTC_FONT_t* font)
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

void drawBar(uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t color)
{
    BSP_LCD_SetTextColor(color);
    BSP_LCD_FillRect(xPos, yPos, xSize, ySize);
}