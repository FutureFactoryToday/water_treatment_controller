/*Pic Array v.2*/
#include <stdint.h>
#include "TFT/bmp.h" 
#define   WIDTH   42
#define   HEIGHT  38
#define   SIZE  1596
const BITMAPSTRUCT Logo __attribute__((aligned)) =
{
  {
    WIDTH,
    HEIGHT,
    SIZE
  },
  {
  #ifdef _565_FORMAT
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1968,	0x1290,	0x03b8,	0x0397,	0x0397,	0x0b13,	0x1947,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1968,	0x0335,	0x12d1,	0x0af2,	0x03b8,	0x0397,	0x03b8,	0x0af3,	0x1947,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1189,	0x0355,	0x03b8,	0x03b8,	0x1a0c,	0x0b14,	0x0397,	0x0397,	0x03b8,	0x0b34,	0x1947,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1968,	0x0355,	0x0397,	0x0397,	0x0397,	0x0af3,	0x19ca,	0x03b8,	0x0397,	0x0397,	0x03b8,	0x0af3,	0x1967,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1189,	0x0355,	0x0398,	0x0397,	0x0397,	0x0397,	0x03b8,	0x120c,	0x124d,	0x0397,	0x0397,	0x0397,	0x03b8,	0x0b34,	0x1968,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1968,	0x0334,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0376,	0x1926,	0x0af2,	0x0398,	0x0397,	0x0397,	0x03b8,	0x0af2,	0x1947,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1189,	0x0355,	0x0398,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x03b8,	0x126e,	0x1946,	0x0397,	0x0397,	0x0397,	0x0397,	0x03b8,	0x0b35,	0x1968,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1947,	0x0334,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0b35,	0x1947,	0x124d,	0x03b8,	0x0397,	0x0397,	0x0397,	0x03b8,	0x0af3,	0x1946,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1189,	0x0356,	0x0398,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x03b8,	0x126e,	0x1926,	0x0af2,	0x0397,	0x0397,	0x0397,	0x0397,	0x03b8,	0x0b35,	0x1968,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1968,	0x0334,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0b55,	0x18e5,	0x19ca,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0398,	0x0af3,	0x1947,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1968,	0x0356,	0x0398,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x03b9,	0x19ca,	0x1905,	0x12b0,	0x0398,	0x0397,	0x0397,	0x0397,	0x0397,	0x0398,	0x0b34,	0x1968,	0x1927,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1947,	0x0314,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0398,	0x12b0,	0x1905,	0x19a9,	0x0376,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0398,	0x0af3,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1968,	0x0356,	0x0398,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0355,	0x1989,	0x1906,	0x128f,	0x0398,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x03b8,	0x0b34,	0x1967,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1926,	0x1968,	0x0314,	0x0397,	0x0397,	0x0397,	0x0398,	0x03b8,	0x0398,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x11ec,	0x1926,	0x1968,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0398,	0x0af3,	0x1926,	0x1927,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1926,	0x1968,	0x0355,	0x03b8,	0x0397,	0x0397,	0x0376,	0x124e,	0x122d,	0x12b0,	0x0b13,	0x0356,	0x0397,	0x03b8,	0x0398,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0398,	0x12b0,	0x1926,	0x1905,	0x12b1,	0x03b8,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x03b8,	0x0b14,	0x1968,	0x1927,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1926,	0x1968,	0x0af3,	0x0398,	0x0397,	0x0397,	0x0397,	0x0397,	0x0b13,	0x1926,	0x1926,	0x1947,	0x1989,	0x19cb,	0x124e,	0x12b1,	0x0b34,	0x0397,	0x03b9,	0x03b8,	0x0398,	0x0397,	0x0398,	0x0b55,	0x1926,	0x1926,	0x19ca,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0af3,	0x1926,	0x1927,	0x1947,	0x1947,	
	0x1926,	0x1968,	0x0355,	0x03b8,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x03b8,	0x12b0,	0x1926,	0x1947,	0x1947,	0x1926,	0x1926,	0x1926,	0x1926,	0x1926,	0x1989,	0x1a2d,	0x12b1,	0x0af3,	0x0355,	0x03b8,	0x19a9,	0x1926,	0x1947,	0x0af3,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x03b8,	0x0b13,	0x1968,	0x1947,	0x1947,	
	0x1968,	0x0334,	0x03b9,	0x0398,	0x0398,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x11cb,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1926,	0x1947,	0x1988,	0x19ca,	0x1968,	0x1947,	0x1926,	0x128f,	0x03d9,	0x03b8,	0x03b8,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0397,	0x0398,	0x0b13,	0x1905,	0x1947,	
	0x19a9,	0x124e,	0x128f,	0x12b0,	0x12d1,	0x0af3,	0x0b14,	0x0b34,	0x0355,	0x0376,	0x03b8,	0x0396,	0x1989,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1927,	0x1947,	0x1947,	0x1947,	0x1926,	0x1968,	0x19eb,	0x128f,	0x0af2,	0x0b34,	0x0397,	0x0397,	0x03b8,	0x0397,	0x0397,	0x03b8,	0x0b13,	0x1947,	
	0x1947,	0x1926,	0x1926,	0x1926,	0x1926,	0x1947,	0x1968,	0x1968,	0x1989,	0x19ca,	0x11cb,	0x120c,	0x1989,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1926,	0x1926,	0x1947,	0x1968,	0x19ca,	0x120c,	0x126f,	0x0af3,	0x0376,	0x03b8,	0x03d9,	0x120c,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1927,	0x1926,	0x1926,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1127,	0x1106,	0x1106,	0x1106,	0x1106,	0x1106,	0x1126,	0x1947,	0x1947,	0x1947,	0x1147,	0x1106,	0x1106,	0x1106,	0x1106,	0x1106,	0x10e6,	0x10e5,	0x10e5,	0x1105,	0x1147,	0x11cb,	0x11eb,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1127,	0x322a,	0x530d,	0x52cc,	0x52cc,	0x52cc,	0x52cc,	0x428b,	0x1947,	0x1947,	0x1147,	0x21a8,	0x52ed,	0x52ec,	0x52ec,	0x52ec,	0x52ec,	0x52ec,	0x4acc,	0x4aac,	0x428b,	0x428b,	0x4aab,	0x29a8,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1147,	0x2188,	0x8c71,	0xa514,	0x9cf3,	0x9cf3,	0xa514,	0x8c72,	0x1127,	0x1947,	0x1127,	0x29e9,	0xbdf7,	0xbdf7,	0xbdf7,	0xbdf7,	0xbdf7,	0xbdf7,	0xbdf7,	0xbdf7,	0xbdf7,	0xc618,	0xbdd7,	0x3209,	
	0x1947,	0x1947,	0x1127,	0x1127,	0x1127,	0x1127,	0x1147,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1126,	0x320a,	0xa534,	0x94d3,	0x94d3,	0x9cd3,	0x8431,	0x1127,	0x1947,	0x1127,	0x21a8,	0xad76,	0xb596,	0xb596,	0xb596,	0xb596,	0xb596,	0xb596,	0xb596,	0xb5b6,	0xbdf7,	0x4acc,	0x1127,	
	0x1947,	0x1967,	0x4aab,	0x322a,	0x29e9,	0x29c9,	0x2188,	0x1947,	0x1947,	0x1127,	0x1126,	0x1106,	0x1106,	0x1126,	0x1127,	0x1127,	0x1127,	0x1947,	0x1947,	0x1947,	0x08e6,	0x5b2d,	0x9cf3,	0x94d3,	0x9cd3,	0x8431,	0x1127,	0x1947,	0x1127,	0x2168,	0x9d14,	0xb5b6,	0xb596,	0xb596,	0xb596,	0xb596,	0xb596,	0xb5b6,	0xb5b6,	0x4aac,	0x08e6,	0x1947,	
	0x1947,	0x1127,	0x5b2d,	0x9cf3,	0x94b3,	0x8c92,	0x8451,	0x7c10,	0x7bf0,	0x6baf,	0x5b2d,	0x52ed,	0x52cc,	0x426b,	0x3209,	0x29e9,	0x21a8,	0x1127,	0x08e6,	0x08e6,	0x08e6,	0x1127,	0x73d0,	0x9cd3,	0x9cf3,	0x7bf0,	0x1126,	0x1947,	0x1147,	0x1968,	0x9cf3,	0xb5b6,	0xb596,	0xb596,	0xb596,	0xb596,	0xb5b6,	0xc5f7,	0x4acc,	0x1106,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1106,	0x426b,	0x9cd3,	0x9cf3,	0x9cd3,	0x9cd3,	0x9cf3,	0x9cf3,	0x9cf3,	0x9cf3,	0x9cf3,	0xa514,	0xa514,	0xa514,	0xa513,	0x9cf3,	0x9cd3,	0x9492,	0x8451,	0x636e,	0x73af,	0x9cd3,	0x9cf3,	0x5b0d,	0x1106,	0x1947,	0x1947,	0x1967,	0x94d3,	0xb5b6,	0xb596,	0xb596,	0xb596,	0xb5b6,	0xb596,	0x4acc,	0x08e5,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x0906,	0x3a4a,	0x94b2,	0x9cf3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x9cd3,	0x9cd3,	0x9cf3,	0x9cd3,	0x94d3,	0xa514,	0x426b,	0x1126,	0x1947,	0x1147,	0x1967,	0x9cd3,	0xb5b6,	0xb596,	0xb596,	0xb5b6,	0xbdd7,	0x530d,	0x1106,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1106,	0x1127,	0x6baf,	0x9cd3,	0x9cd3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x9cd3,	0x9492,	0x1967,	0x1147,	0x1947,	0x1127,	0x2188,	0xa535,	0xb5b6,	0xb596,	0xb5b6,	0xb596,	0x4acc,	0x08c5,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1127,	0x1147,	0x428b,	0x94b2,	0xa514,	0x9cd3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0xa514,	0x634e,	0x1106,	0x1947,	0x1947,	0x1127,	0x2188,	0xad96,	0xb596,	0xb5b6,	0xbdf7,	0x52ed,	0x1106,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1106,	0x1967,	0x52ed,	0x8c92,	0x9cf3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x94d3,	0x9cf3,	0x7c10,	0x2168,	0x1127,	0x1947,	0x1947,	0x1127,	0x322a,	0xbdd7,	0xb5b6,	0xb596,	0x52cc,	0x08c5,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1127,	0x1106,	0x29c9,	0x5b2d,	0x9cd3,	0xa514,	0x9cf3,	0x9cd3,	0x9cd3,	0x94d3,	0x94d3,	0x9cd3,	0x9cd3,	0xa514,	0x9492,	0x21a8,	0x1127,	0x1947,	0x1947,	0x1947,	0x1106,	0x52ed,	0xbdf7,	0xbdd7,	0x5b0d,	0x1126,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1127,	0x1106,	0x08e6,	0x3a4a,	0x6b8f,	0x8431,	0x8c51,	0x94b2,	0x94b2,	0x8c72,	0x8431,	0x4acc,	0x1126,	0x1127,	0x1947,	0x1947,	0x1947,	0x1947,	0x08e6,	0x94d3,	0xbdd7,	0x52cd,	0x08c5,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1126,	0x1106,	0x1967,	0x21a8,	0x31e9,	0x31e9,	0x21a8,	0x1947,	0x1106,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1147,	0x1967,	0xb596,	0x5b2e,	0x1106,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1127,	0x1127,	0x1127,	0x1127,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1127,	0x5b0d,	0x52cd,	0x08e5,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x29e9,	0x1127,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1127,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	0x1947,	
	
  #endif

  #ifdef _24bit_FORMAT
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x2c,0x44,	0x10,0x50,0x80,	0x00,0x74,0xc4,	0x00,0x70,0xb8,	0x00,0x70,0xbc,	0x08,0x60,0x9c,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x2c,0x40,	0x00,0x64,0xac,	0x0c,0x58,0x8c,	0x08,0x5c,0x94,	0x00,0x74,0xc0,	0x00,0x70,0xb8,	0x00,0x74,0xc0,	0x08,0x5c,0x98,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x30,0x4c,	0x00,0x68,0xac,	0x00,0x74,0xc0,	0x00,0x74,0xc4,	0x14,0x40,0x60,	0x08,0x60,0xa0,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x74,0xc0,	0x04,0x64,0xa8,	0x18,0x28,0x3c,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x2c,0x3c,	0x00,0x68,0xac,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xbc,	0x08,0x5c,0x98,	0x18,0x38,0x54,	0x00,0x74,0xc4,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x74,0xc0,	0x08,0x5c,0x9c,	0x18,0x2c,0x3c,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x30,0x4c,	0x00,0x68,0xac,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc0,	0x10,0x40,0x64,	0x10,0x48,0x6c,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc4,	0x08,0x64,0xa4,	0x18,0x2c,0x40,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x2c,0x3c,	0x04,0x64,0xa8,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xbc,	0x04,0x6c,0xb4,	0x1c,0x24,0x34,	0x08,0x5c,0x94,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc0,	0x08,0x5c,0x98,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x30,0x48,	0x00,0x68,0xac,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc4,	0x10,0x4c,0x74,	0x1c,0x28,0x34,	0x00,0x70,0xb8,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc4,	0x08,0x64,0xa8,	0x18,0x2c,0x40,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x28,0x3c,	0x04,0x64,0xa8,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xbc,	0x04,0x64,0xa8,	0x18,0x28,0x38,	0x10,0x48,0x6c,	0x00,0x74,0xc4,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc0,	0x08,0x5c,0x9c,	0x18,0x28,0x34,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x30,0x48,	0x00,0x68,0xb0,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc0,	0x10,0x4c,0x74,	0x18,0x24,0x2c,	0x08,0x5c,0x94,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc0,	0x08,0x64,0xa8,	0x18,0x2c,0x40,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x2c,0x40,	0x04,0x64,0xa4,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xbc,	0x08,0x68,0xa8,	0x18,0x1c,0x28,	0x14,0x38,0x50,	0x00,0x70,0xc0,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xc0,	0x08,0x5c,0x98,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x2c,0x44,	0x00,0x68,0xb0,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc8,	0x14,0x38,0x54,	0x18,0x20,0x28,	0x0c,0x54,0x84,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xc0,	0x08,0x64,0xa0,	0x14,0x2c,0x44,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x28,0x3c,	0x04,0x60,0xa0,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xc0,	0x0c,0x54,0x84,	0x18,0x20,0x2c,	0x14,0x34,0x4c,	0x04,0x6c,0xb4,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xc0,	0x08,0x5c,0x9c,	0x18,0x24,0x30,	0x18,0x28,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x2c,0x40,	0x00,0x68,0xb0,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xbc,	0x04,0x68,0xac,	0x14,0x30,0x48,	0x18,0x20,0x2c,	0x10,0x50,0x7c,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc4,	0x08,0x64,0xa4,	0x18,0x2c,0x3c,	0x18,0x28,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x2c,0x40,	0x04,0x60,0xa0,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xc0,	0x00,0x74,0xc4,	0x00,0x70,0xc0,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xbc,	0x14,0x3c,0x5c,	0x18,0x24,0x30,	0x18,0x2c,0x40,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xc0,	0x08,0x5c,0x9c,	0x18,0x24,0x30,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x2c,0x40,	0x00,0x68,0xac,	0x00,0x74,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x6c,0xb8,	0x14,0x48,0x70,	0x10,0x44,0x6c,	0x0c,0x54,0x84,	0x08,0x60,0x9c,	0x04,0x68,0xb0,	0x00,0x70,0xb8,	0x00,0x74,0xc0,	0x00,0x70,0xc0,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xc0,	0x0c,0x54,0x84,	0x18,0x24,0x34,	0x18,0x20,0x2c,	0x0c,0x54,0x88,	0x00,0x74,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc0,	0x08,0x60,0xa0,	0x18,0x2c,0x40,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x24,0x34,	0x14,0x2c,0x40,	0x04,0x5c,0x9c,	0x00,0x70,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xbc,	0x08,0x60,0xa0,	0x18,0x24,0x30,	0x18,0x24,0x30,	0x18,0x28,0x3c,	0x18,0x30,0x48,	0x14,0x38,0x58,	0x10,0x48,0x74,	0x0c,0x54,0x88,	0x08,0x64,0xa4,	0x04,0x70,0xbc,	0x00,0x74,0xc8,	0x00,0x74,0xc4,	0x00,0x70,0xc0,	0x00,0x70,0xbc,	0x00,0x70,0xc0,	0x08,0x68,0xa8,	0x18,0x24,0x34,	0x18,0x24,0x34,	0x14,0x38,0x54,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xc0,	0x08,0x5c,0x98,	0x18,0x24,0x30,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x24,0x34,	0x14,0x2c,0x40,	0x00,0x68,0xac,	0x00,0x74,0xc0,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc4,	0x0c,0x54,0x84,	0x18,0x24,0x30,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x24,0x30,	0x18,0x24,0x30,	0x18,0x24,0x2c,	0x18,0x24,0x34,	0x18,0x30,0x44,	0x14,0x44,0x64,	0x0c,0x54,0x88,	0x08,0x5c,0x9c,	0x04,0x68,0xa8,	0x04,0x74,0xc0,	0x18,0x34,0x4c,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x08,0x5c,0x9c,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x74,0xc4,	0x08,0x60,0x9c,	0x18,0x2c,0x3c,	0x18,0x28,0x34,	0x18,0x28,0x38,	
	0x14,0x2c,0x44,	0x04,0x64,0xa8,	0x00,0x74,0xc8,	0x00,0x70,0xc0,	0x00,0x70,0xc0,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x14,0x38,0x54,	0x18,0x24,0x30,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x30,0x44,	0x14,0x38,0x54,	0x14,0x2c,0x40,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x10,0x50,0x7c,	0x00,0x78,0xcc,	0x00,0x74,0xc4,	0x00,0x74,0xc0,	0x00,0x70,0xc0,	0x00,0x70,0xbc,	0x00,0x70,0xbc,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xb8,	0x00,0x70,0xc0,	0x08,0x60,0x9c,	0x18,0x20,0x2c,	0x18,0x28,0x38,	
	0x18,0x34,0x4c,	0x14,0x48,0x70,	0x10,0x50,0x7c,	0x0c,0x54,0x84,	0x0c,0x58,0x8c,	0x08,0x5c,0x98,	0x08,0x60,0xa4,	0x04,0x64,0xa8,	0x04,0x68,0xac,	0x00,0x6c,0xb4,	0x00,0x74,0xc0,	0x04,0x70,0xb8,	0x14,0x30,0x48,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x18,0x24,0x30,	0x18,0x2c,0x40,	0x14,0x3c,0x58,	0x10,0x50,0x7c,	0x08,0x5c,0x94,	0x04,0x64,0xa4,	0x00,0x70,0xb8,	0x00,0x70,0xc0,	0x00,0x74,0xc0,	0x00,0x70,0xc0,	0x00,0x70,0xbc,	0x00,0x74,0xc4,	0x08,0x60,0x9c,	0x18,0x28,0x3c,	
	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x24,0x30,	0x18,0x24,0x30,	0x18,0x24,0x34,	0x18,0x28,0x38,	0x18,0x2c,0x3c,	0x14,0x2c,0x40,	0x18,0x30,0x48,	0x14,0x38,0x50,	0x14,0x38,0x58,	0x14,0x40,0x5c,	0x18,0x30,0x44,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x24,0x30,	0x18,0x28,0x34,	0x18,0x2c,0x40,	0x14,0x38,0x54,	0x10,0x40,0x64,	0x0c,0x4c,0x78,	0x0c,0x5c,0x98,	0x04,0x6c,0xb4,	0x00,0x74,0xc0,	0x00,0x78,0xcc,	0x10,0x40,0x60,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x24,0x34,	0x18,0x24,0x34,	0x18,0x24,0x34,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x24,0x38,	0x10,0x20,0x34,	0x10,0x20,0x34,	0x10,0x20,0x34,	0x10,0x20,0x34,	0x10,0x20,0x34,	0x10,0x24,0x34,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x10,0x20,0x34,	0x10,0x20,0x34,	0x10,0x20,0x34,	0x10,0x20,0x30,	0x10,0x20,0x30,	0x10,0x1c,0x2c,	0x10,0x1c,0x2c,	0x10,0x1c,0x28,	0x14,0x20,0x2c,	0x10,0x28,0x38,	0x10,0x38,0x5c,	0x14,0x3c,0x58,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x24,0x38,	0x34,0x44,0x50,	0x54,0x60,0x68,	0x50,0x58,0x64,	0x50,0x58,0x64,	0x50,0x58,0x64,	0x50,0x58,0x64,	0x44,0x50,0x58,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x24,0x34,0x44,	0x54,0x5c,0x68,	0x50,0x5c,0x64,	0x50,0x5c,0x64,	0x50,0x5c,0x64,	0x50,0x5c,0x64,	0x50,0x5c,0x64,	0x4c,0x58,0x64,	0x48,0x54,0x60,	0x44,0x50,0x5c,	0x44,0x50,0x58,	0x48,0x54,0x5c,	0x28,0x34,0x40,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x20,0x30,0x40,	0x88,0x8c,0x8c,	0xa0,0xa0,0xa0,	0x9c,0x9c,0xa0,	0x9c,0x9c,0xa0,	0xa0,0xa0,0xa0,	0x88,0x8c,0x90,	0x14,0x24,0x38,	0x14,0x28,0x38,	0x14,0x24,0x38,	0x2c,0x3c,0x48,	0xc0,0xbc,0xbc,	0xbc,0xbc,0xbc,	0xbc,0xbc,0xbc,	0xbc,0xbc,0xbc,	0xbc,0xbc,0xbc,	0xbc,0xbc,0xbc,	0xbc,0xbc,0xbc,	0xbc,0xbc,0xbc,	0xbc,0xbc,0xbc,	0xc0,0xc0,0xc0,	0xb8,0xb8,0xb8,	0x30,0x40,0x4c,	
	0x18,0x28,0x38,	0x14,0x28,0x38,	0x10,0x24,0x34,	0x10,0x24,0x34,	0x14,0x24,0x38,	0x14,0x24,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x10,0x24,0x34,	0x34,0x40,0x50,	0xa4,0xa4,0xa4,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x98,0x98,0x9c,	0x80,0x84,0x88,	0x14,0x24,0x38,	0x14,0x28,0x38,	0x14,0x24,0x38,	0x20,0x34,0x44,	0xac,0xac,0xb0,	0xb4,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb4,0xb4,0xb4,	0xbc,0xbc,0xbc,	0x4c,0x58,0x64,	0x10,0x24,0x34,	
	0x14,0x28,0x38,	0x1c,0x2c,0x3c,	0x44,0x54,0x5c,	0x34,0x44,0x50,	0x2c,0x3c,0x4c,	0x28,0x38,0x48,	0x20,0x30,0x40,	0x18,0x28,0x3c,	0x14,0x28,0x38,	0x14,0x24,0x38,	0x10,0x24,0x34,	0x10,0x20,0x34,	0x10,0x20,0x34,	0x10,0x24,0x34,	0x10,0x24,0x34,	0x14,0x24,0x38,	0x14,0x24,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x08,0x1c,0x30,	0x5c,0x64,0x6c,	0x9c,0x9c,0x9c,	0x94,0x98,0x98,	0x98,0x98,0x9c,	0x80,0x84,0x88,	0x10,0x24,0x34,	0x14,0x28,0x38,	0x14,0x24,0x38,	0x1c,0x2c,0x40,	0xa0,0xa0,0xa4,	0xb4,0xb4,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb4,0xb4,0xb4,	0xb4,0xb4,0xb4,	0x4c,0x54,0x64,	0x08,0x1c,0x2c,	0x14,0x28,0x38,	
	0x14,0x28,0x38,	0x14,0x24,0x38,	0x5c,0x64,0x6c,	0x9c,0x9c,0x9c,	0x94,0x94,0x98,	0x8c,0x90,0x94,	0x84,0x88,0x8c,	0x7c,0x80,0x84,	0x78,0x7c,0x80,	0x6c,0x74,0x78,	0x5c,0x64,0x6c,	0x54,0x5c,0x68,	0x50,0x58,0x64,	0x40,0x4c,0x58,	0x30,0x40,0x4c,	0x28,0x3c,0x48,	0x24,0x34,0x44,	0x10,0x24,0x38,	0x08,0x1c,0x30,	0x08,0x1c,0x30,	0x08,0x1c,0x2c,	0x14,0x24,0x38,	0x74,0x78,0x80,	0x98,0x98,0x9c,	0x98,0x9c,0x9c,	0x78,0x7c,0x84,	0x10,0x24,0x34,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x1c,0x2c,0x3c,	0x98,0x9c,0xa0,	0xb4,0xb4,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb4,0xb4,0xb4,	0xc0,0xbc,0xc0,	0x4c,0x58,0x64,	0x10,0x20,0x34,	0x14,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x14,0x28,0x38,	0x0c,0x20,0x34,	0x3c,0x4c,0x54,	0x98,0x98,0x98,	0x9c,0x9c,0x9c,	0x98,0x98,0x9c,	0x98,0x98,0x9c,	0x98,0x9c,0x9c,	0x9c,0x9c,0x9c,	0x9c,0x9c,0x9c,	0x9c,0x9c,0xa0,	0x9c,0x9c,0xa0,	0xa0,0xa0,0xa0,	0xa0,0xa0,0xa0,	0xa0,0xa0,0xa0,	0xa0,0xa0,0xa0,	0x9c,0x9c,0x9c,	0x98,0x98,0x9c,	0x90,0x90,0x94,	0x84,0x88,0x8c,	0x64,0x6c,0x74,	0x70,0x74,0x7c,	0x98,0x98,0x9c,	0x9c,0x9c,0x9c,	0x58,0x60,0x68,	0x10,0x20,0x34,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x18,0x2c,0x3c,	0x94,0x98,0x9c,	0xb4,0xb4,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb4,0xb4,0xb4,	0xb0,0xb0,0xb0,	0x4c,0x58,0x64,	0x08,0x1c,0x2c,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x0c,0x20,0x30,	0x38,0x48,0x54,	0x90,0x94,0x94,	0x9c,0x9c,0xa0,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x98,0x98,0x98,	0x98,0x98,0x98,	0x98,0x98,0x9c,	0x9c,0x9c,0x9c,	0x98,0x98,0x9c,	0x94,0x98,0x98,	0xa0,0xa0,0xa0,	0x40,0x4c,0x54,	0x10,0x24,0x34,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x1c,0x2c,0x3c,	0x98,0x98,0x9c,	0xb4,0xb4,0xb4,	0xb0,0xb0,0xb4,	0xb0,0xb0,0xb4,	0xb4,0xb4,0xb4,	0xb8,0xb8,0xb8,	0x54,0x60,0x68,	0x0c,0x20,0x34,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x10,0x20,0x34,	0x10,0x24,0x38,	0x6c,0x74,0x78,	0x98,0x98,0x9c,	0x98,0x98,0x9c,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x98,0x98,0x98,	0x90,0x90,0x94,	0x1c,0x2c,0x3c,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x14,0x24,0x38,	0x20,0x30,0x40,	0xa4,0xa4,0xa8,	0xb4,0xb4,0xb4,	0xb0,0xb0,0xb4,	0xb4,0xb4,0xb4,	0xb0,0xb0,0xb4,	0x4c,0x58,0x64,	0x08,0x18,0x2c,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x24,0x38,	0x14,0x28,0x38,	0x44,0x50,0x5c,	0x94,0x94,0x94,	0xa0,0xa0,0xa0,	0x98,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0xa0,0xa0,0xa0,	0x60,0x68,0x70,	0x10,0x20,0x34,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x14,0x24,0x38,	0x20,0x30,0x44,	0xac,0xb0,0xb0,	0xb0,0xb0,0xb4,	0xb4,0xb4,0xb4,	0xbc,0xbc,0xbc,	0x54,0x5c,0x68,	0x0c,0x20,0x34,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x0c,0x20,0x34,	0x18,0x2c,0x3c,	0x54,0x5c,0x68,	0x8c,0x90,0x94,	0x9c,0x9c,0x9c,	0x98,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x94,0x98,0x98,	0x9c,0x9c,0x9c,	0x7c,0x80,0x84,	0x1c,0x2c,0x3c,	0x14,0x24,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x10,0x24,0x34,	0x34,0x44,0x50,	0xb8,0xb8,0xb8,	0xb4,0xb4,0xb4,	0xb0,0xb0,0xb4,	0x50,0x58,0x64,	0x08,0x18,0x2c,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x24,0x38,	0x10,0x20,0x34,	0x28,0x38,0x48,	0x5c,0x64,0x6c,	0x98,0x98,0x9c,	0xa0,0xa0,0xa0,	0x9c,0x9c,0x9c,	0x98,0x98,0x9c,	0x98,0x98,0x9c,	0x98,0x98,0x98,	0x98,0x98,0x98,	0x98,0x98,0x9c,	0x98,0x98,0x9c,	0xa0,0xa0,0xa0,	0x90,0x90,0x94,	0x24,0x34,0x44,	0x10,0x24,0x34,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x0c,0x20,0x34,	0x50,0x5c,0x68,	0xbc,0xbc,0xbc,	0xb8,0xb8,0xb8,	0x54,0x60,0x6c,	0x10,0x24,0x34,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x14,0x24,0x38,	0x0c,0x20,0x34,	0x08,0x1c,0x30,	0x3c,0x48,0x54,	0x68,0x70,0x78,	0x80,0x84,0x88,	0x88,0x88,0x8c,	0x94,0x94,0x94,	0x94,0x94,0x98,	0x88,0x8c,0x90,	0x80,0x84,0x88,	0x4c,0x58,0x60,	0x10,0x24,0x34,	0x10,0x24,0x34,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x08,0x1c,0x30,	0x94,0x98,0x9c,	0xb8,0xb8,0xb8,	0x50,0x58,0x64,	0x08,0x18,0x2c,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x10,0x24,0x34,	0x0c,0x20,0x34,	0x18,0x2c,0x3c,	0x24,0x34,0x44,	0x2c,0x3c,0x4c,	0x30,0x3c,0x4c,	0x24,0x34,0x44,	0x18,0x28,0x38,	0x10,0x20,0x34,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x18,0x2c,0x38,	0xb0,0xb0,0xb4,	0x5c,0x64,0x70,	0x0c,0x20,0x30,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x14,0x24,0x38,	0x14,0x24,0x38,	0x14,0x24,0x38,	0x14,0x24,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x10,0x24,0x34,	0x58,0x60,0x6c,	0x50,0x58,0x64,	0x08,0x1c,0x2c,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x14,0x28,0x38,	0x2c,0x3c,0x4c,	0x14,0x24,0x38,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x14,0x28,0x38,	0x14,0x24,0x38,	0x14,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	0x18,0x28,0x38,	
	#endif
	}
};