#ifndef _SKOOTER_
#define _SKOOTER_

#include "Lidar.h"
#include "PanTilt.h"
#include "Tracks.h"
#include "Cabinet.h"

class Skooter
{
public:
	void setup(int forwardPin, int turnPin, int panPin, int tiltPin, int minTilt, int maxTilt);
	void doStuff();
private:
	Lidar lidar;
	PanTilt panTilt;
	Tracks tracks;
	Cabinet cabinet;
};

#endif
