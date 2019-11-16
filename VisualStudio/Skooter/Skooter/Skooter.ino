#include "Skooter.h"

Skooter skooter;


void setup() {
	skooter.attach(9, 11);
}

void loop() {
	skooter.turning();
}
