#include "blinker.h"

Blinker::Blinker(uint8_t pin, uint8_t state)
{
	_pin = pin;
	_state = state;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, _state);
}

Blinker::~Blinker()
{
	
}

void Blinker::blink()
{
	_state = !_state;
	digitalWrite(_pin, _state);
}
