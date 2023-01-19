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
  uint16_t data[];
} BITMAPSTRUCT;

#endif /* __BMP_H_ */
