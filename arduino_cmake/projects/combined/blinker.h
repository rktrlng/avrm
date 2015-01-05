/*
 * blinker.h
 * 
 * An example of how you would use a .cpp file in your Arduino project
 * 
 */

#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>

class Blinker
{
	public:
		Blinker(uint8_t pin, uint8_t state);
		virtual ~Blinker();
		
		void blink();
	
	private:
		int _pin;
		int _state;
};

#endif /* BLINKER_H */ 
