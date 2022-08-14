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
/* Private includes ----------------------------------------------------------*/
#include "Settings.h"
#include "TFT_LL.h"
#include "TFT_Commands.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
	uint32_t TFT_ID;
/* Private function prototypes -----------------------------------------------*/
	uint8_t setColumnAdress(uint8_t column);
	uint8_t setPageAdress(uint8_t page);
	void LCD_WR_REG (uint8_t data, uint8_t hold);
	void LCD_WR_DATA (uint8_t data, uint8_t hold);
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
/*** √Î‡‚Ì˚Â ÙÛÌÍˆËË ***/
uint8_t initTFT(void){
	uint32_t ID;
	initTFT_LL(SPI);
	rebootTFT();
	
	LCD_WR_REG(0XF1, TRUE);
	LCD_WR_DATA(0x36, TRUE);
	LCD_WR_DATA(0x04, TRUE);
	LCD_WR_DATA(0x00, TRUE);
	LCD_WR_DATA(0x3C, TRUE);
	LCD_WR_DATA(0X0F, TRUE);
	LCD_WR_DATA(0x8F, TRUE);
	LCD_WR_REG(0XF2, TRUE);
	LCD_WR_DATA(0x18, TRUE);
	LCD_WR_DATA(0xA3, TRUE);
	LCD_WR_DATA(0x12, TRUE);
	LCD_WR_DATA(0x02, TRUE);
	LCD_WR_DATA(0XB2, TRUE);
	LCD_WR_DATA(0x12, TRUE);
	LCD_WR_DATA(0xFF, TRUE);
	LCD_WR_DATA(0x10, TRUE);
	LCD_WR_DATA(0x00, TRUE);
	LCD_WR_REG(0XF8, TRUE);
	LCD_WR_DATA(0x21, TRUE);
	LCD_WR_DATA(0x04, TRUE);
	LCD_WR_REG(0XF9, TRUE);
	LCD_WR_DATA(0x00, TRUE);
	LCD_WR_DATA(0x08, TRUE);
	LCD_WR_REG(0x36, TRUE);
	LCD_WR_DATA(0x08, TRUE);
	LCD_WR_REG(0xB4, TRUE);
	LCD_WR_DATA(0x00, TRUE);
	LCD_WR_REG(0xC1, TRUE);
	LCD_WR_DATA(0x47, TRUE); //0x41
	LCD_WR_REG(0xC5, TRUE);
	LCD_WR_DATA(0x00, TRUE);
	LCD_WR_DATA(0xAF, TRUE); //0x91
	LCD_WR_DATA(0x80, TRUE);
	LCD_WR_DATA(0x00, TRUE);
	LCD_WR_REG(0xE0, TRUE);
	LCD_WR_DATA(0x0F, TRUE);
	LCD_WR_DATA(0x1F, TRUE);
	LCD_WR_DATA(0x1C, TRUE);
	LCD_WR_DATA(0x0C, TRUE);
	LCD_WR_DATA(0x0F, TRUE);
	LCD_WR_DATA(0x08, TRUE);
	LCD_WR_DATA(0x48, TRUE);
	LCD_WR_DATA(0x98, TRUE);
	LCD_WR_DATA(0x37, TRUE);
	LCD_WR_DATA(0x0A, TRUE);
	LCD_WR_DATA(0x13, TRUE);
	LCD_WR_DATA(0x04, TRUE);
	LCD_WR_DATA(0x11, TRUE);
	LCD_WR_DATA(0x0D, TRUE);
	LCD_WR_DATA(0x00, TRUE);
	LCD_WR_REG(0xE1, TRUE);
	LCD_WR_DATA(0x0F, TRUE);
	LCD_WR_DATA(0x32, TRUE);
	LCD_WR_DATA(0x2E, TRUE);
	LCD_WR_DATA(0x0B, TRUE);
	LCD_WR_DATA(0x0D, TRUE);
	LCD_WR_DATA(0x05, TRUE);
	LCD_WR_DATA(0x47, TRUE);
	LCD_WR_DATA(0x75, TRUE);
	LCD_WR_DATA(0x37, TRUE);
	LCD_WR_DATA(0x06, TRUE);
	LCD_WR_DATA(0x10, TRUE);
	LCD_WR_DATA(0x03, TRUE);
	LCD_WR_DATA(0x24, TRUE);
	LCD_WR_DATA(0x20, TRUE);
	LCD_WR_DATA(0x00, TRUE);
	LCD_WR_REG(0x3A, TRUE);
	LCD_WR_DATA(0x66, TRUE);
	LCD_WR_REG(0x11, TRUE);
	LCD_WR_REG(0x36, TRUE);
	LCD_WR_DATA(0x28, TRUE);
	LL_mDelay(120);
	LCD_WR_REG(0x29, TRUE);
	
//  LCD_direction(USE_HORIZONTAL);//…Ë÷√LCDœ‘ æ∑ΩœÚ
//	LCD_LED=1;//µ„¡¡±≥π‚	 
//	LCD_Clear(WHITE);//«Â»´∆¡∞◊…´
	
//	readResult_t readRes;
//	uint8_t readResBuf[4] = {0};
//	readRes.dataBuf = readResBuf;
//	readRes.result = 0;
//	readID(&readRes);
//	uint8_t waitTime = _1ms_cnt + 500; //∆‰ÂÏ 500 ÏÒ
//	while (readRes.result != FINISH || _1ms_cnt != waitTime);
//	if (readRes.result == FINISH) {
//		TFT_ID = (readResBuf[3]<<26) + (readResBuf[2]<<16)+ (readResBuf[1]<<8);
//		return 1;
//	}
//	
//	initTFT_LL(PARAL);
//	readRes.result = 0;
//	for(uint8_t i = 0; i< sizeof(readResBuf);i++){
//		readResBuf[i] = 0;
//	}
//	readID(&readRes);
//	waitTime = _1ms_cnt + 500; //∆‰ÂÏ 500 ÏÒ
//	while (readRes.result != FINISH || _1ms_cnt != waitTime);
//	if (readRes.result == FINISH) {
//		TFT_ID = (readResBuf[3]<<26) + (readResBuf[2]<<16)+ (readResBuf[1]<<8);
//		return 1;
//	}
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

uint8_t placePic(uint32_t coordX, uint32_t coordY, uint32_t hight, uint32_t width, uint8_t* pic){
	
}

uint8_t drawPixel(uint32_t coordX, uint32_t coordY, pixel_t* pix){
	
}

uint8_t drawLine (uint32_t coordX1, uint32_t coordY1, uint32_t coordX2, uint32_t coordY2, pixel_t pix){
	
}

/*** ¬ÌÛÚÂÌÌËÂ ÙÛÌÍˆËË  ***/
uint8_t setColumnAdress(uint8_t column){
	
}

uint8_t setPageAdress(uint8_t page){
	
}
