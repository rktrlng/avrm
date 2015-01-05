#include <avr/io.h>
#include <inttypes.h>
#include "buttons.h"

void buttons_init(void)
{
	//DDRB &= ~((1 << DDB0) | (1 << DDB1) | (1 << DDB2)); // Clear the PB0, PB1, PB2 pin
	DDRB &= ~((1 << DDB0) | (1 << DDB1)); // Clear the PB0, PB1 pin
    // PB0,PB1,PB2 (PCINT0, PCINT1, PCINT2 pin) are now inputs

    //PORTB |= ((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2)); // turn On the Pull-up
    PORTB |= ((1 << PORTB0) | (1 << PORTB1)); // turn On the Pull-up
    // PB0, PB1 and PB2 are now inputs with pull-up enabled
    
    PCICR |= (1 << PCIE0);     // set PCIE0 to enable PCMSK0 scan
    
    //PCMSK0 |= ((1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2));   // set PCINT0,1,2 to trigger an interrupt on state change
    PCMSK0 |= ((1 << PCINT0) | (1 << PCINT1));   // set PCINT0,1,2 to trigger an interrupt on state change
}

char buttons_state(char button)
{
	return PORTB & (1 << button);
}
