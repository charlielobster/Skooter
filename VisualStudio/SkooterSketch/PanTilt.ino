#include "PanTilt.h" //gives this source file PanTilt access to the declarations in the header file "PanTilt.h"

// the function attach belongs to the class PanTilt
// the use of the :: operator indicates a class-level declaration (ie. it is a definition shared by all the instances of this class)
void PanTilt::attach(int p, int t)
{
	m_pan.attach(p); // calls the function attach to the variable (instance), of type Servo, m_pan
	m_tilt.attach(t); // calls the the function attach to the variable (instance), of type Servo, m_tilt
}

// the function setTiltRange belongs to the class PanTilt
void PanTilt::setTiltRange(int minT, int maxT)
{
	m_minTilt = minT; // defines variables (provides them with values minT and maxT) belonging to class PanTilt
	m_maxTilt = maxT;
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
