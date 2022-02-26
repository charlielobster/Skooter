#ifndef _SKOOTER_H_
#define _SKOOTER_H_

#include "Lidar.h" 
#include "PanTilt.h"

typedef struct LidarPanTilt
{
	LidarPanTilt() : distance(9999) {}
	unsigned long timestamp;
	int distance;
	int theta; // pan
	int phi;  // tilt
} lidarPanTilt;

typedef enum SkooterState
{
	AWAKE,
	SEEKING_NEAREST_NEIGHBOR,
	SEEKING_SPIRALING_OUT,
	SEEKING_SPIRALING_IN,
	MESMERIZED,
	MESMERIZED_SPIRALING_OUT,
	MESMERIZED_SPIRALING_IN
} skooterState;

class Skooter
{
public:  
	constexpr static int SPIRAL_DELAY = 10;
	constexpr static int BEE_LINE_DELAY = 5;
	constexpr static int DELTA = 30;
	Skooter();
	void setup();
	void loop(); 
    
private: 
	Lidar lidar;
	PanTilt panTilt;

	skooterState m_state;

	lidarPanTilt m_closest;

	lidarPanTilt m_current;
	lidarPanTilt m_last;

	int m_panTiltDelay;
	double m_spiralRadius;
	double m_theta;
};

#endif
