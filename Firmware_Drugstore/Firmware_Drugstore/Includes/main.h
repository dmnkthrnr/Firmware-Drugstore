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