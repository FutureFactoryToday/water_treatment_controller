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
#include "..\..\GUI\Logo\LOGO_MAIN.h"
/*Public defines */
#define TFT_INIT_DEL 10

extern const unsigned char gImage_LOGO_MAIN2;
typedef struct  
{										    
	uint16_t width;			//LCD ¿í¶È
	uint16_t height;			//LCD ¸ß¶È
	uint16_t id;				  //LCD ID
	uint8_t  dir;			  //ºáÆÁ»¹ÊÇÊúÆÁ¿ØÖÆ£º0£¬ÊúÆÁ£»1£¬ºáÆÁ¡£	
	uint16_t	 wramcmd;		//¿ªÊ¼Ð´gramÖ¸Áî
	uint16_t  setxcmd;		//ÉèÖÃx×ø±êÖ¸Áî
	uint16_t  setycmd;		//ÉèÖÃy×ø±êÖ¸Áî	 
}_lcd_dev; 	

//LCD²ÎÊý
extern _lcd_dev lcddev;	//¹ÜÀíLCDÖØÒª²ÎÊý
/////////////////////////////////////ÓÃ»§ÅäÖÃÇø///////////////////////////////////	 
#define USE_HORIZONTAL  	 0//¶¨ÒåÒº¾§ÆÁË³Ê±ÕëÐý×ª·½Ïò 	0-0¶ÈÐý×ª£¬1-90¶ÈÐý×ª£¬2-180¶ÈÐý×ª£¬3-270¶ÈÐý×ª
#define USE_VERTICAL 1
#define USE_HORISONTAL_180 2
#define USE_VERTICAL_180 3
//////////////////////////////////////////////////////////////////////////////////	  
//¶¨ÒåLCDµÄ³ß´ç
#define LCD_W 320
#define LCD_H 480

//»­±ÊÑÕÉ«
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
#define BROWN 			0XBC40 //×ØÉ«
#define BRRED 			0XFC07 //×ØºìÉ«
#define GRAY  			0X8430 //»ÒÉ«
//GUIÑÕÉ«

#define DARKBLUE      	 0X01CF	//ÉîÀ¶É«
#define LIGHTBLUE      	 0X7D7C	//Ç³À¶É«  
#define GRAYBLUE       	 0X5458 //»ÒÀ¶É«
//ÒÔÉÏÈýÉ«ÎªPANELµÄÑÕÉ« 
 
#define LIGHTGREEN     	0X841F //Ç³ÂÌÉ«
#define LIGHTGRAY     0XEF5B //Ç³»ÒÉ«(PANNEL)
#define LGRAY 			 		0XC618 //Ç³»ÒÉ«(PANNEL),´°Ìå±³¾°É«

#define LGRAYBLUE      	0XA651 //Ç³»ÒÀ¶É«(ÖÐ¼ä²ãÑÕÉ«)
#define LBBLUE          0X2B12 //Ç³×ØÀ¶É«(Ñ¡ÔñÌõÄ¿µÄ·´É«)

//TFTLCD²¿·ÖÍâÒªµ÷ÓÃµÄº¯Êý		   
extern uint16_t  POINT_COLOR;//Ä¬ÈÏºìÉ«    
extern uint16_t  BACK_COLOR; //±³¾°ÑÕÉ«.Ä¬ÈÏÎª°×É«
/*Ñòðóêòóðà ïèêñåëÿ*/
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
void LCD_DrawPoint(uint16_t x,uint16_t y);//»­µã
uint16_t  LCD_ReadPoint(uint16_t x,uint16_t y); //¶Áµã
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);		   
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);

uint16_t LCD_RD_DATA(void);//¶ÁÈ¡LCDÊý¾Ý									    
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

