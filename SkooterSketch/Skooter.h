#ifndef _SKOOTER_H_
#define _SKOOTER_H_

#include <Servo.h>
#include "LIDARLite.h" 

constexpr static int PAN_PIN = 6;
constexpr static int TILT_PIN = 9;
constexpr static int MIN_TILT = 30;
constexpr static int LEVEL_TILT = 35;
constexpr static int START_TILT = 60;
constexpr static int UP_TILT = 125;
constexpr static int MAX_TILT = 180;
constexpr static int PAN_CENTER = 90;
//	constexpr static int SPIRAL_DELAY = 10;
//	constexpr static int BEE_LINE_DELAY = 5;
//	constexpr static int DELTA = 30;

typedef struct LidarEvent
{
	LidarEvent() : timestamp(0), distance(32767), pan(0), tilt(0) {}
	unsigned long timestamp;
	int distance;
	int pan; // pan
	int tilt;  // tilt
} lidarEvent;

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
	Skooter();
	void setup();
	void loop(); 
    
private: 
	LIDARLite m_lidar;
	Servo m_pan;
	Servo m_tilt;

	skooterState m_state;

	lidarEvent m_closest;
	lidarEvent m_current;
	lidarEvent m_last;

//	int m_panTiltDelay;
//	double m_spiralRadius;
//	double m_theta;
};

#endif
