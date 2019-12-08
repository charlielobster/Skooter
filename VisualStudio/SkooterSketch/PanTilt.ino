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

void PanTilt::setCalibratedPan(int cp) 
{ 
	m_calibratedPan = cp; 
}

void PanTilt::setCalibratedTilt(int ct) 
{ 
	m_calibratedPan = ct; 
}

void PanTilt::calibrate() 
{ 
	m_pan.write(m_calibratedPan); 
	m_tilt.write(m_calibratedTilt); 
}
