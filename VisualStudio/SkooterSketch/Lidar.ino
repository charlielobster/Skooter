#include "Lidar.h" // allows the source file "Lidar" access to the library "Lidar.h"

void Lidar::setup() { // the function "setup" belongs to the class "Lidar"
	eye.begin(0, true); 
}

int Lidar::distance() // the function "measure" belongs to the class (::) "Lidar"
{
	return eye.distance(); // returns the function "distance" which is called to the variable (instance) "eye"
}

//void loop() {
//	//FIXME constantly check for distance in front of Scooter
//	//limit determines the distance at which Scooter will stop to look around
//	int limit = 500;
//	if (dist <= limit) {
//		//lookPan();
//	}
//}
//void setup() {
//	//LIDAR Setup
//	// Initialize serial connection to display distance readings, example gives 115200
//	Serial.begin(9600);
//	// Set to default config (0) and I2C to 400 kHz (true)
//	eyeScooter.begin(0, true);
//	// 0=default, 1=short,hispd, 2=default,hispd,loacc, 3=maxrange, 4=hisensitivity, 5=losensitivity
//	//FIXME is this unecessary? --> eyeScooter.configure(0);
//	//Servo Setup
//	// attaches 3 to the servo object
//	servoPan.attach(3);
//	servoTilt.attach(5);
//	lookPan();
//	lookTilt(angleInterest);
//}
