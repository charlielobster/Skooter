#include "Lidar.h"

void Lidar::setup() {
	eye.begin(0, true);
}

int Lidar::measure() 
{
	return eye.distance();
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

