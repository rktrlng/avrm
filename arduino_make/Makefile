#######################################################################
#                   Arduino Makefile for the AVRM                     #
#                                                                     #
#                      Based on the Makefile by:                      #
#         Paulo H. "Taka" Torrens <paulo_torrens@hotmail.com>         #
#            https://github.com/takanuva/arduino-makefile             #
#                                                                     #
#       This is using Arduino 1.0.2, but without the USB stuff        #
#######################################################################

PROGRAMMER = linuxgpio
MCU = atmega328p
F_CPU = 8000000
FORMAT = ihex

OUTPUT = project

CC = avr-gcc $(CPP_FLAGS)
LD = avr-gcc $(LD_FLAGS)
AR = avr-ar $(AR_FLAGS)
OBJCP = avr-objcopy
SIZE = avr-size -A --mcu=$(MCU)
AVRDUDE = avrdude

LIBRARIES = arduino.a
OBJECTS = src/main.o
INCLUDES = -I/usr/lib/avr/include/avr -I./include -Isrc -Ilib/arduino
DEFINES = -DF_CPU=$(F_CPU)L

CPP_FLAGS = -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) $(DEFINES) $(INCLUDES)
LD_FLAGS = -Os -Wl,--gc-sections -mmcu=$(MCU)
AR_FLAGS = rcs

all: $(LIBRARIES) $(OUTPUT).hex

arduino.a: lib/arduino/wiring_pulse.o lib/arduino/WInterrupts.o lib/arduino/main.o lib/arduino/wiring_analog.o lib/arduino/Tone.o lib/arduino/HardwareSerial.o lib/arduino/wiring_digital.o lib/arduino/pins_arduino.o lib/arduino/Print.o lib/arduino/wiring_shift.o lib/arduino/WMath.o lib/arduino/WString.o lib/arduino/wiring.o lib/arduino/new.o lib/arduino/Stream.o lib/arduino/IPAddress.o
	$(AR) arduino.a lib/arduino/wiring_pulse.o
	$(AR) arduino.a lib/arduino/WInterrupts.o
	$(AR) arduino.a lib/arduino/main.o
	$(AR) arduino.a lib/arduino/wiring_analog.o
	$(AR) arduino.a lib/arduino/Tone.o
	$(AR) arduino.a lib/arduino/HardwareSerial.o
	$(AR) arduino.a lib/arduino/wiring_digital.o
	$(AR) arduino.a lib/arduino/pins_arduino.o
	$(AR) arduino.a lib/arduino/Print.o
	$(AR) arduino.a lib/arduino/wiring_shift.o
	$(AR) arduino.a lib/arduino/WMath.o
	$(AR) arduino.a lib/arduino/WString.o
	$(AR) arduino.a lib/arduino/wiring.o
	$(AR) arduino.a lib/arduino/new.o
	$(AR) arduino.a lib/arduino/Stream.o
	$(AR) arduino.a lib/arduino/IPAddress.o

lib/arduino/wiring_pulse.o: lib/arduino/wiring_pulse.c
	$(CC) -c lib/arduino/wiring_pulse.c -o lib/arduino/wiring_pulse.o

lib/arduino/WInterrupts.o: lib/arduino/WInterrupts.c
	$(CC) -c lib/arduino/WInterrupts.c -o lib/arduino/WInterrupts.o

lib/arduino/main.o: lib/arduino/main.cpp
	$(CC) -c lib/arduino/main.cpp -o lib/arduino/main.o

lib/arduino/wiring_analog.o: lib/arduino/wiring_analog.c
	$(CC) -c lib/arduino/wiring_analog.c -o lib/arduino/wiring_analog.o

lib/arduino/Tone.o: lib/arduino/Tone.cpp
	$(CC) -c lib/arduino/Tone.cpp -o lib/arduino/Tone.o

lib/arduino/HardwareSerial.o: lib/arduino/HardwareSerial.cpp
	$(CC) -c lib/arduino/HardwareSerial.cpp -o lib/arduino/HardwareSerial.o

lib/arduino/wiring_digital.o: lib/arduino/wiring_digital.c
	$(CC) -c lib/arduino/wiring_digital.c -o lib/arduino/wiring_digital.o

lib/arduino/pins_arduino.o: lib/arduino/pins_arduino.c
	$(CC) -c lib/arduino/pins_arduino.c -o lib/arduino/pins_arduino.o

lib/arduino/Print.o: lib/arduino/Print.cpp
	$(CC) -c lib/arduino/Print.cpp -o lib/arduino/Print.o

lib/arduino/wiring_shift.o: lib/arduino/wiring_shift.c
	$(CC) -c lib/arduino/wiring_shift.c -o lib/arduino/wiring_shift.o

lib/arduino/WMath.o: lib/arduino/WMath.cpp
	$(CC) -c lib/arduino/WMath.cpp -o lib/arduino/WMath.o

lib/arduino/WString.o: lib/arduino/WString.cpp
	$(CC) -c lib/arduino/WString.cpp -o lib/arduino/WString.o

lib/arduino/wiring.o: lib/arduino/wiring.c
	$(CC) -c lib/arduino/wiring.c -o lib/arduino/wiring.o

lib/arduino/new.o: lib/arduino/new.cpp
	$(CC) -c lib/arduino/new.cpp -o lib/arduino/new.o

lib/arduino/Stream.o: lib/arduino/Stream.cpp
	$(CC) -c lib/arduino/Stream.cpp -o lib/arduino/Stream.o

lib/arduino/IPAddress.o: lib/arduino/IPAddress.cpp
	$(CC) -c lib/arduino/IPAddress.cpp -o lib/arduino/IPAddress.o

src/main.o: src/main.cpp
	$(CC) -c src/main.cpp -o src/main.o

$(OUTPUT).elf: $(OBJECTS) $(LIBRARIES)
	$(LD) $(OBJECTS) $(LIBRARIES) -lm -o $(OUTPUT).elf

$(OUTPUT).hex: $(OUTPUT).elf
	$(OBJCP) -O ihex -R .eeprom $(OUTPUT).elf $(OUTPUT).hex
	$(SIZE) $(OUTPUT).hex
  
.PHONY: flash clean

flash: all
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -Uflash:w:$(OUTPUT).hex:i -v
	./reset_gpio.sh

clean:
	@rm -f $(LIBRARIES) $(OUTPUT).elf $(OUTPUT).hex $(shell find . -follow -name "*.o")

