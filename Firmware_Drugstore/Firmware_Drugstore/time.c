/*
 * time.c
 *
 * Created: 21.03.2017 16:13:36
 *  Author: thurnerd
 */ 

#include "sam.h"

#include "Includes/main.h"
#include "Includes/time.h"
#include "Includes/ui.h"

//-----------------------------------------------------------------------------
// Init 1msTimer
//-----------------------------------------------------------------------------
void Init1msTimer(void)
{

}

// ---------------------------------------------------------------------------
//  Zeitlichen Ablauf regeln
//  Rückgabe 0, wenn im falschen Modus
// ---------------------------------------------------------------------------
uint8_t TimerAkt(void)
{
	static uint16_t Old10ms=0;
	
	//Wenn neue ms
	if (Old10ms != _10ms)
	{
		Old10ms = _10ms;
		
		ReadTasten();
				
		switch (Old10ms)
		{
			case 50:
				break;
				
			
			default:
				break;
		}
	}
	return 0;
}



void TC2_Handler(void)
{

}
	