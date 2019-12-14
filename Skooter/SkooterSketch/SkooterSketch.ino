#include "Skooter.h"

Skooter skooter;

void setup() 
{
	Serial.begin(74880);
	skooter.setup();
}

void loop() 
{
	skooter.loop();
}
