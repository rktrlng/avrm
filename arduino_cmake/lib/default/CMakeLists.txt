#include paths
include_directories (/usr/lib/avr/include/avr)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/boards/${BOARD_INCLUDE_DIR})
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/core)

include_directories ("EEPROM/")
include_directories ("Esplora/")
include_directories ("Ethernet/")
include_directories ("Ethernet/utility/")
include_directories ("Firmata/")
include_directories ("LiquidCrystal/")
include_directories ("SD/")
include_directories ("SD/utility/")
include_directories ("Servo/")
include_directories ("SoftwareSerial/")
include_directories ("SPI/")
include_directories ("Stepper/")
#include_directories ("WiFi/")
#include_directories ("WiFi/utility/")
include_directories ("Wire/")
include_directories ("Wire/utility/")

# Create a library called "default" which includes multiple source files.
# The extension is already found. Any number of sources could be listed here.
add_library (
	default 
	STATIC 
	EEPROM/EEPROM.cpp 
	Esplora/Esplora.cpp 
	Ethernet/Dhcp.cpp 
	Ethernet/Dns.cpp 
	Ethernet/Ethernet.cpp 
	Ethernet/EthernetClient.cpp 
	Ethernet/EthernetServer.cpp 
	Ethernet/EthernetUdp.cpp 
	Ethernet/utility/socket.cpp 
	Ethernet/utility/w5100.cpp 
	Firmata/Firmata.cpp 
	LiquidCrystal/LiquidCrystal.cpp 
	Servo/Servo.cpp 
	SD/SD.cpp 
	SD/File.cpp 
	SD/utility/Sd2Card.cpp 
	SD/utility/SdFile.cpp 
	SD/utility/SdVolume.cpp 
	SoftwareSerial/SoftwareSerial.cpp 
	Stepper/Stepper.cpp 
	SPI/SPI.cpp 
#	WiFi/WiFi.cpp 
#	WiFi/WiFiClient.cpp 
#	WiFi/WiFiServer.cpp 
#	WiFi/utility/server_drv.cpp 
#	WiFi/utility/socket.c 
#	WiFi/utility/spi_drv.cpp 
	Wire/Wire.cpp 
	Wire/utility/twi.c 
)
