#ifndef _WIDG_H
#define _WIDG_H

#include "main.h"
#include "layout.h"

button_t drawFillButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label, bool isTouch);

void drawFillArcRec (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t color);

button_t drawTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label);
button_t drawDarkTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint8_t* label);

void drawMainBar(bool returnBut, uint16_t xPosLogo, uint16_t yPosLogo, uint8_t* label);

void drawMainWindow();

void drawList(uint8_t scrollCnt);

typedef enum
{
    OkCancel,
    Time,
    Save
}statusBar_t;

void drawStatusBarOkCancel();

void drawStatusBarSave(uint8_t* label);

void drawStatusBarEmpty();

void drawScrollButton (uint16_t scPos);

void drawStaticLines();
#endif 