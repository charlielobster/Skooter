#ifndef _TRACKS_ // prevents problems if someone accidentally #include's the library twice
#define _TRACKS_

#include <Servo.h> // makes Servo library available to the sketch and includes it in the code sent to the board

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

private: // NOT accessible outside of the class "Tracks"
	Servo forward; // class Servo, instance "forward"
	Servo turn; // class Servo, instance "turn"
	int pos = 0; // data type integer (16 bits, 2 bytes), variable "pos", value "0"
};
#endif
