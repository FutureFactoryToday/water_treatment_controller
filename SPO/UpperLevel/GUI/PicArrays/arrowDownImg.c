#include <stdint.h>
#include "TFT\lcd.h"
#include "TFT\bmp.h"

#define   WIDTH   37	
#define   HEIGHT  21

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

const BITMAPSTRUCT gImage_ARROWDOWN __attribute__((aligned)) =
{
    WIDTH,
    HEIGHT,
    WIDTH * HEIGHT ,
  {0XD6BA, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XD6BA, 
0XFFFF, 
0XCE79, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XCE79, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XC638, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XCE59, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFDF, 
0XC618, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XC618, 
0XFFDF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XF7BE, 
0XBDF7, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XBDF7, 
0XF7BE, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XEF7D, 
0XBDD7, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XBDD7, 
0XF79E, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XE73C, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XBDD7, 
0XEF7D, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XDEFB, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5D7, 
0XE75D, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XD6BA, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XE71C, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XCE59, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XDEDB, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFDF, 
0XC638, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XD69A, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFDF, 
0XBDF7, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XCE59, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XF79E, 
0XBDD7, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XC638, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XEF5D, 
0XB5D7, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XC618, 
0XFFDF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XE71C, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XBDF7, 
0XF7BE, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XDEDB, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XBDD7, 
0XEF7D, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XD69A, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5D7, 
0XEF5D, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XC659, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XE73C, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFDF, 
0XC618, 
0XB5B6, 
0XB5B6, 
0XB5B6, 
0XDEFB, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XF7BE, 
0XBDF7, 
0XB5B6, 
0XD6BA, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XEF7D, 
0XD69A, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
0XFFFF, 
}
};