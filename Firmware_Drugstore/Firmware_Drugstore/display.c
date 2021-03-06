/*
 * display.c
 *
 * Created: 28.03.2017 15:50:24
 *  Author: thurnerd
 */ 

#include "Includes/main.h"
#include "Includes/display.h"
#include "Includes/spi.h"
#include "Includes/settings.h"
#include "Includes/lut.h"

 //-----------------------------------------------------------------------------
 // Write Instruction to Display
 //-----------------------------------------------------------------------------
 void write_display_instruction(uint8_t cmd)
 {
	 REG_PORT_OUT1 &= ~(1<<DISPLAY_RS_PIN_NUM);
	 //REG_PORT_OUTCLR1 |= DISPLAY_RS_PIN;
	 spi_write(cmd);
 }

 //-----------------------------------------------------------------------------
 // Write Data to Display
 //-----------------------------------------------------------------------------
 void write_display_data(uint8_t data)
 {
	REG_PORT_OUT1 |= (1<<DISPLAY_RS_PIN_NUM);
	 //REG_PORT_OUTSET1 |= DISPLAY_RS_PIN;
	 spi_write(data);
 }

 //-----------------------------------------------------------------------------
 // Init Display
 //-----------------------------------------------------------------------------
 void InitDisplay(void)
 {
	contrast_level = 14;
	
	RESET(); 
	REG_PORT_OUT1 |= (1<<DISPLAY_RESET_PIN_NUM);
	Delay_ms(200);
	REG_PORT_OUT1 &= ~(1<<DISPLAY_RESET_PIN_NUM);
	Delay_ms(200);
 	REG_PORT_OUT1 |= (1<<DISPLAY_RESET_PIN_NUM);

	Delay_ms(200);
    CLEAR_ADC();
    SET_SHL();
    CLEAR_BIAS();
    Power_Control(0x07);
    Regulor_Resistor_Select(0x05);
    Set_Contrast_Control_Register(contrast_level);
	Initial_Dispay_Line(0x00);
	DISPLAY_ON();
 }
 
 
 
 
//-----------------------------------------------------------------------------
//Specify DDRAM line for COM0 0~63
//-----------------------------------------------------------------------------
void Initial_Dispay_Line(uint8_t line)
{
    line|=0x40;
    write_display_instruction(line);
}

//-----------------------------------------------------------------------------
// Set page address 0~15
//-----------------------------------------------------------------------------
void Set_Page_Address(uint8_t add)
{
    add=0xb0|add;
    write_display_instruction(add);
}

//-----------------------------------------------------------------------------
// Set Column address
//-----------------------------------------------------------------------------
void Set_Column_Address(uint8_t add)
{
    write_display_instruction((0x10|(add>>4)));
	write_display_instruction((0x0f&add));
}

//-----------------------------------------------------------------------------
// Set Power Control
// Power_Control   4 (internal converte ON) + 2 (internal regulor ON) + 1 (internal follower ON)
//-----------------------------------------------------------------------------
void Power_Control(uint8_t vol)
{
    write_display_instruction((0x28|vol));
}

//-----------------------------------------------------------------------------
//  Regulor resistor select
//            1+Rb/Ra  Vo=(1+Rb/Ra)Vev    Vev=(1-(63-a)/162)Vref   2.1v
//            0  3.0       4  5.0(default)
//            1  3.5       5  5.5
//            2  4         6  6
//            3  4.5       7  6.4
//
//-----------------------------------------------------------------------------
void Regulor_Resistor_Select(uint8_t r)
{
    write_display_instruction((0x20|r));
}

//-----------------------------------------------------------------------------
//a(0-63) 32default   Vev=(1-(63-a)/162)Vref   2.1v
//-----------------------------------------------------------------------------
void Set_Contrast_Control_Register(uint8_t mod)
{
    write_display_instruction(0x81);
	write_display_instruction(mod);
}

//-----------------------------------------------------------------------------
// Send Picture to Display (whole Display!)
//-----------------------------------------------------------------------------
void display_picture(uint8_t pic[])
{
	uint8_t i;
	uint8_t j;
	
	Initial_Dispay_Line(0x40);
	for (i=0;i<0x8;i++)
	{
		Set_Page_Address(i);
		Set_Column_Address(0x00);
		for (j=0;j<0x80;j++)
		{
			write_display_data(pic[i*0x80+j]);
		}
	}
}

//-----------------------------------------------------------------------------
// Write Text on Display
//-----------------------------------------------------------------------------
void Write_text(uint8_t *data, uint8_t line, uint8_t column, uint8_t len, uint8_t start)
{
	data += start;
	for (uint8_t j = 0; (*data != '\0') && (j<len); j++)
	{
		Initial_Dispay_Line(0x00);
		Set_Column_Address((column+j)*8);
		Set_Page_Address(line);
		for(uint8_t i = 1; i<16; i+=2)
		{
			write_display_data(font[(*(data)-32)*16+i]);
		}
		
		Set_Page_Address(line+1);
		Set_Column_Address((column+j)*8);
		for(uint8_t i = 0; i<17; i+=2)
		{
			write_display_data(font[(*(data)-32)*16+i]);
		}
		data++;	
	}		
}

//-----------------------------------------------------------------------------
// Clear Display
//-----------------------------------------------------------------------------
void clear_display(void)
{
	uint8_t i;
	uint8_t j;
	
	Initial_Dispay_Line(0x40);
	for (i=0;i<0x8;i++)
	{
		Set_Page_Address(i);
		Set_Column_Address(0x00);
		for (j=0;j<0x80;j++)
		{
			write_display_data(0x00);
		}
	}
}

//-----------------------------------------------------------------------------
// Display STM
//-----------------------------------------------------------------------------
uint8_t ChangeDisplaySate(void)
{
	switch(DisplayState)
	{
		case DISPLAY_IDLE:
			get_date_string();
			Write_text((uint8_t*)"DrugStore",0,3, TEXTSTRING);
			Write_text((uint8_t*)&DateString,2,4, DATESTRING);
			Write_text((uint8_t*)&DateString,4,4, TIMESTRING);
			break;

		case DISPLAY_MENUE:
			break;

		case DISPLAY_SET_DATETIME:
			break;

		default:
			clear_display();
			get_date_string();
			Write_text((uint8_t*)"DrugStore",0,3, TEXTSTRING);
			Write_text((uint8_t*)&DateString,2,4, DATESTRING);
			Write_text((uint8_t*)&DateString,4,4, TIMESTRING);
			return (1);
			break;
	}
	return (0);
}