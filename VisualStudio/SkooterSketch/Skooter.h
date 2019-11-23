#ifndef _SKOOTER_ // prevents problems if someone accidentally #include's the library twice
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
private: // classes are inaccessible outside of the class "Skooter" (belong privately to the class "Skooter")
	Lidar lidar; // classes and their instances, only accessible within class "Skooter" 
	PanTilt panTilt;
	Tracks tracks;
	Cabinet cabinet;
};

#endif
