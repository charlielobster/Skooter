#include "Skooter.h" // gives this source file access to the declared types, enums, and static variables in "Skooter.h"

// function setup (initializes variables, pin modes, start using libraries, etc.) belongs to class Skooter  
void Skooter::setup(int forwardPin, int turnPin, int panPin, int tiltPin, int minTilt, int maxTilt)
{
//	cabinet.setup(); // calls the function setup to the variable (instance), cabinet, which belongs to the class Cabinet, which belongs, privately, to the class Skooter
	tracks.attach(forwardPin, turnPin);
	//panTilt.attach(panPin, tiltPin);
	//panTilt.setTiltRange(minTilt, maxTilt);
	//lidar.setup();
}

// function do stuff belongs to the class Skooter
void Skooter::doStuff()
{
	tracks.goForward(5);
	delay(5000);
}

// the function lookPan belongs to the class Skooter
void Skooter::lookPan()
{
	// for loop: for (initialization; condition; increment) {}
	for (int a = 0; a <= 180; a++) {
		panTilt.panWrite(a);
		delay(25);
		cabinet.writeLidarData(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
	} 
}

// the function lookTilt belonds to the class Skooter
void Skooter::lookTilt()
{
	// lidar tilts (rotates about its azimuthal angle) from the angle minTilt to the angle maxTilt in steps of 1
	for (int a = panTilt.minTilt(); a <= panTilt.maxTilt(); a++) {
		// call the PanTilt instance panTilt's function tiltWrite, with the value of a 
		panTilt.tiltWrite(a);
		delay(25); // delays for 25 ms
		cabinet.writeLidarData(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
	}
}

// the function lookScan belongs to the class Skooter
void Skooter::lookScan()
{
	// panTilt goes to its zeroes
	panTilt.calibrate();
	delay(250);

	for (int t = panTilt.minTilt(); t <= panTilt.maxTilt(); t++) {
		
		panTilt.tiltWrite(t);

		// pan the lidar along a plane which deviates from a plane parallel with the floor by the angle (tiltAngle - calibratedAngle)
		// collect 181 readings between 0 and 180 degrees, in steps of 1
		for (int p = 0; p <= 180; p++) {

			// call the PanTilt instance panTilt's function panWrite, with the value of p
			panTilt.panWrite(p);
			// write the lidar distance, tracks, and panTilt related data to the cabinet...
			cabinet.writeLidarData(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
		}

		t++; // increment t again

		// call the PanTilt instance panTilt's function tiltWrite, with the value of t 
		panTilt.tiltWrite(t);

		// pan the lidar along a plane which deviates from a plane parallel with the floor by the angle (tiltAngle - calibratedAngle)
		// collect 181 readings between 180 degrees and 0 degrees, in steps of 1
		for (int p = 180; p >= 0; p--) {
			// call PanTilt instance panTilt's function panWrite, with the value of p 
			panTilt.panWrite(p);
			// write the lidar distance, tracks, and panTilt related data to the cabinet...
			cabinet.writeLidarData(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
		}
	}
	panTilt.calibrate();
}

//FIXME ONLY RUN IF IN FRONT OF WALL
int Skooter::calibrateTilt() 
{
	int calibratedTilt = -1;
	float minDistance = 9999.9;

	panTilt.calibrate();
	delay(250);

	for (int tiltAngle = panTilt.minTilt(); tiltAngle <= panTilt.maxTilt(); tiltAngle++) {

		panTilt.tiltWrite(tiltAngle);
		delay(50);

		int sum = lidar.distance();
		for (int i = 0; i < 9; i++) {
			sum += lidar.distance();
		}
		float avgDistance = sum / 10.0;

		if (avgDistance < minDistance) 
		{
			minDistance = avgDistance;
			calibratedTilt = tiltAngle;
		}
	}

	panTilt.setCalibratedTilt(calibratedTilt);
  
	return calibratedTilt;
}

int Skooter::calingPan() 
{
	int calibratedPan = -1;
	float minDistance = 9999.9;

	panTilt.calibrate();
	delay(50);

	for (int a = 0; a <= 180; a++) {

		panTilt.panWrite(a);
		delay(15);

		int sum = lidar.distance();
		for (int i = 0; i < 9; i++) {
			sum += lidar.distance();
		}
		float avgDistance = sum / 10.0;

		if (avgDistance < minDistance) 
		{
			minDistance = avgDistance;
			calibratedPan = a;
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
  //    tracks.turnLeft(90-/*calibratedPan*/); 
  //	FIXME turnRight has to be able to take in a degree and turn long enough to reach that degree then stop
  //  }
  //  else if (calibratedPan > 95) {
  //    tracks.turnRight(180-/*calibratedPan*/); 
  //	FIXME as above and also check which direction each one is
  //  }
  //  calingPan();
  //}
  //
  //return calibratedPan;
}
