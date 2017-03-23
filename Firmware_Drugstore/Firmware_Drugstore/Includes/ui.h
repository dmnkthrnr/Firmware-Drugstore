/*
 * ui.h
 *
 * Created: 21.03.2017 16:15:39
 *  Author: thurnerd
 */ 


#ifndef UI_H_
#define UI_H_

#include "main.h"

enum eBUTTON_STATES{
	BUTTON_STARTUP = 0,
	BUTTON_OFF,
	BUTTON_SHORT,
	BUTTON_1S,
	BUTTON_2S,
	BUTTON_3S,
	BUTTON_4S,
	BUTTON_5S,
	BUTTON_8S,
	BUTTON_SHORT_DONE,
	BUTTON_SHORT_REC,
	BUTTON_1S_DONE,
	BUTTON_2S_DONE,
	BUTTON_3S_DONE,
	BUTTON_4S_DONE,
	BUTTON_5S_DONE,
	BUTTON_8S_DONE,
};

void UiInit(void);
uint8_t ReadTasten(void);
void UpdateTastenCounter(void);
void SetCounterState(void);
void ActCounter(uint8_t OnOff, uint8_t InputNr);




#endif /* UI_H_ */