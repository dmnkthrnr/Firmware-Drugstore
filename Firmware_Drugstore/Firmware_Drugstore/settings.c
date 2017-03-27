/*
 * settings.c
 *
 * Created: 16.03.2017 14:23:41
 *  Author: thurnerd
 */ 

#include "Includes/main.h"

#include "Includes/i2c.h"
#include "Includes/settings.h"
#include "Includes/AB1805.h"
#include "Includes/uart.h"
#include "Includes/stepper_motor.h"
#include "Includes/time.h"
#include "Includes/ui.h"
#include "Includes/spi.h"

void InitPorts()
{
	//Init I2C
	//PA08 SERCOM0/PAD[0] Multiplex C SDA
	//PA09 SERCOM0/PAD[1] Multiplex C SCL
	PORT->Group[0].PINCFG[8].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[9].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[4].reg = PORT_PMUX_PMUXE(0x2) | PORT_PMUX_PMUXO(0x2);
	
	//Init Uart Virtual COM-PORT
	//PA22 SERCOM3/PAD[0] Multiplex C Tx
	//PA23 SERCOM3/PAD[1] Multiplex C Rx
	PORT->Group[0].PINCFG[22].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[23].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[11].reg = PORT_PMUX_PMUXE(0x2) | PORT_PMUX_PMUXO(0x2);

 	//Init SPI
 	//PB17 SERCOM5/PAD[1] GPIO SS
 	PORT->Group[1].DIR.reg |= PORT_PB17;
 	//PB16 SERCOM5/PAD[0] Multiplex C MISO
 	PORT->Group[1].PINCFG[16].bit.PMUXEN = 1;
 	PORT->Group[1].PMUX[16/2].reg = PORT_PMUX_PMUXE(0x2);
 	//PB22 SERCOM5/PAD[2] Multiplex D MOSI
 	PORT->Group[1].PINCFG[22].bit.PMUXEN = 1;
 	PORT->Group[1].PMUX[22/2].reg |= PORT_PMUX_PMUXE(0x3);
 	//PB23 SERCOM5/PAD[3] Multiplex D SCK
 	PORT->Group[1].PINCFG[23].bit.PMUXEN = 1;
 	PORT->Group[1].PMUX[23/2].reg |= PORT_PMUX_PMUXO(0x3);
	
	//Pin PB14 GCLK_IO[0]
	PORT->Group[1].PINCFG[14].bit.PMUXEN = 1;
	PORT->Group[1].PMUX[14/2].reg |= PORT_PMUX_PMUXE(0x7);
	
	//Testpin PA10
	PORT->Group[0].DIR.reg |= PORT_PA10;
	
	//Pin PA15 (SW0 Xplained Board) auf Eingang schalten
	PORT->Group[0].OUTSET.reg |= PORT_PA15;
	PORT->Group[0].PINCFG[15].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[15].bit.INEN = 1;
	PORT->Group[0].PINCFG[15].bit.PULLEN = 1;
	PORT->Group[0].PMUX[15/2].reg |= PORT_PMUX_PMUXO(0x0);
	
	//Pin PA11 auf Eingang schalten
	//PORT->Group[0].OUTSET.reg |= PORT_PA11;
	PORT->Group[0].PINCFG[11].bit.PMUXEN = 1;
	PORT->Group[0].PINCFG[11].bit.INEN = 1;
	PORT->Group[0].PINCFG[11].bit.PULLEN = 1;
	PORT->Group[0].PMUX[11/2].reg |= PORT_PMUX_PMUXO(0x0);
	
	//Init Stepper Motor Ports
	REG_PORT_DIRSET0 = AIN1 | AIN2 | BIN1 | BIN2 | MOTOR_SLEEP; //Set Pins to Output
	REG_PORT_OUTCLR0 = AIN1 | AIN2 | BIN1 | BIN2 | MOTOR_SLEEP; //Set Pins to LOW
}

void InitClocks()
{	
	//Set OSC8M to 8MHz
	SYSCTRL->OSC8M.bit.PRESC = 0x0;
	
	
	//Enable Generic Clock 0 to OSC8M
	GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(0x00) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_OE | GCLK_GENCTRL_SRC_OSC8M;
	//Enable Generic Clock 1 to OSCULP32K
	GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(0x01) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_OSCULP32K;
	
	//Peripheries with OSC8M (GEN GLCK[0])
	//Clock to SERCOM0 I2C
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_SERCOM0_CORE;
	//Clock to SERCOM3 UART
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_SERCOM3_CORE;
	//Clock to SERCOM5 SPI
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_SERCOM5_CORE;
	//Clock to TC3 10msCounter
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC2_TC3;
	
	//Peripheries with OSCULP32K (GEN GLCK[1])
	//Clock to EIC
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK1 | GCLK_CLKCTRL_ID_EIC;
	
	while (GCLK->STATUS.bit.SYNCBUSY){}
}

//-----------------------------------------------------------------------------
// Init External Interrupt Controller
//-----------------------------------------------------------------------------
void InitEIC(void)
{	
	PM->APBAMASK.bit.EIC_ = 1;
	
	EIC->CTRL.bit.SWRST = 1;
	while(EIC->STATUS.bit.SYNCBUSY == 1){}
	
	EIC->WAKEUP.bit.WAKEUPEN11 = 1;
		
	//Pin PA11 ExtInt[11]
	EIC->CONFIG[1].bit.SENSE3 = 0x01;
	EIC->CONFIG[1].bit.FILTEN3 = 0x00;
	
	EIC->CTRL.bit.ENABLE = 1;
	while(EIC->STATUS.bit.SYNCBUSY == 1){}
	
	EIC->INTENSET.bit.EXTINT11 = 1;


}


// ---------------------------------------------------------------------------
//  Power Up: Alles aktivieren nach Sleep
// ---------------------------------------------------------------------------
void PowerUp(void)
{	
	//SPI SERCOM5
	PORT->Group[1].PINCFG[22].bit.PMUXEN = 1;
	PORT->Group[1].PINCFG[23].bit.PMUXEN = 1;
}


// ---------------------------------------------------------------------------
//  Power Down Stromsparen
// ---------------------------------------------------------------------------
void PowerDown(void)
{
	//SPI SERCOM5
	PORT->Group[1].PINCFG[22].bit.PMUXEN = 0;
	PORT->Group[1].PINCFG[23].bit.PMUXEN = 0;
}


// ---------------------------------------------------------------------------
//  Alles Initialisieren
// ---------------------------------------------------------------------------
uint8_t InitAll(void)
{
	InitPorts();
	InitClocks();
	InitEIC();
	
	Init10msTimer();
	UiInit();
	
	InitI2C();
	InitUART();
	InitSPI();
	
	InitAB1805();
	
	return(0);
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

// ---------------------------------------------------------------------------
//  Delay ms
// ---------------------------------------------------------------------------
void Delay_ms(uint16_t Milliseconds)
{
	for(uint32_t i=0; i<=Milliseconds*5; i++){}
}