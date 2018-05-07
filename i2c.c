/*
 * i2c.c
 *
 *  Created on: 7 maj 2018
 *      Author: pszymans
 */

#include "i2c.h"

void i2c_init(uint16_t speed_kHz) {
	// Calculate TWBR register value based on CPU freq and provided required I2C bus speed
	// TWBR = (((CPU_freq/SCL_speed)-16)/(2*prescaler))
	// Default prescaler value is 1
	uint8_t bitrate = (F_CPU/1000l)/speed_kHz;
	if(bitrate >= 16) {
		bitrate = (bitrate - 16) >> 1;
	}
	TWBR = bitrate;
}

// Function for sending start condition
void TWI_start( void )
{
	TWCR = ( 1<<TWINT )|( 1<<TWEN )|( 1<<TWSTA );
	while( !(TWCR & ( 1<<TWINT )) );
}

// Function for sending stop condition
void TWI_stop( void )
{
	TWCR = ( 1<<TWINT )|( 1<<TWEN )|( 1<<TWSTO );
	while( !(TWCR & ( 1<<TWSTO )) );
}

// Function for writing one byte
void TWI_write( uint8_t byte )
{
	TWDR = byte;
	TWCR = ( 1<<TWINT )|( 1<<TWEN );
	while( !(TWCR & ( 1<<TWINT )) );
}

// Function for reading one byte
uint8_t TWI_read( uint8_t ack )
{
	TWCR = ( 1<<TWINT )|( ack<<TWEA )|( 1<<TWEN );
	while( !(TWCR & ( 1<<TWINT )) );
	return TWDR;
}

// Write data from buffer to device
void TWI_write_buf( uint8_t address, uint8_t length, uint8_t *buf )
{
	TWI_start();
	TWI_write(address);
	while (length--) TWI_write(*buf++);
	TWI_stop();
}

// Read data from device to buffer
void TWI_read_buf( uint8_t address, uint8_t length, uint8_t *buf )
{
	TWI_start();
	TWI_write(address);
	TWI_start();
	TWI_write(address + 1);
	while (length--) *buf++ = TWI_read( length ? I2C_ACK : I2C_NOACK );
	TWI_stop();
}
