/**
 * Always include core library
 * 
 */
#include <Arduino.h>

/**
 * Optionally, include custom libraries
 * 
 */
//#include <Adafruit_MCP23017.h>
//#include <IRremote.h>
//#include <MIDI.h>
//#include <Ping.h>

/**
 * Optionally, include extra libraries
 * 
 */
//#include <EEPROM.h>
//#include <Ethernet.h>
//#include <Firmata.h>
//#include <LiquidCrystal.h>
//#include <SD.h>
//#include <Servo.h>
//#include <SoftwareSerial.h> // untested for 12MHz gertboard
//#include <SPI.h>
//#include <Stepper.h>
//#include <WiFi.h> // TODO: fix
//#include <Wire.h>
//#include <Esplora.h> // Enable Esplora in Makefile

/**
 * Your arduino 'sketch' goes below
 * 
 */
int led1 = 13; // 13 9 10 3 5 6 
int led2 = 5;

void setup() {
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	Serial.begin(9600);
}

void loop() {
	digitalWrite(led1, HIGH);
	digitalWrite(led2, LOW);
	Serial.write("tick\r\n");
	delay(500);

	digitalWrite(led1, LOW);
	digitalWrite(led2, HIGH);
	Serial.write("tock\r\n");
	delay(500);
}
