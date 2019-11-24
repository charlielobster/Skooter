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
	inline int minTilt() { return m_minTilt; }
	inline int maxTilt() { return m_maxTilt; }
	inline int panAngle() { return m_panAngle; }
	inline int tiltAngle() { return m_tiltAngle; }
	void panWrite(int angle);
	void tiltWrite(int angle);
	inline int calibratedPan() { return m_calibratedPan; }
	inline int calibratedTilt() { return m_calibratedTilt; }
	void setCalibratedPan(int cp);
	void setCalibratedTilt(int ct);
	void calibrate();
	
private: // inaccessible outside of the class "PanTilt"
	Servo m_pan; // declare an instance "m_pan" of the class "Servo"
	Servo m_tilt; // declare an instance "m_tilt" of the class "Servo"
	int m_minTilt; // declare a variable "m_minTilt" of data type int
	int m_maxTilt; // declare a variable "m_maxTilt" of data type int
	int m_panAngle; 
	int m_tiltAngle;
	int m_calibratedTilt;
	int m_calibratedPan;
};

#endif
