// compile and upload with:
// make flash
#include <avr/io.h>
#include <util/delay.h>

#define LED0    (1 << 0)
#define LED1    (1 << 1)
#define LED2    (1 << 5)
#define LEDMASK (LED0 | LED1 | LED2)

int main(void)
{
	DDRB |= LED2; // LED2 pin is output
	PORTB &= ~(LED2 & LEDMASK); // LED2 is off

	for (;;) {
		PORTB ^= (LED2 & LEDMASK); // invert LED2 pin
		_delay_ms(50);
		PORTB ^= (LED2 & LEDMASK); // invert LED2 pin
		_delay_ms(950);
	}

	return 0;
}
