#include "Tracks.h" // gives this implementation file access to the definitions in the header file "Tracks.h"

// the function "attach" belongs to the class "Tracks"
// the use of the :: operator indicates a class-level declaration (ie. it is a definition "shared" by all the instances of this class)
void Tracks::attach(int f, int t)
{
	forward.attach(f); // calls the function "attach" (attaches Servo variable to a pin) to the variable, of type Servo, forward
	turn.attach(t); // calls the function "attach" to the variable (instance), of type Servo, turn
}

// the function "turnRight" belongs to the class "Tracks"
void Tracks::turnRight()
{
	turn.write(90 + TURN_SPEED); // calls the function "write" to the variable (instance), of type Servo, "turn"
}

// the function "turnLeft" belongs to the class "Tracks"
void Tracks::turnLeft()
{
	turn.write(90 - TURN_SPEED); // calls the function "write" (writes a value (speed) to the continuoius rotation servo) to the variable (instance), of type Servo, "turn"; argument of write is a speed
}

// the function "goForward" belongs to the class "Tracks"
void Tracks::goForward()
{
	forward.write(90 + MOVE_SPEED); // calls the function "write" to the variable (instance), of type Servo, "forward"
}

// the function "goBackward" belongs to the class "Tracks"
void Tracks::goBackward()
{
	forward.write(90 - MOVE_SPEED); // calls the function "write" to the variable (instance), of type Servo, "forward"
}

// the function "stop" belongs to the class "Tracks"
void Tracks::stop()
{
	forward.write(90); // calls the function "write" to the variable (instance), of type Servo, "forward"
	turn.write(90); // calls the function "write" to the variable (instance, of type Servo, "turn"
}
