#ifndef _TRACKS_
#define _TRACKS_

#include <Servo.h>

class Tracks 
{
public: 
	const int MOVE_SPEED = 15;
	const int TURN_SPEED = 15;

	void attach(int f, int t);

	void turnRight();
	void turnLeft();

	void goForward();
	void goBackward();
	void stop();

private:
	Servo forward;
	Servo turn;
	int pos = 0;
};
#endif
