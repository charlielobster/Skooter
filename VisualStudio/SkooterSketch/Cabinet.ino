#include "Cabinet.h" // gives this sketch access to the definitions in the header file "Cabinet.h"

void Cabinet::setup() // the function setup belongs to the class Cabinet
{
	// we'll use the initialization code from the utility libraries
	// since we're just testing if the card is working!
	if (!card.init(SPI_HALF_SPEED, CHIP_SELECT)) {
		Serial.println("initialization failed");
		return;
	}

	// Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
	if (!volume.init(card)) {
		Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
		return;
	}

	root.openRoot(volume);
}

void Cabinet::writeLidarData(int x, int y, int heading, int theta, int phi, int d)
{
	char data[100]; // buffer for a line in the file

	if (!SD.begin(10)) {
		Serial.println("Initialization failed!");
		return;
	}

	lidarData = SD.open("readings.txt", FILE_WRITE); //opens file for reading and writing

	// if the file opened okay, write to it:
	if (lidarData) {
		// use sprintf to create a formatted string of data comprising one line of 6 comma-separated values
		sprintf(data, "%d,%d,%d,%d,%d,%d", x, y, heading, theta, phi, d);
		// print to monitor
		Serial.println(data);
		// save into file
		lidarData.println(data);
		// close the file:
		lidarData.close();
	}
	else {
		// if the file didn't open, print an error:
		Serial.println("error opening readings.txt");
	}
}

String Cabinet::readNextLine()
{
	lidarData = SD.open("readings.txt");
	//lidarData.fileposition...
	return "";
}

String Cabinet::readLineAtPosition(int position)
{
	String s = "";
	// re-open the file for reading:
	lidarData = SD.open("readings.txt");

	// if the lidarData instance is returning something not 0 and position is inside the file 
	// and we successfully went to it with a call to seek()... 
	// whew! sometimes the code is a lot easier to write than to explain!
	if (lidarData && position < lidarData.size() && lidarData.seek(position)) 
	{ 
		// read the string we find at position...
		s = lidarData.readStringUntil('\n');
		// close the file:
		lidarData.close();
	}
	else 
	{
		// if the file didn't open, print an error:
		Serial.println("error opening readings.txt");
	}
	// whether we found something or not, return a String
	return s;
}
