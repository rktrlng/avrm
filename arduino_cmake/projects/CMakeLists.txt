# Make sure the compiler can find the header files for the 'board'.
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/boards/${BOARD_INCLUDE_DIR})

# Make sure the compiler can find the header files for the 'core' library.
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/core)

# Make sure the compiler can find the header files for the 'default' library.
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/EEPROM)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/Esplora)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/Ethernet)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/Ethernet/utility)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/Firmata)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/LiquidCrystal)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/SD)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/Servo)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/SoftwareSerial)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/SPI)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/Stepper)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/WiFi)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/WiFi/utility)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/Wire)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/default/Wire/utility)

# Make sure the compiler can find the header files for the 'custom' library.
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/custom/Adafruit_MCP23017)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/custom/IRremote)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/custom/MIDI)
include_directories (${ARDUINO_LIB_SOURCE_DIR}/${ARDUINO_LIB_DIR}/custom/Ping)

# Recurse further into the "project" subdirectories.
add_subdirectory (blinky)
add_subdirectory (combined)
add_subdirectory (i2cslave)
add_subdirectory (keyboard)
add_subdirectory (ping)
add_subdirectory (tinybasic)
