#ifndef _TRACKS_ 
// prevent duplicate declaration of types, enums and static variables if this header file is included more than once
// https://en.wikipedia.org/wiki/Include_guard
#define _TRACKS_

// declare class Tracks
// Tracks uses the sabertooth 2x5 rc motor driver with the following configuration:
// pin 3 is ON, 1, 2, 4, 5, 6 are OFF
// FWD and TURN orange connected to forwardPin and turnPin (see attach)
// FLIP + (red) and - (brown) connected to arduino Vin and Gnd
class Tracks
{
public:	// accessible outside of the class Tracks
	// class consts: these values are referenced with the syntax Tracks::TYPE_NAME since they are not tied to an instance of Tracks
	// consts are read-only (values cannot be changed), preferred over #define for defining constants in C++ classes
	const int MOVE_SPEED = 20;
	const int TURN_SPEED = 20; 
	const float MOVE_TIME = 100;	// unused
	const float TURN_TIME = 100;

	Tracks() : m_x(0), m_y(0), m_heading(0) {}	// default constructor 
	// : operator - set default values for member variables m_x, m_y, m_heading
	// empty {} body - in this case, constructor's only job is to assign defaults (ie. no memory allocation)
	~Tracks() {}	// ~ destructor - also empty {} body (no memory clean-up)
							   
	// class instance (member) functions - declarations of various functions
	void attach(int forwardPin, int turnPin);

	// these methods require some knowledge of the battery-level to work consistently
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

private: // inaccessible outside of Tracks
	void turnRight();
	void forward();
	void backward();
	void turnLeft();

	Servo left; // class Servo, instance forward - (note: compile-time error if no #include <Servo.h>)
	Servo right; // class Servo, instance turn
	int m_heading;
	int m_x;
	int m_y;
};
#endif
