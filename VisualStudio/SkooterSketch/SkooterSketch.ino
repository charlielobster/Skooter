#include "Skooter.h"

Skooter skooter;

void setup()
{
	Serial.begin(9600);
	skooter.setup(5, 3, 9, 6, 28, 118);
}

void loop()
{
	skooter.doStuff();
}