/*
 * ui.c
 *
 * Created: 21.03.2017 16:17:07
 *  Author: thurnerd
 */ 

#include "Includes/main.h"

#include "Includes/ui.h"
#include "Includes/AB1805.h"
#include "Includes/uart.h"


// ---------------------------------------------------------------------------
//  Init Vars of UserInterface
// ---------------------------------------------------------------------------
void UiInit(void)
{
	int i;
	for (i=0;i<TA_ANZ_MAX;i++)
	{
		TaxState[i] = BUTTON_STARTUP;
		TaxCounter[i] = 0;
	}
}

// ---------------------------------------------------------------------------
//  Set State of Buttons because of UpCounter And DownCounter
// ---------------------------------------------------------------------------
void SetCounterState(void)
{
	uint8_t i;
	for (i=0;i<TA_ANZ_MAX;i++)
	{
		switch (TaxCounter[i])
		{
			case -10:
				switch (TaxState[i])
				{
					case BUTTON_SHORT:
					case BUTTON_SHORT_REC:
						TaxState[i] = BUTTON_SHORT_DONE;
						break;
					case BUTTON_1S:
						TaxState[i] = BUTTON_1S_DONE;
						break;
					case BUTTON_2S:
						TaxState[i] = BUTTON_2S_DONE;
						break;
					case BUTTON_3S:
						TaxState[i] = BUTTON_3S_DONE;
						break;
					case BUTTON_4S:
						TaxState[i] = BUTTON_4S_DONE;
						break;
					case BUTTON_5S:
						TaxState[i] = BUTTON_5S_DONE;
						break;
					case BUTTON_8S:
						TaxState[i] = BUTTON_8S_DONE;
						break;

					default:
						TaxState[i] = BUTTON_OFF;
						break;
				}
				break;
			case -20:
				TaxState[i] = BUTTON_OFF;
				break;
			case 5:
				TaxState[i] = BUTTON_SHORT;
				break;
			case 100:
				TaxState[i] = BUTTON_1S;
				uart_write((uint8_t*)&"1SEK",4);
				break;
			case 200:
				TaxState[i] = BUTTON_2S;
				uart_write((uint8_t*)&"2SEK",4);
				break;
			case 300:
				TaxState[i] = BUTTON_3S;
				break;
			case 400:
				TaxState[i] = BUTTON_4S;
				break;
			case 500:
				TaxState[i] = BUTTON_5S;
				break;
		}
	}
}

// ---------------------------------------------------------------------------
//  ActCounter
// ---------------------------------------------------------------------------
void ActCounter(uint8_t OnOff, uint8_t InputNr)
{
	if (OnOff)
	{
		if (TaxCounter[InputNr]<-10)
			TaxCounter[InputNr] = 1;
		else if (TaxCounter[InputNr]<30000)
			TaxCounter[InputNr]++;
		
	}
	else
	{
		if (TaxCounter[InputNr]>0)
			TaxCounter[InputNr] = -1;
		else if (TaxCounter[InputNr]>-30000)
			TaxCounter[InputNr]--;
	}
}

// ---------------------------------------------------------------------------
//  Tasten werden gelesen
// ---------------------------------------------------------------------------
inline void UpdateTastenCounter(void)
{
	ActCounter(TASTER_IF, TA_SW0_NR);
	
	SetCounterState();
}

uint8_t ReadTasten()
{
	UpdateTastenCounter();
	
	// SW0 kurz gedrückt und losgelassen
	if (TaxState[TA_SW0_NR] == BUTTON_SHORT_DONE)
	{
		TaxState[TA_SW0_NR] = BUTTON_OFF;
		get_date_string();
		uart_write(DateString,17);
		return (1);
	}
	
	if (TaxState[TA_SW0_NR] == BUTTON_2S_DONE)
	{
		TaxState[TA_SW0_NR] = BUTTON_OFF;
		uart_write((uint8_t*)&"SLEEP",5);
		return (GOTOSLEEP);
	}
	
	return (1);

}

// ---------------------------------------------------------------------------
//  Go to sleep
// ---------------------------------------------------------------------------
void gotosleep()
{
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__DSB();
	__WFI();
}

// ---------------------------------------------------------------------------
//  Wake Up via PA11 from Sleep
// ---------------------------------------------------------------------------
void EIC_Handler()
{
	if (EIC->INTFLAG.bit.EXTINT11 == 1)
	{
		EIC->INTFLAG.bit.EXTINT11 = 1; //Interrupt Flag löschen
		while(EIC->INTFLAG.bit.EXTINT11 == 1){}
		write_rtc_register(STATUS_REGISTER, 0x00);
		get_date_string();
		uart_write(DateString,17);
	}
}