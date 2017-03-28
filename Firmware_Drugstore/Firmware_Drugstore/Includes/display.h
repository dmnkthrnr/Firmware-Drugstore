/*
 * display.h
 *
 * Created: 28.03.2017 15:50:05
 *  Author: thurnerd
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "main.h"

void write_display_instruction(uint8_t cmd);
void write_display_data(uint8_t data);

void InitDisplay(void);

void Initial_Dispay_Line(uint8_t line);
void Set_Page_Address(uint8_t add);
void Set_Column_Address(uint8_t add);
void Power_Control(uint8_t vol);
void Regulor_Resistor_Select(uint8_t r);
void Set_Contrast_Control_Register(uint8_t mod);

#endif /* DISPLAY_H_ */