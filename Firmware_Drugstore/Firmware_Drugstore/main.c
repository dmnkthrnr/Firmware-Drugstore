/*
 * Firmware_Drugstore.c
 *
 * Created: 21.03.2017 15:26:06
 * Author : thurnerd
 */ 


#include "sam.h"

#include "Includes/i2c.h"
#include "Includes/main.h"
#include "Includes/settings.h"
#include "Includes/AB1805.h"
#include "Includes/uart.h"

void enable_interrupts(void);

int main(void)
{
	/* Initialize the SAM system */
	SystemInit();
	//Das ist ein GithubTest
	enable_interrupts();
	
	InitPorts();
	InitClocks();
	
	Init10msTimer();
	
	InitI2C();
	InitUART();
	
	InitAB1805();
	//Set DateTime
	set_datetime(0x17,0x03,0x22,0x03,0x15,0x07,0x00);
	
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
}
