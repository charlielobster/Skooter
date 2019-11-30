#include "Tracks.h" 

void Tracks::attach(int forwardPin, int turnPin)
{
	left.attach(turnPin, 1000, 2000); 
	right.attach(forwardPin, 1000, 2000); 
}

void Tracks::turnRight()
{
	right.write(90 - TURN_SPEED); 
	left.write(90 + TURN_SPEED); 
}

void Tracks::turnLeft()
{
	right.write(90 + TURN_SPEED); 
	left.write(90 - TURN_SPEED); 
}

void Tracks::forward()
{
	left.write(90 - MOVE_SPEED);
	right.write(90 - MOVE_SPEED); 
}

void Tracks::backward()
{
	left.write(90 + MOVE_SPEED);
	right.write(90 + MOVE_SPEED);
}

void Tracks::stop()
{
	left.write(90);
	right.write(90);
}

// 90 means turn Skooter 90 degrees to the left, -90 means turn Skooter 90 degrees to the right
void Tracks::turnToAngle(int angle)
{
	// trinary operator a ? b : c is equivalent to if (a) b; else c;
	(angle < 0 ? clockwiseTurn(-angle) : counterClockwiseTurn(angle) );
}

void Tracks::clockwiseTurn(int angle)
{
	int d = floor(angle * 10250.0 / 360.0);
	right.write(40);
	left.write(130);
	delay(d);
	left.write(90);
	right.write(90);
}

void Tracks::counterClockwiseTurn(int angle)
{
	int d = floor(angle * 11000.0 / 360.0);
	right.write(130);
	left.write(40);
	delay(d);
	left.write(90);
	right.write(90);
}

void Tracks::clockwiseCircle()
{
	right.write(40);
	left.write(130);
	delay(10750);
	left.write(90);
	right.write(90);
}

void Tracks::counterClockwiseCircle()
{
	right.write(130);
	left.write(40);
	delay(11250);
	left.write(90);
	right.write(90);
}

void Tracks::goForward(int units)
{
	forward();
	delay(units * MOVE_TIME);
	stop();
}

void Tracks::goBackward(int units)
{
	backward();
	delay(units * MOVE_TIME);
	stop();
	//  delay(MINIMUM_WAIT_TIME);
}
