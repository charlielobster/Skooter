#ifndef _TRACKS_
#define _TRACKS_

#include <Servo.h>

class Tracks 
{
public: 
	Servo forward;
	Servo turn;
	int pos = 0;   
	void attach(int f, int t);
	void turning();
	void goForward();

};
#endif
