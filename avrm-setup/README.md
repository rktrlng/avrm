AVRM setup
==========

setup
-----

	Usage: setup [options]

	[options] is any of the following:
	  -h		 help		show this info
	  -a		 apt-get	apt-get all prerequisites
	  -p		 patch		patch arduino
	  -c		 compile	compile + install from source
	  -b		 binary		install pre-compiled avrdude binary
	  -f		 fuses		set m328p fuses (with crystal)
	  -t		 test		make + upload test/blinky.hex
	  -r		 remove		remove avrdude from system

Usage
-----

Run 'setup -a' to install all prerequisites (AVR toolchain, cmake, minicom, autoconf, bison, flex etcetera).

Run 'setup -p' to patch the Arduino IDE so it recognizes your board.

Run 'setup -c' to compile and install avrdude from source, or 'setup -b' to install a precompiled avrdude-6.1 with 'linuxgpio' enabled, config file (avrdude.conf) and man file (avrdude.1.gz) to the right places.

Run 'setup -f' to set the fuses for the ATmega328P. Do this once for every new chip.

avrdude-6.1-linuxgpio
---------------------
This is plain, vanilla [avrdude-6.1](http://download.savannah.gnu.org/releases/avrdude/avrdude-6.1.tar.gz) as you can get it from [download.savannah.gnu.org](http://download.savannah.gnu.org/releases/avrdude/).

This compiles and installs avrdude from source, enabling avrdude to bitbang the Raspberry Pi GPIO pins using the 'linuxgpio' (sysfsgpio) interface that's standard available in avrdude-6.1.

Prerequisite to build avrdude from source:

	sudo apt-get install flex bison

connections
-----------
Make the following connections between the AVR and the Raspberry Pi (don't forget GND and VCC, where VCC is 3.3V).

	SCK    =  11
	MOSI   =  10
	MISO   =  9
	RESET  =  8

avrdude usage:

	avrdude -c linuxgpio -p m328p -U flash:w:blinky.hex -v

If the project has a Makefile or is a cmake project, usually 'make flash' or something similar also works. Try 'make help'.

ino usage
---------

To create, build and upload a template ino file (src/sketch.ino):

	mkdir beep
	cd beep
	ino init -t blink

	ino build -m avrm12
	ino upload -m avrm12 -p /dev/ttyAMA0

If 'ino upload' gives you verification errors, upload 'by hand':

	cd .build/avrm12
	avrdude -v -c linuxgpio -p m328p -U flash:w:firmware.hex
	cd ../..

To start a serial connection on 9600 baud:

	ino serial -p /dev/ttyAMA0 -b 9600

Find more info on using the ino tool here: [inotool.org](http://inotool.org/)
