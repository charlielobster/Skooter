#ifndef _SKOOTER_H_
#define _SKOOTER_H_

#include <Servo.h>
#include "LIDARLite.h" 

constexpr static int MAX_DISTANCE = 32767;
constexpr static int PAN_PIN = 6;
constexpr static int TILT_PIN = 9;
constexpr static int MIN_TILT = 30;
constexpr static int LEVEL_TILT = 35;
constexpr static int START_TILT = 55;
constexpr static int UP_TILT = 125;
constexpr static int MAX_TILT = 180; 
constexpr static int MIN_PAN = 20; // 10;
constexpr static int PAN_CENTER = 90;
constexpr static int MAX_PAN = 160; // 170;
constexpr static int WAKE_DELAY = 100000;
constexpr static int MIN_EDGE_DELTA = 40;
constexpr static int SMALL_MOVE_DELAY = 25;
constexpr static int LARGE_MOVE_DELAY = 1500;

typedef struct LidarEvent
{
	LidarEvent() : distance(MAX_DISTANCE), pan(0) {}
	int distance;
	int pan;
} lidarEvent;

// Skooter is a state-machine to circumvent delay() calls
typedef enum SkooterState
{
	AWAKE,
	STOP_MOVING,
	FINDING_CLOSEST,
	MOVING_TO_CLOSEST,
	FINDING_LEFT_EDGE,
	FINDING_RIGHT_EDGE,
	CORRECTING_LEFT,
	CORRECTING_RIGHT
} skooterState;

class Skooter
{
public:  
	Skooter();
	void setup();
	void loop(); 
    
private: 
	void getLidarEvent();
	void tryPanningRight();
	void tryPanningLeft();
	void moveToClosest();

	LIDARLite m_lidar;
	Servo m_pan;
	Servo m_tilt;

	skooterState m_state;

	lidarEvent m_current;	// as opposed to the current hit
	lidarEvent m_closest;	// the closest hit, presumably an object with left and right edges
	lidarEvent m_leftEdge;	// right edge pan angle < left edge pan angle, 
	lidarEvent m_rightEdge;	// since the angles are from Skooter's point of view
	lidarEvent m_lastHit;	// last hit on the nearest object 

	// sprintf to m_lineBuffer to format logs
	char m_lineBuffer[80];
};

#endif
