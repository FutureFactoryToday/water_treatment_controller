/**
  ******************************************************************************
  * @file    TFT.h
  * @brief   This file contains all the function prototypes for
  *          the TFT.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TFT_H_
#define _TFT_H_

/*Includes */
#include "main.h"
#include "SPI/SPI_Handler.h"
#include "TFT/TFT_LL.h"
//#include "..\..\GUI\Logo\LOGO_MAIN.h"
/*Public defines */
#define TFT_INIT_DEL 10

//extern const unsigned char gImage_LOGO_MAIN2;
typedef struct  
{										    
	uint16_t width;			//LCD їн¶И
	uint16_t height;			//LCD ёЯ¶И
	uint16_t id;				  //LCD ID
	uint8_t  dir;			  //єбЖБ»№КЗКъЖБїШЦЖЈє0Ј¬КъЖБЈ»1Ј¬єбЖБЎЈ	
	uint16_t	 wramcmd;		//їЄКјРґgramЦёБо
	uint16_t  setxcmd;		//ЙиЦГxЧш±кЦёБо
	uint16_t  setycmd;		//ЙиЦГyЧш±кЦёБо	 
}_lcd_dev; 	

//LCDІОКэ
extern _lcd_dev lcddev;	//№ЬАнLCDЦШТЄІОКэ
/////////////////////////////////////УГ»§ЕдЦГЗш///////////////////////////////////	 
#define USE_HORIZONTAL  	 0//¶ЁТеТєѕ§ЖБЛіК±ХлРэЧЄ·ЅПт 	0-0¶ИРэЧЄЈ¬1-90¶ИРэЧЄЈ¬2-180¶ИРэЧЄЈ¬3-270¶ИРэЧЄ
#define USE_VERTICAL 1
#define USE_HORISONTAL_180 2
#define USE_VERTICAL_180 3
//////////////////////////////////////////////////////////////////////////////////	  
//¶ЁТеLCDµДіЯґз
#define LCD_W 320
#define LCD_H 480

//»­±КСХЙ«
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //ЧШЙ«
#define BRRED 			0XFC07 //ЧШємЙ«
#define GRAY  			0X8430 //»ТЙ«
//GUIСХЙ«

#define DARKBLUE      	 0X01CF	//ЙоА¶Й«
#define LIGHTBLUE      	 0X7D7C	//ЗіА¶Й«  
#define GRAYBLUE       	 0X5458 //»ТА¶Й«
//ТФЙПИэЙ«ОЄPANELµДСХЙ« 
 
#define LIGHTGREEN     	0X841F //ЗіВМЙ«
#define LIGHTGRAY     0XEF5B //Зі»ТЙ«(PANNEL)
#define LGRAY 			 		0XC618 //Зі»ТЙ«(PANNEL),ґ°Ме±іѕ°Й«

#define LGRAYBLUE      	0XA651 //Зі»ТА¶Й«(ЦРјдІгСХЙ«)
#define LBBLUE          0X2B12 //ЗіЧША¶Й«(СЎФсМхДїµД·ґЙ«)

//TFTLCDІї·ЦНвТЄµчУГµДєЇКэ		   
extern uint16_t  POINT_COLOR;//Д¬ИПємЙ«    
extern uint16_t  BACK_COLOR; //±іѕ°СХЙ«.Д¬ИПОЄ°ЧЙ«
/*Структура пикселя*/
typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_t;

/*Global params*/
extern uint32_t TFT_ID;

/*Prototypes */
uint8_t initTFT(void);
uint8_t readID(readResult_t *result);
uint8_t placePic(uint32_t coordX, uint32_t coordY, uint32_t hight, uint32_t width, uint8_t* pic); 
uint8_t drawPixel(uint32_t coordX, uint32_t coordY, pixel_t* pix);
uint8_t drawLine (uint32_t coordX1, uint32_t coordY1, uint32_t coordX2, uint32_t coordY2, pixel_t pix);

void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(uint16_t Color);	 
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x,uint16_t y);//»­µг
uint16_t  LCD_ReadPoint(uint16_t x,uint16_t y); //¶Бµг
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);		   
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);

uint16_t LCD_RD_DATA(void);//¶БИЎLCDКэѕЭ									    
uint16_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
uint16_t LCD_ReadRAM(void);		   
uint16_t LCD_BGR2RGB(uint16_t c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(uint16_t Data);
void LCD_direction(uint8_t direction );

#endif /* __TFT_H__ */

