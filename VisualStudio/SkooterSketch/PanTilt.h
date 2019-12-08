#ifndef _PANTILT_H_
#define _PANTILT_H_

#include <Servo.h> 

class PanTilt 
{
public: 
	static const int PAN_PIN = 9;
	static const int TILT_PIN = 6;
	static const int MIN_TILT = 28;
	static const int MAX_TILT = 118;

	void setup();
	inline int panAngle() { return m_panAngle; }
	inline int tiltAngle() { return m_tiltAngle; }
	void panWrite(int angle);
	void tiltWrite(int angle);
	inline int calibratedPan() { return m_calibratedPan; }
	inline int calibratedTilt() { return m_calibratedTilt; }
	void setCalibratedPan(int cp);
	void setCalibratedTilt(int ct);
	void calibrate();
	
private: 
	Servo m_pan; 
	Servo m_tilt; 
	int m_panAngle; 
	int m_tiltAngle;
	int m_calibratedTilt;
	int m_calibratedPan;
};

#endif
