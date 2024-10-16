
#include "main.h"
#ifdef ST7796S	
#include "TFT/ts.h"
#include "TFT/lcd/FT6336/ft6336.h"
#include "TFT/lcd/FT6336/ctpiic.h"

#include "string.h" 

#define TP_PRES_DOWN 0x80
#define TP_CATH_PRES 0x40

extern uint8_t touch_flag;
uint16_t ret[2];

/* Touchscreen */
bool     ft6336_ts_Init(uint16_t DeviceAddr);
uint8_t  ft6336_ts_DetectTouch(uint16_t DeviceAddr);
void     ft6336_ts_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y);

TS_DrvTypeDef   ft6336_ts_drv =
{
  ft6336_ts_Init,
  0,
  0,
  0,
  ft6336_ts_DetectTouch,
  ft6336_ts_GetXY,
  0,
  0,
  0,
  0,
	0,
	0
};


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
	CTP_IIC_Send_Byte(FT_CMD_WR);	//发送写命令 	 
	CTP_IIC_Wait_Ack(); 	 										  		   
	CTP_IIC_Send_Byte(reg&0XFF);   	//发送低8位地址
	CTP_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
		CTP_IIC_Send_Byte(buf[i]);  	//发数据
		ret=CTP_IIC_Wait_Ack();
		if(ret)
		{
			break;
		}
	}
  CTP_IIC_Stop();					//产生一个停止条件	    
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
 	CTP_IIC_Send_Byte(FT_CMD_WR);   	//发送写命令 	 
	CTP_IIC_Wait_Ack(); 	 										  		   
 	CTP_IIC_Send_Byte(reg&0XFF);   	//发送低8位地址
	CTP_IIC_Wait_Ack();  
 	CTP_IIC_Start();  	 	   
	CTP_IIC_Send_Byte(FT_CMD_RD);   	//发送读命令		   
	CTP_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CTP_IIC_Read_Byte(i==(len-1)?0:1); //发数据	  
	} 
  CTP_IIC_Stop();//产生一个停止条件     
} 

/*****************************************************************************
 * @name       :uint8_t FT5426_Init(void)
 * @date       :2020-05-13 
 * @function   :Initialize the ft5426 touch screen
 * @parameters :none
 * @retvalue   :1-Initialization successful
								1-initialization failed
******************************************************************************/		
bool ft6336_ts_Init(uint16_t DeviceAddr)
{
	uint8_t temp[2]; 	
	
	CTP_IIC_Init();      	//初始化电容屏的I2C总线  
	LL_GPIO_ResetOutputPin(TOUCH_RES_GPIO_Port, TOUCH_RES_Pin);
	//FT_RST=0;				//复位
	LL_mDelay(10);
 	//FT_RST=1;				//释放复位		  
	LL_GPIO_SetOutputPin(TOUCH_RES_GPIO_Port, TOUCH_RES_Pin);  
	LL_mDelay(500);  	
//	temp[0]=0;
//	FT6336_WR_Reg(FT_DEVIDE_MODE,temp,1);	//进入正常操作模式 
//	FT6336_WR_Reg(FT_ID_G_MODE,temp,1);		//查询模式 
	//temp[0]=40;								//触摸有效值，22，越小越灵敏	
	//FT6336_WR_Reg(FT_ID_G_THGROUP,temp,1);	//设置触摸有效值
	FT6336_RD_Reg(FT_ID_G_FOCALTECH_ID,&temp[0],1);
	if(temp[0]!=0x11)
	{
		return 0;
	}
	FT6336_RD_Reg(FT_ID_G_CIPHER_MID,&temp[0],2);
	if(temp[0]!=0x26)
	{
		return 0;
	}
	if((temp[1]!=0x00)&&(temp[1]!=0x01)&&(temp[1]!=0x02))
	{
		return 0;
	}
	FT6336_RD_Reg(FT_ID_G_CIPHER_HIGH,&temp[0],1);
	if(temp[0]!=0x64)
	{
		return 0;
	}

	return 1;
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
uint8_t ft6336_ts_DetectTouch(uint16_t DeviceAddr)
{
	uint8_t mode;
	static uint8_t t=0;//语疣怆�轵� 桧蝈疴嚯铎 玎镳铖�, 黩钺� 耥桤栩� 磬沭箸牦 磬 窒 
	
	FT6336_RD_Reg(FT_REG_NUM_FINGER,&mode,1);//昨屙桢 耦耱��龛� 蝾麝� 赅襦龛� 
	if(mode&&(mode<3))
	{
		ft6336_ts_drv.isTouched = 1;
	} else {
		ft6336_ts_drv.isTouched = 0;
	}
	
	return ft6336_ts_drv.isTouched;
}


void ft6336_ts_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y)
{
	uint8_t buf[4];

	FT6336_RD_Reg(FT_TP1_REG,buf,4);	
	
	ft6336_ts_drv.ty=((uint16_t)(buf[0]&0X0F)<<8)+buf[1];
	
	ft6336_ts_drv.tx=((uint16_t)(buf[2]&0X0F)<<8)+buf[3];
	*X = ft6336_ts_drv.tx;
	*Y = ft6336_ts_drv.ty;
			
}
#endif
