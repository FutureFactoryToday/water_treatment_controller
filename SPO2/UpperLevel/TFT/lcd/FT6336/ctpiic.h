#ifdef ST7796S
#ifndef __CTPIIC_H
#include <stdint.h>
  	   		   
//
#define CTP_SDA_IN()  {LL_GPIO_SetPinMode(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin,LL_GPIO_MODE_FLOATING);}
#define CTP_SDA_OUT() {LL_GPIO_SetPinMode(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin,LL_GPIO_MODE_OUTPUT);LL_GPIO_SetPinOutputType(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin,LL_GPIO_OUTPUT_OPENDRAIN);}
//	 
#define SET_CTP_IIC_SCL    LL_GPIO_SetOutputPin(TOUCH_SCL_GPIO_Port,TOUCH_SCL_Pin)//PBout(5) 			//SCL     
#define SET_CTP_IIC_SDA    LL_GPIO_SetOutputPin(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin)//PAout(9) 			//SDA	 
#define CLR_CTP_IIC_SCL    LL_GPIO_ResetOutputPin(TOUCH_SCL_GPIO_Port,TOUCH_SCL_Pin)//PBout(5) 			//SCL     
#define CLR_CTP_IIC_SDA    LL_GPIO_ResetOutputPin(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin)//PAout(9) 			//SDA	 
#define CTP_READ_SDA   		 LL_GPIO_IsInputPinSet(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin)//PAin(9)  			// 

//
void CTP_IIC_Init(void);                	//			 
void CTP_IIC_Start(void);				//
void CTP_IIC_Stop(void);	  				//
void CTP_IIC_Send_Byte(uint8_t txd);			//
uint8_t CTP_IIC_Read_Byte(unsigned char ack);	//
uint8_t CTP_IIC_Wait_Ack(void); 				//
void CTP_IIC_Ack(void);					
void CTP_IIC_NAck(void);					
void CTP_Delay(uint8_t Delay);
#endif


#endif




