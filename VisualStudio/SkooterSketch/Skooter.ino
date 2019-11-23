#include "Skooter.h" // gives source file "Skooter" access to the library "Skooter.h"

void Skooter::setup(int forwardPin, int turnPin, int panPin, int tiltPin, int minTilt, int maxTilt) // function "setup" (initializes variables, pin modes, start using libraries, etc.) belongs to class "Skooter"  
{
	cabinet.setup(); // calls the function "setup" to the variable (instance), cabinet, which belongs to the class "Cabinet", which belongs, privately, to the class "Skooter"
	//tracks.attach(forwardPin, turnPin);
	//panTilt.attach(panPin, tiltPin);
	//panTilt.setTiltRange(minTilt, maxTilt);
	//lidar.setup();
}

void Skooter::doStuff() // function "do stuff" belongs to the class "Skooter"
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
int calTilt() {
  int calibratedTilt = minTilt;
  float minDistance = 9999.9;

  pan.write(calibratedPan);
  delay(250);
  tilt.write(calibratedTilt);
  delay(250);

  for (int tiltAngle = minTilt; tiltAngle <= maxTilt; tiltAngle++) {
    tilt.write(tiltAngle);
    delay(15);

    int sum = eye.distance();
    for (int i = 0; i < 9; i++) {
      sum = sum + eye.distance(false);
    }
    float avgDistance = sum / 10.0;

    if (avgDistance < minDistance) {
      minDistance = avgDistance;
      calibratedTilt = tiltAngle;
    }

  }

  tilt.write(calibratedTilt);
  delay(250);
  
  return calibratedTilt;
}


int calingPan() {
  int calibratedPan = 0;
  float minDistance = 9999.9;

  pan.write(calibratedPan);
  delay(250);
  tilt.write(calibratedTilt);
  delay(250);

  for (int panAngle = 0; panAngle < 180; panAngle++) {
    pan.write(panAngle);
    delay(15);

    int sum = eye.distance();
    for (int i = 0; i < 9; i++) {
      sum = sum + eye.distance(false);
    }
    float avgDistance = sum / 10.0;

    if (avgDistance < minDistance) {
      minDistance = avgDistance;
      calibratedPan = panAngle;
    }

  }

  pan.write(calibratedPan);
  delay(250);
  
  return calibratedPan;

}

int calPan() {
  calingPan();
  while (calibratedPan < 85 || calibratedPan > 95) {
    if (calibratedPan < 85) {
      tracks.turnLeft(90-/*calibratedPan*/); //FIXME turnRight has to be able to take in a degree and turn long enough to reach that degree then stop
    }
    else if (calibratedPan > 95) {
      tracks.turnRight(180-/*calibratedPan*/); //FIXME as above and also check which direction each one is
    }
    calingPan();
  }
  
  return calibratedPan;
}
