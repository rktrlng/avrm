all:
	avra main.asm -l main.lst -m main.map -o main.hex

flash: all
	avrdude -v -c linuxgpio -p atmega328p -U flash:w:main.hex

clean:
	rm *.cof
	rm *.hex
	rm *.obj
	rm *.lst
	rm *.map
