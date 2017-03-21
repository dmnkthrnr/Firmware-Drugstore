/*
 * uart.h
 *
 * Created: 21.03.2017 08:26:51
 *  Author: thurnerd
 */ 


#ifndef UART_H_
#define UART_H_

#include "sam.h"

void InitUART(void);

void uart_write(uint8_t *data, uint8_t size);
void uart_read();



#endif /* UART_H_ */