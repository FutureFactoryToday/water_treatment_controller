/**
  ******************************************************************************
  * @file    .h
  * @brief   This file contains all the function prototypes for
  *          the .c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _WTC_FONTS_H_
#define _WTC_FONTS_H_

/*Includes */
#include <stdint.h>

/*Public defines */
typedef struct {
	uint16_t width;
	uint8_t bitsArray[];
} glyph_t;

typedef struct{
	uint16_t height;
	glyph_t* glyph[];
} WTC_FONT_t;

/*Global params*/
extern const WTC_FONT_t Oxygen_Mono_8;
extern const WTC_FONT_t Oxygen_Mono_12;
extern const WTC_FONT_t Oxygen_Mono_16;
extern const WTC_FONT_t Oxygen_Mono_20;
extern const WTC_FONT_t Oxygen_Mono_24;
/*Prototypes */


#endif /* __WTC_FONTS_H__ */

