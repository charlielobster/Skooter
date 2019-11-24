#include "Tracks.h" // gives this implementation file access to the definitions in the header file "Tracks.h"

void Tracks::attach(int f, int t) // the function "attach" belongs to the class (::)  "Tracks"
{
	forward.attach(f); // calls the function "attach" (attaches Servo variable to a pin) to the variable, of type Servo, forward
	turn.attach(t); // calls the function "attach" to the variable (instance), of type Servo, turn
}

void Tracks::turnRight() // the function "turnRight" belongs to the class (::) "Tracks"
{
	turn.write(90 + TURN_SPEED); // calls the function "write" to the variable (instance), of type Servo, "turn"
}

void Tracks::turnLeft() // the function "turnLeft" belongs to the class (::) "Tracks"
{
	turn.write(90 - TURN_SPEED); // calls the function "write" (writes a value (speed) to the continuoius rotation servo) to the variable (instance), of type Servo, "turn"; argument of write is a speed
}

void Tracks::goForward() // the function "goForward" belongs to the class "Tracks"
{
	forward.write(90 + MOVE_SPEED); // calls the function "write" to the variable (instance), of type Servo, "forward"
}

void Tracks::goBackward() // the function "goBackward" belongs to the class (::) "Tracks"
{
	forward.write(90 - MOVE_SPEED); // calls the function "write" to the variable (instance), of type Servo, "forward"
}

void Tracks::stop() // the function "stop" belongs to the class (::) "Tracks"
{
	forward.write(90); // calls the function "write" to the variable (instance), of type Servo, "forward"
	turn.write(90); // calls the function "write" to the variable (instance, of type Servo, "turn"
}
