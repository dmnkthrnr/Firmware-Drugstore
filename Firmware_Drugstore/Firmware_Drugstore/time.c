/*
 * time.c
 *
 * Created: 21.03.2017 16:13:36
 *  Author: thurnerd
 */ 

#include "Includes/main.h"

#include "Includes/time.h"
#include "Includes/i2c.h"
#include "Includes/ui.h"
#include "Includes/uart.h"
#include "Includes/AB1805.h"
#include "Includes/stepper_motor.h"



//-----------------------------------------------------------------------------
// Init 1msTimer
//-----------------------------------------------------------------------------
void Init10msTimer(void)
{
	PM->APBCMASK.bit.TC3_ = 1;
	_10ms = 0;
	Sekunde = 0;
	
	TC3->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT16;
	TC3->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV2;
	
	TC3->COUNT16.INTENSET.bit.MC0 = 1;
	//alle 10ms Interrupt
	TC3->COUNT16.CC[0].bit.CC = 40000;
	
	TC3->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
	while ( TC3->COUNT16.STATUS.bit.SYNCBUSY == 1 ){}
}

// ---------------------------------------------------------------------------
//  Zeitlichen Ablauf regeln
//  Rückgabe 0, wenn im falschen Modus
// ---------------------------------------------------------------------------
uint8_t TimerAkt(void)
{
	static uint16_t Old10ms=0;
	static uint8_t buttonstate = 0;
	static uint16_t gotosleep = 0;
	
	
	//Wenn neue ms
	if (Old10ms != _10ms)
	{
		Old10ms = _10ms;
		buttonstate = ReadTasten();
		
		if (buttonstate == GOTOSLEEP)
		{
			gotosleep = 1;	
		}
		
				
		switch (Old10ms)
		{
			case 10:
				if (gotosleep)
				{
 					gotosleep = 0;
					return (1);
				}
				break;						
			
			default:
				break;
		}
	}
	return 0;
}



void TC3_Handler(void)
{
	if (TC3->COUNT16.INTFLAG.bit.MC0 == 1)
	{
		TC3->COUNT16.INTFLAG.bit.MC0 = 1;
		TC3->COUNT16.COUNT.bit.COUNT = 0;
		//PORT->Group[0].OUTTGL.reg |= PORT_PA10;
		_10ms++;
		if(_10ms == 100)
		{
			_10ms = 0;
			Sekunde++;
		}
	}
}
	