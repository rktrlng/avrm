#include <avr/io.h>
#include <inttypes.h>
#include "leds.h"

void leds_init(void)
{
	// setup outputs for PORTD and PORTB
	// D3 = PWM
	// B3 = PWM
	// B5 = blinky
	DDRD |= (1 << 3);
	DDRB |= (1 << 3) | (1 << 5);
}

void blink_B5(void)
{
	PORTB ^= (1 << 5);
}
