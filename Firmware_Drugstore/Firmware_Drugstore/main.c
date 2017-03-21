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
	
	enable_interrupts();
	
	InitPorts();
	InitClocks();
	
	InitI2C();
	InitUART();
	
	InitAB1805();
	//Set DateTime
	set_datetime(0x17,0x03,0x21,0x02,0x13,0x21,0x40);
	
	/* Replace with your application code */
	while (1)
	{
		//Wait 1s
		for(uint32_t i=0;i<2000000;i++){}
		get_date_string();
		uart_write(&DateString,17);
	}
}

void enable_interrupts()
{
	NVIC_EnableIRQ(SERCOM3_IRQn);
}
