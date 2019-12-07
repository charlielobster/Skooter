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
// ** CS - pin CHIP_SELECT

class Cabinet // declaration of the class Cabinet
{
public:
	static const int CHIP_SELECT = 10; 
	
	// lidarData: declare an instance of the class File 
	// (a class contains consts, member functions, and member variables)
	
	// function declarations : return type void (no objects returned)
	void setup();	// SD.begin(CHIP_SELECT)
	void writeLine(String s);
	void writeFileToSerial();

private:
	File m_dataFile;

};

#endif
