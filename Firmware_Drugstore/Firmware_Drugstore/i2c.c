/*
 * i2c.c
 *
 * Created: 16.03.2017 13:57:26
 *  Author: thurnerd
 */ 

#include "Includes/i2c.h"
#include "Includes/main.h"

#include "sam.h"

//-----------------------------------------------------------------------------
// Init I2C Master Mode
//-----------------------------------------------------------------------------
void InitI2C()
{
	PM->APBCMASK.bit.SERCOM0_ = 1;
	//Set I2C Mode to Master Mode
	SERCOM0->I2CM.CTRLA.reg |= SERCOM_I2CM_CTRLA_MODE(0x5);
		
	//BAUD berechnung: fref/(2*fBaud) -1
	SERCOM0->I2CM.BAUD.reg |= SERCOM_I2CM_BAUD_BAUD(207); // = 9600 Baud
		
	//Enable Smart Mode
	SERCOM0->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_SMEN;
	while (SERCOM0->I2CM.SYNCBUSY.reg);
		
	//Enable I2C
	SERCOM0->I2CM.CTRLA.reg |= SERCOM_I2CM_CTRLA_ENABLE;
	while (SERCOM0->I2CM.SYNCBUSY.reg);
		
	//Set Busstate to IDLE Mode
	SERCOM0->I2CM.STATUS.reg |= SERCOM_I2CM_STATUS_BUSSTATE(0x1);
	while (SERCOM0->I2CM.SYNCBUSY.reg);

}

//-----------------------------------------------------------------------------
// WRITE Data to Slave
//-----------------------------------------------------------------------------
void i2c_write(uint8_t *data, uint8_t size)
{
	//Send Slave Address and Write
	SERCOM0->I2CM.ADDR.reg = I2C_ADDRESS<<1 | I2C_TRANSFER_WRITE;
	
	while (0 == (SERCOM0->I2CM.INTFLAG.reg & SERCOM_I2CM_INTFLAG_MB));

	//If no ACK from Slave send STOP
	if (SERCOM0->I2CM.STATUS.reg & SERCOM_I2CM_STATUS_RXNACK)
	{
		SERCOM0->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);
	}
	
	//Send Data
	for (int i = 0; i < size; i++)
	{
		SERCOM0->I2CM.DATA.reg = SERCOM_I2CM_DATA_DATA(data[i]);

		while (0 == (SERCOM0->I2CM.INTFLAG.reg & SERCOM_I2CM_INTFLAG_MB));
		
		//If no ACK send STOP
		if (SERCOM0->I2CM.STATUS.reg & SERCOM_I2CM_STATUS_RXNACK)
		{
			SERCOM0->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);
		}
	}
	
	//Send STOP
	SERCOM0->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);

}

//-----------------------------------------------------------------------------
// READ Data from Slave
//-----------------------------------------------------------------------------
void i2c_read(uint8_t *data, uint8_t size)
{
	//Write Slave Address and Read
	SERCOM0->I2CM.ADDR.reg = I2C_ADDRESS<<1 | I2C_TRANSFER_READ;

	while (0 == (SERCOM0->I2CM.INTFLAG.reg & SERCOM_I2CM_INTFLAG_SB));
	
	//If no ACK send STOP
	if (SERCOM0->I2CM.STATUS.reg & SERCOM_I2CM_STATUS_RXNACK)
	{
		SERCOM0->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);
	}
	
	//Clear ACKACT because Smart Mode is enabled
	SERCOM0->I2CM.CTRLB.reg &= ~SERCOM_I2CM_CTRLB_ACKACT;
	
	//Read Data from Slave
	for (int i = 0; i < size-1; i++)
	{
		data[i] = SERCOM0->I2CM.DATA.reg;
		while (0 == (SERCOM0->I2CM.INTFLAG.reg & SERCOM_I2CM_INTFLAG_SB));
	}
	
	//Send no ACK when no more bytes will be read, and send STOP
	if (size)
	{
		SERCOM0->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_ACKACT;
		SERCOM0->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);
		data[size-1] = SERCOM0->I2CM.DATA.reg;
	}
}

//-----------------------------------------------------------------------------
// Write Start to I2C
//-----------------------------------------------------------------------------
void i2c_write_start(void)
{
	SERCOM0->I2CM.ADDR.reg = I2C_ADDRESS<<1 | I2C_TRANSFER_WRITE;

	while (0 == (SERCOM0->I2CM.INTFLAG.reg & SERCOM_I2CM_INTFLAG_MB));

	if (SERCOM0->I2CM.STATUS.reg & SERCOM_I2CM_STATUS_RXNACK)
	{
		SERCOM0->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);
	}
}

//-----------------------------------------------------------------------------
// Write Data to I2C
//-----------------------------------------------------------------------------
void i2c_write_byte(uint8_t byte)
{
	SERCOM0->I2CM.DATA.reg = byte;

	while (0 == (SERCOM0->I2CM.INTFLAG.reg & SERCOM_I2CM_INTFLAG_MB));

	if (SERCOM0->I2CM.STATUS.reg & SERCOM_I2CM_STATUS_RXNACK)
	{
		SERCOM0->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);
	}
}

//-----------------------------------------------------------------------------
// Write STOP to I2C
//-----------------------------------------------------------------------------
void i2c_write_stop(void)
{
	SERCOM0->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);
}
