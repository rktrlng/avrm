#include <Arduino.h>

#include "blinker.h"	// for the .cpp file
#include "test.h"		// for the .c file

Blinker blinker1(3, HIGH);
Blinker blinker2(5, LOW);

void setup() {
	Serial.begin(9600);
	
	// from our 'test' .c/.h-file
	char a = TEST;
	test(a);
}

void loop() {
	blinker1.blink();
	blinker2.blink();
	Serial.write("blink\r\n");
	delay(1000);
}
