#include "MotorSkooter.h"

MotorSkooter skooter;

void setup() 
{
	Serial.begin(38400);
	skooter.setup();
}

void loop() 
{
//	skooter.loop();
}
