#ifndef _CABINET_H_
// prevent duplicate declaration of types, enums and static variables if this header file is included more than once
// https://en.wikipedia.org/wiki/Include_guard
#define _CABINET_H_

#include <SPI.h> // include the SPI and SD header files, making their declarations, types, and static variables accesible to this header file, "Cabinet.h"
#include <SD.h>

#include "LidarData.h"

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKRZero SD: SDCARD_SS_PIN
// SD card attached to SPI bus as follows:
// ** MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
// ** MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
// ** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
// ** CS - pin 10

class Cabinet // declaration of the class Cabinet
{
public:
	const int CHIP_SELECT = 10; 
	
	File lidarData; 
	// lidarData: declare an instance of the class File 
	// (a class contains consts, member functions, and member variables)
	
	// function declarations : return type void (no objects returned)
	void setup();	// set up variables using the SD utility library functions
	void writeLidarData(int x, int y, int heading, int theta, int phi, int d); 
	void writeLidarData(const LidarData &ld); // write a LidarData
	String readLineAtPosition(int position);
	String readNextLine();

private:
	Sd2Card card;
	SdVolume volume;
	SdFile root;
};

#endif
