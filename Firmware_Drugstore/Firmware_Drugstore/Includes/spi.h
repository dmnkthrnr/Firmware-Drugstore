/*
 * spi.h
 *
 * Created: 26.03.2017 14:08:42
 *  Author: domi_
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "main.h"

void InitSPI(void);
void write_display_instruction(uint8_t cmd);
void write_display_data(uint8_t data);




#endif /* SPI_H_ */