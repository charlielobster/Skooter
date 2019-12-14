#ifndef _TRACKS_H_
#define _TRACKS_H_

#include <Servo.h>

// Tracks uses the sabertooth 2x5 rc motor driver with the following configuration:
// pin 3 is ON, 1, 2, 4, 5, 6 are OFF
// FWD and TURN orange connected to forwardPin and turnPin (see attach)
// FLIP + (red) and - (brown) connected to arduino Vin and Gnd
class Tracks
{
public:	
	static const int MOVE_SPEED = 20;
	static const int TURN_SPEED = 20; 
	static const int MOVE_TIME = 100;	// unused
	static const int TURN_TIME = 100;
	static const int FORWARD_PIN = 5;
	static const int TURN_PIN = 4;

	Tracks();
	~Tracks() {}

	void setup();
	void turnToAngle(int angle);
	void clockwiseTurn(int angle);
	void clockwiseCircle();
	void counterClockwiseTurn(int angle);
	void counterClockwiseCircle();

	void goForward(int units);
	void goBackward(int units);
	void stop();

	inline int heading() { return m_heading; }
	inline int x() { return m_x; }
	inline int y() { return m_y; }

private: 
	void turnRight();
	void forward();
	void backward();
	void turnLeft();

	Servo left; 
	Servo right; 
	int m_heading;
	int m_x;
	int m_y;
};
#endif
