#ifndef _PANTILT_H_
#define _PANTILT_H_

#include <Servo.h> 

class PanTilt 
{
public: 
  constexpr static int PAN_PIN = 6;
  constexpr static int TILT_PIN = 9;
  constexpr static int MIN_TILT = 28;
  constexpr static int MAX_TILT = 180;  
  constexpr static int LEVEL_TILT = 35;
  constexpr static int HALF_TILT = 71;
  constexpr static int UP_TILT = 125;
  constexpr static int PAN_CENTER = 90;

	PanTilt() : 
		m_panAngle(PAN_CENTER),
		m_tiltAngle(LEVEL_TILT) {}

	void setup();
	void panWrite(int angle);
	void tiltWrite(int angle);
	inline int panAngle() { return m_panAngle; }
	inline int tiltAngle() { return m_tiltAngle; }

private: 
	Servo m_pan; 
	Servo m_tilt; 
	int m_panAngle; 
	int m_tiltAngle;
};

#endif
