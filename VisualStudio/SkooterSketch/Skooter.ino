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
