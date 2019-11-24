#ifndef _SKOOTER_ 
// prevent duplicate declaration of types, enums and static variables if this header file is included more than once
// https://en.wikipedia.org/wiki/Include_guard
#define _SKOOTER_

// preprocessor directives: make all the declarations, types, static variables, etc in these header files available to this header file
#include "Lidar.h" 
#include "PanTilt.h"
#include "Tracks.h"
#include "Cabinet.h"

class Skooter
{
public:  // accessible outside of the class "Skooter"
	void setup(int forwardPin, int turnPin, int panPin, int tiltPin, int minTilt, int maxTilt); 
	void doStuff(); 
	int calTilt();
	int calingPan();
	int calPan();
	void lookPan();
	void lookTilt();
	void lookScan();

private: // inaccessible outside of the class "Skooter" (these belong privately to instances of this class, "Skooter")
	// lidar, panTilt, tracks, and cabinet are instances of their classes, only accessible within this class, "Skooter" 
	Lidar lidar;
	PanTilt panTilt;
	Tracks tracks;
	Cabinet cabinet;
};

#endif
