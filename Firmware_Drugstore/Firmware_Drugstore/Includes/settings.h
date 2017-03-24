/*
 * settings.h
 *
 * Created: 16.03.2017 14:23:31
 *  Author: thurnerd
 */ 


#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "main.h"

uint8_t InitAll(void);

void InitPorts(void);
void InitClocks(void);
void InitEIC(void);

void Value2String( int16_t Value, uint8_t *DestPtr, uint8_t Stellen);
void Delay_ms(uint16_t Milliseconds);

#endif /* SETTINGS_H_ */