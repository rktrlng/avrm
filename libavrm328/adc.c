#include <avr/io.h>
#include <inttypes.h>
#include "adc.h"

void adc_init(void)
{
	// select Vref=AVcc
	ADMUX |= (1<<REFS0);
	// set prescaler to 128 and enable ADC 
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);    
}

uint16_t read_adc(uint8_t channel)
{
	// select adc channel
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	// do conversion
	ADCSRA |= (1<<ADSC);
	// wait until adc conversion is complete
	while( ADCSRA & (1<<ADSC) ) {
		; // nop
	}
	
	return ADC;
}
