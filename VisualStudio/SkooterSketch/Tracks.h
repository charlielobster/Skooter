#ifndef _TRACKS_ 
// prevent duplicate declaration of types, enums and static variables if this header file is included more than once
// https://en.wikipedia.org/wiki/Include_guard
#define _TRACKS_

#include <Servo.h> // make the Servo header file declarations available to this class and ultimately, to the board

// declare class "Tracks"
class Tracks
{
public:	// accessible outside of the class "Tracks"

	// class consts: these values are referenced with the syntax Tracks::TYPE_NAME since they are not tied to an instance of Tracks
	// consts are "read-only" (values cannot be changed), preferred over #define for defining constants in C++ classes
	const int MOVE_SPEED = 15;
	const int TURN_SPEED = 15; 
							   
	// class instance member functions
	void attach(int f, int t); // declaration of various functions
	void turnRight();
	void turnLeft();
	void goForward();
	void goBackward();
	void stop();

private: // inaccessible outside of "Tracks"
	Servo forward; // class Servo, instance "forward" - (note: compile-time error if no #include <Servo.h>)
	Servo turn; // class Servo, instance "turn"
	int pos = 0; // data type integer (16 bits, 2 bytes), variable "pos", value "0"
};
#endif
