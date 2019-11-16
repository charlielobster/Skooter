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
	//delay(10);
	//for (pos = 0; pos <= 90; pos += 1) {	// Skooter slows down from max speed to null (90)
	//	turn.write(pos);
	//	delay(10);							// slows down behavior FIXME make this into a variable we can control
	//}
	//for (pos = 90; pos >= 0; pos -= 1) {	// Skooter speeds up from null (90)
	//	turn.write(pos);
	//	delay(10);							// FIXME use variable described above
	//}
}

void Tracks::turnLeft()
{
	turn.write(90 + TURN_SPEED);
	//for (pos = 90; pos <= 180; pos += 1) {	// Skooter speeds up from null (90) to max
	//	turn.write(pos);
	//	delay(10);							// slows down behavior FIXME make this into a variable we can control
	//}
	//for (pos = 180; pos >= 90; pos -= 1) {// Skooter slows down from max to null (90)
	//	turn.write(pos);
	//	delay(10);							// FIXME use variable described above
	//}
}

void Tracks::goForward() 
{
	forward.write(90 - MOVE_SPEED);
	//for (pos = 0; pos <= 90; pos += 1) {
	//	forward.write(pos);              
	//	delay(10);                       
	//}
	//for (pos = 90; pos >= 0; pos -= 1) { 
	//	forward.write(pos);              
	//	delay(10);                       
	//}
}

void Tracks::goBackward()
{
	forward.write(90 + MOVE_SPEED);
	//for (pos = 90; pos <= 180; pos += 1) {	// Skooter speeds up from null (90) to max
	//	forward.write(pos);
	//	delay(10);							// slows down behavior FIXME make this into a variable we can control
	//}
	//for (pos = 180; pos >= 90; pos -= 1) {	// Skooter slows down from max to null (90)
	//	forward.write(pos);
	//	delay(10);							// FIXME use variable described above
	//}
}

void Tracks::stop()
{
	forward.write(90);
	turn.write(90);
}
