#ifndef _CABINET_H_
#define _CABINET_H_

#define _NAME_PREFIX_ "skdata_"
#define _EXTENSION_ ".txt"

#include <SPI.h> 
#include <SD.h>
#include <SoftwareSerial.h>

typedef enum CabinetState
{
    NO_ACTIVITY = 0,
	OPENING_CURRENT_FILE,
	OPENING_REQUESTED_FILE,
	WRITING_TO_CURRENT_FILE
} cabinetState;

// SD card attached to SPI bus as follows:
// CS - pin CHIP_SELECT 10
// MOSI - pin 11 on Uno
// MISO - pin 12 on Uno
// SCK - pin 13 on Uno

// ESP8266-01 TX and RX attached to pin ESP_TX_PIN and ESP_RX_PIN
class Cabinet 	
{
public:
	static const bool CLEAR_DIRECTORY_AT_SETUP = true;
	static const int CHIP_SELECT = 10; 
    static const int MAX_FILE_SIZE = 4096; // restrict file sizes to under 4K 
    static const int ESP_TX_PIN = 3;    // Uno RX to ESP TX
    static const int ESP_RX_PIN = 2;    // Uno TX to ESP RX
    static const int DELAY = 50;

    Cabinet();
	void setup();	
    void loop();
	void writeLine(String line);
	inline cabinetState state() { return m_state;  }

private:	
    void clearDirectory();
    void writeDirectoryContents();
    void writeCurrentFileName();
    void openCurrentFile();
    void writeToCurrentFile();
    void checkForFileName();   
    void checkIfRequestedFileIsOpen();

	int m_fileCount;
    int m_requestedFileNameIndex;
	File m_currentFile;
	char m_currentFileName[13];
    char m_requestedFileName[13];
	char m_currentLine[40];
    int m_currentLineIndex;
    SoftwareSerial m_softwareSerial;
	cabinetState m_state;
};

#endif
