#include "Cabinet.h" // gives this sketch access to the definitions in the header file "Cabinet.h"

void Cabinet::setup() // the function setup belongs to the class Cabinet
{
	if (!SD.begin(CHIP_SELECT)) {
		Serial.println("initialization failed!");
	}
}

void Cabinet::writeLine(String s)
{
	m_dataFile = SD.open("readings.txt", FILE_WRITE); //opens file for reading and writing

	// if the file opened okay, write to it:
	if (m_dataFile) {		
		// save into file
		m_dataFile.println(s);
		// close the file:
		m_dataFile.close();
	}
	else {
		// if the file didn't open, print an error:
		Serial.println("error opening readings.txt");
	}
}

void Cabinet::writeFileToSerial()
{
	String s = "";
	m_dataFile = SD.open("readings.txt");
	if (m_dataFile) {
		while (m_dataFile.available()) {
			s = m_dataFile.readStringUntil('\n');
			Serial.println(s);
		}
		m_dataFile.close();
	}
}
