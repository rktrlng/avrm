#include <avr/io.h>
#include <inttypes.h>
#include "timers.h"

void timer0_init(void)
{
	// setup timer 0 for CTC
	TCCR0A |= (1 << WGM01); // MAX counter = value OCR0A (Mode 2 / CTC)

	//TCCR0B |= 0x01; // prescaler = 1;		// TCCR0B |= (1 << CS00);
	//TCCR0B |= 0x02; // prescaler = 8;		// TCCR0B |= (1 << CS01);
	TCCR0B |= 0x03; // prescaler = 64;		// TCCR0B |= (1 << CS01) | (1 << CS00);
	//TCCR0B |= 0x04; // prescaler = 256;	// TCCR0B |= (1 << CS02);
	//TCCR0B |= 0x05; // prescaler = 1024;	// TCCR0B |= (1 << CS02) | (1 << CS00);
	
	// when OCR0A = 125 and prescaler = 64, TIMER0_COMPA_vect interrupt is triggered 1000 times/sec
	// because: 8000000 / 64 / 125 = 1000;
	OCR0A = 125; // OCR0A is 8 bit, so max 255
	
	// trigger interrupt when Timer0 == OCR0A
	TIMSK0 = 1 << OCIE0A;
}

void timer2_init(void)
{
	// setup timer 2 for none-inverting PWM
	
	// output on PB3
    TCCR2A |= (1 << COM2A1);
    // output on PD3
    TCCR2A |= (1 << COM2B1);
    
    // fast PWM mode (mode 3)
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    // phase correct (mode 1)
    //TCCR2A |= (1 << WGM20);
    
    // prescaler
    TCCR2B |= (1 << CS20); // 8000000 / 1 / 256 = 31.250KHz
    //TCCR2B |= (1 << CS21); // 8000000 / 8 / 256 = 3.90625KHz
    
    // 50% duty cycle (initial values)
    OCR2A = 127;
    OCR2B = 127;
}

