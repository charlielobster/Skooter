#ifndef _SKOOTER_H_
#define _SKOOTER_H_

#include "Lidar.h" 
#include "PanTilt.h"
#include "Tracks.h"
#include "Cabinet.h"
#include "NoiseMaker.h"

class Skooter
{
public:  
	void setup(); 
	void doStuff(); 
	int calibrateTilt();
	int calingPan();
	int calPan();
	void lookPan();
	void lookTilt();
	void lookScan();

private: 
	Lidar lidar;
	PanTilt panTilt;
	Tracks tracks;
	Cabinet cabinet;
	NoiseMaker noiseMaker;

	bool doSomething = true;
};

#endif
