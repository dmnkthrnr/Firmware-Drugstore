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

void enable_interrupts(void);

int main(void)
{
	/* Initialize the SAM system */
	SystemInit();
	
	enable_interrupts();
	
	State = STM_START;

	/* Replace with your application code */
	while (1)
	{
		//Wait a little bit
		switch (State)
		{
			case STM_START:
				InitAll();
				
				//Set DateTime
				set_datetime(0x17,0x03,0x24,0x04,0x10,0x14,0x35);
					
				set_seconds_alarm(0x40);
				set_minutes_alarm(get_minute());
				set_hour_alarm(get_hour());
				set_date_alarm(get_date());
				set_month_alarm(get_month());
				set_day_alarm(get_day());
				State = STM_IDLE;
				break;
				
			case STM_IDLE:
				TimerAkt();
// 				if (!TimerAkt())
// 					State = STM_SLEEP;
				break;
			case STM_SLEEP:
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
