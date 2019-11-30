#include "Tracks.h" // gives this implementation file access to the definitions in the header file "Tracks.h"

// the function attach belongs to the class Tracks
// the use of the :: operator indicates a class-level declaration (ie. it is a definition shared by all the instances of this class)

void Tracks::attach(int forwardPin, int turnPin)
{
	left.attach(turnPin, 1000, 2000); // calls the function attach (attaches Servo variable to a pin) to the variable, of type Servo, forward
	right.attach(forwardPin, 1000, 2000); // calls the function attach to the variable (instance), of type Servo, turn
}

// the function turnRight belongs to the class Tracks
void Tracks::turnRight()
{
	right.write(90 - TURN_SPEED); // calls the function write to the variable (instance), of type Servo, turn
	left.write(90 + TURN_SPEED); // calls the function write to the variable (instance), of type Servo, turn
}

// the function turnLeft belongs to the class Tracks
void Tracks::turnLeft()
{
	right.write(90 + TURN_SPEED); // call the function write (writes a value (speed) to the continuoius rotation servo) to the variable (instance), of type Servo, turn; argument of write is a speed
	left.write(90 - TURN_SPEED); // call the function write (writes a value (speed) to the continuoius rotation servo) to the variable (instance), of type Servo, turn; argument of write is a speed
}

// the function goForward belongs to the class Tracks
void Tracks::forward()
{
	left.write(90 - MOVE_SPEED); // calls the function write to the variable (instance), of type Servo, forward
	right.write(90 - MOVE_SPEED); // calls the function write to the variable (instance), of type Servo, forward
}

// the function goBackward belongs to the class Tracks
void Tracks::backward()
{
	left.write(90 + MOVE_SPEED); // calls the function write to the variable (instance), of type Servo, forward
	right.write(90 + MOVE_SPEED); // calls the function write to the variable (instance), of type Servo, forward
}

// the function stop belongs to the class Tracks
void Tracks::stop()
{
	left.write(90); // calls the function write to the variable (instance), of type Servo, forward
	right.write(90); // calls the function write to the variable (instance, of type Servo, turn
}

//turnToAngle, goForward, goBackward use the above to control Skooter

// 90 means turn Skooter 90 degrees to the right, -90 means turn Skooter 90 degrees to the left
void Tracks::turnToAngle(int angle)
{
	if (angle < 0) {
		clockwiseTurn(-angle);
	}
	else {
		counterClockwiseTurn(angle);
	}
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

void Tracks::clockwiseCircle()
{
	right.write(40);
	left.write(130);
	delay(10750);
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
