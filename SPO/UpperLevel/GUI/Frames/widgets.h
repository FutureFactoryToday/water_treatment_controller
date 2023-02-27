#ifndef _WIDG_H
#define _WIDG_H

#include "main.h"
#include "layout.h"

void drawFillButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t radius, uint16_t* label, uint16_t color, bool isTouch);

void drawTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t radius, uint16_t* label, uint16_t color, uint16_t color2);

void drawMainBar(bool returnBut, uint16_t xPosLogo, uint16_t yPosLogo, uint16_t* label);

void drawMainWindow();

typedef enum
{
    OkCancel,
    Time,
    Save
}statusBar_t;
void drawStatusBarOkCancel();

void drawStatusBarSave(uint16_t* label);

void drawStatusBarEmpty();

void drawScrollButton (uint16_t scPos);

#endif 