#include <stdint.h>
#include "TFT\lcd.h"
#include "TFT\bmp.h"

#define   WIDTH   50	
#define   HEIGHT  40

#if LCD_REVERSE16 == 0
#define  RC(a)   a
#endif
#if LCD_REVERSE16 == 1
#define  RC(a)   ((((a) & 0xFF) << 8) | (((a) & 0xFF00) >> 8))
#endif

// struct packing
#ifdef  __GNUC__
#pragma pack(push, 1)
#elif   defined(__CC_ARM)	
#pragma push
#pragma pack(1)
#endif

const BITMAPSTRUCT gImage_ARROWUP __attribute__((aligned)) =
{
  {
    0x4d42u,
    sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + (WIDTH * HEIGHT * 2),
    0x0000u,
    0x0000u,
    sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER)
  },
  {
    sizeof(BITMAPINFOHEADER),
    WIDTH,
    HEIGHT,
    1u,
    16,
    0x00000003u,
    (WIDTH * HEIGHT * 2),
    0x00000000ul,
    0x00000000ul,
    0x00000000ul,
    0x00000000ul
  },
  {}
};