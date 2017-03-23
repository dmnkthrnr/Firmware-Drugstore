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
	
	InitPorts();
	InitClocks();
	InitEIC();
	
	Init10msTimer();
	
	InitI2C();
	InitUART();
	
	InitAB1805();
	//Set DateTime
	set_datetime(0x17,0x03,0x23,0x04,0x11,0x08,0x45);
	
	set_seconds_alarm(0x50);
	set_minutes_alarm(get_minute());
	set_hour_alarm(get_hour());
	set_date_alarm(get_date());
	set_month_alarm(get_month());
	set_day_alarm(get_day());
	
	
	
	
	
	/* Replace with your application code */
	while (1)
	{
		//Wait a little bit
		for (uint32_t i=0; i<500; i++){}
		TimerAkt();
	}
}

void enable_interrupts()
{
	NVIC_EnableIRQ(SERCOM3_IRQn);
	NVIC_EnableIRQ(TC3_IRQn);
	NVIC_EnableIRQ(EIC_IRQn);
}
