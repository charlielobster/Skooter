#ifndef _PANTILT_ 
// prevent duplicate declaration of types, enums and static variables if this header file is included more than once
// https://en.wikipedia.org/wiki/Include_guard
#define _PANTILT_

#include <Servo.h> // include the declarations made in the Servo.h header file

class PanTilt // declare class "PanTilt"
{
public: // accessible outside of the class "PanTilt"
	// function declarations
	void attach(int p, int t);
	void setTiltRange(int minT, int maxT);
	void lookPan();
	void lookTilt();
	void lookScan();
	int getMinTilt();
	int getMaxTilt();
	int getPanAngle();
	int getTiltAngle();
	void panWrite(int angle);
	void tiltWrite(int angle);
	int getCalibratedPan();
	int getCalibratedTilt();
	void setCalibratedPan(int cp);
	void setCalibratedTilt(int ct);
	void calibrate();
	
private: 
	// inaccessible outside of the class "PanTilt"
	Servo pan; // declare an instance "pan" of the class "Servo"
	Servo tilt; // declare an instance "tilt" of the class "Servo"
	int minTilt; // create a variable "minTilt" of data type "int"
	int maxTilt; // create a variable "maxTilt" of data type "int"
	int panAngle; 
	int tiltAngle;
	int calibratedTilt;
	int calibratedPan;
};

#endif
