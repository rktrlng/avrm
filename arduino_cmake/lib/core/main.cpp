#include <Arduino.h>
#include "avr/power.h"

int main(void)
{
	clock_prescale_set(clock_div_1);
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();
    
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}
        
	return 0;
}

