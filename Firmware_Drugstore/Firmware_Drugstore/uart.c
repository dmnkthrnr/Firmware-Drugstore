/*
 * uart.c
 *
 * Created: 21.03.2017 08:28:03
 *  Author: thurnerd
 */ 

#include "Includes/main.h"
#include "Includes/uart.h"

void InitUART(void)
{
	PM->APBCMASK.bit.SERCOM3_ = 1;
	//Disable USART
	SERCOM3->USART.CTRLA.bit.ENABLE = 0;
	
	//Mode: USART with internal Clock
	//LSB FIRST
	//RXPO: SERCOM PAD[1] is used for data reception (0x3)
	//TXPO: TxD Pin Location is SERCOM PAD[0] (0x2)
	SERCOM3->USART.CTRLA.reg |= SERCOM_USART_CTRLA_MODE(1)		|
								SERCOM_USART_CTRLA_DORD			|
								SERCOM_USART_CTRLA_RXPO(0x1)	|
								SERCOM_USART_CTRLA_TXPO(0x0);
								
	//Set Baudrate to 115200
	SERCOM3->USART.BAUD.reg |= SERCOM_USART_BAUD_BAUD(0xC504);
	
	//Enable Rx and Tx
	SERCOM3->USART.CTRLB.reg |= SERCOM_USART_CTRLB_RXEN |
								SERCOM_USART_CTRLB_TXEN;
	while (SERCOM3->USART.SYNCBUSY.reg);
	
	SERCOM3->USART.INTENSET.reg = SERCOM_USART_INTENSET_RXC;

	//Enable USART
	SERCOM3->USART.CTRLA.bit.ENABLE = 1; // |= SERCOM_USART_CTRLA_ENABLE;
	while (SERCOM3->USART.SYNCBUSY.bit.ENABLE);
}

void uart_write(uint8_t *data, uint8_t size)
{
	for (uint16_t i=0;i<size;i++)
	{
		while(SERCOM3->USART.INTFLAG.bit.DRE == 0);
		SERCOM3->USART.DATA.reg = data[i];
	}
}

void SERCOM3_Handler()
{
		recievedata[recieve_counter] = SERCOM3->USART.DATA.reg;

	if (recievedata[recieve_counter] == '\r')
	{
		recievedata[recieve_counter] = 0;
		recieve_counter = 0;
		new_data = 1;
	}
	else
	{
		recieve_counter++;
		new_data = 0;
	}
}