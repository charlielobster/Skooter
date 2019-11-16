#include "Skooter.h"

void Skooter::attach(int f, int t)
{
	forward.attach(f);
	turn.attach(t);
}

void Skooter::turning() {

	for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
	  // in steps of 1 degree
		turn.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		turn.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}

}

void Skooter::goForward() {
	for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
	  // in steps of 1 degree
		forward.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		forward.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
}