#include paths
include_directories (/usr/lib/avr/include/avr)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/boards/${BOARD_INCLUDE_DIR})
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/core)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/Wire) # needed for Adafruit_MCP23017

include_directories (Adafruit_MCP23017)
include_directories (IRremote)
include_directories (MIDI)
include_directories (OneWire)
include_directories (Ping)

# Create a library called "custom" which includes multiple source files.
# The extension is already found. Any number of sources could be listed here.
add_library (
	custom 
	STATIC 
	Adafruit_MCP23017/Adafruit_MCP23017.cpp 
	IRremote/IRremote.cpp 
	MIDI/MIDI.cpp 
	OneWire/OneWire.cpp 
	Ping/Ping.cpp 
)
