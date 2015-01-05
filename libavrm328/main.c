#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "adc.h"
#include "spi.h"
#include "i2c.h"
#include "uart.h"
#include "timers.h"
#include "leds.h"
#include "buttons.h"


int main(void)
{
	// init the buttons
	buttons_init();
	
	// init the LEDs
	leds_init();
	
	// init slave SPI
	//spi_init_slave();
	
	// init slave I2C
	//i2c_init(0x32);
	
	// init the ADC
	adc_init();
	
	// init the timers
	timer0_init(); // CTC
	timer2_init(); // PWM
	
	// init the UART
	usart_init(9600);
	
	// enable interrupts
	sei();
	
	for (;;) {
		; // nop
	}
	
	return 0;
}

// #####################################################################
ISR(SPI_STC_vect) 
{
	uint8_t rx_data = SPDR;   // Read what slave received
	SPDR = rx_data;   // Slave sends what it received on next SPI transmit
	
	usart_write_string(" ## SPI RX interrupt: [");
	usart_write_char(rx_data);
	usart_write_string("]\r\n");
}

// #####################################################################
ISR(USART_RX_vect)
{
	// UDR0 is the USART RX buffer
	uint8_t rx_data = UDR0;
	
	usart_write_string("USART RX interrupt: [");
	usart_write_char(rx_data);
	usart_write_string("]\r\n");
}

// #####################################################################
// PB0, PB1, PB2  (0x07)
volatile uint8_t portbhistory = 0xFF; // default is high because the pull-up

ISR (PCINT0_vect)
{
	uint8_t changedbits;

	changedbits = PINB ^ portbhistory;
	portbhistory = PINB;

	if(changedbits & (1 << PINB0))
	{
		// PCINT0 changed
		usart_write_string("PCINT0 CHANGE");
		if( (portbhistory & (1 << PINB0)) == 1 ) {
			// LOW to HIGH pin change
			usart_write_string(" LOW to HIGH\r\n");
		} else {
			// HIGH to LOW pin change
			usart_write_string(" HIGH to LOW\r\n");
		}
	}
	
	if(changedbits & (1 << PINB1))
	{
		// PCINT1 changed
		usart_write_string("PCINT1 CHANGE");
		if( (portbhistory & (1 << PINB1)) == 1 ) {
			// LOW to HIGH pin change
			usart_write_string(" LOW to HIGH\r\n");
		} else {
			// HIGH to LOW pin change
			usart_write_string(" HIGH to LOW\r\n");
		}
	}
/*
	if(changedbits & (1 << PINB2))
	{
		// PCINT2 changed
		usart_write_string("PCINT2 CHANGE");
		if( (portbhistory & (1 << PINB2)) == 1 ) {
			// LOW to HIGH pin change
			usart_write_string(" LOW to HIGH\r\n");
		} else {
			// HIGH to LOW pin change
			usart_write_string(" HIGH to LOW\r\n");
		}
	}
*/
}

// #####################################################################
// CTC interrupt counter for Timer 0
volatile unsigned int counter=0;

// this is called 1000 times/sec
ISR(TIMER0_COMPA_vect)
{
	counter++;
	
	if (counter%100 == 0) { // every 100ms
		// read ADC
		uint16_t data = read_adc(0);
		
		// convert from 10 bit to 8 bit, and set PWM duty cycles
		uint8_t out = (uint8_t) (data / 4);
		OCR2A = out;		// PB3
		OCR2B = 255 - out;	// PD3
		
		// send adc value to usart
		char buffer[5];
		itoa(data, buffer, 10);
		usart_write_string(buffer);
		usart_write_string("\r\n");
	}
	if (counter%500 == 0) { // every 500ms
		blink_B5();
	}
	
	// counter reached max, reset
	if (counter == 1000) {
		counter = 0;
	}
}

// #####################################################################
volatile uint8_t buffer_address;
volatile uint8_t txbuffer[0xFF];
volatile uint8_t rxbuffer[0xFF];

ISR(TWI_vect)
{
	usart_write_string(" ## I2C RX interrupt\r\n");
	
	// temporary stores the received data
	uint8_t data;
	
	// own address has been acknowledged
	if( (TWSR & 0xF8) == TW_SR_SLA_ACK ){  
		buffer_address = 0xFF;
		// clear TWI interrupt flag, prepare to receive next byte and acknowledge
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
	}
	else if( (TWSR & 0xF8) == TW_SR_DATA_ACK ) { // data has been received in slave receiver mode
		// save the received byte inside data 
		data = TWDR;
		
		usart_write_string(" ## I2C RX interrupt: [");
		usart_write_char(data);
		usart_write_string("]\r\n");
		
		// check wether an address has already been transmitted or not
		if (buffer_address == 0xFF) {
			buffer_address = data; 
			
			// clear TWI interrupt flag, prepare to receive next byte and acknowledge
			TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
		} else { // if a databyte has already been received
			
			// store the data at the current address
			rxbuffer[buffer_address] = data;
			
			// increment the buffer address
			buffer_address++;
			
			// if there is still enough space inside the buffer
			if(buffer_address < 0xFF){
				// clear TWI interrupt flag, prepare to receive next byte and acknowledge
				TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
			} else {
				// clear TWI interrupt flag, prepare to receive last byte and don't acknowledge
				TWCR |= (1<<TWIE) | (1<<TWINT) | (0<<TWEA) | (1<<TWEN); 
			}
		}
	} else if ( (TWSR & 0xF8) == TW_ST_DATA_ACK ) { // device has been addressed to be a transmitter
		// copy data from TWDR to the temporary memory
		data = TWDR;
		
		// if no buffer read address has been sent yet
		if( buffer_address == 0xFF ){
			buffer_address = data;
		}
		
		// copy the specified buffer address into the TWDR register for transmission
		TWDR = txbuffer[buffer_address];
		// increment buffer read address
		buffer_address++;
		
		// if there is another buffer address that can be sent
		if(buffer_address < 0xFF){
			// clear TWI interrupt flag, prepare to send next byte and receive acknowledge
			TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
		}
		else{
			// clear TWI interrupt flag, prepare to send last byte and receive not acknowledge
			TWCR |= (1<<TWIE) | (1<<TWINT) | (0<<TWEA) | (1<<TWEN); 
		}
	} else {
		// if none of the above apply prepare TWI to be addressed again
		TWCR |= (1<<TWIE) | (1<<TWEA) | (1<<TWEN);
	} 
}
