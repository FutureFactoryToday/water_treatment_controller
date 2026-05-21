#ifndef _WIDG_H
#define _WIDG_H

#include "main.h"
#include "layout.h"

button_t drawFillButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label, bool isTouch);

button_t drawFillCustomButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label, uint8_t *pBmp, uint16_t butColor, uint16_t backColor, uint16_t textColor, bool isTouch);

button_t drawFillArcRec (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t color);

button_t drawTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label);
button_t drawDarkTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label);
button_t drawLightTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label);

void drawMainBar(bool returnBut, bool homeBut, uint16_t xPosLogo, uint16_t yPosLogo, uint8_t* label);

void drawMainWindow(void);

void drawList(uint8_t scrollCnt);

typedef enum
{
    OkCancel,
    Time,
    Save
}statusBar_t;

void drawStatusBarOkCancel(void);

 void drawStatusBarOkCancelCustom(uint8_t* okBut, uint8_t* cancelBut);

void drawStatusBarSave(uint8_t* label);

void drawStatusBarLabel(uint8_t* label);

void drawStatusBarEmpty(void);

void drawMainStatusBar(uint16_t nextСycleTime, uint16_t сurrentWaterConsumption, uint16_t amountOfWater);

void drawScrollButton (uint16_t scPos);

void drawStaticLines(void);

void drawClock(void);

button_t drawCustomTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label,uint16_t textColor, uint16_t backColor);

button_t drawCustom2TextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label1, uint8_t* label2 ,uint16_t textColor, uint16_t backColor);
button_t drawCustom3TextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label1, uint8_t* label2 ,uint16_t textColor, uint16_t backColor);

void drawDebugInfo(void);
#endif 
