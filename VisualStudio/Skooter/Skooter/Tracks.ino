#include "Tracks.h"

void Tracks::attach(int f, int t)
{
	forward.attach(f);
	turn.attach(t);
	stop();
}

void Tracks::turnRight() 
{
	turn.write(90 - TURN_SPEED);
}

void Tracks::turnLeft()
{
	turn.write(90 + TURN_SPEED);
}

void Tracks::goForward() 
{
	forward.write(90 - MOVE_SPEED);
}

void Tracks::goBackward()
{
	forward.write(90 + MOVE_SPEED);
}

void Tracks::stop()
{
	forward.write(90);
	turn.write(90);
}

