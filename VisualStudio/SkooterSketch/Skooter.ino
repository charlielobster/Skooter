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

//FIXME ONLY RUN IF IN FRONT OF WALL
int Skooter::calTilt() 
{
	int minTilt = panTilt.getMinTilt();
	int maxTilt = panTilt.getMaxTilt();
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
