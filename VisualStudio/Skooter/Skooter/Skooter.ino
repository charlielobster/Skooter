/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo fwdSkooter;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo turnSkooter;

int pos = 0;    // variable to store the servo position

void setup() {
	fwdSkooter.attach(9);  // attaches the servo on pin 9 to the servo object
	turnSkooter.attach(11);
}

void turning() {

	for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
	  // in steps of 1 degree
		turnSkooter.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		turnSkooter.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}

}

void forward() {
	for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
	  // in steps of 1 degree
		fwdSkooter.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		fwdSkooter.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
}

void loop() {
	turning();
}
