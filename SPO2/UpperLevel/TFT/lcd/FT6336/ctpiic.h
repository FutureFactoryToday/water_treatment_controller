
#ifndef __CTPIIC_H
#include <stdint.h>
  	   		   
//IIC IO方向设置
#define CTP_SDA_IN()  {LL_GPIO_SetPinMode(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin,LL_GPIO_MODE_FLOATING);LL_GPIO_SetPinPull(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin,LL_GPIO_PULL_UP);}//{GPIOA->CFGHR&=0XFFFFFF0F;GPIOA->CFGHR|=8<<4*1;}
#define CTP_SDA_OUT() {LL_GPIO_SetPinMode(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin,LL_GPIO_OUTPUT_OPENDRAIN);LL_GPIO_SetPinPull(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin,LL_GPIO_PULL_UP);}//{GPIOA->CFGHR&=0XFFFFFF0F;GPIOA->CFGHR|=3<<4*1;}

//IO操作函数	 
#define SET_CTP_IIC_SCL    LL_GPIO_SetOutputPin(TOUCH_SCL_GPIO_Port,TOUCH_SCL_Pin)//PBout(5) 			//SCL     
#define SET_CTP_IIC_SDA    LL_GPIO_SetOutputPin(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin)//PAout(9) 			//SDA	 
#define CLR_CTP_IIC_SCL    LL_GPIO_ResetOutputPin(TOUCH_SCL_GPIO_Port,TOUCH_SCL_Pin)//PBout(5) 			//SCL     
#define CLR_CTP_IIC_SDA    LL_GPIO_ResetOutputPin(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin)//PAout(9) 			//SDA	 
#define CTP_READ_SDA   LL_GPIO_IsInputPinSet(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin)//PAin(9)  			//输入SDA 

//IIC所有操作函数
void CTP_IIC_Init(void);                	//初始化IIC的IO口				 
void CTP_IIC_Start(void);				//发送IIC开始信号
void CTP_IIC_Stop(void);	  				//发送IIC停止信号
void CTP_IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t CTP_IIC_Read_Byte(unsigned char ack);	//IIC读取一个字节
uint8_t CTP_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void CTP_IIC_Ack(void);					//IIC发送ACK信号
void CTP_IIC_NAck(void);					//IIC不发送ACK信号

#endif







