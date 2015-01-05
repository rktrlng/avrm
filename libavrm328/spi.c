#include <avr/io.h>
#include "spi.h"

void spi_init_master(void)
{
	//set MISO as input
	DDRB &= (0<<PB4);
	//set SCK, MOSI and SS as output
	DDRB |= ((0<<PB5)|(1<<PB3)|(0<<PB2));
	
	//enable SPI
	SPCR |= (1<<SPE);
	SPCR |= (1<<SPR0); // clock rate Fosc/16 (500KHz@8MHz / 750KHz@12MHz)
	//SPCR |= (0<<SPR0); // clock rate Fosc/4 (2MHz@8MHz)
	SPCR |= (1<<MSTR); // master
}

void spi_master_transmit(char data)
{
	/* Start transmission */
	SPDR = data;
	
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}

void spi_init_slave(void)
{
	//set SCK, MOSI and SS as input
	DDRB &= (0<<PB5)|(0<<PB3)|(0<<PB2);
	//set MISO as output
	DDRB |= (1<<PB4);
	//set SS to high
	PORTB |= (1<<PB2);
	
	//enable SPI
	SPCR |= (1<<SPE);
	SPCR |= (0<<MSTR); // slave
	SPCR |= (1<<SPIE); // enable interrupt
}

char spi_slave_receive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
		;
	
	/* Return Data Register */
	return SPDR;
}
