/*
 * stepper_motor.c
 *
 * Created: 23.03.2017 10:19:25
 *  Author: thurnerd
 */ 

#include "Includes/main.h"
#include "Includes/settings.h"
#include "Includes/stepper_motor.h"

void motor_move(uint8_t iMSchritte, uint8_t Speed, bool Direction)
{
	int i = 0;
	REG_PORT_OUTSET0 = MOTOR_SLEEP; //Enable Driver
	if(Direction == Forward)
	{
		//							AIN1 | AIN2 | BIN1 | BIN2

		Delay_ms(Speed);
		do
		{
			REG_PORT_OUTSET0 = AIN1;//     1 |    1 |    0 |    0
			REG_PORT_OUTSET0 = BIN1;
			REG_PORT_OUTCLR0 = AIN2;
			REG_PORT_OUTCLR0 = BIN2;
			Delay_ms(Speed);
			REG_PORT_OUTCLR0 = AIN1;//     0 |    1 |    1 |    0
			REG_PORT_OUTSET0 = BIN1;
			REG_PORT_OUTSET0 = AIN2;
			REG_PORT_OUTCLR0 = BIN2;
			Delay_ms(Speed);
			REG_PORT_OUTCLR0 = AIN1;//     0 |    0 |    1 |    1
			REG_PORT_OUTCLR0 = BIN1;
			REG_PORT_OUTSET0 = AIN2;
			REG_PORT_OUTSET0 = BIN2;
			Delay_ms(Speed);
			REG_PORT_OUTSET0 = AIN1;//     1 |    0 |    0 |    1
			REG_PORT_OUTCLR0 = BIN1;
			REG_PORT_OUTCLR0 = AIN2;
			REG_PORT_OUTSET0 = BIN2;
			Delay_ms(Speed);
			i++;
		} while (i != iMSchritte);
		
		REG_PORT_OUTCLR0 = BIN1 | AIN2 | AIN1 | BIN2;
	}
	else if(Direction == Back)
	{
		//							AIN1 | AIN2 | BIN1 | BIN2
		REG_PORT_OUTSET0 = AIN2;//     0 |    1 |    0      0
		REG_PORT_OUTCLR0 = AIN1;
		Delay_ms(Speed);
		do
		{	REG_PORT_OUTSET0 = AIN1;//     1 |    0 |    0 |    1
			REG_PORT_OUTCLR0 = BIN1;
			REG_PORT_OUTCLR0 = AIN2;
			REG_PORT_OUTSET0 = BIN2;
			Delay_ms(Speed);
			REG_PORT_OUTCLR0 = AIN1;//     0 |    0 |    1 |    1
			REG_PORT_OUTCLR0 = BIN1;
			REG_PORT_OUTSET0 = AIN2;
			REG_PORT_OUTSET0 = BIN2;
			Delay_ms(Speed);
			REG_PORT_OUTCLR0 = AIN1;//     0 |    1 |    1 |    0
			REG_PORT_OUTSET0 = BIN1;
			REG_PORT_OUTSET0 = AIN2;
			REG_PORT_OUTCLR0 = BIN2;
			Delay_ms(Speed);
			REG_PORT_OUTSET0 = AIN1;//     1 |    1 |    0 |    0
			REG_PORT_OUTSET0 = BIN1;
			REG_PORT_OUTCLR0 = AIN2;
			REG_PORT_OUTCLR0 = BIN2;
			Delay_ms(Speed);
			i++;
		} while(i != iMSchritte); //i = iMSchritte --> Abbruch der Schleife
		
		REG_PORT_OUTSET0 = AIN1 | BIN2 | AIN2 | BIN1;
	}
}