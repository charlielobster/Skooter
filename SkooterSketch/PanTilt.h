#ifndef _PANTILT_H_
#define _PANTILT_H_

#include <Servo.h> 

class PanTilt
{
public:
	constexpr static int PAN_PIN = 6;
	constexpr static int TILT_PIN = 9;
	constexpr static int MIN_TILT = 30;
	constexpr static int LEVEL_TILT = 35;
	constexpr static int START_TILT = 60;
	constexpr static int UP_TILT = 125;
	constexpr static int MAX_TILT = 180;
	constexpr static int PAN_CENTER = 90;

	PanTilt() {}

	inline void setup()
	{
		m_pan.attach(PAN_PIN);
		m_tilt.attach(TILT_PIN);
	}
	inline void setTheta(int angle) { m_pan.write(angle); }
	inline void setPhi(int angle) { m_tilt.write(angle); }
	inline int theta() { return m_pan.read(); }
	inline int phi() { return m_tilt.read(); }

private: 
	Servo m_pan; 
	Servo m_tilt; 
};

#endif
