#ifndef _CABINET_ // prevents problems if someone accidentally #include's the library twice
#define _CABINET_

#include <SPI.h> // includes the libraries "SPI" and "SD" making them accesible to the header file "Cabinet.h"
#include <SD.h>

class Cabinet // creation of the class "Cabinet"
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

  File lidarData; // creates an instance (lidarData) of the class "File"; a class contains functions and variables
  
	void setup();
 
	void writePosition(float x, float y, float forwardAngle, float panAngle, float tiltAngle, int distance); // function declaration "void"=data type

  // Serial.begin(9600);s
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("Initialization failed!");
    while (1); // creates and infinite loop
  }
  Serial.println("Initialization complete.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  lidarData = SD.open("readings.txt", FILE_WRITE); //opens file for reading and writing

  // if the file opened okay, write to it:
  if (lidarData) {
    Serial.print("Writing to readings...");
    lidarData.println("testing 1, 2, 3.");
    // close the file:
    lidarData.close();
    Serial.println("Complete.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening readings.txt");
  }

  // re-open the file for reading:
  lidarData = SD.open("readings.txt");
  if (lidarData) {
    Serial.println("readings.txt:");

    // read from the file until there's nothing else in it:
    while (lidarData.available()) {
      Serial.write(lidarData.read());
    }
    // close the file:
    lidarData.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening readings.txt");
  }
}

void loop() {
  // nothing happens after setup
}
};

#endif
