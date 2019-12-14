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
	void loop(); 
	//int calibrateTilt();
	//int calingPan();
	//int calPan();
	void pan(int increment);
	void tilt(int increment);
	void scan(int increment);
 //   void checkBuffer();
    
private: 
	Lidar lidar;
	PanTilt panTilt;
	Tracks tracks;
	Cabinet cabinet;
	NoiseMaker noiseMaker;

	long i = 0;
	bool doSomething = true;
};

#endif
