/**
  ******************************************************************************
  * @file           : TFT.c
  * @brief          : 
  ******************************************************************************
  * @attention
  *
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "TFT.h"

/* Private includes ----------------------------------------------------------*/
#include "Settings.h"
#include "TFT_LL.h"
#include "TFT_Commands.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
_lcd_dev lcddev;

//»­±ÊÑÕÉ«,±³¾°ÑÕÉ«
uint16_t POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF; 
	uint32_t TFT_ID;
/* Private function prototypes -----------------------------------------------*/
	uint8_t setColumnAdress(uint8_t column);
	uint8_t setPageAdress(uint8_t page);
	void LCD_WR_REG (uint8_t data, uint8_t hold);
	void LCD_WR_DATA (uint8_t data, uint8_t hold);
	void LCD_WR_DATA_PIX (uint8_t* data, uint8_t hold);
	
/* Private user code ---------------------------------------------------------*/
void LCD_WR_REG (uint8_t data, uint8_t hold){
	readResult_t msg;
	msg.dataBuf = &data;
	msg.result = 0;
	
	processMsg(&msg,1,COMMAND,SEND,hold);
	while(msg.result != FINISH);
	
}
	void LCD_WR_DATA (uint8_t data, uint8_t hold){
	readResult_t msg;
	msg.dataBuf = &data;
	msg.result = 0;
	
	processMsg(&msg,1,DATA,SEND,hold);
	while(msg.result != FINISH);
	}
	
	void LCD_WR_DATA_PIX (uint8_t* data, uint8_t hold){
	readResult_t msg;
	msg.dataBuf = data;
	msg.result = 0;
	
	processMsg(&msg,3,DATA,SEND,hold);
	while(msg.result != FINISH);
	}
/*** Ãëàâíûå ôóíêöèè ***/
uint8_t initTFT(void){
	uint32_t ID;
	initTFT_LL(SPI);
	rebootTFT();
	
	LCD_WR_REG(0XF1, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x36, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x04, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x00, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x3C, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0X0F, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x8F, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0XF2, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x18, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0xA3, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x12, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x02, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0XB2, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x12, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0xFF, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x10, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x00, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0XF8, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x21, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x04, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0XF9, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x00, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x08, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0x36, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x08, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0xB4, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x00, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0xC1, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x47, TRUE); //0x41
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0xC5, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x00, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0xAF, TRUE); //0x91
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x80, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x00, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0xE0, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x0F, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x1F, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x1C, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x0C, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x0F, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x08, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x48, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x98, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x37, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x0A, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x13, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x04, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x11, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x0D, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x00, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0xE1, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x0F, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x32, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x2E, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x0B, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x0D, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x05, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x47, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x75, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x37, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x06, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x10, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x03, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x24, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x20, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x00, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0x3A, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x66, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0x11, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	
	LCD_WR_REG(0x36, TRUE);
	LL_mDelay(TFT_INIT_DEL);
	LCD_WR_DATA(0x28, TRUE);
	
	#ifndef SIM
	LL_mDelay(120);
	#endif
	LCD_WR_REG(0x29, FALSE);
	LL_mDelay(TFT_INIT_DEL);
  LCD_direction(USE_VERTICAL);//ÉèÖÃLCDÏÔÊ¾·½Ïò
	
	LCD_Clear(WHITE);
	LL_mDelay(100);
	//Pic_test();
	//LL_mDelay(1000);
	//Rotate_Test();
	//LL_mDelay(1000);
	//LCD_Clear(WHITE);
	uint8_t x_cent = (480 - 150)/2;
	uint8_t y_cent = (320-150)/2;
	Gui_Drawbmp16(x_cent,y_cent ,150,150,&gImage_LOGO_MAIN2);
	return 0;
}

uint8_t readID(readResult_t *result){
	readResult_t cmdBuf;
	uint8_t cmd = ILI_READ_ID;
	cmdBuf.result = 0;
	cmdBuf.dataBuf = &cmd;
	uint8_t res = processMsg(&cmdBuf,1, COMMAND, SEND, TRUE);
	res &= processMsg(result, 4,DATA,RCV,FALSE);
	return res;
}

//uint8_t placePic(uint32_t coordX, uint32_t coordY, uint32_t hight, uint32_t width, uint8_t* pic){
//	
//}

//uint8_t drawPixel(uint32_t coordX, uint32_t coordY, pixel_t* pix){
//	
//}

//uint8_t drawLine (uint32_t coordX1, uint32_t coordY1, uint32_t coordX2, uint32_t coordY2, pixel_t pix){
//	
//}

///*** Âíóòðåííèå ôóíêöèè  ***/
//uint8_t setColumnAdress(uint8_t column){
//	
//}

//uint8_t setPageAdress(uint8_t page){
//	
//}
/*****************************************************************************
 * @name       :void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd,TRUE);	
	LCD_WR_DATA(xStar>>8,TRUE);
	LCD_WR_DATA(0x00FF&xStar,TRUE);		
	LCD_WR_DATA(xEnd>>8,TRUE);
	LCD_WR_DATA(0x00FF&xEnd,TRUE);

	LCD_WR_REG(lcddev.setycmd,TRUE);	
	LCD_WR_DATA(yStar>>8,TRUE);
	LCD_WR_DATA(0x00FF&yStar,TRUE);		
	LCD_WR_DATA(yEnd>>8,TRUE);
	LCD_WR_DATA(0x00FF&yEnd,TRUE);

	LCD_WriteRAM_Prepare();	//¿ªÊ¼Ð´ÈëGRAM		
//	LCD_WR_REG(ILI_NOP, FALSE);
}   

/*****************************************************************************
 * @name       :void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);	
} 

/*****************************************************************************
 * @name       :void LCD_direction(uint8_t direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/ 
void LCD_direction(uint8_t direction)
{ 
			lcddev.setxcmd=0x2A;
			lcddev.setycmd=0x2B;
			lcddev.wramcmd=0x2C;
	switch(direction){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;		
			LCD_WriteReg(0x36,(1<<6)|(1<<3));//0 degree MY=0,MX=0,MV=0,ML=0,BGR=1,MH=0
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(1<<5));//90 degree MY=0,MX=1,MV=1,ML=1,BGR=1,MH=0
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			LCD_WriteReg(0x36,(1<<3)|(1<<7));//180 degree MY=1,MX=1,MV=0,ML=0,BGR=1,MH=0
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(1<<5)|(1<<6)|(1<<7));//270 degree MY=1,MX=0,MV=1,ML=0,BGR=1,MH=0
		break;	
		default:break;
	}	
}	 
/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd, FALSE);
}	 

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(uint16_t Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/	 
void Lcd_WriteData_16Bit(uint16_t Data)
{	
  //18Bit	
	uint8_t tempBuf[3];
	tempBuf[0] = (Data>>8)&0xF8;
	tempBuf[1] = (Data>>3)&0xFC;
	tempBuf[2] = Data<<3&0xF8;
	LCD_WR_DATA_PIX(tempBuf,TRUE);//RED
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(uint16_t x,uint16_t y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/	
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_SetCursor(x,y);//ÉèÖÃ¹â±êÎ»ÖÃ 
	Lcd_WriteData_16Bit(POINT_COLOR); 
}

/*****************************************************************************
 * @name       :void LCD_Clear(uint16_t Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/	
void LCD_Clear(uint16_t Color)
{
  unsigned int i,m;  
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);   
	for(i=0;i<lcddev.height;i++)
	{
    for(m=0;m<lcddev.width;m++)
    {	
			Lcd_WriteData_16Bit(Color);
		}
	}
//	LCD_WR_REG(ILI_NOP,FALSE);
} 
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg,TRUE);  
	LCD_WR_DATA(LCD_RegValue, FALSE);	    		 
}	 