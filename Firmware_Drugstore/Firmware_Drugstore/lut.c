/*
 * lut.c
 *
 * Created: 29.03.2017 09:36:55
 *  Author: thurnerd
 */ 

#include "Includes/main.h"
#include "Includes/lut.h"

uint8_t pic[]=
{/*--  ????????D:\????\????\ERC12864-12 Series.bmp  --*/
	/*--  ??x??=128x64  --*/
	0xFF,0x01,0x01,0xF9,0x49,0x49,0x49,0x49,0x01,0xC1,0xB1,0x89,0xB1,0xC1,0x01,0x31,
	0x49,0x49,0x91,0x01,0x09,0x09,0xF9,0x09,0x09,0x01,0xF9,0x49,0x49,0xC9,0x31,0x01,
	0x01,0xF9,0x01,0x01,0x31,0x49,0x49,0x91,0x01,0x01,0xF9,0x01,0x01,0xF9,0x31,0x41,
	0x81,0xF9,0x01,0x01,0xF1,0x09,0x09,0x49,0xD1,0x01,0x01,0x01,0x01,0x09,0x09,0xF9,
	0x09,0x09,0x01,0xF9,0x49,0x49,0x49,0x49,0x01,0xF1,0x09,0x09,0x09,0x11,0x01,0x01,
	0xF9,0x41,0x41,0x41,0xF9,0x01,0x01,0x01,0x01,0x01,0xF1,0x09,0x09,0x09,0x11,0x01,
	0x01,0xF1,0x09,0x09,0x09,0xF1,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xF9,0x01,
	0x01,0x01,0x09,0x09,0xF9,0x09,0x09,0x01,0xF9,0x09,0x09,0x09,0xF1,0x01,0x01,0xFF,
	0xFF,0x00,0x00,0x03,0x02,0x02,0x02,0x02,0x02,0x01,0x00,0x00,0x00,0x01,0x02,0x01,
	0x02,0x02,0x01,0x00,0x80,0x80,0xF3,0x80,0x80,0x00,0xE3,0x20,0x20,0x20,0xE3,0x00,
	0x00,0x03,0x00,0xE0,0x21,0x22,0x22,0x21,0x20,0x20,0xF3,0x20,0x00,0x03,0x00,0x40,
	0x41,0x43,0xC0,0x70,0x41,0x42,0x42,0x42,0x61,0x40,0x00,0x40,0x40,0x40,0x40,0x43,
	0xD0,0x60,0x40,0x43,0x42,0x42,0x42,0x02,0x00,0x21,0x22,0xE2,0x12,0x01,0x40,0x80,
	0x03,0xF0,0x00,0x00,0x03,0x80,0x80,0xF2,0x80,0x00,0x81,0x82,0x82,0xF2,0x81,0x80,
	0x80,0x01,0x02,0x02,0x02,0x01,0x00,0x00,0x02,0x00,0x00,0x06,0x00,0x00,0x03,0x02,
	0x02,0x02,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x01,0x00,0x00,0xFF,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x80,0x60,0x1F,0x00,0x7F,0x80,0x9F,0x92,0x92,0x92,0x9F,0xE0,
	0x00,0x00,0x00,0xFF,0x42,0x42,0x42,0x42,0x42,0x42,0xFF,0x00,0x00,0x00,0x00,0x40,
	0x26,0x15,0x0C,0x84,0xFF,0x04,0x0C,0x14,0x24,0x40,0x00,0x00,0x80,0x40,0x20,0x18,
	0x07,0x42,0x82,0x42,0x3E,0x00,0x00,0x00,0x11,0x09,0x05,0xFF,0x05,0x19,0x12,0x14,
	0x10,0xFF,0x08,0x08,0x00,0x08,0x84,0xFF,0x02,0x80,0x80,0x8E,0x52,0x23,0x52,0x8E,
	0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,0x44,0x44,
	0x44,0x44,0x00,0x00,0xFC,0xFC,0x84,0x84,0x84,0xFC,0x78,0x00,0x00,0xF0,0xF8,0x0C,
	0x04,0x04,0x04,0x0C,0x08,0x00,0x30,0x18,0xFC,0xFC,0x00,0x00,0x08,0x0C,0x84,0xC4,
	0xFC,0x38,0x00,0xB8,0xFC,0x44,0x44,0xFC,0xB8,0x00,0xF0,0xF8,0x44,0x44,0xCC,0x88,
	0x00,0x00,0xC0,0x30,0xFC,0xFC,0x00,0x00,0x80,0x80,0x80,0x00,0x30,0x18,0xFC,0xFC,
	0x00,0x00,0x08,0x0C,0x84,0xC4,0xFC,0x38,0x00,0x00,0x60,0x90,0x90,0x10,0x10,0x20,
	0x00,0x80,0x40,0x40,0x40,0x80,0x00,0xC0,0x80,0x40,0x00,0xD0,0x00,0x80,0x40,0x40,
	0x40,0x80,0x00,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x08,0x08,
	0x08,0x08,0x00,0x00,0x0F,0x0F,0x00,0x00,0x01,0x07,0x0E,0x08,0x00,0x03,0x07,0x0C,
	0x08,0x08,0x08,0x0C,0x04,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x0C,0x0E,0x0B,0x09,
	0x08,0x08,0x00,0x07,0x0F,0x08,0x08,0x0F,0x07,0x00,0x07,0x0F,0x08,0x08,0x0F,0x07,
	0x00,0x03,0x02,0x02,0x0F,0x0F,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,
	0x00,0x00,0x0C,0x0E,0x0B,0x09,0x08,0x08,0x00,0x00,0x04,0x08,0x08,0x09,0x09,0x06,
	0x00,0x07,0x09,0x09,0x09,0x05,0x00,0x0F,0x00,0x00,0x00,0x0F,0x00,0x07,0x09,0x09,
	0x09,0x05,0x00,0x04,0x09,0x09,0x0A,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
	0xFF,0x00,0x00,0x80,0xC0,0x00,0x00,0x00,0x80,0x40,0x40,0x40,0x80,0x00,0x80,0x40,
	0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x40,0x40,0x80,0x00,
	0x00,0x00,0x80,0xC0,0x00,0x00,0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x80,0x00,0x40,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x40,0x40,0x40,0x80,0x00,0xC0,0x40,0x40,0x40,
	0x80,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x40,0x40,0x80,0x00,0x00,
	0xC0,0x40,0x40,0x40,0x00,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x80,0xC0,0x00,0xFF,
	0xFF,0x80,0x81,0x80,0xBF,0x80,0x80,0x80,0xA0,0xB0,0xA8,0xA4,0xA3,0x80,0x9D,0xA2,
	0xA2,0xA2,0x9D,0x80,0xA1,0x92,0x8C,0x92,0xA1,0x80,0x9F,0xA2,0xA2,0xA2,0x9C,0x80,
	0x8C,0x8B,0x88,0xBF,0x88,0x80,0x80,0x80,0x80,0xBF,0x84,0x84,0x84,0x83,0x80,0xBF,
	0x80,0xA1,0x92,0x8C,0x92,0xA1,0x80,0x9E,0xA5,0xA5,0xA5,0x96,0x80,0xBF,0x80,0x92,
	0xA5,0xA5,0xA9,0x92,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,0x80,0x91,0xA2,0xA2,0xA4,0xA4,0x98,0x80,0xBF,0x84,0x84,0x84,
	0x83,0x80,0xBF,0xA0,0xA0,0xA0,0xA0,0x80,0x8F,0x90,0xA0,0xA0,0xA0,0x90,0x80,0x93,
	0xA2,0xA2,0xA2,0x9C,0x80,0x9F,0xA0,0xA0,0xA0,0x9F,0x80,0x81,0x80,0xBF,0x80,0xFF
};