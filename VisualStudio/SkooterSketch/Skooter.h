#ifndef _SKOOTER_ 
// prevent duplicate declaration of types, enums and static variables if this header file is included more than once
// https://en.wikipedia.org/wiki/Include_guard
#define _SKOOTER_

#include "Lidar.h" // preprocessor directives, makes all the listed libraries available to this header file
#include "PanTilt.h"
#include "Tracks.h"
#include "Cabinet.h"

class Skooter
{
public:  // functions are accessible outside of the class "Skooter"
	void setup(int forwardPin, int turnPin, int panPin, int tiltPin, int minTilt, int maxTilt); 
	void doStuff(); 
	int calTilt();
	int calingPan();
	int calPan();

private: // classes are inaccessible outside of the class "Skooter" (belong privately to the class "Skooter")
	Lidar lidar; // classes and their instances, only accessible within class "Skooter" 
	PanTilt panTilt;
	Tracks tracks;
	Cabinet cabinet;
};

#endif
