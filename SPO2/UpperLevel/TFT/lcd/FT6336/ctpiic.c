
#include "main.h"
#ifdef ST7796S
#include "TFT/lcd/FT6336/ctpiic.h"


/*****************************************************************************
 * @name       :void CTP_Delay(void)
 * @date       :2020-05-13 
 * @function   :Delay in controlling IIC speed
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
inline void CTP_Delay(uint8_t Delay)
{
	uDelayTim->CNT = 0;
	while(uDelayTim->CNT < Delay);
} 

/*****************************************************************************
 * @name       :void CTP_IIC_Init(void)
 * @date       :2020-05-13 
 * @function   :Initialize IIC
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void CTP_IIC_Init(void)
{		
	LL_TIM_EnableCounter(uDelayTim);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);
	LL_TIM_SetPrescaler(uDelayTim,35);
	SET_CTP_IIC_SCL;
	SET_CTP_IIC_SDA;
	LL_GPIO_SetPinMode(TOUCH_SCL_GPIO_Port,TOUCH_SCL_Pin,LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(TOUCH_SCL_GPIO_Port,TOUCH_SCL_Pin,LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetPinMode(CAP_TOUCH_INT_GPIO_Port, CAP_TOUCH_INT_Pin, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(CAP_TOUCH_INT_GPIO_Port,CAP_TOUCH_INT_Pin,LL_GPIO_PULL_UP);
	CTP_SDA_OUT();

}

/*****************************************************************************
 * @name       :void CTP_IIC_Start(void)
 * @date       :2020-05-13 
 * @function   :Generating IIC starting signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void CTP_IIC_Start(void)
{
	CTP_SDA_OUT();     //sda线输出
	SET_CTP_IIC_SDA;	  	  
	SET_CTP_IIC_SCL;
	CTP_Delay(1);
 	CLR_CTP_IIC_SDA;//START:when CLK is high,DATA change form high to low 
	CTP_Delay(1);
	CLR_CTP_IIC_SCL;//钳住I2C总线，准备发送或接收数据 
}	

/*****************************************************************************
 * @name       :void CTP_IIC_Stop(void)
 * @date       :2020-05-13 
 * @function   :Generating IIC stop signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/   
void CTP_IIC_Stop(void)
{ 
	CTP_SDA_OUT();//sda线输出
	CLR_CTP_IIC_SCL;
	CLR_CTP_IIC_SDA;
	CTP_Delay(1);
	SET_CTP_IIC_SCL;
	CTP_Delay(1);
	SET_CTP_IIC_SDA;//STOP:when CLK is high DATA change form low to high 
}

/*****************************************************************************
 * @name       :uint8_t CTP_IIC_Wait_Ack(void)
 * @date       :2020-05-13 
 * @function   :Wait for the response signal
 * @parameters :None
 * @retvalue   :0-receive response signal successfully
								1-receive response signal unsuccessfully
******************************************************************************/ 
uint8_t CTP_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	CTP_SDA_IN();      //SDA设置为输入  
	SET_CTP_IIC_SDA;CTP_Delay(1);	   
	SET_CTP_IIC_SCL;CTP_Delay(1);	 
	while(LL_GPIO_IsInputPinSet(TOUCH_SDA_GPIO_Port,TOUCH_SDA_Pin))
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CTP_IIC_Stop();
			return 1;
		} 
	}
	CLR_CTP_IIC_SCL;//时钟输出0 	   
	return 0;  
} 

/*****************************************************************************
 * @name       :void CTP_IIC_Ack(void)
 * @date       :2020-05-13 
 * @function   :Generate ACK response signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 
void CTP_IIC_Ack(void)
{
	CLR_CTP_IIC_SCL;
	CTP_SDA_OUT();
	CLR_CTP_IIC_SDA;
	CTP_Delay(1);
	SET_CTP_IIC_SCL;
	CTP_Delay(1);
	CLR_CTP_IIC_SCL;
}

/*****************************************************************************
 * @name       :void CTP_IIC_NAck(void)
 * @date       :2020-05-13 
 * @function   :Don't generate ACK response signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	    
void CTP_IIC_NAck(void)
{
	CLR_CTP_IIC_SCL;
	CTP_SDA_OUT();
	SET_CTP_IIC_SDA;
	CTP_Delay(1);
	SET_CTP_IIC_SCL;
	CTP_Delay(1);
	CLR_CTP_IIC_SCL;
}	

/*****************************************************************************
 * @name       :void CTP_IIC_Send_Byte(uint8_t txd)
 * @date       :2020-05-13 
 * @function   :send a byte data by IIC bus
 * @parameters :txd:Data to be sent
 * @retvalue   :None
******************************************************************************/					 				     		  
void CTP_IIC_Send_Byte(uint8_t txd)
{                        
  uint8_t t;   
 	CTP_SDA_OUT(); 	  
  CLR_CTP_IIC_SCL;//拉低时钟开始数据传输
  for(t=0;t<8;t++)
  { 
		if ((txd&0x80)>>7 == 1){
			SET_CTP_IIC_SDA;
		} else {
			CLR_CTP_IIC_SDA;
		}
    txd<<=1; 	      
		SET_CTP_IIC_SCL;
		CTP_Delay(1);
		CLR_CTP_IIC_SCL;	
		CTP_Delay(1);
  }	 
} 	

/*****************************************************************************
 * @name       :uint8_t CTP_IIC_Read_Byte(unsigned char ack)
 * @date       :2020-05-13 
 * @function   :read a byte data by IIC bus
 * @parameters :ack:0-send nACK
									  1-send ACK
 * @retvalue   :Data to be read
******************************************************************************/	    
uint8_t CTP_IIC_Read_Byte(unsigned char ack)
{
	uint8_t i,receive=0;
 	CTP_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        CLR_CTP_IIC_SCL; 	    	   
		CTP_Delay(3);
		SET_CTP_IIC_SCL;  
		receive<<=1;
		if(CTP_READ_SDA)receive++;   
	}	  				 
	if (!ack)CTP_IIC_NAck();//发送nACK
	else CTP_IIC_Ack(); //发送ACK   
 	return receive;
}

#endif

























