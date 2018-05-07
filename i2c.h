/*
 * i2c.h
 *
 *  Created on: 7 maj 2018
 *      Author: pszymans
 */

#ifndef I2C_I2C_H_
#define I2C_I2C_H_

#include <avr/io.h>

#define I2C_ACK (0)
#define I2C_NOACK (1)

void i2c_init(uint16_t speed_kHz);
void TWI_start( void );
void TWI_stop( void );
void TWI_write( uint8_t byte );
uint8_t TWI_read( uint8_t ack );

uint8_t i2c_read_from_buffer(uint8_t address, uint8_t length, uint8_t *buf);
uint8_t i2c_write_from_buffer(uint8_t address, uint8_t length, uint8_t *buf);


#endif /* I2C_I2C_H_ */
