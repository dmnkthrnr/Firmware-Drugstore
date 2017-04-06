/*
 * Firmware_Drugstore.c
 *
 * Created: 21.03.2017 15:26:06
 * Author : thurnerd
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
#include "Includes/display.h"
#include "Includes/lut.h"

void enable_interrupts(void);
void disable_interrupts(void);

int main(void)
{
	/* Initialize the SAM system */
	SystemInit();
	disable_interrupts();
	
	//Alles initialisieren
	InitAll(); 
	
	enable_interrupts();
	
	State = STM_START;

	/* Replace with your application code */
	while (1)
	{
		switch (State)
		{
			case STM_START:
				DisplayState = DISPLAY_IDLE;
				//Init Uhr
				InitAB1805();
				//Set DateTime
				set_datetime(0x17,0x04,0x06,0x00,0x22,0x40,0x45);
					
				set_seconds_alarm(0x40);
				set_minutes_alarm(get_minute());
				set_hour_alarm(get_hour());
				set_date_alarm(get_date());
				set_month_alarm(get_month());
				set_day_alarm(get_day());
				
				//Init Display
				InitDisplay();
				Delay_ms(1000); //ca 2,5ms
				REVERSE_DISPLAY_OFF();
				ENTIRE_DISPLAY_OFF();

				clear_display();
		
				State = STM_IDLE;
				break;
				
			case STM_STARTAFTERSLEEP:
				PowerUp();
				State = STM_IDLE;
				break;
				
			case STM_IDLE:
 				if (!TimerAkt())
 					State = STM_SLEEP;
				break;
				
			case STM_SLEEP:
				PowerDown();
				gotosleep();
				State = STM_STARTAFTERSLEEP;
				break;
		}
	}
}

void enable_interrupts()
{
	NVIC_EnableIRQ(SERCOM3_IRQn);
	NVIC_EnableIRQ(TC3_IRQn);
	NVIC_EnableIRQ(EIC_IRQn);

}

void disable_interrupts()
{
	NVIC_DisableIRQ(SERCOM3_IRQn);
	NVIC_DisableIRQ(TC3_IRQn);
	NVIC_DisableIRQ(EIC_IRQn);
}
