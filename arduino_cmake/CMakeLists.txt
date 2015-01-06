## We're cross-compiling, so set the compiler BEFORE project()
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> csr <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> csr <TARGET> <LINK_FLAGS> <OBJECTS>")

# The name of our project is "ARDUINO_LIB". CMakeLists files in this project can
# refer to the root source directory of the project as ${ARDUINO_LIB_SOURCE_DIR}
# and to the root binary directory of the project as ${ARDUINO_LIB_BINARY_DIR}.
cmake_minimum_required(VERSION 2.6)
project(ARDUINO_LIB)
set(ARDUINO_VERSION 103)

################################################################################
#                            START BOARD OPTIONS                               #
################################################################################

# Supported BOARD_TYPE options: 
# standard, avrm8, avrm12, avrm32u4, gertboard, gertduino, leonardo, custom
set(BOARD_TYPE avrm8)

if (BOARD_TYPE MATCHES standard)
	set(BOARD_INCLUDE_DIR standard)
	set(MCU atmega328p)
	set(F_CPU 16000000)
	add_definitions(-DUSB_VID=0x0000 -DUSB_PID=0x0000)
	set(PROGRAMMER stk500v1)
	set(PORT /dev/ttyACM0)
	set(UPLOAD_RATE 57600)
	set(MESSAGE 'upload with: make flash_<projectname>')
elseif (BOARD_TYPE MATCHES avrm8)
	set(BOARD_INCLUDE_DIR standard)
	set(MCU atmega328p)
	set(F_CPU 8000000)
	add_definitions(-DUSB_VID=0x0000 -DUSB_PID=0x0000)
	set(PROGRAMMER linuxgpio)
	set(PORT 0)				# unused, but must be set
	set(UPLOAD_RATE 0)		# unused, but must be set
	set(MESSAGE 'upload with: make gpio_<projectname>')
elseif (BOARD_TYPE MATCHES avrm12)
	set(BOARD_INCLUDE_DIR standard)
	set(MCU atmega328p)
	set(F_CPU 12000000)
	add_definitions(-DUSB_VID=0x0000 -DUSB_PID=0x0000)
	set(PROGRAMMER linuxgpio)
	set(PORT 0)				# unused, but must be set
	set(UPLOAD_RATE 0)		# unused, but must be set
	set(MESSAGE 'upload with: make gpio_<projectname>')
elseif (BOARD_TYPE MATCHES avrm32u4)
	set(BOARD_INCLUDE_DIR leonardo)
	set(MCU atmega32u4)
	set(F_CPU 16000000)
	set(PROGRAMMER linuxgpio)
	set(PORT 0)				# unused, but must be set
	set(UPLOAD_RATE 0)		# unused, but must be set
	set(USB_PID 0x8036)
	set(USB_VID 0x2341)
	add_definitions(-DUSB_VID=${USB_VID} -DUSB_PID=${USB_PID} -DUSBCON)
	set(MESSAGE 'upload with: make gpio_<projectname>')
elseif (BOARD_TYPE MATCHES gertboard)
	set(BOARD_INCLUDE_DIR standard)
	set(MCU atmega328p)
	set(F_CPU 12000000)
	add_definitions(-DUSB_VID=0x0000 -DUSB_PID=0x0000)
	set(PROGRAMMER linuxgpio)
	set(PORT 0)				# unused, but must be set
	set(UPLOAD_RATE 0)		# unused, but must be set
	set(MESSAGE 'upload with: make gpio_<projectname>')
elseif (BOARD_TYPE MATCHES gertduino)
	set(BOARD_INCLUDE_DIR standard)
	set(MCU atmega328p)
	set(F_CPU 16000000)
	add_definitions(-DUSB_VID=0x0000 -DUSB_PID=0x0000)
	set(PROGRAMMER linuxgpio)
	set(PORT 0)				# unused, but must be set
	set(UPLOAD_RATE 0)		# unused, but must be set
	set(MESSAGE 'upload with: make gpio_<projectname>')
elseif(BOARD_TYPE MATCHES leonardo)
	set(BOARD_INCLUDE_DIR leonardo)
	set(MCU atmega32u4)
	set(F_CPU 16000000)
	add_definitions(-DUSB_VID=0x2341 -DUSB_PID=0x8036 -DUSBCON)
	set(PROGRAMMER avr109)
	set(PORT /dev/ttyACM0)
	set(UPLOAD_RATE 57600)
	set(MESSAGE 'upload with: make flash_<projectname>')
elseif(BOARD_TYPE MATCHES custom)
	set(BOARD_INCLUDE_DIR leonardo)
	set(MCU atmega32u4)
	set(F_CPU 16000000)
	add_definitions(-DUSB_VID=0x03EB -DUSB_PID=0x2066 -DUSBCON)
	set(PROGRAMMER dfu)		# unused, but must be set
	set(PORT 0)				# unused, but must be set
	set(UPLOAD_RATE 0)		# unused, but must be set
	set(MESSAGE 'upload with: make dfu_<projectname>')
else()
	set(MCU atmega32u4)
	set(F_CPU 16000000)
	set(USB_PID 0x8036)
	set(USB_VID 0x2341)
	add_definitions(-DUSB_VID=${USB_VID} -DUSB_PID=${USB_PID} -DUSBCON)
	set(MESSAGE 'upload with: make flash_* !!WARNING!! NO BOARD DEFINED !!WARNING!!')
endif()
################################################################################
#                             END BOARD OPTIONS                                #
################################################################################

add_definitions(-DF_CPU=${F_CPU}L -DARDUINO=${ARDUINO_VERSION})

set(C_FLAGS "-g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=${MCU}")
set(LD_FLAGS "-Os -Wl,--gc-sections -mmcu=${MCU} -L.")

set(CMAKE_CXX_FLAGS ${C_FLAGS})
set(CMAKE_C_FLAGS ${C_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS ${LD_FLAGS})

set(UNEXPORT_SCR_PATH ${ARDUINO_LIB_SOURCE_DIR}/lib/boards)
MACRO(POST_PROCESS prog chip port baud)
	ADD_CUSTOM_TARGET(${PRJ_NAME}.hex 
		make && 
		avr-objcopy -O ihex -R .eeprom ${PRJ_NAME}.elf ${HEX_PATH} && 
		avr-size -A --mcu=${MCU} ${HEX_PATH} &&
		echo ${MESSAGE}
	)
	ADD_CUSTOM_TARGET(flash_${PRJ_NAME} 
		make ${PRJ_NAME}.hex && 
		avrdude -p ${chip} -c ${prog} -P ${port} -b ${baud} -D -U flash:w:${HEX_PATH}:i -v
	)
	ADD_CUSTOM_TARGET(gpio_${PRJ_NAME} 
		make ${PRJ_NAME}.hex && 
		avrdude -p ${chip} -c ${prog} -U flash:w:${HEX_PATH}:i -v &&
		cd ${UNEXPORT_SCR_PATH} &&
		./reset_gpio.sh
	)
	ADD_CUSTOM_TARGET(dfu_${PRJ_NAME} 
		make ${PRJ_NAME}.hex && 
		dfu-programmer ${chip} erase &&
		dfu-programmer ${chip} flash ${HEX_PATH}
	)
	ADD_CUSTOM_TARGET(clean_${PRJ_NAME} 
		make clean &&
		rm ${HEX_PATH}
	)
ENDMACRO(POST_PROCESS)

# Recurse into the "lib" and "projects" subdirectories.
set(ARDUINO_LIB_DIR lib)

add_subdirectory (${ARDUINO_LIB_DIR})
add_subdirectory (projects)
