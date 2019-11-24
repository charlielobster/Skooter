#ifndef _TRACKS_ 
// prevent duplicate declaration of types, enums and static variables if this header file is included more than once
// https://en.wikipedia.org/wiki/Include_guard
#define _TRACKS_

#include <Servo.h> // make the Servo header file declarations available to this class and ultimately, to the board

// declare class Tracks
class Tracks
{
public:	// accessible outside of the class Tracks
	// class consts: these values are referenced with the syntax Tracks::TYPE_NAME since they are not tied to an instance of Tracks
	// consts are read-only (values cannot be changed), preferred over #define for defining constants in C++ classes
	const int MOVE_SPEED = 15;
	const int TURN_SPEED = 15; 

	Tracks() : m_x(0), m_y(0), m_heading(0) {}	// default constructor 
	// : operator - set default values for member variables m_x, m_y, m_heading
	// empty {} body - in this case, constructor's only job is to assign defaults (ie. no memory allocation)
	~Tracks() {}	// ~ destructor - also empty {} body (no memory clean-up)
							   
	// class instance (member) functions - declarations of various functions
	void attach(int f, int t);
	void turnRight();
	void turnLeft();
	void turnToAngle(int angle);
	void goForward();
	void goBackward();
	void stop();
	inline int heading() { return m_heading; }
	inline int x() { return m_x; }
	inline int y() { return m_y; }

private: // inaccessible outside of Tracks
	Servo forward; // class Servo, instance forward - (note: compile-time error if no #include <Servo.h>)
	Servo turn; // class Servo, instance turn
	int m_heading;
	int m_x;
	int m_y;
};
#endif
