#include "Skooter.h"

Skooter skooter;
long i = 0;

void setup()
{
	Serial.begin(9600);
	skooter.setup(5, 3, 9, 6, 28, 118);
	Serial.println("setup");
}

void loop()
{
	Serial.println("loop: " + String(i) + " " + String(millis(), DEC));
	skooter.doStuff();
	i++;
}