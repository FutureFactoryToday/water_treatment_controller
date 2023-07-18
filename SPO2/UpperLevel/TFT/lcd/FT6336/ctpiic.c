
/****************************************************************************************************
//=========================================��Դ����================================================//
//     LCDģ��                CH32��Ƭ��
//      VCC          ��        DC5V/3.3V      //��Դ
//      GND          ��          GND          //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI����
//     LCDģ��                CH32��Ƭ��    
//    SDI(MOSI)      ��          PA7          //Һ����SPI��������д�ź�
//    SDO(MISO)      ��          PA6          //Һ����SPI�������ݶ��źţ��������Ҫ�������Բ�����
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      CH32��Ƭ�� 
//       LED         ��          PB6          //Һ������������źţ��������Ҫ���ƣ����Բ��ӣ�
//       SCK         ��          PA5          //Һ����SPI����ʱ���ź�
//      LCD_RS       ��          PB7          //Һ��������/��������ź�
//      LCD_RST      ��          PB8          //Һ������λ�����ź�
//      LCD_CS       ��          PB9          //Һ����Ƭѡ�����ź�
//=========================================������������=========================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��                CH32��Ƭ�� 
//     CTP_INT       ��          PA8          //���ݴ����������ж��ź�
//     CTP_SDA       ��          PA9          //���ݴ�����IIC���������ź�
//     CTP_RST       ��          PA10         //���ݴ�����������λ�ź�
//     CTP_SCL       ��          PB5          //���ݴ�����IIC����ʱ���ź�
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
	CTP_SDA_OUT();     //sda�����
	SET_CTP_IIC_SDA;	  	  
	SET_CTP_IIC_SCL;
	CTP_Delay(1);
 	CLR_CTP_IIC_SDA;//START:when CLK is high,DATA change form high to low 
	CTP_Delay(1);
	CLR_CTP_IIC_SCL;//ǯסI2C���ߣ�׼�����ͻ�������� 
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
	CTP_SDA_OUT();//sda�����
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
	CTP_SDA_IN();      //SDA����Ϊ����  
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
	CLR_CTP_IIC_SCL;//ʱ�����0 	   
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
  CLR_CTP_IIC_SCL;//����ʱ�ӿ�ʼ���ݴ���
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
 	CTP_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        CLR_CTP_IIC_SCL; 	    	   
		CTP_Delay(3);
		SET_CTP_IIC_SCL;  
		receive<<=1;
		if(CTP_READ_SDA)receive++;   
	}	  				 
	if (!ack)CTP_IIC_NAck();//����nACK
	else CTP_IIC_Ack(); //����ACK   
 	return receive;
}




























