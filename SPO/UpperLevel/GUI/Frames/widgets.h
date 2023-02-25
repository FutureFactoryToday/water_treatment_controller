#ifndef _WIDG_H
#define _WIDG_H

#include "main.h"
#include "layout.h"

void drawFillButton (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t radius, uint16_t* label, uint16_t color, bool isTouch);

void drawTextLabel (uint16_t xPos, uint16_t yPos, uint16_t xSize, uint16_t ySize, uint16_t radius, uint16_t* label, uint16_t color, uint16_t color2, WTC_FONT_t* font);

void drawMainBar(bool returnBut, uint16_t xPosLogo, uint16_t yPosLogo, uint16_t* label);

typedef enum
{
    OkCancel,
    Time,
    Save
}statusBar_t;
void drawStatusBar(statusBar_t stBar);

#endif 