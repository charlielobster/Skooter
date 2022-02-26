#include "PanTilt.h" 

void PanTilt::setup()
{
	m_pan.attach(PAN_PIN);
	m_tilt.attach(TILT_PIN);	
}

void PanTilt::panWrite(int angle) 
{ 
	m_panAngle = angle;
	m_pan.write(m_panAngle);
}

void PanTilt::tiltWrite(int angle) 
{ 
	m_tiltAngle = angle;
	m_tilt.write(m_tiltAngle);
}
