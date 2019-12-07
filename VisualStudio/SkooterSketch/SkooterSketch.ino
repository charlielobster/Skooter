#include "Skooter.h"
#include "LidarData.h"

Cabinet cabinet;
Skooter skooter;
long i = 0;

void setup()
{
	Serial.begin(9600);
//	skooter.setup(5, 3, 9, 6, 28, 118);
	Serial.println("setup");
	cabinet.setup();
	int cabinetChipSelect = Cabinet::CHIP_SELECT;
}

void loop()
{
	if (i == 0) {

		LidarData ld;
		ld.x = 732;
		ld.y = 73;
		ld.heading = 710;
		ld.theta = 75;
		ld.phi = 790;
		ld.d = 70;

		cabinet.writeLine(ld.toString());

		Serial.println("wrote this lidarData to cabinet");
		Serial.println(ld.toString());

		Serial.println("writing contents of cabinet file to serial...");
		String s;

		cabinet.writeFileToSerial();

		//	skooter.doStuff();
		Serial.println("loop: " + String(i) + " " + String(millis(), DEC));
	}

	i++;
}