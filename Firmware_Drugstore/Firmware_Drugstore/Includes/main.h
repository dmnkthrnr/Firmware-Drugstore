/*
 * main.h
 *
 * Created: 16.03.2017 13:57:46
 *  Author: thurnerd
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "sam.h"

#define I2C_ADDRESS AM1805

#define I2C_TRANSFER_WRITE  0
#define I2C_TRANSFER_READ   1

uint8_t recievedata[30];
uint8_t senddata[30];
char DateString[17];

volatile uint8_t new_data;	
volatile uint8_t recieve_counter;

//-----------------------------------------------------------------------------
// Time Defines
//-----------------------------------------------------------------------------
uint16_t _10ms;
uint16_t Sekunde;


//-----------------------------------------------------------------------------
// User Interface Defines 
//-----------------------------------------------------------------------------
#define TASTER_IF (!(PORT->Group[2].IN.reg & PORT_PA01))

#define TA_SW0_NR 0
#define TA_NONE   1

#define TA_ANZ_MAX 1

int16_t TaxCounter[TA_ANZ_MAX];
uint8_t TaxState[TA_ANZ_MAX];


//-----------------------------------------------------------------------------
// AB1805 Uhrenbaustein Defines
//-----------------------------------------------------------------------------
#define AM1805 0x69

#define HUNDRETH_REGISTER           0x00
#define SECOND_REGISTER             0x01
#define MINUTE_REGISTER             0x02
#define HOUR_REGISTER               0x03
#define DATE_REGISTER               0x04
#define MONTH_REGISTER              0x05
#define YEAR_REGISTER               0x06
#define DAY_REGISTER                0x07
#define HUNDRETH_ALARM_REGISTER     0x08
#define SECOND_ALARM_REGISTER       0x09
#define MINUTE_ALARM_REGISTER       0x0A
#define HOUR_ALARM_REGISTER         0x0B
#define DATE_ALARM_REGISTER         0x0C
#define MONTH_ALARM_REGISTER        0x0D
#define DAY_ALARM_REGISTER          0x0E
#define STATU_REGISTER              0x0F

#define CONTROL1_REGISTER           0x10
#define CONTROL2_REGISTER           0x11
#define INT_MASK_REGISTER           0x12
#define SQW_REGISTER                0x13
#define CAL_XT_REGISTER             0x14
#define CAL_RC_HI_REGISTER          0x15
#define CAL_RC_LOW_REGISTER         0x16
#define INT_POLARITY_REGISTER       0x17
#define TIMER_CONTROL_REGISTER      0x18
#define TIMER_REGISTER              0x19
#define TIMER_INITIAL_REGISTER      0x1A
#define WDT_REGISTER                0x1B
#define OSC_CONTROL_REGISTER        0x1C
#define OSC_STATUS_REGISTER         0x1D

#define CONFIG_KEY_REGISTER         0x1F
#define TRICKLE_REGISTER            0x20
#define BREF_CONTROL_REGISTER       0x21

#define AFCTRL_REGISTER             0x26
#define BATMODE_REGISTER            0x27

#define ID0_REGISTER                0x28
#define ID1_REGISTER                0x29
#define ID2_REGISTER                0x2A
#define ID3_REGISTER                0x2B
#define ID4_REGISTER                0x2C
#define ID5_REGISTER                0x2D
#define ID6_REGISTER                0x2E
#define ASTAT_REGISTER              0X2F

#define OCTRL_REGISTER              0x30
#define EXTENSION_ADDRESS_REGISTER  0x3F

#define TENTH_MASK                  0xF0
#define HUNDRETH_MASK               0x0F
#define SECOND_MASK                 0x7F
#define MINUTE_MASK                 0x7F
#define HOUR_24_MASK                0x3F
#define HOUR_12_MASK                0x1F
#define AM_PM_MASK                  0x20
#define DATE_MASK                   0x3F
#define MONTH_MASK                  0x1F
#define YEAR_MASK                   0xFF
#define DAY_MASK                    0x07

#define TENTH_ALARM_MASK            0xF0
#define HUNDRETH_ALARM_MASK         0xF0
#define SECOND_ALARM_MASK           0x7F
#define MINUTE_ALARM_MASK           0x7F
#define HOUR_24_ALARM_MASK          0x3F
#define HOUR_12_ALARM_MASK          0x1F
#define DATE_ALARM_MASK             0x3F
#define MONTH_ALARM_MASK            0x1F
#define WEEKDAY_ALARM_MASK          0x07
//#define STATUS_MASK                 0x

#define MONDAY                      0
#define TUESDAY                     1
#define WEDNESDAY                   2
#define THURSDAY                    3
#define FRIDAY                      4
#define SATURDAY                    5
#define SUNDAY                      6

#define MIN_SECOND                  0
#define MAX_SECOND                  0x60
#define MIN_MINUTE                  0
#define MAX_MINUTE                  0x60
#define MIN_HOURS                   0
#define MAX_HOURS                   0x24
#define MIN_DAY                     1
#define MAX_DAY                     0x08
#define MIN_DATE                    0
#define MAX_DATE                    0x32
#define MIN_MONTH                   0
#define MAX_MONTH                   0x13
#define MIN_YEAR                    0
#define MAX_YEAR                    0x100

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