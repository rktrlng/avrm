// compile and upload with:
// make flash
#include <avr/io.h>
#include <util/delay.h>

#define LED0    (1 << 0)
#define LED1    (1 << 1)
#define LED2    (1 << 5)
#define LED3    (1 << 7)
//#define LEDMASK (LED0 | LED1 | LED2)
#define LEDMASK (LED3)

int main(void)
{
	DDRC |= LED3; // LED2 pin is output
	PORTC &= ~(LED3 & LEDMASK); // LED2 is off

	for (;;) {
		PORTC ^= (LED3 & LEDMASK); // invert LED2 pin
		_delay_ms(50);
		PORTC ^= (LED3 & LEDMASK); // invert LED2 pin
		_delay_ms(950);
	}

	return 0;
}
