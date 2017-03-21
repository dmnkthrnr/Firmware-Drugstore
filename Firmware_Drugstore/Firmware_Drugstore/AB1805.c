/*
 * AB1805.c
 *
 * Created: 17.03.2017 13:02:10
 *  Author: thurnerd
 */ 

#include "sam.h"
#include "Includes/main.h"
#include "Includes/i2c.h"
#include "Includes/AB1805.h"
#include "Includes/settings.h"


void InitAB1805()
{
	//CMDR = 2 / OFFSETR = 4222
	write_rtc_register(CAL_RC_HI_REGISTER, 0x90);		
	//recievedata[3]=read_rtc_register(CAL_RC_HI_REGISTER);
	write_rtc_register(CAL_RC_LOW_REGISTER, 0x7E);
	//recievedata[4]=read_rtc_register(CAL_RC_LOW_REGISTER);
	
	//Enable Oscillator Register (Key 0xA1)
	write_rtc_register(CONFIG_KEY_REGISTER,0xA1);
	//Enable RC Oscillator
	write_rtc_register(0x1C,0x80);
	
	//1Hz to Output Pin
	write_rtc_register(CONTROL2_REGISTER, 0x01);	//SQW Mode Selected on PIN FOUT/nIRQ (11)
	write_rtc_register(SQW_REGISTER, 0x8F);			//1Hz Output
}

uint8_t read_rtc_register(const uint8_t rtc_register)
{
	senddata[0] = rtc_register;
	
	i2c_write(&senddata,1);
	i2c_read(&recievedata,1);
	
	return recievedata[0]; 
}

uint8_t write_rtc_register(const uint8_t rtc_register, const uint8_t data)
{
	senddata[0] = rtc_register;
	senddata[1] = data;
	
	i2c_write(&senddata,2);
	
	return (1);
}

uint8_t get_rtc_data(const uint8_t rtc_register, const uint8_t register_mask)
{
	return (read_rtc_register(rtc_register) & register_mask);
}

uint8_t get_second(void)
{
	return get_rtc_data(SECOND_REGISTER, SECOND_MASK);
}

uint8_t get_minute(void)
{
	return get_rtc_data(MINUTE_REGISTER, MINUTE_MASK);
}

uint8_t get_hour(void)
{
	return get_rtc_data(HOUR_REGISTER, HOUR_24_MASK);
}

uint8_t get_day(void)
{
	return get_rtc_data(DAY_REGISTER, DAY_MASK);
}

uint8_t get_date(void)
{
	return get_rtc_data(DATE_REGISTER, DATE_MASK);
}

uint8_t get_month(void)
{
	return get_rtc_data(MONTH_REGISTER, MONTH_MASK);
}

uint8_t get_year(void)
{
	return get_rtc_data(YEAR_REGISTER, YEAR_MASK);
}

void get_datetime(void)
{
	_seconds = get_second();
	_minutes = get_minute();
	_hour = get_hour();
	_day = get_day();
	_date = get_date();
	_month = get_month();
	_year = get_year();
}

void set_second(const uint8_t value) {
	_seconds = value % MAX_SECOND;
	write_rtc_register(SECOND_REGISTER, _seconds);
}

void set_minute(const uint8_t value) {
	_minutes = value % MAX_MINUTE;
	write_rtc_register(MINUTE_REGISTER, _minutes);
}

void set_hour(const uint8_t value) {
	_hour = value % MAX_HOURS;
	write_rtc_register(HOUR_REGISTER, _hour);
}

void set_day(const uint8_t value) {
	_day = value % MAX_DAY;
	write_rtc_register(DAY_REGISTER, _day);
}

void set_date(const uint8_t value) {
	_date = value % MAX_DATE;
	write_rtc_register(DATE_REGISTER, _date);
}

void set_month(const uint8_t value) {
	_month = value % MAX_MONTH;
	write_rtc_register(MONTH_REGISTER, _month);
}

void set_year(const uint8_t value) {
	_year = value % MAX_YEAR;
	write_rtc_register(YEAR_REGISTER, value);
}

void set_datetime(uint8_t year, uint8_t month, uint8_t date, uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds) {
	set_year(year);
	set_month(month);
	set_date(date);
	set_day(day);
	set_hour(hour);
	set_minute(minutes);
	set_second(seconds);
}

uint8_t get_seconds_alarm(void){
	_alarm_seconds = get_rtc_data(SECOND_ALARM_REGISTER, SECOND_ALARM_MASK);
	return _alarm_seconds;
}

uint8_t get_minutes_alarm(void) {
	_alarm_minutes = get_rtc_data(MINUTE_ALARM_REGISTER, MINUTE_ALARM_MASK);
	return _alarm_minutes;
}

uint8_t get_hour_alarm(void) {
	_alarm_hour = get_rtc_data(HOUR_ALARM_REGISTER, HOUR_24_ALARM_MASK);
	return _alarm_hour;
}

uint8_t get_day_alarm(void) {
	_alarm_day = get_rtc_data(DAY_ALARM_REGISTER, WEEKDAY_ALARM_MASK);
	return _alarm_day;
}

uint8_t get_date_alarm(void) {
	_alarm_date = get_rtc_data(DATE_ALARM_REGISTER, DATE_ALARM_MASK);
	return _alarm_date;
}

uint8_t get_month_alarm(void) {
	_alarm_month = get_rtc_data(MONTH_ALARM_REGISTER, MONTH_ALARM_MASK);
	return _alarm_month;
}

uint8_t set_seconds_alarm(uint8_t value) {
	_alarm_seconds = value % MAX_SECOND;
	return (value == _alarm_seconds);
}

uint8_t set_minutes_alarm(uint8_t value) {
	_alarm_minutes = value % MAX_MINUTE;
	return (value == _alarm_minutes);
}

uint8_t set_hour_alarm(uint8_t value) {
	_alarm_hour = value % MAX_HOURS;
	return (value == _alarm_hour);
}

uint8_t set_day_alarm(uint8_t value) {
	_alarm_day = value % MAX_DAY;
	return (value == _alarm_day);
}

uint8_t set_date_alarm(uint8_t value) {
	_alarm_date = value % MAX_DATE;
	return (value == _alarm_date);
}

uint8_t set_month_alarm(uint8_t value) {
	_alarm_month = value % MAX_MONTH;
	return (value == _alarm_month);
}

uint8_t set_year_alarm(uint8_t value) {
	_alarm_year = value % MAX_YEAR;
	return (value == _alarm_year);
}



	
void get_date_string(void)
{
	_date = get_date();
	Value2String(((_date & 0xF0) >> 4),(uint8_t*)&DateString[0],1);
	Value2String(_date & 0x0F,(uint8_t*)&DateString[1],1);
	DateString[2] = '.';
	
	_month = get_month();
	Value2String(((_month & 0xF0) >> 4),(uint8_t*)&DateString[3],1);
	Value2String(_month & 0x0F,(uint8_t*)&DateString[4],1);
	DateString[5] = '.';
	
	_year = get_year();
	Value2String(((_year & 0xF0) >> 4),(uint8_t*)&DateString[6],1);
	Value2String(_year & 0x0F,(uint8_t*)&DateString[7],1);
	DateString[8] = '/';
	
	_hour = get_hour();
	Value2String(((_hour & 0xF0) >> 4),(uint8_t*)&DateString[9],1);
	Value2String(_hour & 0x0F,(uint8_t*)&DateString[10],1);
	DateString[11] = ':';
	
	_minutes = get_minute();
	Value2String(((_minutes & 0xF0) >> 4),(uint8_t*)&DateString[12],1);
	Value2String(_minutes & 0x0F,(uint8_t*)&DateString[13],1);
	DateString[14] = ':';
	
	_seconds = get_second();
	Value2String(((_seconds & 0xF0) >> 4),(uint8_t*)&DateString[15],1);
	Value2String(_seconds & 0x0F,(uint8_t*)&DateString[16],1);
}