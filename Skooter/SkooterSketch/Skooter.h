#ifndef _SKOOTER_H_
#define _SKOOTER_H_

#include "Lidar.h" 
#include "PanTilt.h"
#include "Tracks.h"
//#include "Cabinet.h"
#include "NoiseMaker.h"

typedef enum SkooterState
{
    AWAKE,
    SCAN_PANNING,
    SCAN_TILTING,
    SCAN_GETTING_AVERAGE,
    SCAN_TAKING_MEASUREMENT,
    SCAN_WRITING_TO_FILE,
    TAKING_MEASUREMENT,
    DONE
} skooterState;

class Skooter
{
public:  
    static const int DELAY = 20;
    static const int SHORT_DELAY = 5;
    static const double DELTA = .5;
    static const double MINIMUM_AVERAGES = 4;
    static const int MOTION_SCAN_RATE = 4;
    static const int SCAN_INCREMENT = 2;
    static const int MIN_DISTANCE = 150;
    Skooter();
	void setup();
	void loop(); 
    
private: 
	Lidar lidar;
	PanTilt panTilt;
	Tracks tracks;
//	Cabinet cabinet;
	NoiseMaker noiseMaker;

    skooterState m_state;
    int m_delay;
    int m_scanTiltAngle;
    int m_scanPanAngle;
    double m_avgReading; 
    int m_currentReading;   
    int m_numReadings;
    bool m_scanningLeft;
    bool m_scanningUp;
};

#endif
