#include "Tracks.h"

Tracks tracks;

void setup() {
	tracks.attach(9, 11);
}

void loop() {
	tracks.goForward();
}
