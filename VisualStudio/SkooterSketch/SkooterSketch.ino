#include "Skooter.h"

static long i = 0;

Skooter skooter;

void setup() {
	Serial.begin(9600);
	skooter.setup(5, 3, 9, 6, 28, 118);
	Serial.println("setup");
}

void loop() {

	if (i == 0) {
		skooter.doStuff();
		Serial.println("loop: " + String(i) + " " + String(millis(), DEC));
	}

	i++;
}