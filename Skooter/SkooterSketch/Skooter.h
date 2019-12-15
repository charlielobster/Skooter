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
    static const int DELAY = 10;
    static const int SHORT_DELAY = 0;
    static const double DELTA = .75;
    static const double MINIMUM_AVERAGES = 4;
    static const int MOTION_SCAN_RATE = 4;
    static const int SCAN_INCREMENT = 2;
    static const int MIN_DISTANCE = 150;
	void setup();
	void loop(); 
	//int calibrateTilt();
	//int calingPan();
	//int calPan();
	void pan(int increment);
	void tilt(int increment);
	void scan(int increment);
    void doMotionScan();
 //   void checkBuffer();
    
private: 
	Lidar lidar;
	PanTilt panTilt;
	Tracks tracks;
	Cabinet cabinet;
	NoiseMaker noiseMaker;

	long i = 0;
    int currentDistance = 0;
	bool doSomething = true;
};

#endif
