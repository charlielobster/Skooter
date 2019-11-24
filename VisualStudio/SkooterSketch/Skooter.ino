#include "Skooter.h" // gives source file "Skooter" access to the library "Skooter.h"

// function "setup" (initializes variables, pin modes, start using libraries, etc.) belongs to class "Skooter"  
void Skooter::setup(int forwardPin, int turnPin, int panPin, int tiltPin, int minTilt, int maxTilt)
{
	cabinet.setup(); // calls the function "setup" to the variable (instance), cabinet, which belongs to the class "Cabinet", which belongs, privately, to the class "Skooter"
	//tracks.attach(forwardPin, turnPin);
	//panTilt.attach(panPin, tiltPin);
	//panTilt.setTiltRange(minTilt, maxTilt);
	//lidar.setup();
}

// function "do stuff" belongs to the class "Skooter"
void Skooter::doStuff()
{
//	cabinet.writePosition(x, y, forwardAngle, panAngle, tiltAngle, d);
	//panTilt.lookPan();
	//delay(500);
	//panTilt.lookTilt();
	//delay(500);

	//int d = lidar.measure();
	//Serial.println(d);
	//delay(5);

	//tracks.turnRight();
	//delay(500);
	//tracks.stop();
	//delay(500);
	//tracks.goForward();
	//delay(500);
	//tracks.stop();
	//delay(500);
	//tracks.turnLeft();
	//delay(500);
	//tracks.stop();
	//delay(500);
	//tracks.goBackward();
	//delay(500);
	//tracks.stop();

	//delay(500);
}

// the function "lookPan" belongs to the class Skooter
void Skooter::lookPan()
{
	for (int a = 0; a < 180; a++) { // for loop: for (initialization; condition; increment) {}
		panTilt.panWrite(a);
		delay(25);
	} // pans the lidar 180 degrees, in steeps of 1, and then delays for 25 ms
}

// the function "lookTilt" belonds to the class "Skooter"
void Skooter::lookTilt()
{
	for (int a = panTilt.minTilt(); a < panTilt.maxTilt(); a++) { // lidar tilts (rotates about its azimuthal angle) from the angle "minTilt" to the angle "maxTilt" in steps of "tiltAngle"
		panTilt.tiltWrite(a); // calls the function "write" (writes a value of 'tiltAngle' to the servo) to the variable (instance), of type Servo, "tilt"
		delay(25); // delays for 25 ms

	}
}

// the function "lookScan" belongs to the class "Skooter"
void Skooter::lookScan()
{
	// Skooter goes to its zeroes
	panTilt.calibrate();

	for (int t = panTilt.minTilt(); t <= panTilt.maxTilt(); t++) {
		panTilt.tiltWrite(t);
		for (int p = 0; p <= 180; p++) { // pans the lidar horizontally (parallel to the plane in which Skooter rests) 180 degrees in steps of "panAngle"
			panTilt.panWrite(p); // calls the function "write" (writes the value of "panAngle" passed in from the for loop to the step servo) to the variable (instance), of type Servo, "pan"
			cabinet.writeLidarData(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.measure());
		}
		t++; // increments the "tiltAngle" in steps of "tiltAngle" (seems superfluous, imo)
		panTilt.tiltWrite(t); // calls the function "write" (writes a value of "tiltAngle" passed in from the for loop to the step servo) to the variable (instance) "tilt"
		for (int p = 180; p >= 0; p--) { // pans the lidar from 180 degrees to 0 in steps of "panAngle"
			panTilt.panWrite(p); // calls the function "write" (writes a value of "panAngle" passed in from the for loop to the step servo) to the variable (instance) of "pan"
			cabinet.writeLidarData(tracks.x(), tracks.y(), tracks.heading(), t, p, lidar.measure());
		}
	}
	panTilt.calibrate();
}

//FIXME ONLY RUN IF IN FRONT OF WALL
int Skooter::calTilt() 
{
	int minTilt = panTilt.minTilt();
	int maxTilt = panTilt.maxTilt();
	int calibratedTilt = minTilt;
	float minDistance = 9999.9;

	panTilt.tiltWrite(calibratedTilt);
	delay(250);

  for (int tiltAngle = minTilt; tiltAngle <= maxTilt; tiltAngle++) {
    panTilt.tiltWrite(tiltAngle);
    delay(15);

    int sum = lidar.measure();
    for (int i = 0; i < 9; i++) {
		sum = sum + lidar.measure();
    }
    float avgDistance = sum / 10.0;

    if (avgDistance < minDistance) {
      minDistance = avgDistance;
      calibratedTilt = tiltAngle;
    }

  }

  panTilt.setCalibratedTilt(calibratedTilt);
  
  return calibratedTilt;
}


int Skooter::calingPan() 
{
  int calibratedPan = 0;
  float minDistance = 9999.9;

  panTilt.calibrate();
  delay(50);

  for (int panAngle = 0; panAngle < 180; panAngle++) {
    panTilt.panWrite(panAngle);
    delay(15);

    int sum = lidar.measure();
    for (int i = 0; i < 9; i++) {
      sum = sum + lidar.measure();
    }
    float avgDistance = sum / 10.0;

    if (avgDistance < minDistance) {
      minDistance = avgDistance;
      calibratedPan = panAngle;
    }

  }
	
  panTilt.setCalibratedPan(calibratedPan);
  
  return calibratedPan;

}

int Skooter::calPan() 
{
  //calingPan();
  //while (calibratedPan < 85 || calibratedPan > 95) {
  //  if (calibratedPan < 85) {
  //    tracks.turnLeft(90-/*calibratedPan*/); //FIXME turnRight has to be able to take in a degree and turn long enough to reach that degree then stop
  //  }
  //  else if (calibratedPan > 95) {
  //    tracks.turnRight(180-/*calibratedPan*/); //FIXME as above and also check which direction each one is
  //  }
  //  calingPan();
  //}
  //
  //return calibratedPan;
}
