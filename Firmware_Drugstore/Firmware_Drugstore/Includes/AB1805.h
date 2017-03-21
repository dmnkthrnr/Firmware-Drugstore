/*
 * AB1805.h
 *
 * Created: 17.03.2017 13:00:25
 *  Author: thurnerd
 */ 


#ifndef AB1805_H_
#define AB1805_H_

#include "sam.h"

void InitAB1805(void);

uint8_t read_rtc_register(const uint8_t rtc_register);
uint8_t write_rtc_register(const uint8_t rtc_register, const uint8_t data);

uint8_t get_rtc_data(const uint8_t rtc_register, const uint8_t register_mask);

uint8_t get_second(void);
uint8_t get_minute(void);
uint8_t get_hour(void);
uint8_t get_day(void);
uint8_t get_date(void);
uint8_t get_month(void);
uint8_t get_year(void);

void get_datetime(void);

void set_second(const uint8_t value);
void set_minute(const uint8_t value);
void set_hour(const uint8_t value);
void set_day(const uint8_t value);
void set_date(const uint8_t value);
void set_month(const uint8_t value);
void set_year(const uint8_t value);

void set_datetime(uint8_t year, uint8_t month, uint8_t date, uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds);

uint8_t get_seconds_alarm(void);
uint8_t get_minutes_alarm(void);
uint8_t get_hour_alarm(void);
uint8_t get_day_alarm(void);
uint8_t get_date_alarm(void);
uint8_t get_month_alarm(void);

uint8_t set_seconds_alarm(uint8_t value);
uint8_t set_minutes_alarm(uint8_t value);
uint8_t set_hour_alarm(uint8_t value);
uint8_t set_day_alarm(uint8_t value);
uint8_t set_date_alarm(uint8_t value);
uint8_t set_month_alarm(uint8_t value);
uint8_t set_year_alarm(uint8_t value);

void get_date_string(void);

#endif /* AB1805_H_ */