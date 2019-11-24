#include "PanTilt.h" //gives this source file "PanTilt" access to the declarations in the header file "PanTilt.h"

// the function "attach" belongs to the class "PanTilt"
// the use of the :: operator indicates a class-level declaration (ie. it is a definition "shared" by all the instances of this class)
void PanTilt::attach(int p, int t)
{
	pan.attach(p); // calls the function "attach" to the variable (instance), of type Servo, "pan"
	tilt.attach(t); // calls the the function "attach" to the variable (instance), of type Servo, "tilt"
}

// the function "setTiltRange" belongs to the class "PanTilt"
void PanTilt::setTiltRange(int minT, int maxT)
{
	minTilt = minT; // defines variables (provides them with values (min and max)) belonging to class "PanTilt"
	maxTilt = maxT;
}

int PanTilt::getMinTilt() 
{ 
	return minTilt; 
}

int PanTilt::getMaxTilt() 
{ 
	return maxTilt; 
}

int PanTilt::getPanAngle() 
{ 
	return panAngle; 
}

int PanTilt::getTiltAngle() 
{ 
	return tiltAngle;
}

void PanTilt::panWrite(int angle) 
{ 
	panAngle = angle;  
	pan.write(panAngle); 
}

void PanTilt::tiltWrite(int angle) 
{ 
	tiltAngle = angle; 
	tilt.write(tiltAngle); 
}

int PanTilt::getCalibratedPan() 
{ 
	return calibratedPan;
}

int PanTilt::getCalibratedTilt() 
{ 
	return calibratedTilt; 
}

void PanTilt::setCalibratedPan(int cp) 
{ 
	calibratedPan = cp; 
}

void PanTilt::setCalibratedTilt(int ct) 
{ 
	calibratedPan = ct; 
}

void PanTilt::calibrate() 
{ 
	pan.write(calibratedPan); 
	tilt.write(calibratedTilt); 
}
