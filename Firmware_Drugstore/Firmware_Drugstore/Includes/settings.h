/*
 * settings.h
 *
 * Created: 16.03.2017 14:23:31
 *  Author: thurnerd
 */ 


#ifndef SETTINGS_H_
#define SETTINGS_H_


void InitPorts(void);
void InitClocks(void);

void Value2String( int16_t Value, uint8_t *DestPtr, uint8_t Stellen);

#endif /* SETTINGS_H_ */