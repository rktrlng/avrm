#include "common.h"
#include "spi.h"

// To communicate with the MCU we only need the SPI bus and SPI chip select B
void setup_gpio()
{
	INP_GPIO(7);  SET_GPIO_ALT(7,0); // SS B
	//INP_GPIO(8);  SET_GPIO_ALT(8,0); // SS A //  this is used by avrdude to program (RESET low)
	INP_GPIO(9);  SET_GPIO_ALT(9,0); // MISO
	INP_GPIO(10); SET_GPIO_ALT(10,0); // MOSI
	INP_GPIO(11); SET_GPIO_ALT(11,0); // CLK
}


//
//  Send commands to SPI device
//
void main(void)
{
	// Map the I/O sections
	setup_io();
	
	// activate SPI bus pins
	setup_gpio();
	
	// Setup SPI bus
	setup_spi();
	
	// Send command
	int i;
	for (;;) {
		command_avrm(65, 66, 67, 68);
		usleep(500000);
	}
	
	// Restore IO
	restore_io();
}
