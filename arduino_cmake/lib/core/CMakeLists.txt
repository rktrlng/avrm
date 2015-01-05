#include paths
include_directories (/usr/lib/avr/include/avr)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/boards/${BOARD_INCLUDE_DIR})
include_directories ("./")

# Create a library called "core" which includes multiple source files.
# The extension is already found. Any number of sources could be listed here.
add_library (
	core 
	STATIC 
	CDC.cpp 
	HardwareSerial.cpp 
	HID.cpp 
	IPAddress.cpp 
	main.cpp 
	malloc.c 
	new.cpp 
	Print.cpp 
	Stream.cpp 
	Tone.cpp 
	USBCore.cpp 
	WInterrupts.c 
	wiring.c 
	wiring_analog.c 
	wiring_digital.c 
	wiring_pulse.c 
	WMath.cpp 
	WString.cpp 
)
