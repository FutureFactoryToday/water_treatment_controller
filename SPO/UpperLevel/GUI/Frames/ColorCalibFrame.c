#include "ColorCalibFrame.h"

static void createFrame();

uint32_t result_color = 0;
uint16_t red = 0;
uint16_t green = 0;
uint16_t blue = 0;
static button_t start, redBut, greenBut, blueBut;

void ShowColorCalibFrame(void)
{
    createFrame();
	while(1)
	{
        if (updateFlags.sec == true){
            drawClock();
            updateFlags.sec = false;
        }
        

        if (start.isPressed == true){
			drawFillButton(25, 80, 200, 40, "Старт", true);
			start.isPressed = false;
		}
        if (redBut.isPressed == true){
            drawDarkTextLabel(25,126,200,40,intToStr(red));
			redBut.isPressed = false;
		}        
        if (greenBut.isPressed == true){
            drawDarkTextLabel(25,172,200,40,intToStr(green));
			greenBut.isPressed = false;
		}        
        if (blueBut.isPressed == true){
            drawDarkTextLabel(25,219,200,40,intToStr(blue));
			blueBut.isPressed = false;
		}
        
		if(retBut.isPressed == true){
			return;
        }   
            
        if (start.isReleased == true){
            drawFillButton(25, 80, 200, 40, "Старт", false);
			start.isReleased = false;
		}
        if (redBut.isReleased == true){
            red = ShowKeyboardFrame(0,31);
            createFrame();
			redBut.isReleased = false;
		}
        if (greenBut.isReleased == true){
            green = ShowKeyboardFrame(0,63);
            createFrame();
			greenBut.isReleased = false;
		}
        if (blueBut.isReleased == true){
            blue = ShowKeyboardFrame(0,31);
            createFrame();
			blueBut.isReleased = false;
		}
	}
}

void createFrame(void)
{
	TC_clearButtons();
	//Static refresh

    drawMainBar(true, 190, 5, " ");
    
    drawMainWindow();
    
    BSP_LCD_SetTextColor(result_color);    
    BSP_LCD_FillRect(253, 80, 200, 180);
    
    start = drawFillButton(25, 80, 200, 40, "Старт", false);
    redBut = drawTextLabel(25, 126, 200, 40, intToStr(red));
    greenBut = drawTextLabel(25, 172, 200, 40, intToStr(green));
    blueBut = drawTextLabel(25, 219, 200, 40, intToStr(blue));
    
    BSP_LCD_SetTextColor(LCD_COLOR_RED);    
    BSP_LCD_FillCircle(205, 146, 12);
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);    
    BSP_LCD_FillCircle(205, 192, 12);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITEBLUE);    
    BSP_LCD_FillCircle(205, 238, 12);
    
    drawStatusBarEmpty();
    
    drawClock();
	
	/*Add buttons settings*/
	
	/*Add Buttons*/
    TC_addButton(&start);
    TC_addButton(&redBut);
    TC_addButton(&greenBut);
    TC_addButton(&blueBut);
    TC_addButton(&retBut);
}
