#include <LIDARLite.h>
#include "Tracks.h"
#include "Lidar.h"
#include "PanTilt.h"

Tracks tracks;
PanTilt panTilt;
Lidar lidar;

void setup() 
{
	tracks.attach(11, 10);
	panTilt.attach(9, 6);
	panTilt.setTiltRange(110, 180);
	lidar.setup();
}

void loop() {

	panTilt.lookPan();
	delay(500);
	panTilt.lookTilt();
	delay(500);

	int d = lidar.measure();
	Serial.println(d);
	delay(5);

	tracks.turnRight();				
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
