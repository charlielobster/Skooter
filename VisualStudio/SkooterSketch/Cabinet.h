#ifndef _CABINET_
#define _CABINET_

#include <SPI.h>
#include <SD.h>

class Cabinet
{
public:
	//SD card attached to SPI bus as follows:
	//** MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
	//** MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
	//** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
	//** CS - pin 10

	// set up variables using the SD utility library functions:
	Sd2Card card;
	SdVolume volume;
	SdFile root;

	// change this to match your SD shield or module;
	// Arduino Ethernet shield: pin 4
	// Adafruit SD shields and modules: pin 10
	// Sparkfun SD shield: pin 8
	// MKRZero SD: SDCARD_SS_PIN
	const int chipSelect = 10;
	void setup();
	void writePosition(float x, float y, float forwardAngle, float panAngle, float tiltAngle, int distance);
};

#endif
