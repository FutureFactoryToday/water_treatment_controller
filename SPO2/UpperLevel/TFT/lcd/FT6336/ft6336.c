#include "main.h"
#include "TFT/lcd/FT6336/ft6336.h"
#include "TFT/lcd/FT6336/ctpiic.h"

#include "string.h" 

#define TP_PRES_DOWN 0x80
#define TP_CATH_PRES 0x40

_m_tp_dev tp_dev;

extern uint8_t touch_flag;

/*****************************************************************************
 * @name       :uint8_t FT5426_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
 * @date       :2020-05-13 
 * @function   :Write data to ft5426 once
 * @parameters :reg:Start register address for written
								buf:the buffer of data written
								len:Length of data written
 * @retvalue   :0-Write succeeded 
								1-Write failed
******************************************************************************/ 
uint8_t FT6336_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i;
	uint8_t ret=0;
	CTP_IIC_Start();	 
	CTP_IIC_Send_Byte(FT_CMD_WR);	//����д���� 	 
	CTP_IIC_Wait_Ack(); 	 										  		   
	CTP_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CTP_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
		CTP_IIC_Send_Byte(buf[i]);  	//������
		ret=CTP_IIC_Wait_Ack();
		if(ret)
		{
			break;
		}
	}
  CTP_IIC_Stop();					//����һ��ֹͣ����	    
	return ret; 
}

/*****************************************************************************
 * @name       :void FT5426_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
 * @date       :2020-05-13 
 * @function   :Read data to ft5426 once
 * @parameters :reg:Start register address for read
								buf:the buffer of data read
								len:Length of data read
 * @retvalue   :none
******************************************************************************/			  
void FT6336_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i; 
 	CTP_IIC_Start();	
 	CTP_IIC_Send_Byte(FT_CMD_WR);   	//����д���� 	 
	CTP_IIC_Wait_Ack(); 	 										  		   
 	CTP_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CTP_IIC_Wait_Ack();  
 	CTP_IIC_Start();  	 	   
	CTP_IIC_Send_Byte(FT_CMD_RD);   	//���Ͷ�����		   
	CTP_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CTP_IIC_Read_Byte(i==(len-1)?0:1); //������	  
	} 
  CTP_IIC_Stop();//����һ��ֹͣ����     
} 

/*****************************************************************************
 * @name       :uint8_t FT5426_Init(void)
 * @date       :2020-05-13 
 * @function   :Initialize the ft5426 touch screen
 * @parameters :none
 * @retvalue   :0-Initialization successful
								1-initialization failed
******************************************************************************/		
uint8_t TS_IO_Init(void)
{
	uint8_t temp[2]; 	
	
	CTP_IIC_Init();      	//��ʼ����������I2C����  
	LL_GPIO_ResetOutputPin(TOUCH_RES_GPIO_Port, TOUCH_RES_Pin);
	//FT_RST=0;				//��λ
	LL_mDelay(10);
 	//FT_RST=1;				//�ͷŸ�λ		  
	LL_GPIO_SetOutputPin(TOUCH_RES_GPIO_Port, TOUCH_RES_Pin);  
	LL_mDelay(500);  	
//	temp[0]=0;
//	FT6336_WR_Reg(FT_DEVIDE_MODE,temp,1);	//������������ģʽ 
//	FT6336_WR_Reg(FT_ID_G_MODE,temp,1);		//��ѯģʽ 
	//temp[0]=40;								//������Чֵ��22��ԽСԽ����	
	//FT6336_WR_Reg(FT_ID_G_THGROUP,temp,1);	//���ô�����Чֵ
	FT6336_RD_Reg(FT_ID_G_FOCALTECH_ID,&temp[0],1);
	if(temp[0]!=0x11)
	{
		return 1;
	}
	FT6336_RD_Reg(FT_ID_G_CIPHER_MID,&temp[0],2);
	if(temp[0]!=0x26)
	{
		return 1;
	}
	if((temp[1]!=0x00)&&(temp[1]!=0x01)&&(temp[1]!=0x02))
	{
		return 1;
	}
	FT6336_RD_Reg(FT_ID_G_CIPHER_HIGH,&temp[0],1);
	if(temp[0]!=0x64)
	{
		return 1;
	}

	return 0;
}

const uint16_t FT6336_TPX_TBL[2]={FT_TP1_REG,FT_TP2_REG};

/*****************************************************************************
 * @name       :uint8_t FT5426_Scan(void)
 * @date       :2020-05-13 
 * @function   :Scan touch screen (query mode)
 * @parameters :none
 * @retvalue   :Current touch screen status
								0-No touch
								1-With touch
******************************************************************************/	
uint8_t TS_IO_DetectToch(void)
{
	uint8_t buf[4];
	uint8_t i=0;
	uint8_t res=0;
	uint8_t temp;
	uint8_t mode;
	static uint8_t t=0;//���������� ���������� �������, ����� ������� �������� �� �� 
	t++;
	if((t%10)==0||t<10)//� ������ �������� ������� CTP_Scan �������������� ������ 10 ���, ��� ��������� ��������� ������� ��.
	{
		FT6336_RD_Reg(FT_REG_NUM_FINGER,&mode,1);//������ ��������� ����� ������� 
		if(mode&&(mode<3))
		{
			temp=0XFF<<mode;//������������ ���������� ������ � 1 �����, ��������������� ����������� tp_dev.sta
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			for(i=0;i<CTP_MAX_TOUCH;i++)
			{
				FT6336_RD_Reg(FT6336_TPX_TBL[i],buf,4);	//������ �������� ���������� XY
				if(tp_dev.sta&(1<<i))	//��� ��������?
				{
					tp_dev.x[i]=((uint16_t)(buf[0]&0X0F)<<8)+buf[1];
					tp_dev.y[i]=((uint16_t)(buf[2]&0X0F)<<8)+buf[3];
//					switch(lcddev.dir)
//					{
//						case 0:
//							tp_dev.x[i]=((uint16_t)(buf[0]&0X0F)<<8)+buf[1];
//							tp_dev.y[i]=((uint16_t)(buf[2]&0X0F)<<8)+buf[3];						
//							break;
//						case 1:
//							tp_dev.y[i]=lcddev.height-(((uint16_t)(buf[0]&0X0F)<<8)+buf[1]);
//							tp_dev.x[i]=((uint16_t)(buf[2]&0X0F)<<8)+buf[3];						
//							break;
//						case 2:
//							tp_dev.x[i]=lcddev.width-(((uint16_t)(buf[0]&0X0F)<<8)+buf[1]);
//							tp_dev.y[i]=lcddev.height-(((uint16_t)(buf[2]&0X0F)<<8)+buf[3]);								
//							break;
//						case 3:
//							tp_dev.y[i]=((uint16_t)(buf[0]&0X0F)<<8)+buf[1];
//							tp_dev.x[i]=lcddev.width-(((uint16_t)(buf[2]&0X0F)<<8)+buf[3]);	
//							break;
//					} 

				}			
			} 
			res=1;
			if(tp_dev.x[0]==0 && tp_dev.y[0]==0)mode=0;	//���� ��� ����������� ������ ����� 0, ����������� ��� ������.
			t=0;		//�������� ���� ���, �� ����� ���������� ������������� �� ����� 10 ���, ��� ����� ���������� ������� ���������.
		}
	}
	if(mode==0)//��� ������� ����� �������
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//��� ����� ��
		{
			tp_dev.sta&=~(1<<7);	//�������� ���� ����������
		}else						//������ �� �������
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//�������� ����� �������������� �������	
		}	 
	} 
	if(t>240)t=10;//����� ������ ������� � 10.
	return res;
}
