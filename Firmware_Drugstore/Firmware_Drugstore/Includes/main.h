/*
 * main.h
 *
 * Created: 16.03.2017 13:57:46
 *  Author: thurnerd
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "sam.h"
#include "stdio.h"
#include "stdbool.h"




// ---------------------------------------------------------------------------
//  States
// ---------------------------------------------------------------------------
#define STM_START					1
#define STM_STARTAFTERSLEEP			2
#define STM_IDLE  					3
#define STM_SLEEP 					4

volatile uint8_t State;
volatile uint8_t DisplayState;

// ---------------------------------------------------------------------------
//  Display Defines
// ---------------------------------------------------------------------------
#define DISPLAY_RS_PIN				PORT_PB11
#define DISPLAY_RESET_PIN			PORT_PB10	
#define DISPLAY_SPI_CHIP_SELECT_PIN	PORT_PB17

#define DISPLAY_RESET_PIN_NUM		10
#define DISPLAY_RS_PIN_NUM			11
#define DISPLAY_CS_PIN_NUM			17

#define DISPLAY_ON()           write_display_instruction(0xaf)   //  Display on
#define DISPLAY_OFF()          write_display_instruction(0xae)   //  Display off
#define SET_ADC()              write_display_instruction(0xa1)   //  Reverse disrect (SEG131-SEG0)
#define CLEAR_ADC()            write_display_instruction(0xa0)   //  Normal disrect (SEG0-SEG131)
#define REVERSE_DISPLAY_ON()   write_display_instruction(0xa7)   //  Reverse display : 0 illuminated
#define REVERSE_DISPLAY_OFF()  write_display_instruction(0xa6)   //  Normal display : 1 illuminated
#define ENTIRE_DISPLAY_ON()    write_display_instruction(0xa5)   //  Entire dislay   Force whole LCD point
#define ENTIRE_DISPLAY_OFF()   write_display_instruction(0xa4)   //  Normal display
#define SET_BIAS()             write_display_instruction(0xa3)   //  bias 1
#define CLEAR_BIAS()           write_display_instruction(0xa2)   //  bias 0
#define SET_MODIFY_READ()      write_display_instruction(0xe0)   //  Stop automatic increment of the column address by the read instruction
#define RESET_MODIFY_READ()    write_display_instruction(0xee)   //  Cancel Modify_read, column address return to its initial value just before the Set Modify Read instruction is started
#define RESET()                write_display_instruction(0xe2)
#define SET_SHL()              write_display_instruction(0xc8)   // SHL 1,COM63-COM0
#define CLEAR_SHL()            write_display_instruction(0xc0)   // SHL 0,COM0-COM63

#define START_COLUMN	0x00
#define START_PAGE		0x00
#define	STARTLINE_SET	0x00

volatile uint8_t contrast_level;

// ---------------------------------------------------------------------------
//  Display Strings
// ---------------------------------------------------------------------------
#define DATESTRING	8,0
#define TIMESTRING	8,9
#define TEXTSTRING	100,0	

// ---------------------------------------------------------------------------
//  Display States
// ---------------------------------------------------------------------------
#define DISPLAY_IDLE			0
#define DISPLAY_MENUE			1
#define DISPLAY_SET_DATETIME	2

//-----------------------------------------------------------------------------
// Settings Defines
//-----------------------------------------------------------------------------
#define AIN1			PORT_PA04
#define AIN2			PORT_PA05
#define BIN1			PORT_PA06
#define BIN2			PORT_PA07
#define MOTOR_SLEEP		PORT_PA03


//-----------------------------------------------------------------------------
// Stepper Motor Defines
//-----------------------------------------------------------------------------
#define Forward true
#define Back false
#define StepSize 18 //StepSize*10
#define stepsPerRevolution = 3600 / StepSize;  // change this to fit the number of steps per revolution for your motor

//-----------------------------------------------------------------------------
// I2C Defines
//-----------------------------------------------------------------------------
#define I2C_TRANSFER_WRITE  0
#define I2C_TRANSFER_READ   1

uint8_t recievedata[70];
uint8_t senddata[30];

//-----------------------------------------------------------------------------
// UART Defines
//-----------------------------------------------------------------------------
volatile uint8_t new_data;	
volatile uint8_t recieve_counter;

//-----------------------------------------------------------------------------
// Time Defines
//-----------------------------------------------------------------------------
volatile uint16_t _10ms;
volatile uint16_t Sekunde;


//-----------------------------------------------------------------------------
// User Interface Defines 
//-----------------------------------------------------------------------------
#define TASTER_IF (!(PORT->Group[0].IN.reg & PORT_PA15))

#define TA_SW0_NR	0
#define TA_ANZ_MAX	1

#define GOTOSLEEP	2

volatile int16_t TaxCounter[TA_ANZ_MAX];
volatile uint8_t TaxState[TA_ANZ_MAX];


//-----------------------------------------------------------------------------
// AB1805 Uhrenbaustein Defines
//-----------------------------------------------------------------------------
#define I2C_ADDRESS_AB1805 0x69

uint8_t DateString[17];

volatile uint8_t _year;
volatile uint8_t _month;
volatile uint8_t _date;
volatile uint8_t _day;
volatile uint8_t _hour;
volatile uint8_t _minutes;
volatile uint8_t _seconds;

volatile uint8_t _alarm_year;
volatile uint8_t _alarm_month;
volatile uint8_t _alarm_date;
volatile uint8_t _alarm_day;
volatile uint8_t _alarm_hour;
volatile uint8_t _alarm_minutes;
volatile uint8_t _alarm_seconds;

#endif /* MAIN_H_ */