#ifndef I2C_H
#define I2C_H

//https://github.com/devthrash/I2C-slave-lib

//sudo apt-get install i2c-tools
//enable SPI and I2C in sudo raspi-config
//add to /etc/modules:
//	i2c-bcm2708
//	i2c-dev

// sudo i2cdetect -y 1

#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>

void i2c_init(uint8_t address);
void i2c_stop(void);

#endif // I2C_H
