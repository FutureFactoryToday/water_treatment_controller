#include "MCP3421.h"
typedef struct {
	unsigned RDY:1;
	unsigned C:2;
	unsigned O_C:1;
	unsigned S:2;
	unsigned G:2;
} mcpStatus_t;

#define _240SPS 0x00
#define _60SPS 0x01
#define _15SPS 0x02
#define _3_75SPS 0x03

#define DEF_C 0x00

#define _1VV 0x00
#define _2VV 0x01
#define _4VV 0x02
#define _8VV 0x03

#define CONT_MODE 0x01
#define ONE_SHOT 0x00

#define READY 0x00

#define RESTART_CONV 0x01


typedef union {
	mcpStatus_t bits;
	uint8_t all;
} mcpStatusReg_t;

uint8_t inited;
mcpStatusReg_t statusReg;

uint32_t ADC_VAL;
uint8_t inputBuf[4];



i2c_buf_t mcpBuf;

void MCP_RESTART_CONVERSION(void);
	
uint8_t INIT_MCP(){
	uint8_t comResult;
	
	comResult = I2C_Manual_Read(MCP_ADR,inputBuf,4);
	
	if (comResult != 1)
		return 0;
	
	statusReg.all = inputBuf[3];
	statusReg.bits.O_C = ONE_SHOT;
	statusReg.bits.S = _3_75SPS;
	statusReg.bits.C = _1VV;
	statusReg.bits.RDY = RESTART_CONV;
	
	comResult = I2C_Manual_Send(MCP_ADR,&statusReg.all,1);
	if (comResult != 1)
		return 0;
	
	mcpBuf.adr = MCP_ADR;
	mcpBuf.buf = inputBuf;
	mcpBuf.bufSize = 4;
	mcpBuf.dataSize = 4;
	mcpBuf.status.all = 0;
	mcpBuf.callBack = MCP_TRANSFORM_DATA;
	
	LL_TIM_SetCounter(MCP_TIM,0);
	LL_TIM_ClearFlag_CC1(MCP_TIM);
	LL_TIM_EnableIT_CC1(MCP_TIM);
	
	return 1;
}

void MCP_READ_DATA(){
	if (mcpBuf.status.bits.inProcess == 0){
	mcpBuf.buf = inputBuf;
	mcpBuf.bufSize = 4;
	mcpBuf.dataSize = 4;
	
	I2C_Read(&mcpBuf);
}
}

uint32_t MCP_GET_DATA(){
	if (mcpBuf.status.bits.newData == 1){
		
	}
	return ADC_VAL;
}

void MCP_TRANSFORM_DATA (){
	uint32_t temp = inputBuf[0]&0x01 << 16;
	temp += inputBuf[1] << 8;
	temp += inputBuf[2];
	ADC_VAL = temp;
	statusReg.all = inputBuf[3];
	
	MCP_RESTART_CONVERSION();
}
void MCP_RESTART_CONVERSION(){
	
	statusReg.bits.RDY = RESTART_CONV;
	inputBuf[3] = statusReg.all;
	mcpBuf.buf = &inputBuf[3];
	mcpBuf.bufSize = 1;
	mcpBuf.dataSize = 1;
	mcpBuf.status.all = 0;
	
	I2C_Send(&mcpBuf);
}
