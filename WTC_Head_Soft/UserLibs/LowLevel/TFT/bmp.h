/*
 * bmp.h
 *
 */

#ifndef __BMP_H_
#define __BMP_H_
#include <stdint.h>
#define OFFSET_BITMAP         8

typedef struct __attribute__((packed)) {
  uint16_t biWidth;
  uint16_t biHeight;
	uint32_t dataSize;
} BITMAPINFOHEADER;

typedef struct __attribute__((packed)) {
  BITMAPINFOHEADER infoHeader;
	#ifdef _565_FORMAT 
  uint16_t data[];
	#endif
	#ifdef _24bit_FORMAT
	uint8_t data[];
	#endif
} BITMAPSTRUCT;

#endif /* __BMP_H_ */
