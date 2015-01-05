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



// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void receiveEvent(int howMany);

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  
  Serial.write("Ready...\r\n");
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

