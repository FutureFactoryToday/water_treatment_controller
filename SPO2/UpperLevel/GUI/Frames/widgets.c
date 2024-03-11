#include "widgets.h"

button_t drawFillButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label, bool isTouch)
{
    uint16_t radius = ySize/4;
    
    button_t but;
    but.x = xPos;
    but.y = yPos;
    but.xSize = xSize;
    but.ySize = ySize; 
    but.isPressed = false;
    but.wasPressed = false;
    but.isReleased = false;
    but.pressCnt = false;
    
    if(isTouch)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    }
    else
    {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
        BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    }
//    if(radius != 0)
//    {
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
        
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 15, label, CENTER_MODE);
    
    return but;
}

button_t drawFillCustomButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label, uint8_t *pBmp, uint16_t color, bool isTouch)
{
    uint16_t radius = ySize/4;
    
    button_t but;
    but.x = xPos;
    but.y = yPos;
    but.xSize = xSize;
    but.ySize = ySize; 
    but.isPressed = false;
    but.wasPressed = false;
    but.isReleased = false;
    but.pressCnt = false;
    
    if(isTouch)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    }
    else
    {
        BSP_LCD_SetTextColor(color);
        BSP_LCD_SetBackColor(color);
    }
//    if(radius != 0)
//    {
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
        
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    BSP_LCD_DisplayStringAt(xPos + 20, yPos + ySize/2 - 15, label, LEFT_MODE);
    BSP_LCD_SetFont(&Oxygen_Mono_24);
    
    BSP_LCD_DrawBitmap(xPos + xSize - 50,yPos + 10, pBmp);
    
    return but;
}


void drawFillArcRec (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t color)
{
    uint16_t oldTextColor = BSP_LCD_GetTextColor();
    uint16_t oldBackColor = BSP_LCD_GetBackColor();
    
    uint16_t radius = ySize/4;
    BSP_LCD_SetTextColor(color);
    
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
        
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
    
    BSP_LCD_SetTextColor(oldTextColor);
    BSP_LCD_SetBackColor(oldBackColor);
}

button_t drawTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label)
{
    uint16_t radius = ySize/4;
    
    button_t but;
    but.x = xPos;
    but.y = yPos;
    but.xSize = xSize;
    but.ySize = ySize; 
    but.isPressed = false;
    but.wasPressed = false;
    but.isReleased = false;
    but.pressCnt = false;
    
//    
//    if(radius != 0)
//    {
    BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
    
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
   
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(xPos + 1, yPos + radius + 1, xSize - 2, ySize - radius * 2 - 2);
    BSP_LCD_FillRect(xPos + radius + 1, yPos + 1, xSize - radius * 2 - 2, ySize - 1);
    
    BSP_LCD_FillCircle(xPos + radius + 1, yPos + radius + 1, radius);
    BSP_LCD_FillCircle(xPos + radius + 1, (yPos + ySize) - radius - 1, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius - 1, (yPos + ySize) - radius - 1, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius - 1, yPos + radius + 1, radius);
//    }
//    else
//    {
//        BSP_LCD_FillRect(xPos, yPos, xSize, ySize);
//    }
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 15, label, CENTER_MODE);
    
    return but;
}

button_t drawCustomTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label,uint16_t textColor, uint16_t backColor)
{
	uint16_t oldTextColor = BSP_LCD_GetTextColor();
	uint16_t oldBackColor = BSP_LCD_GetBackColor();
	
    uint16_t radius = ySize/4;
    
    button_t but;
    but.x = xPos;
    but.y = yPos;
    but.xSize = xSize;
    but.ySize = ySize; 
    but.isPressed = false;
    but.wasPressed = false;
    but.isReleased = false;
    but.pressCnt = false;
    
//    
//    if(radius != 0)
//    {
    BSP_LCD_SetTextColor(backColor);
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
    
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
   
    
//    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//    BSP_LCD_FillRect(xPos + 1, yPos + radius + 1, xSize - 2, ySize - radius * 2 - 2);
//    BSP_LCD_FillRect(xPos + radius + 1, yPos + 1, xSize - radius * 2 - 2, ySize - 1);
//    
//    BSP_LCD_FillCircle(xPos + radius + 1, yPos + radius + 1, radius);
//    BSP_LCD_FillCircle(xPos + radius + 1, (yPos + ySize) - radius - 1, radius);
//    BSP_LCD_FillCircle((xPos + xSize) - radius - 1, (yPos + ySize) - radius - 1, radius);
//    BSP_LCD_FillCircle((xPos + xSize) - radius - 1, yPos + radius + 1, radius);
//    }
//    else
//    {
//        BSP_LCD_FillRect(xPos, yPos, xSize, ySize);
//    }
    BSP_LCD_SetBackColor(backColor);
    BSP_LCD_SetTextColor(textColor);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 15, label, CENTER_MODE);
    
		BSP_LCD_SetTextColor(oldTextColor);
		BSP_LCD_SetBackColor(oldBackColor);
    return but;
}

 button_t drawDarkTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label){
	     uint16_t radius = ySize/4;
    
    button_t but;
    but.x = xPos;
    but.y = yPos;
    but.xSize = xSize;
    but.ySize = ySize; 
    but.isPressed = false;
    but.wasPressed = false;
    but.isReleased = false;
    but.pressCnt = false;
    
//    
//    if(radius != 0)
//    {
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
    
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
   
   
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 15, label, CENTER_MODE);
    
    return but;
 }
 
button_t drawLightTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label){
	uint16_t radius = ySize/4;
    
    button_t but;
    but.x = xPos;
    but.y = yPos;
    but.xSize = xSize;
    but.ySize = ySize; 
    but.isPressed = false;
    but.wasPressed = false;
    but.isReleased = false;
    but.pressCnt = false;
    
//    
//    if(radius != 0)
//    {
    BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
    
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
   
   
    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 15, label, CENTER_MODE);
    
    return but;
 }
  
void drawMainBar(bool returnBut, bool homeBut, uint16_t xPosLogo, uint16_t yPosLogo, uint8_t* label)
{
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect(MAINBAR_POS_X,MAINBAR_POS_Y, MAINBAR_SIZE_X, MAINBAR_SIZE_Y);
    
    if(homeBut) {
        BSP_LCD_DrawBitmap(HOME_BUT_X, HOME_BUT_Y + 10, &gImage_HOMEBUT);
    }
    
    if(returnBut)
        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 10, RETURN_BUT_POS_Y + 10, &gImage_RETURNARROW);
    else {
        BSP_LCD_DrawBitmap(xPosLogo, yPosLogo, &Logo);
    }
    
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(MODE_STATUS_TEXT_X, MODE_STATUS_TEXT_Y, label, LEFT_MODE);
}

void drawMainWindow()
{
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(MAIN_WINDOW_POS_X,MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y);
}

void drawList(uint8_t scrollCnt)
{
    drawStaticLines();
    
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X,FIRST_CURSOR_POS_Y + 9,ITEM_MENU[scrollCnt],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X,SECOND_CURSOR_POS_Y + 9,ITEM_MENU[scrollCnt + 1],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X,THRID_CURSOR_POS_Y + 9,ITEM_MENU[scrollCnt + 2],LEFT_MODE);
	BSP_LCD_DisplayStringAt(FIRST_CURSOR_POS_X,FOURTH_CURSOR_POS_Y + 9,ITEM_MENU[scrollCnt + 3],LEFT_MODE);
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

void drawStatusBarSave(uint8_t* label)
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

void drawStatusBarLabel(uint8_t* label)
{
    BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(TEXT_X, TEXT_Y ,label, LEFT_MODE);
}


void drawStatusBarEmpty()
{
    BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
}

void drawMainStatusBar(uint16_t nextСycleTime, uint16_t сurrentWaterConsumption, uint16_t amountOfWater)
{
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(TEXT_X, TEXT_Y ,intToStr(nextСycleTime), LEFT_MODE);
    BSP_LCD_DisplayStringAt(TEXT_X + 50, TEXT_Y , NEXT_CYCLE_TIME, LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(TEXT_X + 110, TEXT_Y ,intToStr(сurrentWaterConsumption), LEFT_MODE);
    BSP_LCD_DisplayStringAt(TEXT_X + 160, TEXT_Y ,CURRENT_WATER_CONSUMPTION, LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(TEXT_X + 270, TEXT_Y ,intToStr(amountOfWater), LEFT_MODE);
    BSP_LCD_DisplayStringAt(TEXT_X + 300, TEXT_Y ,AMOUNT_OF_WATER, LEFT_MODE);
}

void drawScrollButton (uint16_t scPos)
{
   uint16_t scrollPos = scPos * 45;
   BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
    
   BSP_LCD_FillRect(SCROLLKEYUP_POS_X, SCROLLKEYUP_POS_Y + SCROLLBAR_RADIUS, SCROLLKEYUP_SIZE_X, SCROLLKEYUP_SIZE_Y - SCROLLBAR_RADIUS * 2);
   BSP_LCD_FillRect(SCROLLKEYUP_POS_X + SCROLLBAR_RADIUS, SCROLLKEYUP_POS_Y, SCROLLKEYUP_SIZE_X - SCROLLBAR_RADIUS * 2, SCROLLKEYUP_SIZE_Y + 1);
    
   BSP_LCD_FillCircle(SCROLLKEYUP_POS_X + SCROLLBAR_RADIUS, SCROLLKEYUP_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle(SCROLLKEYUP_POS_X + SCROLLBAR_RADIUS, (SCROLLKEYUP_POS_Y + SCROLLKEYUP_SIZE_Y) - SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle((SCROLLKEYUP_POS_X + SCROLLKEYUP_SIZE_X) - SCROLLBAR_RADIUS, (SCROLLKEYUP_POS_Y + SCROLLKEYUP_SIZE_Y) - SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle((SCROLLKEYUP_POS_X + SCROLLKEYUP_SIZE_X) - SCROLLBAR_RADIUS, SCROLLKEYUP_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);

   BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 13, UP_ARROW_POS_Y + 10 ,&gImage_ARROWUP);
    
   
   BSP_LCD_FillRect(SCROLLKEYDOWN_POS_X, SCROLLKEYDOWN_POS_Y + SCROLLBAR_RADIUS, SCROLLKEYDOWN_SIZE_X, SCROLLKEYDOWN_SIZE_Y - SCROLLBAR_RADIUS * 2);
   BSP_LCD_FillRect(SCROLLKEYDOWN_POS_X + SCROLLBAR_RADIUS, SCROLLKEYDOWN_POS_Y, SCROLLKEYDOWN_SIZE_X - SCROLLBAR_RADIUS * 2, SCROLLKEYDOWN_SIZE_Y + 1);
    
   BSP_LCD_FillCircle(SCROLLKEYDOWN_POS_X + SCROLLBAR_RADIUS, SCROLLKEYDOWN_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle(SCROLLKEYDOWN_POS_X + SCROLLBAR_RADIUS, (SCROLLKEYDOWN_POS_Y + SCROLLKEYDOWN_SIZE_Y) - SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle((SCROLLKEYDOWN_POS_X + SCROLLKEYDOWN_SIZE_X) - SCROLLBAR_RADIUS, (SCROLLKEYDOWN_POS_Y + SCROLLKEYDOWN_SIZE_Y) - SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle((SCROLLKEYDOWN_POS_X + SCROLLKEYDOWN_SIZE_X) - SCROLLBAR_RADIUS, SCROLLKEYDOWN_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);

   BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 13, DOWN_ARROW_POS_Y + 10 ,&gImage_ARROWDOWN);
    
    
//   BSP_LCD_SetTextColor(LCD_COLOR_WHITE); 
    
//   BSP_LCD_FillRect(SCROLLBAR_CURSOR_POS_X, SCROLLBAR_CURSOR_POS_Y + SCROLLBAR_CURSOR_RADIUS + scrollPos, SCROLLBAR_CURSOR_SIZE_X, SCROLLBAR_CURSOR_SIZE_Y - SCROLLBAR_CURSOR_RADIUS * 2);
//   BSP_LCD_FillRect(SCROLLBAR_CURSOR_POS_X + SCROLLBAR_CURSOR_RADIUS, SCROLLBAR_CURSOR_POS_Y + scrollPos, SCROLLBAR_CURSOR_SIZE_X - SCROLLBAR_CURSOR_RADIUS * 2, SCROLLBAR_CURSOR_SIZE_Y + 1);
//    
//   BSP_LCD_FillCircle(SCROLLBAR_CURSOR_POS_X + SCROLLBAR_CURSOR_RADIUS, SCROLLBAR_CURSOR_POS_Y + SCROLLBAR_CURSOR_RADIUS + scrollPos, SCROLLBAR_CURSOR_RADIUS);
//   BSP_LCD_FillCircle(SCROLLBAR_CURSOR_POS_X + SCROLLBAR_CURSOR_RADIUS, (SCROLLBAR_CURSOR_POS_Y + SCROLLBAR_CURSOR_SIZE_Y) - SCROLLBAR_CURSOR_RADIUS + scrollPos, SCROLLBAR_CURSOR_RADIUS);
//   BSP_LCD_FillCircle((SCROLLBAR_CURSOR_POS_X + SCROLLBAR_CURSOR_SIZE_X) - SCROLLBAR_CURSOR_RADIUS, (SCROLLBAR_CURSOR_POS_Y + SCROLLBAR_CURSOR_SIZE_Y) - SCROLLBAR_CURSOR_RADIUS + scrollPos, SCROLLBAR_CURSOR_RADIUS);
//   BSP_LCD_FillCircle((SCROLLBAR_CURSOR_POS_X + SCROLLBAR_CURSOR_SIZE_X) - SCROLLBAR_CURSOR_RADIUS, SCROLLBAR_CURSOR_POS_Y + SCROLLBAR_CURSOR_RADIUS + scrollPos, SCROLLBAR_CURSOR_RADIUS);
}

//Private func

void drawStaticLines()
{
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_DrawLine(STATIC_LINE_X, STATIC_LINE_Y, 350, STATIC_LINE_Y);
    BSP_LCD_DrawLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER, 350, STATIC_LINE_Y + STATIC_LINE_SPASER);
    BSP_LCD_DrawLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER*2, 350, STATIC_LINE_Y + STATIC_LINE_SPASER*2);
    BSP_LCD_DrawLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER*3, 350, STATIC_LINE_Y + STATIC_LINE_SPASER*3);
    BSP_LCD_DrawLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER*4, 350, STATIC_LINE_Y + STATIC_LINE_SPASER*4);
}