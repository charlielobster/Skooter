#ifndef _PANTILT_ // prevents problems if someone accidentally #include's the library twice
#define _PANTILT_

#include <Servo.h> // grants header file access to the library "Servo"

class PanTilt // creates the class "PanTilt"
{
public: // functions are accessible outside of the class "PanTilt"
	void attach(int p, int t); // declaration of functions
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
	
private: // instances and variables are NOT inaccessible outside of the class "PanTilt"
	Servo pan; // creates the instance "pan" of the class "Servo"
	Servo tilt; // creates the instance "tilt" of the class "Servo"
	int minTilt; // creates a variable "minTilt" of data type "int"
	int maxTilt; // creates a variable "maxTilt" of data type "int"
	int panAngle; 
	int tiltAngle;
	int calibratedTilt;
	int calibratedPan;
};

#endif
