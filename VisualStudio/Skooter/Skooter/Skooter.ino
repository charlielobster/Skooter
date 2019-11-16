#include "Tracks.h"

Tracks tracks;

void setup() {
	tracks.attach(9, 11);
}

void loop() {
	tracks.turnRight();				// FIXME there is a weird overlap going on here where one of the turns is affecting the other
	delay(500);
	tracks.stop();
	delay(500);
	tracks.goForward();
	delay(500);
	tracks.stop();
	delay(500);
	tracks.turnLeft();
	delay(500);
	tracks.stop();
	delay(500);
	tracks.goBackward();
	delay(500);
	tracks.stop();
	delay(500);
}
