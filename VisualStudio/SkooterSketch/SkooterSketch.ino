/*
 Name:		SkooterSketch.ino
 Created:	11/20/2019 1:53:19 PM
 Author:	skoob
*/
#include "Skooter.h"

Skooter skooter;

void setup() {
	skooter.setup(11, 10, 9, 6, 110, 180);
}

void loop() {
	skooter.doStuff();
}
