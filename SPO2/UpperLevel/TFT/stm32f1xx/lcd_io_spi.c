/*
 * SPI LCD driver STM32F1
 * author: Roberto Benjami
 * version:  2021.01.09
 *
 * - hardware, software SPI
 * - 3 modes (only TX, half duplex, full duplex)
*/

#include "Settings.h"
#ifdef SPI_LCD

//-----------------------------------------------------------------------------
#include "main.h"
#include "TFT\lcd.h"
#include "lcd_io_spi.h"

#define DMA_MAXSIZE           0xFFFE
#define FILL_BUF_SIZE 1
volatile uint8_t fillBuf[FILL_BUF_SIZE*3];
volatile uint8_t watch[5];
//-----------------------------------------------------------------------------
/* Link function for LCD peripheral */
void  LCD_Delay (uint32_t delay);
void  LCD_IO_Init(void);
void  LCD_IO_Bl_OnOff(uint8_t Bl);

void  LCD_IO_WriteCmd8(uint8_t Cmd);
void  LCD_IO_WriteCmd16(uint16_t Cmd);
void  LCD_IO_WriteData8(uint8_t Data);
void  LCD_IO_WriteData16(uint16_t Data);

void  LCD_IO_WriteCmd8DataFill16(uint8_t Cmd, uint16_t Data, uint32_t Size);
void  LCD_IO_WriteCmd8MultipleData8(uint8_t Cmd, uint8_t *pData, uint32_t Size);
void  LCD_IO_WriteCmd8MultipleData16(uint8_t Cmd, uint16_t *pData, uint32_t Size);
void  LCD_IO_WriteCmd16DataFill16(uint16_t Cmd, uint16_t Data, uint32_t Size);
void  LCD_IO_WriteCmd16MultipleData8(uint16_t Cmd, uint8_t *pData, uint32_t Size);
void  LCD_IO_WriteCmd16MultipleData16(uint16_t Cmd, uint16_t *pData, uint32_t Size);

void  LCD_IO_ReadCmd8MultipleData8(uint8_t Cmd, uint8_t *pData, uint32_t Size, uint32_t DummySize);
void  LCD_IO_ReadCmd8MultipleData16(uint8_t Cmd, uint16_t *pData, uint32_t Size, uint32_t DummySize);
void  LCD_IO_ReadCmd8MultipleData24to16(uint8_t Cmd, uint16_t *pData, uint32_t Size, uint32_t DummySize);
void  LCD_IO_ReadCmd16MultipleData8(uint16_t Cmd, uint8_t *pData, uint32_t Size, uint32_t DummySize);
void  LCD_IO_ReadCmd16MultipleData16(uint16_t Cmd, uint16_t *pData, uint32_t Size, uint32_t DummySize);
void  LCD_IO_ReadCmd16MultipleData24to16(uint16_t Cmd, uint16_t *pData, uint32_t Size, uint32_t DummySize);

void  LCD_IO_Delay(uint32_t c);

void LCD_IO_WriteCmd8DataFill8(uint8_t Cmd, uint8_t* Data, uint32_t Size);
bool		LCD_IO_isBusy();
//=============================================================================

#define BITBAND_ACCESS(a, b)  *(volatile uint32_t*)(((uint32_t)&a & 0xF0000000) + 0x2000000 + (((uint32_t)&a & 0x000FFFFF) << 5) + (b << 2))

//-----------------------------------------------------------------------------
/* GPIO mode */
#define MODE_ANALOG_INPUT     0x0
#define MODE_PP_OUT_10MHZ     0x1
#define MODE_PP_OUT_2MHZ      0x2
#define MODE_PP_OUT_50MHZ     0x3
#define MODE_FF_DIGITAL_INPUT 0x4
#define MODE_OD_OUT_10MHZ     0x5
#define MODE_OD_OUT_2MHZ      0x6
#define MODE_OD_OUT_50MHZ     0x7
#define MODE_PU_DIGITAL_INPUT 0x8
#define MODE_PP_ALTER_10MHZ   0x9
#define MODE_PP_ALTER_2MHZ    0xA
#define MODE_PP_ALTER_50MHZ   0xB
#define MODE_RESERVED         0xC
#define MODE_OD_ALTER_10MHZ   0xD
#define MODE_OD_ALTER_2MHZ    0xE
#define MODE_OD_ALTER_50MHZ   0xF

#define GPIOX_PORT_(a, b)     GPIO ## a
#define GPIOX_PORT(a)         GPIOX_PORT_(a)

#define GPIOX_PIN_(a, b)      b
#define GPIOX_PIN(a)          GPIOX_PIN_(a)

#define GPIOX_MODE_(a,b,c)    ((GPIO_TypeDef*)(((c & 8) >> 1) + GPIO ## b ## _BASE))->CRL = (((GPIO_TypeDef*)(((c & 8) >> 1) + GPIO ## b ## _BASE))->CRL & ~(0xF << ((c & 7) << 2))) | (a << ((c & 7) << 2))
#define GPIOX_MODE(a, b)      GPIOX_MODE_(a, b)

#define GPIOX_ODR_(a, b)      BITBAND_ACCESS(GPIO ## a ->ODR, b)
#define GPIOX_ODR(a)          GPIOX_ODR_(a)

#define GPIOX_IDR_(a, b)      BITBAND_ACCESS(GPIO ## a ->IDR, b)
#define GPIOX_IDR(a)          GPIOX_IDR_(a)

#define GPIOX_LINE_(a, b)     EXTI_Line ## b
#define GPIOX_LINE(a)         GPIOX_LINE_(a)

#define GPIOX_CLOCK_(a, b)    RCC_APB2ENR_IOP ## a ## EN
#define GPIOX_CLOCK(a)        GPIOX_CLOCK_(a)

#define GPIOX_PORTNUM_A       1
#define GPIOX_PORTNUM_B       2
#define GPIOX_PORTNUM_C       3
#define GPIOX_PORTNUM_D       4
#define GPIOX_PORTNUM_E       5
#define GPIOX_PORTNUM_F       6
#define GPIOX_PORTNUM_G       7
#define GPIOX_PORTNUM_H       8
#define GPIOX_PORTNUM_I       9
#define GPIOX_PORTNUM_J       10
#define GPIOX_PORTNUM_K       11
#define GPIOX_PORTNUM_(a, b)  GPIOX_PORTNUM_ ## a
#define GPIOX_PORTNUM(a)      GPIOX_PORTNUM_(a)

#define GPIOX_PORTNAME_(a, b) a
#define GPIOX_PORTNAME(a)     GPIOX_PORTNAME_(a)

//-----------------------------------------------------------------------------
/* DMA */
#define DMANUM_(a, b, c)                a
#define DMANUM(a)                       DMANUM_(a)

#define DMACHN_(a, b, c)                b
#define DMACHN(a)                       DMACHN_(a)

#define DMAPRIORITY_(a, b, c)           c
#define DMAPRIORITY(a)                  DMAPRIORITY_(a)

#define DMAX_(a, b, c)                  DMA ## a
#define DMAX(a)                         DMAX_(a)

#define DMAX_CHANNEL_(a, b, c)          DMA ## a ## _Channel ## b
#define DMAX_CHANNEL(a)                 DMAX_CHANNEL_(a)

#define DMAX_CHANNEL_IRQ_(a, b, c)      DMA ## a ## _Channel ## b ## _IRQn
#define DMAX_CHANNEL_IRQ(a)             DMAX_CHANNEL_IRQ_(a)

#define DMAX_CHANNEL_IRQHANDLER_(a, b, c) DMA ## a ## _Channel ## b ## _IRQHandler
#define DMAX_CHANNEL_IRQHANDLER(a)      DMAX_CHANNEL_IRQHANDLER_(a)

// Interrupt event pl: if(DMAX_ISR(LCD_DMA_TX) & DMAX_ISR_TCIF(LCD_DMA_TX))...
#define DMAX_ISR_TCIF_(a, b, c)         DMA_ISR_TCIF ## b
#define DMAX_ISR_TCIF(a)                DMAX_ISR_TCIF_(a)

#define DMAX_ISR_HTIF_(a, b, c)         DMA_ISR_HTIF ## b
#define DMAX_ISR_HTIF(a)                DMAX_ISR_HTIF_(a)

#define DMAX_ISR_TEIF_(a, b, c)         DMA_ISR_TEIF ## b
#define DMAX_ISR_TEIF(a)                DMAX_ISR_TEIF_(a)

#define DMAX_ISR_GIF_(a, b, c)          DMA_ISR_GIF ## b
#define DMAX_ISR_GIF(a)                 DMAX_ISR_GIF_(a)

// Interrupt clear pl: DMAX_IFCR(LCD_DMA_TX) = DMAX_IFCR_CTCIF(LCD_DMA_TX) | DMAX_IFCR_CFEIF(LCD_DMA_TX);
#define DMAX_IFCR_CTCIF_(a, b, c)       DMA_IFCR_CTCIF ## b
#define DMAX_IFCR_CTCIF(a)              DMAX_IFCR_CTCIF_(a)

#define DMAX_IFCR_CHTIF_(a, b, c)       DMA_IFCR_CHTIF ## b
#define DMAX_IFCR_CHTIF(a)              DMAX_IFCR_CHTIF_(a)

#define DMAX_IFCR_CTEIF_(a, b, c)       DMA_IFCR_CTEIF ## b
#define DMAX_IFCR_CTEIF(a)              DMAX_IFCR_CTEIF_(a)

#define DMAX_IFCR_CGIF_(a, b, c)        DMA_IFCR_CGIF ## b
#define DMAX_IFCR_CGIF(a)               DMAX_IFCR_CGIF_(a)

//=============================================================================
/* only transmit mode -> clear the DMA RX settings */
#if     LCD_SPI_MODE == 0
#undef  LCD_DMA_RX
#define LCD_DMA_RX        0, 0, 0
#endif

/* Command/data pin set */
#define LCD_RS_CMD            LL_GPIO_ResetOutputPin(TFT_DATA_COM_GPIO_Port,TFT_DATA_COM_Pin)//GPIOX_ODR(LCD_RS) = 0
#define LCD_RS_DATA           LL_GPIO_SetOutputPin(TFT_DATA_COM_GPIO_Port,TFT_DATA_COM_Pin)//GPIOX_ODR(LCD_RS) = 1

/* Reset pin set */
#define LCD_RST_ON            LL_GPIO_ResetOutputPin(TFT_RES_GPIO_Port,TFT_RES_Pin)//GPIOX_ODR(LCD_RST) = 0
#define LCD_RST_OFF           LL_GPIO_SetOutputPin(TFT_RES_GPIO_Port,TFT_RES_Pin)//GPIOX_ODR(LCD_RST) = 1

/* Chip select pin set */
#define LCD_CS_ON             LL_GPIO_ResetOutputPin(TFT_CS_GPIO_Port,TFT_CS_Pin)//GPIOX_ODR(LCD_CS) = 0
#define LCD_CS_OFF            LL_GPIO_SetOutputPin(TFT_CS_GPIO_Port,TFT_CS_Pin)//GPIOX_ODR(LCD_CS) = 1

/* If the read speed is undefinied -> is the same as writing speed */
#ifndef LCD_SPI_SPD_READ
#define LCD_SPI_SPD_READ      LCD_SPI_SPD_WRITE
#endif

/* Write SPI delay (0: none, 1: NOP, 2: clock pin keeping, 3.. LCD_IO_Delay) */
#if     LCD_SPI_SPD_WRITE == 0
#define LCD_WRITE_DELAY
#elif   LCD_SPI_SPD_WRITE == 1
#define LCD_WRITE_DELAY       __NOP()
#elif   LCD_SPI_SPD_WRITE == 2
#define LCD_WRITE_DELAY       GPIOX_ODR(LCD_SCK) = 0
#else
#define LCD_WRITE_DELAY       LCD_IO_Delay(LCD_SPI_SPD_WRITE - 3)
#endif

/* Read SPI delay (0: none, 1: NOP, 2: clock pin keeping, 3.. LCD_IO_Delay) */
#if     LCD_SPI_SPD_READ == 0
#define LCD_READ_DELAY
#elif   LCD_SPI_SPD_READ == 1
#define LCD_READ_DELAY        __NOP()
#elif   LCD_SPI_SPD_READ == 2
#define LCD_READ_DELAY        GPIOX_ODR(LCD_SCK) = 0
#else
#define LCD_READ_DELAY        LCD_IO_Delay(LCD_SPI_SPD_READ - 3)
#endif

#if GPIOX_PORTNUM(LCD_RS) < GPIOX_PORTNUM_A
#error  not definied the LCD RS pin
#endif

#if GPIOX_PORTNUM(LCD_CS) < GPIOX_PORTNUM_A
#error  not definied the LCD CS pin
#endif

#if GPIOX_PORTNUM(LCD_SCK) < GPIOX_PORTNUM_A
#error  not definied the LCD SCK pin
#endif

#if GPIOX_PORTNUM(LCD_MOSI) < GPIOX_PORTNUM_A
#error  not definied the LCD MOSI pin
#endif

#if GPIOX_PORTNUM(LCD_MISO) < GPIOX_PORTNUM_A && LCD_SPI_MODE == 2
#error  not definied the LCD MISO pin
#endif
//-----------------------------------------------------------------------------
uint32_t dmaCircCnt;
bool isDmaCircMode;
//-----------------------------------------------------------------------------

/* Hardware SPI */


#if LCD_SPI == 2
#define SPIX                  SPI2
#define LCD_SPI_RCC_EN        //BITBAND_ACCESS(RCC->APB1ENR, RCC_APB1ENR_SPI2EN_Pos) = 1

#endif

#define LcdSpiMode8()         LL_SPI_SetDataWidth(SPIX,LL_SPI_DATAWIDTH_8BIT)//ITBAND_ACCESS(SPIX->CR1, SPI_CR1_DFF_Pos) = 0
#define LcdSpiMode16()        LL_SPI_SetDataWidth(SPIX,LL_SPI_DATAWIDTH_16BIT)//BITBAND_ACCESS(SPIX->CR1, SPI_CR1_DFF_Pos) = 1

//-----------------------------------------------------------------------------

/* Fullduplex SPI : the direction is fix */
extern inline void LcdDirRead(uint32_t d);
inline void LcdDirRead(uint32_t d)
{
  GPIOX_MODE(MODE_PP_OUT_50MHZ, LCD_SCK);
  while(d--)
  {
    GPIOX_ODR(LCD_SCK) = 0;
    LCD_READ_DELAY;
    GPIOX_ODR(LCD_SCK) = 1;
  }
  GPIOX_MODE(MODE_PP_ALTER_50MHZ, LCD_SCK);
  while(BITBAND_ACCESS(SPIX->SR, SPI_SR_RXNE_Pos))
    d = SPIX->DR;
  SPIX->CR1 = (SPIX->CR1 & ~SPI_CR1_BR) | (LCD_SPI_SPD_READ << SPI_CR1_BR_Pos) | SPI_CR1_RXONLY;
}

extern inline void LcdDirWrite(void);
inline void LcdDirWrite(void)
{
  volatile uint32_t d8 __attribute__((unused));
  SPIX->CR1 &= ~SPI_CR1_SPE;
  while(BITBAND_ACCESS(SPIX->SR, SPI_SR_RXNE_Pos))
    d8 = SPIX->DR;
  SPIX->CR1 = (SPIX->CR1 & ~(SPI_CR1_BR | SPI_CR1_RXONLY)) | (LCD_SPI_SPD_WRITE << SPI_CR1_BR_Pos);
  LCD_IO_Delay(2 ^ LCD_SPI_SPD_READ);
  while(BITBAND_ACCESS(SPIX->SR, SPI_SR_RXNE_Pos))
    d8 = SPIX->DR;
  SPIX->CR1 |= SPI_CR1_SPE;
}

//-----------------------------------------------------------------------------
extern inline void LcdWrite8(uint8_t d8);
inline void LcdWrite8(uint8_t d8)
{
  LL_SPI_TransmitData8(SPIX,d8);//SPIX->DR = d8;
  LCD_IO_Delay(2);
	while(LL_SPI_IsActiveFlag_BSY(SPIX));
  //while(BITBAND_ACCESS(SPIX->SR, SPI_SR_BSY_Pos));
}

//-----------------------------------------------------------------------------
extern inline uint8_t LcdRead8(void);
inline uint8_t LcdRead8(void)
{
  uint8_t d8;
  while(!LL_SPI_IsActiveFlag_RXNE(SPIX));//while(!BITBAND_ACCESS(SPIX->SR, SPI_SR_RXNE_Pos));
  d8 = LL_SPI_ReceiveData8(SPIX);
  return d8;
}

//-----------------------------------------------------------------------------
extern inline void LcdCmdWrite8(uint8_t cmd8);
inline void LcdCmdWrite8(uint8_t cmd8)
{
  LCD_RS_CMD;
  LL_SPI_TransmitData8(SPIX,cmd8);//SPIX->DR = cmd8;
  LCD_IO_Delay(2);
  while(LL_SPI_IsActiveFlag_BSY(SPIX));//while(BITBAND_ACCESS(SPIX->SR, SPI_SR_BSY_Pos));
  LCD_RS_DATA;
}

//-----------------------------------------------------------------------------
extern inline void LcdWrite16(uint16_t d16);
inline void LcdWrite16(uint16_t d16)
{
  LL_SPI_TransmitData16(SPIX,d16);//SPIX->DR = d16;
  LCD_IO_Delay(1);
  while(LL_SPI_IsActiveFlag_BSY(SPIX));//while(BITBAND_ACCESS(SPIX->SR, SPI_SR_BSY_Pos));
}

//-----------------------------------------------------------------------------
extern inline uint16_t LcdRead16(void);
inline uint16_t LcdRead16(void)
{
  uint16_t d16;
  while(!LL_SPI_IsActiveFlag_RXNE(SPIX));//while(!BITBAND_ACCESS(SPIX->SR, SPI_SR_RXNE_Pos));
  d16 = LL_SPI_ReceiveData16(SPIX);//SPIX->DR;
  return d16;
}

//-----------------------------------------------------------------------------
extern inline void LcdCmdWrite16(uint16_t cmd16);
inline void LcdCmdWrite16(uint16_t cmd16)
{
  LCD_RS_CMD;
  LL_SPI_TransmitData16(SPIX,cmd16);//SPIX->DR = cmd16;
  LCD_IO_Delay(2);
   while(LL_SPI_IsActiveFlag_BSY(SPIX));//while(BITBAND_ACCESS(SPIX->SR, SPI_SR_BSY_Pos));
  LCD_RS_DATA;
}

#endif   // #else LCD_SPI == 0

//-----------------------------------------------------------------------------
#if (DMANUM(LCD_DMA_TX) > 0 || DMANUM(LCD_DMA_RX) > 0) && LCD_SPI > 0
/* DMA transfer end check */

/* DMA status
   - 0: all DMA transfers are completed
   - 1: last DMA transfer in progress
   - 2: DMA transfer in progress */
volatile uint32_t LCD_IO_DmaTransferStatus = 0;

//-----------------------------------------------------------------------------
/* Waiting for all DMA processes to complete */

/* no FreeRtos */

extern inline void WaitForDmaEnd(void);
inline void WaitForDmaEnd(void)
{
  while(LCD_IO_DmaTransferStatus);
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/* SPI TX on DMA */

//-----------------------------------------------------------------------------
void DMAX_CHANNEL_IRQHANDLER(LCD_DMA_TX)(void)
{
  if(DMAX(LCD_DMA_TX)->ISR & DMAX_ISR_TCIF(LCD_DMA_TX))
  {
		DMAX(LCD_DMA_TX)->IFCR = DMAX_IFCR_CTCIF(LCD_DMA_TX);
		
		if (isDmaCircMode && dmaCircCnt-- == 0){
			LL_DMA_SetMode(DMA1,LL_DMA_CHANNEL_5,LL_DMA_MODE_NORMAL);
			//DMAX_CHANNEL(LCD_DMA_TX)->CCR &= DMA_CCR_CIRC;
			isDmaCircMode = false;
			dmaCircCnt = 1;
			return;
		}

		if (!isDmaCircMode){
		
			DMAX_CHANNEL(LCD_DMA_TX)->CCR = 0;
			
			while(DMAX_CHANNEL(LCD_DMA_TX)->CCR & DMA_CCR_EN);
			
			BITBAND_ACCESS(SPIX->CR2, SPI_CR2_TXDMAEN_Pos) = 0;
			while(BITBAND_ACCESS(SPIX->SR, SPI_SR_BSY_Pos));
			LCD_IO_Delay(2 ^ LCD_SPI_SPD_WRITE);

			if(LCD_IO_DmaTransferStatus == 1) /* last transfer end ? */
				LCD_CS_OFF;

			/* no FreeRtos */
			LCD_IO_DmaTransferStatus = 0;
		
		} 
  }
  else
    DMAX(LCD_DMA_TX)->IFCR = DMAX_IFCR_CGIF(LCD_DMA_TX);
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteMultiData(void * pData, uint32_t Size, uint32_t dmacr)
{
	
  DMAX(LCD_DMA_TX)->IFCR = DMAX_IFCR_CGIF(LCD_DMA_TX);
  LL_SPI_Disable(SPIX);//SPIX->CR1 &= ~SPI_CR1_SPE;           /* SPI stop */
  DMAX_CHANNEL(LCD_DMA_TX)->CCR = 0;   /* DMA stop */
  while(DMAX_CHANNEL(LCD_DMA_TX)->CCR & DMA_CCR_EN);
  DMAX_CHANNEL(LCD_DMA_TX)->CMAR = (uint32_t)pData;
  DMAX_CHANNEL(LCD_DMA_TX)->CPAR = (uint32_t)&SPIX->DR;
	//DMAX_CHANNEL(LCD_DMA_TX)->CPAR = (uint32_t)tempBuf;
  DMAX_CHANNEL(LCD_DMA_TX)->CNDTR = Size;
  DMAX_CHANNEL(LCD_DMA_TX)->CCR = dmacr;
	//LL_DMA_SetPeriphIncMode(DMA1,LL_DMA_CHANNEL_5,LL_DMA_PERIPH_INCREMENT);
  LL_SPI_EnableDMAReq_TX(SPIX);//BITBAND_ACCESS(SPIX->CR2, SPI_CR2_TXDMAEN_Pos) = 1;
  LL_SPI_Enable(SPIX);//SPIX->CR1 |= SPI_CR1_SPE;
  DMAX_CHANNEL(LCD_DMA_TX)->CCR |= DMA_CCR_EN;
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteMultiData8(uint8_t * pData, uint32_t Size, uint32_t dinc)
{
  uint32_t dmacr;
  static uint8_t d8s;
  if(!dinc)
  {
    d8s = *pData;
    pData = &d8s;
    dmacr = DMA_CCR_TCIE | (0 << DMA_CCR_MSIZE_Pos) |
            (0 << DMA_CCR_PSIZE_Pos) | DMA_CCR_DIR | (0 << DMA_CCR_MINC_Pos) |
            (DMAPRIORITY(LCD_DMA_TX) << DMA_CCR_PL_Pos);
  }
  else
    dmacr = DMA_CCR_TCIE | (0 << DMA_CCR_MSIZE_Pos) |
            (0 << DMA_CCR_PSIZE_Pos) | DMA_CCR_DIR | (1 << DMA_CCR_MINC_Pos) |
            (DMAPRIORITY(LCD_DMA_TX) << DMA_CCR_PL_Pos);

  while(Size)
  {
    if(Size <= DMA_MAXSIZE)
    {
      LCD_IO_DmaTransferStatus = 1;     /* last transfer */
      LCD_IO_WriteMultiData((void *)pData, Size, dmacr);
      Size = 0;
      #if LCD_DMA_TXWAIT == 1
      if(dinc)
        WaitForDmaEnd();
      #endif
    }
    else
    {
      LCD_IO_DmaTransferStatus = 2;     /* no last transfer */
      LCD_IO_WriteMultiData((void *)pData, DMA_MAXSIZE, dmacr);
      if(dinc)
        pData+= DMA_MAXSIZE;
      Size-= DMA_MAXSIZE;
      #if LCD_DMA_TXWAIT != 2
      WaitForDmaEnd();
      #endif
    }
    #if LCD_DMA_TXWAIT == 2
    WaitForDmaEnd();
    #endif
  }
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteMultiData16(uint16_t * pData, uint32_t Size, uint32_t dinc)
{
  uint32_t dmacr;
  static uint16_t d16s;
  if(!dinc)
  {
    d16s = *pData;
    pData = &d16s;
    dmacr = DMA_CCR_TCIE | (1 << DMA_CCR_MSIZE_Pos) |
            (1 << DMA_CCR_PSIZE_Pos) | DMA_CCR_DIR | (0 << DMA_CCR_MINC_Pos) |
            (DMAPRIORITY(LCD_DMA_TX) << DMA_CCR_PL_Pos);
  }
  else
    dmacr = DMA_CCR_TCIE | (1 << DMA_CCR_MSIZE_Pos) |
            (1 << DMA_CCR_PSIZE_Pos) | DMA_CCR_DIR | (1 << DMA_CCR_MINC_Pos) |
            (DMAPRIORITY(LCD_DMA_TX) << DMA_CCR_PL_Pos);

  while(Size)
  {
    if(Size <= DMA_MAXSIZE)
    {
      LCD_IO_DmaTransferStatus = 1;     /* last transfer */
      LCD_IO_WriteMultiData((void *)pData, Size, dmacr);
      Size = 0;
      #if LCD_DMA_TXWAIT == 1
      if(dinc)
        WaitForDmaEnd();
      #endif
    }
    else if(Size < 2 * DMA_MAXSIZE)
    {
      LCD_IO_DmaTransferStatus = 2;     /* no last transfer */
      LCD_IO_WriteMultiData((void *)pData, Size - DMA_MAXSIZE, dmacr);
      if(dinc)
        pData+= Size - DMA_MAXSIZE;
      Size = DMA_MAXSIZE;
      #if LCD_DMA_TXWAIT != 2
      WaitForDmaEnd();
      #endif
    }
    else
    {
      LCD_IO_DmaTransferStatus = 2;     /* no last transfer */
      LCD_IO_WriteMultiData((void *)pData, DMA_MAXSIZE, dmacr);
      if(dinc)
        pData+= DMA_MAXSIZE;
      Size-= DMA_MAXSIZE;
      #if LCD_DMA_TXWAIT != 2
      WaitForDmaEnd();
      #endif
    }
    #if LCD_DMA_TXWAIT == 2
    WaitForDmaEnd();
    #endif
  }
}

#endif // #else DMANUM(LCD_DMA_TX) == 0 || LCD_SPI == 0

//-----------------------------------------------------------------------------
/* SPI RX on DMA */

//-----------------------------------------------------------------------------
void DMAX_CHANNEL_IRQHANDLER(LCD_DMA_RX)(void)
{
  volatile uint8_t d8 __attribute__((unused));
  if(DMAX(LCD_DMA_RX)->ISR & DMAX_ISR_TCIF(LCD_DMA_RX))
  {
    DMAX(LCD_DMA_RX)->IFCR = DMAX_IFCR_CTCIF(LCD_DMA_RX);
    BITBAND_ACCESS(SPIX->CR2, SPI_CR2_RXDMAEN_Pos) = 0; /* SPI DMA off  */
    while(BITBAND_ACCESS(SPIX->SR, SPI_SR_RXNE_Pos))
      d8 = *(uint8_t *)&SPIX->DR;
    SPIX->CR1 = (SPIX->CR1 & ~SPI_CR1_BR) | ((LCD_SPI_SPD_READ << SPI_CR1_BR_Pos) | SPI_CR1_BIDIOE);
    LCD_IO_Delay(2 ^ LCD_SPI_SPD_READ);
    while(BITBAND_ACCESS(SPIX->SR, SPI_SR_RXNE_Pos))
      d8 = SPIX->DR;
    SPIX->CR1 |= SPI_CR1_SPE;
    DMAX_CHANNEL(LCD_DMA_RX)->CCR = 0;
    while(DMAX_CHANNEL(LCD_DMA_RX)->CCR & DMA_CCR_EN);

    LCD_IO_DmaTransferStatus = 0;

  }
  else
    DMAX(LCD_DMA_RX)->IFCR = DMAX_IFCR_CGIF(LCD_DMA_RX);
}

//-----------------------------------------------------------------------------
void LCD_IO_ReadMultiData(void * pData, uint32_t Size, uint32_t dmacr)
{
  DMAX(LCD_DMA_RX)->IFCR = DMAX_IFCR_CGIF(LCD_DMA_RX);
  DMAX_CHANNEL(LCD_DMA_RX)->CCR = 0;  /* DMA stop */
  while(DMAX_CHANNEL(LCD_DMA_RX)->CCR & DMA_CCR_EN);
  DMAX_CHANNEL(LCD_DMA_RX)->CMAR = (uint32_t)pData;  /* memory addr */
  DMAX_CHANNEL(LCD_DMA_RX)->CPAR = (uint32_t)&SPIX->DR; /* periph addr */
  DMAX_CHANNEL(LCD_DMA_RX)->CNDTR = Size;           /* number of data */
  DMAX_CHANNEL(LCD_DMA_RX)->CCR = dmacr;
  DMAX_CHANNEL(LCD_DMA_RX)->CCR |= DMA_CCR_EN;  /* DMA start */
  BITBAND_ACCESS(SPIX->CR2, SPI_CR2_RXDMAEN_Pos) = 1; /* SPI DMA on */
}

//-----------------------------------------------------------------------------
void LCD_IO_ReadMultiData8(uint8_t * pData, uint32_t Size)
{
  uint32_t dmacr;
  dmacr = DMA_CCR_TCIE | (0 << DMA_CCR_MSIZE_Pos) | (0 << DMA_CCR_PSIZE_Pos) |
          DMA_CCR_MINC | (DMAPRIORITY(LCD_DMA_RX) << DMA_CCR_PL_Pos);

  while(Size)
  {
    if(Size > DMA_MAXSIZE)
    {
      LCD_IO_DmaTransferStatus = 2;     /* no last transfer */
      LCD_IO_ReadMultiData((void *)pData, DMA_MAXSIZE, dmacr);
      Size-= DMA_MAXSIZE;
      pData+= DMA_MAXSIZE;
    }
    else
    {
      LCD_IO_DmaTransferStatus = 1;     /* last transfer */
      LCD_IO_ReadMultiData((void *)pData, Size, dmacr);
      Size = 0;
    }
    WaitForDmaEnd();
  }
  LCD_CS_OFF;
  LcdDirWrite();
}

//-----------------------------------------------------------------------------
void LCD_IO_ReadMultiData16(uint16_t * pData, uint32_t Size)
{
  uint32_t dmacr;
  dmacr = DMA_CCR_TCIE | (1 << DMA_CCR_MSIZE_Pos) | (1 << DMA_CCR_PSIZE_Pos) |
          DMA_CCR_MINC | (DMAPRIORITY(LCD_DMA_RX) << DMA_CCR_PL_Pos);

  while(Size)
  {
    if(Size > DMA_MAXSIZE)
    {
      LCD_IO_DmaTransferStatus = 2;     /* no last transfer */
      LCD_IO_ReadMultiData((void *)pData, DMA_MAXSIZE, dmacr);
      Size-= DMA_MAXSIZE;
      pData+= DMA_MAXSIZE;
    }
    else
    {
      LCD_IO_DmaTransferStatus = 1;     /* last transfer */
      LCD_IO_ReadMultiData((void *)pData, Size, dmacr);
      Size = 0;
    }
    WaitForDmaEnd();
  }
  LCD_CS_OFF;
  LcdDirWrite();
}

//-----------------------------------------------------------------------------
void LCD_IO_ReadMultiData16to24(uint16_t * pData, uint32_t Size)
{
  volatile uint8_t d8 __attribute__((unused));
  uint32_t dmadata_ri = 0, rgb888cnt = 0; /* DMA tempbuffer index, rgb888 index (0..2) */
  uint32_t ntdr_follower;               /* NTDR register folower */
  uint8_t  rgb888[3];
  #if LCD_DMA_RX_BUFMODE == 0
  uint8_t dmadata[LCD_DMA_RX_BUFSIZE] __attribute__((aligned));
  #elif LCD_DMA_RX_BUFMODE == 1
  static uint8_t dmadata[LCD_DMA_RX_BUFSIZE] __attribute__((aligned));
  #elif LCD_DMA_RX_BUFMODE == 2
  uint8_t * dmadata;
  dmadata = LCD_DMA_RX_MALLOC(LCD_DMA_RX_BUFSIZE);
  if(!dmadata)
    return;
  #endif
  DMAX(LCD_DMA_RX)->IFCR = DMAX_IFCR_CGIF(LCD_DMA_RX);
  DMAX_CHANNEL(LCD_DMA_RX)->CCR = 0;  /* DMA stop */
  while(DMAX_CHANNEL(LCD_DMA_RX)->CCR & DMA_CCR_EN);
  DMAX_CHANNEL(LCD_DMA_RX)->CMAR = (uint32_t)dmadata;
  DMAX_CHANNEL(LCD_DMA_RX)->CPAR = (uint32_t)&SPIX->DR;
  DMAX_CHANNEL(LCD_DMA_RX)->CNDTR = LCD_DMA_RX_BUFSIZE;
  ntdr_follower = LCD_DMA_RX_BUFSIZE;
  DMAX_CHANNEL(LCD_DMA_RX)->CCR = (0 << DMA_CCR_MSIZE_Pos) |
      (0 << DMA_CCR_PSIZE_Pos) | DMA_CCR_MINC |
      (DMAPRIORITY(LCD_DMA_RX) << DMA_CCR_PL_Pos) | DMA_CCR_CIRC;
  DMAX_CHANNEL(LCD_DMA_RX)->CCR |= DMA_CCR_EN;
  BITBAND_ACCESS(SPIX->CR2, SPI_CR2_RXDMAEN_Pos) = 1;
  while(Size)
  {
    if(ntdr_follower != DMAX_CHANNEL(LCD_DMA_RX)->CNDTR)
    {
      if(!--ntdr_follower)
        ntdr_follower = LCD_DMA_RX_BUFSIZE;
      __NOP(); __NOP(); __NOP();        /* a small wait until the DMA transfer is definitely completed */
      rgb888[rgb888cnt++] = dmadata[dmadata_ri++];
      if(dmadata_ri >= LCD_DMA_RX_BUFSIZE)
        dmadata_ri = 0;
      if(rgb888cnt == 3)
      {
        rgb888cnt = 0;
        Size--;
        *pData++ = (rgb888[0] & 0xF8) << 8 | (rgb888[1] & 0xFC) << 3 | rgb888[2] >> 3;
      }
    }
  }
  BITBAND_ACCESS(SPIX->CR2, SPI_CR2_RXDMAEN_Pos) = 0;
  while(BITBAND_ACCESS(SPIX->SR, SPI_SR_RXNE_Pos))
    d8 = SPIX->DR;
  SPIX->CR1 = (SPIX->CR1 & ~SPI_CR1_BR) | ((LCD_SPI_SPD_WRITE << SPI_CR1_BR_Pos) | SPI_CR1_BIDIOE);
  LCD_IO_Delay(2 ^ LCD_SPI_SPD_READ);
  while(BITBAND_ACCESS(SPIX->SR, SPI_SR_RXNE_Pos))
    d8 = SPIX->DR;
  DMAX_CHANNEL(LCD_DMA_RX)->CCR = 0;
  while(DMAX_CHANNEL(LCD_DMA_RX)->CCR & DMA_CCR_EN);
  LCD_CS_OFF;
  LcdDirWrite();
}


//=============================================================================
#ifdef  __GNUC__
#pragma GCC push_options
#pragma GCC optimize("O0")
#elif   defined(__CC_ARM)
#pragma push
#pragma O0
#endif
void LCD_IO_Delay(uint32_t c)
{
  while(c--);
}
#ifdef  __GNUC__
#pragma GCC pop_options
#elif   defined(__CC_ARM)
#pragma pop
#endif

//=============================================================================
/* Public functions */

void LCD_Delay(uint32_t Delay)
{
  LL_mDelay(Delay);
}

//-----------------------------------------------------------------------------
void LCD_IO_Bl_OnOff(uint8_t B1)
{
  #if GPIOX_PORTNUM(LCD_BL) >= GPIOX_PORTNUM_A
  if(Bl)
    GPIOX_ODR(LCD_BL) = LCD_BLON;
  else
    GPIOX_ODR(LCD_BL) = 1 - LCD_BLON;
  #endif
	if (B1 > 100){
		B1 = 100;
	}
	LL_TIM_OC_SetCompareCH1(BLTim,B1*10);
}

//-----------------------------------------------------------------------------
void LCD_IO_Init(void)
{
  /* Reset pin clock */
  #if GPIOX_PORTNUM(LCD_RST) >= GPIOX_PORTNUM_A
  #define GPIOX_CLOCK_LCD_RST   GPIOX_CLOCK(LCD_RST)
  
  #endif

 
  /* MISO pin clock */
  #if GPIOX_PORTNUM(LCD_MISO) >= GPIOX_PORTNUM_A
  #define GPIOX_CLOCK_LCD_MISO  GPIOX_CLOCK(LCD_MISO)
  #endif




  /* DMA clock */

  #if DMANUM(LCD_DMA_TX) == 1
  #define DMA1_CLOCK_TX         RCC_AHBENR_DMA1EN

  #endif
  #if DMANUM(LCD_DMA_RX) == 1
  #define DMA1_CLOCK_RX         RCC_AHBENR_DMA1EN

  #endif  // #else LCD_SPI == 0

  #if (DMANUM(LCD_DMA_TX) >= 1) || (DMANUM(LCD_DMA_RX) >= 1)
  RCC->AHBENR |= DMA1_CLOCK_TX | DMA1_CLOCK_RX;
  #endif

  //LCD_SPI_ALTERSET;

  /* MISO = input in full duplex mode */
  #if LCD_SPI_MODE == 2                 // Full duplex
  //GPIOX_MODE(MODE_FF_DIGITAL_INPUT, LCD_MISO);
  #endif

  /* Backlight = output, light on */
  #if GPIOX_PORTNUM(LCD_BL) >= GPIOX_PORTNUM_A
  #endif

  /* Reset pin = output, reset off */
  #if GPIOX_PORTNUM(LCD_RST) >= GPIOX_PORTNUM_A
  LCD_RST_OFF;
  #endif
	
  LCD_RS_DATA;
  LCD_CS_OFF;
  

  /* Hardware SPI */
  LCD_SPI_RCC_EN;
  
  /* TX or full duplex */
  SPIX->CR1 = SPI_CR1_CPHA | SPI_CR1_CPOL | SPI_CR1_MSTR | SPI_CR1_SPE | SPI_CR1_SSM | SPI_CR1_SSI | (LCD_SPI_SPD_WRITE << SPI_CR1_BR_Pos);


  SPIX->CR1 |= SPI_CR1_SPE;

  /* Reset the LCD */
  #if GPIOX_PORTNUM(LCD_RST) >= GPIOX_PORTNUM_A // reset
  LCD_Delay(10);
  LCD_RST_ON;
  LCD_Delay(100);
  LCD_RST_OFF;
  #endif
  LCD_Delay(10);

  #if (DMANUM(LCD_DMA_TX) > 0 || DMANUM(LCD_DMA_RX) > 0) && LCD_SPI > 0
  #if DMANUM(LCD_DMA_TX) > 0
  NVIC_SetPriority(DMAX_CHANNEL_IRQ(LCD_DMA_TX), LCD_DMA_IRQ_PR);
  NVIC_EnableIRQ(DMAX_CHANNEL_IRQ(LCD_DMA_TX));
  #endif
  #if DMANUM(LCD_DMA_RX) > 0
  NVIC_SetPriority(DMAX_CHANNEL_IRQ(LCD_DMA_RX), LCD_DMA_IRQ_PR);
  NVIC_EnableIRQ(DMAX_CHANNEL_IRQ(LCD_DMA_RX));
  #endif
  
  #endif  // #if DMANUM(LCD_DMA_RX) > 0
	
	LL_TIM_CC_EnableChannel(BLTim, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableAllOutputs(BLTim);
	LL_TIM_EnableCounter(BLTim);
} // void LCD_IO_Init(void)

//-----------------------------------------------------------------------------
void LCD_IO_WriteCmd8(uint8_t Cmd)
{
  WaitForDmaEnd();
  LcdSpiMode8();
  LCD_CS_ON;
  LcdCmdWrite8(Cmd);
  LCD_CS_OFF;
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteCmd16(uint16_t Cmd)
{
  WaitForDmaEnd();
  LcdSpiMode16();
  LCD_CS_ON;
  LcdCmdWrite16(Cmd);
  LCD_CS_OFF;
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteData8(uint8_t Data)
{
  WaitForDmaEnd();
  LcdSpiMode8();
  LCD_CS_ON;
  LcdWrite8(Data);
  LCD_CS_OFF;
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteData16(uint16_t Data)
{
  WaitForDmaEnd();
  LcdSpiMode16();
  LCD_CS_ON;
  LcdWrite16(Data);
  LCD_CS_OFF;
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteCmd8DataFill16(uint8_t Cmd, uint16_t Data, uint32_t Size)
{
  WaitForDmaEnd();
  LcdSpiMode8();
  LCD_CS_ON;
  LcdCmdWrite8(Cmd);
  LcdSpiMode16();
  LCD_IO_WriteMultiData16(&Data, Size, 0);
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteCmd8MultipleData8(uint8_t Cmd, uint8_t *pData, uint32_t Size)
{
  WaitForDmaEnd();
  LcdSpiMode8();
  LCD_CS_ON;
  LcdCmdWrite8(Cmd);
  LCD_IO_WriteMultiData8(pData, Size, 1);
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteCmd8MultipleData16(uint8_t Cmd, uint16_t *pData, uint32_t Size)
{
  WaitForDmaEnd();
  LcdSpiMode8();
  LCD_CS_ON;
  LcdCmdWrite8(Cmd);
  LcdSpiMode16();
  LCD_IO_WriteMultiData16(pData, Size, 1);
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteCmd16DataFill16(uint16_t Cmd, uint16_t Data, uint32_t Size)
{
  WaitForDmaEnd();
  LcdSpiMode16();
  LCD_CS_ON;
  LcdCmdWrite16(Cmd);
  LCD_IO_WriteMultiData16(&Data, Size, 0);
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteCmd16MultipleData8(uint16_t Cmd, uint8_t *pData, uint32_t Size)
{
  WaitForDmaEnd();
  LcdSpiMode16();
  LCD_CS_ON;
  LcdCmdWrite16(Cmd);
  LcdSpiMode8();
  LCD_IO_WriteMultiData8(pData, Size, 1);
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteCmd16MultipleData16(uint16_t Cmd, uint16_t *pData, uint32_t Size)
{
  WaitForDmaEnd();
  LcdSpiMode16();
  LCD_CS_ON;
  LcdCmdWrite16(Cmd);
  LCD_IO_WriteMultiData16(pData, Size, 1);
}

//-----------------------------------------------------------------------------
void LCD_IO_WriteCmd8DataFill8(uint8_t Cmd, uint8_t* Data, uint32_t Size){
	WaitForDmaEnd();
  LcdSpiMode8();
  LCD_CS_ON;
  LcdCmdWrite8(Cmd);

	uint32_t dmacr;

  dmacr = DMA_CCR_TCIE | (0 << DMA_CCR_MSIZE_Pos) |
            (0 << DMA_CCR_PSIZE_Pos) | DMA_CCR_DIR | (1 << DMA_CCR_MINC_Pos) |
            (DMAPRIORITY(LCD_DMA_TX) << DMA_CCR_PL_Pos);
	
	if (Size > 1) {
		dmacr |= DMA_CCR_CIRC;
		isDmaCircMode = true;
		dmaCircCnt = Size/FILL_BUF_SIZE - 1;
	}
	for(uint32_t i = 0; i < FILL_BUF_SIZE*3; i+=3){
		fillBuf[i] = *Data;
		fillBuf[i+1] = *(Data+1);
		fillBuf[i+2] = *(Data+2);
	}
	LCD_IO_DmaTransferStatus = 1;
  LCD_IO_WriteMultiData((void *)fillBuf, FILL_BUF_SIZE*3, dmacr);
	
//	while(Size)
//  {
//    if(Size <= DMA_MAXSIZE)
//    {
//      LCD_IO_DmaTransferStatus = 1;     /* last transfer */
//      LCD_IO_WriteMultiData((void *)pData, Size, dmacr);
//      Size = 0;
//      #if LCD_DMA_TXWAIT == 1
//      if(dinc)
//        WaitForDmaEnd();
//      #endif
//    }
//    else
//    {
//      LCD_IO_DmaTransferStatus = 2;     /* no last transfer */
//      LCD_IO_WriteMultiData((void *)pData, DMA_MAXSIZE, dmacr);
//      if(dinc)
//        pData+= DMA_MAXSIZE;
//      Size-= DMA_MAXSIZE;
//      #if LCD_DMA_TXWAIT != 2
//      WaitForDmaEnd();
//      #endif
//    }
//    #if LCD_DMA_TXWAIT == 2
//    WaitForDmaEnd();
//    #endif
//  }
}

bool		LCD_IO_isBusy(){
	return (!(LCD_IO_DmaTransferStatus == 0));
}

//-----------------------------------------------------------------------------
void LCD_IO_ReadCmd8MultipleData8(uint8_t Cmd, uint8_t *pData, uint32_t Size, uint32_t DummySize)
{
  WaitForDmaEnd();
  LcdSpiMode8();
  LCD_CS_ON;
  LcdCmdWrite8(Cmd);

  DummySize = (DummySize << 3) + LCD_SCK_EXTRACLK;
  LcdDirRead(DummySize);
  LCD_IO_ReadMultiData8(pData, Size);
}

//-----------------------------------------------------------------------------
void LCD_IO_ReadCmd8MultipleData16(uint8_t Cmd, uint16_t *pData, uint32_t Size, uint32_t DummySize)
{
  WaitForDmaEnd();
  LcdSpiMode8();
  LCD_CS_ON;
  LcdCmdWrite8(Cmd);
  LcdSpiMode16();

  DummySize = (DummySize << 3) + LCD_SCK_EXTRACLK;
  LcdDirRead(DummySize);
  LCD_IO_ReadMultiData16(pData, Size);
}

//-----------------------------------------------------------------------------
void LCD_IO_ReadCmd8MultipleData24to16(uint8_t Cmd, uint16_t *pData, uint32_t Size, uint32_t DummySize)
{
  WaitForDmaEnd();
  LcdSpiMode8();
  LCD_CS_ON;
  LcdCmdWrite8(Cmd);

  DummySize = (DummySize << 3) + LCD_SCK_EXTRACLK;
  LcdDirRead(DummySize);
  LCD_IO_ReadMultiData16to24(pData, Size);
}

//-----------------------------------------------------------------------------
void LCD_IO_ReadCmd16MultipleData8(uint16_t Cmd, uint8_t *pData, uint32_t Size, uint32_t DummySize)
{
  WaitForDmaEnd();
  LcdSpiMode16();
  LCD_CS_ON;
  LcdCmdWrite16(Cmd);
  LcdSpiMode8();

  DummySize = (DummySize << 3) + LCD_SCK_EXTRACLK;
  LcdDirRead(DummySize);
  LCD_IO_ReadMultiData8(pData, Size);
}

//-----------------------------------------------------------------------------
void LCD_IO_ReadCmd16MultipleData16(uint16_t Cmd, uint16_t *pData, uint32_t Size, uint32_t DummySize)
{
  WaitForDmaEnd();
  LcdSpiMode16();
  LCD_CS_ON;
  LcdCmdWrite16(Cmd);

  DummySize = (DummySize << 3) + LCD_SCK_EXTRACLK;
  LcdDirRead(DummySize);
  LCD_IO_ReadMultiData16(pData, Size);
}

//-----------------------------------------------------------------------------
void LCD_IO_ReadCmd16MultipleData24to16(uint16_t Cmd, uint16_t *pData, uint32_t Size, uint32_t DummySize)
{
  WaitForDmaEnd();
  LcdSpiMode16();
  LCD_CS_ON;
  LcdCmdWrite16(Cmd);
  LcdSpiMode8();

  DummySize = (DummySize << 3) + LCD_SCK_EXTRACLK;
  LcdDirRead(DummySize);
  LCD_IO_ReadMultiData16to24(pData, Size);
}

