#ifndef _CABINET_H_
#define _CABINET_H_

#define _NAME_PREFIX_ "dat_"
#define _EXTENSION_ ".txt"

#include <SPI.h> 
#include <SD.h>
#include <SoftwareSerial.h>

typedef enum SerialState
{
    NO_ACTIVITY,
    GETTING_FILE_NAME
} SkooterSerialState;

// SD card attached to SPI bus as follows:
// CS - pin CHIP_SELECT 10
// MOSI - pin 11 on Uno
// MISO - pin 12 on Uno
// SCK - pin 13 on Uno

// ESP8266-01 TX and RX attached to pin ESP_TX_PIN and ESP_RX_PIN
class Cabinet 	
{
public:
	static const int CHIP_SELECT = 10; 
    static const int MAX_FILE_SIZE = 32000; // restrict file sizes to under 32K 
    static const int ESP_TX_PIN = 3;    // Uno RX to ESP TX
    static const int ESP_RX_PIN = 2;    // Uno TX to ESP RX
    static const int DELAY = 50;

    Cabinet();
	void setup();	
    void checkBuffer();
    void openCurrentFile();
    String getNextFileName();
	void writeLine(String s);
    void writeFileContents(String fileName);
    int writeDirectoryContents();
    void writeNextFileName(String fileName);
    void closeCurrentFile();
    void clearDirectory();
    void checkForFileName();

private:	
	File m_dataFile;
	String m_currentFileName;
    String m_requestedFileName;
    int m_fileCount;    
    SoftwareSerial m_softwareSerial;
    SkooterSerialState m_state;
};

#endif
