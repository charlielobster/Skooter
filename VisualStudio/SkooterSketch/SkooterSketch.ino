/*
 Name:		SkooterSketch.ino
 Created:	11/20/2019 1:53:19 PM
 Author:	skoob
*/
#include "Skooter.h"

Skooter skooter;

void setup() {
	skooter.setup(5, 3, 9, 6, 28, 118);
}

void loop() {
	skooter.doStuff();
}
