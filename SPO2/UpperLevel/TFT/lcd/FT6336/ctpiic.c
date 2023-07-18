
/****************************************************************************************************
//=========================================电源接线================================================//
//     LCD模块                CH32单片机
//      VCC          接        DC5V/3.3V      //电源
//      GND          接          GND          //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为SPI总线
//     LCD模块                CH32单片机    
//    SDI(MOSI)      接          PA7          //液晶屏SPI总线数据写信号
//    SDO(MISO)      接          PA6          //液晶屏SPI总线数据读信号，如果不需要读，可以不接线
//=======================================液晶屏控制线接线==========================================//
//     LCD模块 					      CH32单片机 
//       LED         接          PB6          //液晶屏背光控制信号（如果不需要控制，可以不接）
//       SCK         接          PA5          //液晶屏SPI总线时钟信号
//      LCD_RS       接          PB7          //液晶屏数据/命令控制信号
//      LCD_RST      接          PB8          //液晶屏复位控制信号
//      LCD_CS       接          PB9          //液晶屏片选控制信号
//=========================================触摸屏触接线=========================================//
//如果模块不带触摸功能或者带有触摸功能，但是不需要触摸功能，则不需要进行触摸屏接线
//	   LCD模块                CH32单片机 
//     CTP_INT       接          PA8          //电容触摸屏触摸中断信号
//     CTP_SDA       接          PA9          //电容触摸屏IIC总线数据信号
//     CTP_RST       接          PA10         //电容触摸屏触摸复位信号
//     CTP_SCL       接          PB5          //电容触摸屏IIC总线时钟信号
**************************************************************************************************/	
#include "main.h"
#include "TFT/lcd/FT6336/ctpiic.h"


/*****************************************************************************
 * @name       :void CTP_Delay(void)
 * @date       :2020-05-13 
 * @function   :Delay in controlling IIC speed
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void CTP_Delay(uint8_t Delay)
{
	LL_TIM_DisableCounter(uDelayTim);
	LL_TIM_SetCounter(uDelayTim,0);
	LL_TIM_ClearFlag_UPDATE(uDelayTim);
	LL_TIM_SetAutoReload(uDelayTim,72*Delay);
	LL_TIM_EnableCounter(uDelayTim);
	while(!LL_TIM_IsActiveFlag_UPDATE(uDelayTim));
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
	SET_CTP_IIC_SCL;
	SET_CTP_IIC_SDA;
	
	
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




























