/*
 * settings.c
 *
 * Created: 16.03.2017 14:23:41
 *  Author: thurnerd
 */ 

#include "Includes/main.h"
#include "Includes/settings.h"

#include "sam.h"

void InitPorts()
{
	//Init I2C
	//PA08 SERCOM0/PAD[0] Multiplex C SDA
	//PA09 SERCOM0/PAD[1] Multiplex C SCL
	PORT->Group[0].PINCFG[8].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[9].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[4].reg = PORT_PMUX_PMUXE(0x2) | PORT_PMUX_PMUXO(0x2);
	
	//Init Uart Virtual COMPORT
	//PA22 SERCOM3/PAD[0] Multiplex C Tx
	//PA23 SERCOM3/PAD[1] Multiplex C Rx
	PORT->Group[0].PINCFG[22].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[23].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[11].reg = PORT_PMUX_PMUXE(0x2) | PORT_PMUX_PMUXO(0x2);
	
	//Pin PB14 GCLK_IO[0]
	PORT->Group[1].PINCFG[14].bit.PMUXEN = 1;
	PORT->Group[1].PMUX[14/2].reg = PORT_PMUX_PMUXE(0x7);
}

void InitClocks()
{	
	SYSCTRL->OSC8M.bit.PRESC = 0x0;
	
	GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(0x00) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_OE | GCLK_GENCTRL_SRC_OSC8M;
	//Clock to SERCOM0 I2C
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_SERCOM0_CORE;
	//Clock to SERCOM3 UART
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_SERCOM3_CORE;
	
	while (GCLK->STATUS.bit.SYNCBUSY){}
}

// ---------------------------------------------------------------------------
//  Value2String
// ---------------------------------------------------------------------------
void Value2String( int16_t Value, uint8_t *DestPtr, uint8_t Stellen)
{
	uint8_t ValueIsZero=1;

	if (Value<0)
	{
		*DestPtr = '-';
		Value *= -1;
		Stellen--;
		DestPtr++;
	}
	
	if (Stellen==4)
	{
		if (Value>9999)
		{
			Value = 9999;
		}
		*DestPtr = Value/1000;
		if (*DestPtr)
		{
			Value -= (uint16_t)*DestPtr * 1000;
			ValueIsZero = 0;
		}
		if (ValueIsZero)
		{
			*DestPtr = ' ';
		}
		else
		{
			*DestPtr += '0';
		}
		Stellen--;
		DestPtr++;
	}

	
	if (Stellen==3)
	{
		if (Value>999)
		{
			Value = 999;
		}
		*DestPtr = Value/100;
		if (*DestPtr)
		{
			Value -= (uint16_t)*DestPtr * 100;
			ValueIsZero = 0;
		}
		if (ValueIsZero)
		{
			*DestPtr = ' ';
		}
		else
		{
			*DestPtr += '0';
		}
		DestPtr++;
		Stellen--;
	}
	
	
	if (Stellen==2)
	{
		if (Value>99)
		{
			Value = 99;
		}
		*DestPtr = Value/10;
		if (*DestPtr)
		{
			Value -= (uint16_t)*DestPtr * 10;
			ValueIsZero = 0;
		}
		if (ValueIsZero)
		{
			*DestPtr = ' ';
		}
		else
		{
			*DestPtr += '0';
		}
		DestPtr++;
		Stellen--;
	}
	
	if (Stellen==1)
	{
		if (Value>9)
		{
			Value = 9;
		}
		*DestPtr = Value+'0';
	}
}