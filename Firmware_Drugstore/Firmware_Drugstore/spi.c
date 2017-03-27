/*
 * spi.c
 *
 * Created: 26.03.2017 14:08:52
 *  Author: domi_
 */ 

 #include "Includes/main.h"

 #include "Includes/spi.h"
 

 //-----------------------------------------------------------------------------
 // Init SPI 
 //-----------------------------------------------------------------------------
 void InitSPI(void)
 {
	PM->APBCMASK.bit.SERCOM5_ = 1;

	//Disable SPI
	SERCOM5->SPI.CTRLA.bit.ENABLE = 0;
	while (SERCOM5->SPI.SYNCBUSY.bit.ENABLE){}

	//Select SPI Mode 3 (CPHA = 1, CPOL = 1)
	SERCOM5->SPI.CTRLA.bit.CPHA = 1;
	SERCOM5->SPI.CTRLA.bit.CPOL = 1;

	//Select SERCOM5 PAD[0] as MISO (Data Input)
	SERCOM5->SPI.CTRLA.bit.DIPO = 0x0;

	//Select SERCOM5 PAD[0] as MOSI (Data Output)
	SERCOM5->SPI.CTRLA.bit.DOPO = 0x1;

	//Select SPI Master Mode 0x3
	SERCOM5->SPI.CTRLA.bit.MODE = 0x3;

	//BAUD berechnung: fref/(2*fBaud) -1 ??Nochmals überrüfen!!!!
	SERCOM5->SPI.BAUD.reg |= SERCOM_SPI_BAUD_BAUD(39); // = 100000

	//Enable SPI
	SERCOM5->SPI.CTRLA.bit.ENABLE = 1;
	while (SERCOM5->SPI.SYNCBUSY.bit.ENABLE){}
 }

 //-----------------------------------------------------------------------------
 // Write Instruction to Display
 //-----------------------------------------------------------------------------
 void write_display_instruction(uint8_t cmd)
 {
	 
 }

 //-----------------------------------------------------------------------------
 // Write Data to Display
 //-----------------------------------------------------------------------------
 void write_display_data(uint8_t data)
 {
	 
 }