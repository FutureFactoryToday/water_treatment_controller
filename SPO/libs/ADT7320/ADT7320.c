#include "ADT7320/ADT7320.h"

/*Private defines*/

	#define ADT_STATUS_REG_ADR 0x00
		typedef struct {
			unsigned reserved:3;
			unsigned T_LOW:1;
			unsigned T_HIGH:1;
			unsigned T_CRIT:1;
			unsigned nRDY:1;
		} ADT_STATUS_REG_FLAG_t;
		
		typedef union {
			uint8_t full;
			ADT_STATUS_REG_FLAG_t flag;
		} ADT_STATUS_REG_t;
		
	#define ADT_CONFIG_REG_ADR 0x01
		typedef struct {
			unsigned FAULT_QUEUE:2;
			unsigned CT_POLAR:1;
			unsigned INT_POLAR:1;
			unsigned INT_CT_MODE:1;
			unsigned OPERATION_MODE:1;
			unsigned RESOLUTION:1;
		} ADT_CONFIG_REG_FLAG_t;
		
		//Operation modes
			#define CONT_CONVERSION 0x00;
			#define ONE_SHOT 0x01;
			#define ONE_SPS 0x02;
			#define SHUTDOWN 0x03;
		//Resolution variants
			#define _13_BITS 0x00
			#define _16_BITS 0x01
		
		typedef union {
			uint8_t full;
			ADT_CONFIG_REG_FLAG_t flag;
		} ADT_CONFIG_REG_t;
		
/* Global variables */
	ADT_CONFIG_REG_t ADT_CONFIG_REG;
	ADT_STATUS_REG_t ADT_STATUS_REG;
	
	void WAIT_TRANSMIT(void);
	
int ADT_INIT (){
	ADT_CONFIG_REG.full = 0;
	ADT_STATUS_REG.full = 0;
  LL_SPI_Enable(SPI);
	
	uint8_t id = ADT_SIMPLE_READ_DATA(ADT_ID_REG_ADR);
	if (id != ADT_ID_DEFAULT) {
		return 0;
	}
	
	ADT_CONFIG_REG_t config;
	
	config.full = ADT_SIMPLE_READ_DATA(ADT_CONFIG_REG_ADR);
	config.flag.OPERATION_MODE = CONT_CONVERSION;
	config.flag.RESOLUTION = _16_BITS;
	
	ADT_WRITE_DATA(ADT_CONFIG_REG_ADR, config.full);
	
	return 1;
}


int16_t ADT_SIMPLE_READ_DATA(uint8_t adr){
	int16_t spi_data;
	uint8_t command = (adr << 3) | 0x40;
	while (LL_SPI_IsActiveFlag_RXNE(SPI))
	{
		spi_data = LL_SPI_ReceiveData8(SPI);
	}
	//LL_SPI_Disable(SPI);
	//LL_GPIO_TogglePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin);
	CLR_CS();
	LL_SPI_TransmitData8(SPI, command);
	WAIT_TRANSMIT();
	LL_SPI_ReceiveData8(SPI);
	if (adr == ADT_TEMP_VAL_REG_ADR ||
			adr == ADT_T_CRIT_REG_ADR ||
			adr == ADT_T_HIGH_REG_ADR ||
			adr == ADT_T_LOW_REG_ADR)
	{
		LL_SPI_TransmitData16(SPI,0xFFFF);
//		CLR_CS();
//		LL_SPI_Enable(SPI);
		WAIT_TRANSMIT();
		
		spi_data = LL_SPI_ReceiveData8(SPI) << 8;
		spi_data = spi_data + LL_SPI_ReceiveData8(SPI);
	}
	else
	{
		LL_SPI_TransmitData8(SPI, 0xFF);
		
		//LL_SPI_Enable(SPI);
		WAIT_TRANSMIT();
		//spi_data = LL_SPI_ReceiveData8(SPI);
		spi_data = LL_SPI_ReceiveData8(SPI);
		
	}
	SET_CS();
	return spi_data;
}

void ADT_WRITE_DATA(uint8_t adr, uint16_t data){
	uint8_t command = (adr << 3);
	LL_SPI_TransmitData8(SPI, command);
	//WAIT_TRANSMIT();
	if (adr == ADT_TEMP_VAL_REG_ADR ||
			adr == ADT_T_CRIT_REG_ADR ||
			adr == ADT_T_HYST_REG_ADR ||
			adr == ADT_T_HIGH_REG_ADR ||
			adr == ADT_T_LOW_REG_ADR)
	{
		LL_SPI_TransmitData16(SPI,data);
	}
	else 
	{
		LL_SPI_TransmitData8(SPI, data);
	}
	
	WAIT_TRANSMIT();
}

ADT_TEMP_t ADT_READ_TEMP (){
	ADT_TEMP_t result;
	
	
	return result;
}

void WAIT_TRANSMIT(){
	 while (LL_SPI_IsActiveFlag_BSY(SPI));
}
