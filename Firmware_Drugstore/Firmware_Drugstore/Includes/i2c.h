/*
 * i2c.h
 *
 * Created: 16.03.2017 13:57:37
 *  Author: thurnerd
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "sam.h"

void InitI2C(void);

void i2c_write(uint8_t *data, uint8_t size, uint8_t address);
void i2c_read(uint8_t *data, uint8_t size, uint8_t address);
void i2c_write_start(uint8_t address);
void i2c_write_byte(uint8_t byte);
void i2c_write_stop(void);



#endif /* I2C_H_ */