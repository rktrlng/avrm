#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "uart.h"

void usart_init(int baud_rate)
{
	// set baud rate
	int ubrr_val = (((F_CPU / (baud_rate * 16L))) - 1);
	UBRR0H = (uint8_t)(ubrr_val>>8);
	UBRR0L = (uint8_t)(ubrr_val);

	// enable receiver and transmitter
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
	
	// set frame format
	UCSR0C |= (3<<UCSZ00); // 8 data bits
	UCSR0C &= ~(1<<USBS0); // 1 stop bit
	
	// enable USART recieve interrupt
	UCSR0B |= (1 << RXCIE0 );
}



char usart_read_char(void)
{
   // wait until data is available
   while(!(UCSR0A & (1<<RXC0))) {
      ; // nop
   }

   // usart data available in register UDR0
   return UDR0;
}

void usart_write_char(char data)
{
	// wait until transmitter is ready
	while(!(UCSR0A & (1<<UDRE0))) {
		; // nop
	}

	// send the data
	UDR0 = data;
}

void usart_write_string(const char* data)
{
	while (*data != '\0') {
		usart_write_char(*data);
		data++;
	}
}
