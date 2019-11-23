#ifndef _TRACKS_ // prevents problems if someone accidentally #include's the library twice
#define _TRACKS_

#include <Servo.h> // makes Servo library available to the sketch and includes it in the code sent to the board

class Tracks // creates class "Tracks"
{
public: // declared instances and functions are accessible outside of the class "Tracks"
	const int MOVE_SPEED = 15; // instances with values of the data type const int
	const int TURN_SPEED = 15; // const=constant [Variable Scope & Qualifier], makes variables "read-only" (values cannot be changed), preferred over #define for defining constants

	void attach(int f, int t); // declaration of various functions

	void turnRight();
	void turnLeft();

	void goForward();
	void goBackward();

	void stop();

private: // declared classes and their instances, and variables are NOT accessible outside of the class "Tracks"
	Servo forward; // class Servo, instance "forward"
	Servo turn; // class Servo, instance "turn"
	int pos = 0; // data type interger (16 bits, 2 bytes), variable "pos", value "0"
};
#endif
