#include "Cabinet.h" // gives this sketch access to the definitions in the header file "Cabinet.h"

void Cabinet::setup() // the function "setup" belongs to the class "Cabinet"
{
	// Open serial communications and wait for port to open:


	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}


	Serial.print("\nInitializing SD card...");

	// we'll use the initialization code from the utility libraries
	// since we're just testing if the card is working!
	if (!card.init(SPI_HALF_SPEED, chipSelect)) {
		Serial.println("initialization failed. Things to check:");
		Serial.println("* is a card inserted?");
		Serial.println("* is your wiring correct?");
		Serial.println("* did you change the chipSelect pin to match your shield or module?");
		while (1);
	}
	else {
		Serial.println("Wiring is correct and a card is present.");
	}

	// print the type of card
	Serial.println();
	Serial.print("Card type:         ");
	switch (card.type()) {
	case SD_CARD_TYPE_SD1:
		Serial.println("SD1");
		break;
	case SD_CARD_TYPE_SD2:
		Serial.println("SD2");
		break;
	case SD_CARD_TYPE_SDHC:
		Serial.println("SDHC");
		break;
	default:
		Serial.println("Unknown");
	}

	// Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
	if (!volume.init(card)) {
		Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
		while (1);
	}

	Serial.print("Clusters:          ");
	Serial.println(volume.clusterCount());
	Serial.print("Blocks x Cluster:  ");
	Serial.println(volume.blocksPerCluster());

	Serial.print("Total Blocks:      ");
	Serial.println(volume.blocksPerCluster() * volume.clusterCount());
	Serial.println();

	// print the type and size of the first FAT-type volume
	uint32_t volumesize;
	Serial.print("Volume type is:    FAT");
	Serial.println(volume.fatType(), DEC);

	volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
	volumesize *= volume.clusterCount();       // we'll have a lot of clusters
	volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
	Serial.print("Volume size (Kb):  ");
	Serial.println(volumesize);
	Serial.print("Volume size (Mb):  ");
	volumesize /= 1024;
	Serial.println(volumesize);
	Serial.print("Volume size (Gb):  ");
	Serial.println((float)volumesize / 1024.0);

	Serial.println("\nFiles found on the card (name, date and size in bytes): ");
	root.openRoot(volume);

	// list all files in the card with date and size
	root.ls(LS_R | LS_DATE | LS_SIZE);
}

int Cabinet::writePosition(int x, int y, int heading, int theta, int phi, int d)
{

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
	}
	else {
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
	}
	else {
		// if the file didn't open, print an error:
		Serial.println("error opening readings.txt");
	}
};