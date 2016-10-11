
#include "spi_driver.h"

#include <stddef.h>
#include <stdint.h>
#include <avr/io.h>


void spi_select_device(uint8_t *port, uint8_t pin)
{
	static volatile uint8_t *old_port = NULL;
	static volatile uint8_t old_pin = 0x00;
	
	if(old_port)
	{
		// disable SPI to last device used
		*old_port |= old_pin;
	}
	
	old_pin = 0;
	old_port = port;
	old_pin = pin;
	
	*port &= ~pin;
}


uint8_t spi_exchange(uint8_t data)
{
	SPDR = data;
	
	while(!(SPSR & (1 << SPIF)));
	
	return SPDR;
}

void spi_init()
{
	volatile uint8_t _;
	
	DDRB |= (1 << 5) | (1 << 3) | (1 << 2); // SPI master outputs, including hardware-controlled slave select pin
	DDRB &= ~(1 << 4); // SPI master input
	
	SPCR |= (1 << SPE) | (1 << MSTR); // initialize SPI hardware
	
	_ = SPSR; // read SPI status register to clear interrupts, result doesn't matter
	_ = SPDR; // same with SPI data register
}
