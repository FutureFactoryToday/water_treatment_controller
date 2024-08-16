#include "widgets.h"

uint8_t x1 = 75, y1 = 0, y2 = 10, y3 = 20, y4 = 30;
void drawDebugInfo(){
	if (sysParams.vars.status.flags.DebugMode == true){
		WTC_FONT_t* oldFont = BSP_LCD_GetFont();
		uint16_t oldBackColor = BSP_LCD_GetBackColor();
		uint16_t oldTextColor = BSP_LCD_GetTextColor();
		
		BSP_LCD_SetFont(&Oxygen_Mono_8);
		BSP_LCD_SetBackColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_DrawBuffer_Start(x1,y1,400,y2, LCD_COLOR_DARKBLUE);
		uint32_t offset = 0;
		offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,"CurPoz = ",LEFT_MODE);
		offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,intToStr(sysParams.vars.pistonParams.curPoz),LEFT_MODE);
		offset += 10;
		
		offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,"DestPoz = ",LEFT_MODE);
		offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,intToStr(sysParams.vars.pistonParams.destPoz),LEFT_MODE);
		offset += 10;
		
		offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,"MotSpeed% = ",LEFT_MODE);
		offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,intToStr(sysParams.consts.maxMotorSpeedPercent),LEFT_MODE);
		offset += 10;
		
		offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,"Planner = ",LEFT_MODE);
		switch(sysParams.consts.planerConsts.status){
			case(PL_NOT_SET):{
				offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,"Not Set",LEFT_MODE);
				break;
			}
			case(PL_SET):{
				offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,"Set",LEFT_MODE);
				break;
			}
			case(PL_WORKING):{
				offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,"Working",LEFT_MODE);
				break;
			}
			default: {
				offset += BSP_LCD_DisplayStringAt(x1 + offset,y1,"Error",LEFT_MODE);
			}
		}
		
		
		BSP_LCD_DrawBuffer_Stop();
		BSP_LCD_SetFont(oldFont);
		BSP_LCD_SetBackColor(oldBackColor);
		BSP_LCD_SetTextColor(oldTextColor);
	}
}
button_t drawFillButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label, bool isTouch)
{
	uint16_t oldBackColor = BSP_LCD_GetBackColor();
	uint16_t oldTextColor = BSP_LCD_GetTextColor();
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

		BSP_LCD_DrawBuffer_Start(xPos,yPos,xSize,ySize, LCD_COLOR_WHITE);
		
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
        
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 15, label, CENTER_MODE);
		BSP_LCD_SetTextColor(oldTextColor);
		BSP_LCD_SetBackColor(oldBackColor);
		
		BSP_LCD_DrawBuffer_Stop();
    return but;
}

button_t drawFillCustomButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label, uint8_t *pBmp, uint16_t color, uint16_t backColor, bool isTouch)
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
        BSP_LCD_SetBackColor(backColor);
    }
//    if(radius != 0)
//    {
		BSP_LCD_DrawBuffer_Start(xPos,yPos,xSize,ySize, LCD_COLOR_WHITE);
		
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
        
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
    
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetBackColor(color);
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    BSP_LCD_DisplayStringAt(xPos + 20, yPos + ySize/2 - 15, label, LEFT_MODE);
    BSP_LCD_SetFont(&Oxygen_Mono_24);
		
    BSP_LCD_DrawBuffer_Stop();
		
    BSP_LCD_DrawBitmap(xPos + xSize - 45,yPos + 10, pBmp);
    
    return but;
}


button_t drawFillArcRec (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t color)
{
		button_t but;
    uint16_t oldTextColor = BSP_LCD_GetTextColor();
    uint16_t oldBackColor = BSP_LCD_GetBackColor();
    
    uint16_t radius = ySize/4;
    BSP_LCD_SetTextColor(color);
    
		BSP_LCD_DrawBuffer_Start(xPos,yPos,xSize,ySize+1, LCD_COLOR_WHITE);
	
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
        
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
  
		BSP_LCD_DrawBuffer_Stop();
	
    BSP_LCD_SetTextColor(oldTextColor);
    BSP_LCD_SetBackColor(oldBackColor);
	
    but.x = xPos;
    but.y = yPos;
    but.xSize = xSize;
    but.ySize = ySize; 
    but.isPressed = false;
    but.wasPressed = false;
    but.isReleased = false;
    but.pressCnt = false;
	
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
		BSP_LCD_DrawBuffer_Start(xPos,yPos,xSize,ySize+1, LCD_COLOR_WHITE);
	
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
    
		BSP_LCD_DrawBuffer_Stop();
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
		BSP_LCD_DrawBuffer_Start(xPos,yPos,xSize,ySize, LCD_COLOR_WHITE);
		
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
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 15, label, CENTER_MODE);
    BSP_LCD_SetFont(&Oxygen_Mono_24);
    BSP_LCD_SetTextColor(oldTextColor);
		BSP_LCD_SetBackColor(oldBackColor);
		BSP_LCD_DrawBuffer_Stop();
    return but;
}

button_t drawCustom2TextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label1, uint8_t* label2, uint16_t textColor, uint16_t backColor)
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
    
	BSP_LCD_DrawBuffer_Start(xPos,yPos,xSize,ySize, LCD_COLOR_WHITE);
	
    BSP_LCD_SetTextColor(backColor);
    BSP_LCD_FillRect(xPos, yPos + radius, xSize, ySize - radius * 2);
    BSP_LCD_FillRect(xPos + radius, yPos, xSize - radius * 2, ySize + 1);
    
    BSP_LCD_FillCircle(xPos + radius, yPos + radius, radius);
    BSP_LCD_FillCircle(xPos + radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, (yPos + ySize) - radius, radius);
    BSP_LCD_FillCircle((xPos + xSize) - radius, yPos + radius, radius);
   
    BSP_LCD_SetBackColor(backColor);
    BSP_LCD_SetTextColor(textColor);
    BSP_LCD_SetFont(&Oxygen_Mono_20);
    BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 25 + 18, label2, CENTER_MODE);
		BSP_LCD_DisplayStringAt(xPos + xSize/2, yPos + ySize/2 - 25, label1, CENTER_MODE);
    BSP_LCD_SetFont(&Oxygen_Mono_24);
    BSP_LCD_SetTextColor(oldTextColor);
		BSP_LCD_SetBackColor(oldBackColor);
		BSP_LCD_DrawBuffer_Stop();
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
	 BSP_LCD_DrawBuffer_Start(xPos,yPos,xSize,ySize, LCD_COLOR_WHITE);
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
    BSP_LCD_DrawBuffer_Stop();
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
	BSP_LCD_DrawBuffer_Start(xPos,yPos,xSize,ySize, LCD_COLOR_WHITE);
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
    BSP_LCD_DrawBuffer_Stop();
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
        BSP_LCD_DrawBitmap(RETURN_BUT_POS_X + 10, RETURN_BUT_POS_Y + 10, &Logo);
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


void drawStatusBarOkCancel()
{
	BSP_LCD_DrawBuffer_Start(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y, LCD_COLOR_WHITEBLUE);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(CANCEL_X, CANCEL_Y, CANCEL, LEFT_MODE);
    BSP_LCD_DisplayStringAt(OK_X, OK_Y, OK, LEFT_MODE);
	BSP_LCD_DrawBuffer_Stop();
}

void drawStatusBarSave(uint8_t* label)
{
   BSP_LCD_DrawBuffer_Start(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y, LCD_COLOR_WHITEBLUE);

    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(SAVE_X,SAVE_Y,SAVE,LEFT_MODE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(TEXT_X, TEXT_Y ,label, LEFT_MODE);
	BSP_LCD_DrawBuffer_Stop();
}

void drawStatusBarLabel(uint8_t* label)
{
   BSP_LCD_DrawBuffer_Start(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X,STATUSBAR_SIZE_Y, LCD_COLOR_WHITEBLUE);
    
    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(TEXT_X, TEXT_Y ,label, LEFT_MODE);
	BSP_LCD_DrawBuffer_Stop();
}


void drawStatusBarEmpty()
{
    BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y,STATUSBAR_SIZE_X, STATUSBAR_SIZE_Y);
}
static int16_t xOff = 0;
void drawMainStatusBar(uint16_t nextСycleTime, uint16_t сurrentWaterConsumption, uint16_t amountOfWater)
{

		uint8_t offset;		
		BSP_LCD_SetFont(&Oxygen_Mono_20);
	
    BSP_LCD_DrawBuffer_Start(STATUSBAR_POS_X, STATUSBAR_POS_Y, CLOCK_X, STATUSBAR_SIZE_Y,LCD_COLOR_WHITEBLUE);

//    BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
//    BSP_LCD_FillRect(STATUSBAR_POS_X,STATUSBAR_POS_Y, CLOCK_X, STATUSBAR_SIZE_Y);
	
		if(sysParams.consts.planerConsts.startType != IMMEDIATELY){
			int32_t deltTime = sysParams.vars.planer.currentTask->startDateTime - getRTC();
			uint32_t remHours = 0;
			BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			if (sysParams.vars.error.flags.PistonFail != 1 && deltTime >= 0){
				remHours = deltTime/(60*60);
				offset = BSP_LCD_DisplayStringAt(TEXT_X, TEXT_Y ,intToStr(remHours), LEFT_MODE);
				BSP_LCD_DisplayStringAt(TEXT_X + offset + 5, TEXT_Y , NEXT_CYCLE_TIME, LEFT_MODE);
			} else {
				BSP_LCD_DisplayStringAt(TEXT_X, TEXT_Y ,"", LEFT_MODE); 
			}
    }
    BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		//float speed = sysParams.vars.flowCnt;
		float speed = FM_getFlowSpeed()*60;
		offset = 0;
		if (speed > 0){
	/*Float output*/
//			uint32_t a = (int) speed;
//			speed = speed - a;
//			speed = speed * 100;
//			uint32_t b = (int) speed;
//			BSP_LCD_DisplayStringAt(TEXT_X + 110, TEXT_Y ,intToStr(a), RIGHT_MODE);
//			offset += BSP_LCD_DisplayStringAt(TEXT_X + 110 + offset, TEXT_Y ,",", LEFT_MODE);
//			offset += BSP_LCD_DisplayStringAt(TEXT_X + 110 + offset, TEXT_Y ,intToStr(b), LEFT_MODE);
			
		/*Int output*/
			uint32_t a = (uint32_t) round(speed);

			BSP_LCD_DisplayStringAt(TEXT_X + 110, TEXT_Y ,intToStr(a), RIGHT_MODE);
			//offset += BSP_LCD_DisplayStringAt(TEXT_X + 110 + offset, TEXT_Y ,",", LEFT_MODE);
			//offset += BSP_LCD_DisplayStringAt(TEXT_X + 110 + offset, TEXT_Y ,intToStr(b), LEFT_MODE);
		} else {
			offset += BSP_LCD_DisplayStringAt(TEXT_X + 110, TEXT_Y ,intToStr(0), LEFT_MODE);
		}
		
//		offset = BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 - 2, TEXT_Y ,intToStr(sysParams.vars.flowImpulseCnt), RIGHT_MODE);
//		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()/2 + 2, TEXT_Y ,"имп", LEFT_MODE);
    //offset = BSP_LCD_DisplayStringAt(TEXT_X + 110, TEXT_Y ,intToStr(FM_getFlowHzInt()), LEFT_MODE);
		
		BSP_LCD_DisplayStringAt(TEXT_X + 120 + offset + 5, TEXT_Y ,CURRENT_WATER_CONSUMPTION_LITERS, LEFT_MODE);
    
		if(sysParams.consts.planerConsts.startType == IMMEDIATELY || sysParams.consts.planerConsts.startType == UNIVERSAL){
			BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			int32_t remWater = sysParams.consts.planerConsts.filtroCycle - sysParams.consts.waterFromLastFilter;
			if (remWater < 0) {
				remWater = 0;
			}
			if (sysParams.vars.status.flags.WaterInLiters == true){
				BSP_LCD_DisplayStringAt(TEXT_X + 330 - 2 + xOff, TEXT_Y ,intToStr(remWater), RIGHT_MODE);
				BSP_LCD_DisplayStringAt(TEXT_X + 330 + 2 + xOff, TEXT_Y ,LITERS, LEFT_MODE);
			} else {
				BSP_LCD_DisplayStringAt(TEXT_X + 330 - 2 + xOff, TEXT_Y ,intToStr(remWater/1000), RIGHT_MODE);
				BSP_LCD_DisplayStringAt(TEXT_X + 330 + 2 + xOff, TEXT_Y ,M_CUBE, LEFT_MODE);
			}
		}
		BSP_LCD_DrawBuffer_Stop();
}

void drawScrollButton (uint16_t scPos)
{
   uint16_t scrollPos = scPos * 45;
   BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
	
  BSP_LCD_DrawBuffer_Start(SCROLLKEYUP_POS_X, SCROLLKEYUP_POS_Y, SCROLLKEYUP_SIZE_X, SCROLLKEYUP_SIZE_Y + 1,LCD_COLOR_WHITE);
	
   BSP_LCD_FillRect(SCROLLKEYUP_POS_X, SCROLLKEYUP_POS_Y + SCROLLBAR_RADIUS, SCROLLKEYUP_SIZE_X, SCROLLKEYUP_SIZE_Y - SCROLLBAR_RADIUS * 2);
   BSP_LCD_FillRect(SCROLLKEYUP_POS_X + SCROLLBAR_RADIUS, SCROLLKEYUP_POS_Y, SCROLLKEYUP_SIZE_X - SCROLLBAR_RADIUS * 2, SCROLLKEYUP_SIZE_Y + 1);
    
   BSP_LCD_FillCircle(SCROLLKEYUP_POS_X + SCROLLBAR_RADIUS, SCROLLKEYUP_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle(SCROLLKEYUP_POS_X + SCROLLBAR_RADIUS, (SCROLLKEYUP_POS_Y + SCROLLKEYUP_SIZE_Y) - SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle((SCROLLKEYUP_POS_X + SCROLLKEYUP_SIZE_X) - SCROLLBAR_RADIUS, (SCROLLKEYUP_POS_Y + SCROLLKEYUP_SIZE_Y) - SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle((SCROLLKEYUP_POS_X + SCROLLKEYUP_SIZE_X) - SCROLLBAR_RADIUS, SCROLLKEYUP_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
	BSP_LCD_DrawBuffer_Stop();
   BSP_LCD_DrawBitmap(UP_ARROW_POS_X + 13, UP_ARROW_POS_Y + 10 ,&gImage_ARROWUP);
    
  BSP_LCD_DrawBuffer_Start(SCROLLKEYDOWN_POS_X, SCROLLKEYDOWN_POS_Y, SCROLLKEYDOWN_SIZE_X, SCROLLKEYDOWN_SIZE_Y + 1,LCD_COLOR_WHITE); 
   BSP_LCD_FillRect(SCROLLKEYDOWN_POS_X, SCROLLKEYDOWN_POS_Y + SCROLLBAR_RADIUS, SCROLLKEYDOWN_SIZE_X, SCROLLKEYDOWN_SIZE_Y - SCROLLBAR_RADIUS * 2);
   BSP_LCD_FillRect(SCROLLKEYDOWN_POS_X + SCROLLBAR_RADIUS, SCROLLKEYDOWN_POS_Y, SCROLLKEYDOWN_SIZE_X - SCROLLBAR_RADIUS * 2, SCROLLKEYDOWN_SIZE_Y + 1);
    
   BSP_LCD_FillCircle(SCROLLKEYDOWN_POS_X + SCROLLBAR_RADIUS, SCROLLKEYDOWN_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle(SCROLLKEYDOWN_POS_X + SCROLLBAR_RADIUS, (SCROLLKEYDOWN_POS_Y + SCROLLKEYDOWN_SIZE_Y) - SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle((SCROLLKEYDOWN_POS_X + SCROLLKEYDOWN_SIZE_X) - SCROLLBAR_RADIUS, (SCROLLKEYDOWN_POS_Y + SCROLLKEYDOWN_SIZE_Y) - SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
   BSP_LCD_FillCircle((SCROLLKEYDOWN_POS_X + SCROLLKEYDOWN_SIZE_X) - SCROLLBAR_RADIUS, SCROLLKEYDOWN_POS_Y + SCROLLBAR_RADIUS, SCROLLBAR_RADIUS);
	BSP_LCD_DrawBuffer_Stop();
   BSP_LCD_DrawBitmap(DOWN_ARROW_POS_X + 13, DOWN_ARROW_POS_Y + 10 ,&gImage_ARROWDOWN);
 }

//Private func

void drawStaticLines()
{
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_DrawHLine(STATIC_LINE_X, STATIC_LINE_Y, FIRST_CURSOR_SIZE_X - FIRST_CURSOR_POS_X);
	BSP_LCD_DrawHLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER, FIRST_CURSOR_SIZE_X - FIRST_CURSOR_POS_X);
	BSP_LCD_DrawHLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER*2, FIRST_CURSOR_SIZE_X - FIRST_CURSOR_POS_X);
	BSP_LCD_DrawHLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER*3, FIRST_CURSOR_SIZE_X - FIRST_CURSOR_POS_X);
	BSP_LCD_DrawHLine(STATIC_LINE_X, STATIC_LINE_Y + STATIC_LINE_SPASER*4, FIRST_CURSOR_SIZE_X - FIRST_CURSOR_POS_X);
  
}
void drawClock(void){
    
	uint16_t oldTextColor = BSP_LCD_GetTextColor();
	uint16_t oldBackColor = BSP_LCD_GetBackColor();
	time_t rtcTime = LL_RTC_TIME_Get(RTC);
	wtc_time_t time = intToWTCTime(rtcTime);
	BSP_LCD_SetFont(&Oxygen_Mono_20);
	
	BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITEBLUE);
	//BSP_LCD_FillRect(HOUR_X,STATUSBAR_POS_Y,100,STATUSBAR_SIZE_Y);
	BSP_LCD_DrawBuffer_Start(HOUR_X, STATUSBAR_POS_Y, 90, STATUSBAR_SIZE_Y,LCD_COLOR_WHITEBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	if (getTime().second % 2){
		BSP_LCD_DisplayStringAt(DIV_X, CLOCK_Y, getFormatedTime(" "),LEFT_MODE);
		
	} else {
		BSP_LCD_DisplayStringAt(DIV_X, CLOCK_Y, ":",LEFT_MODE);
	}
  BSP_LCD_DisplayStringAt(DIV_X - 3, CLOCK_Y, getFormatedTimeFromSource("hh", &time),RIGHT_MODE);
	BSP_LCD_DisplayStringAt(DIV_X + 7, CLOCK_Y, getFormatedTimeFromSource("mm", &time),LEFT_MODE);
	
  BSP_LCD_SetTextColor(oldTextColor);
  BSP_LCD_SetBackColor(oldBackColor);
	BSP_LCD_DrawBuffer_Stop();
	
	drawDebugInfo();
}
