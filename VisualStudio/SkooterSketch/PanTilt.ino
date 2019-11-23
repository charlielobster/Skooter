#include "PanTilt.h" //gives source file "PanTilt" access to the definitions in the header file "PanTilt.h"

void PanTilt::attach(int p, int t) // the function "attach" belongs to the class (::) "PanTilt"
{
	pan.attach(p); // calls the function "attach" to the variable (instance), of type Servo, "pan"
	tilt.attach(t); // calls the the function "attach" to the variable (instance), of type Servo, "tilt"
}

void PanTilt::setTiltRange(int minT, int maxT) // the function "setTiltRange" belongs to the class (::) "PanTilt"
{
	minTilt = minT; // defines variables (provides them with values (min and max)) belonging to class "PanTilt"
	maxTilt = maxT;
}

void PanTilt::lookPan() // the function "lookPan" belongs to the class the class (::) "PanTilt"
{
	// sweeps the full 180 degree angle in 1 degree steps
	pan.write(0); // assigns the function "write" (writes a value (an angle) of '0' to the step servo) to the variable (instance), of type Servo, "pan"
	delay(500); // delays half a second

	for (int panAngle = 0; panAngle < 180; panAngle++) { // for loop: for (initialization; condition; increment) {}
		pan.write(panAngle); 
		delay(25);
	} // pans the lidar 180 degrees, in steeps of 1, and then delays for 25 ms

	pan.write(180); // calls the function "write" (writes a value (angle in degrees) of '180' to the servo) to the variable (instance), of class Servo, "pan"
	delay(500); // delays for half a second

}

void PanTilt::lookTilt() // the function "lookTilt" belonds to the class (::) "PanTilt"
{
	tilt.write(minTilt); // calls the function "write" (writes a value of "minTilt" to the step servo) to the variable (instance), of type Servo, "tilt"
	delay(1000); // delays for a second

	for (int tiltAngle = minTilt; tiltAngle <= maxTilt; tiltAngle++) { // lidar tilts (rotates about its azimuthal angle) from the angle "minTilt" to the angle "maxTilt" in steps of "tiltAngle"
		tilt.write(tiltAngle); // calls the function "write" (writes a value of 'tiltAngle' to the servo) to the variable (instance), of type Servo, "tilt"
		delay(25); // delays for 25 ms
	}

	tilt.write(maxTilt); // calls the function "write" (writes a value 'maxTilt' to the step servo) to the variable (instance), of type Servo, "tilt"
	delay(1000);
}

void PanTilt::lookScan() // the function "lookScan" belongs to the class (::) "PanTilt"
{
	// scooter first pans to lower left corner
	pan.write(0); // calls the function "write" (writes a value of '0' to the step servo) to the variable (instance), of type Servo, "pan"
	tilt.write(0); // calls the function "write" (writes a value of '0' to the step servo) to the variable (instance), of type Servo, "tilt"

	for (int tiltAngle = minTilt; tiltAngle <= maxTilt; tiltAngle++) { 
		tilt.write(tiltAngle);
		for (int panAngle = 0; panAngle <= 180; panAngle++) { // pans the lidar horizontally (parallel to the plane in which Skooter rests) 180 degrees in steps of "panAngle"
			pan.write(panAngle); // calls the function "write" (writes the value of "panAngle" passed in from the for loop to the step servo) to the variable (instance), of type Servo, "pan"
		//	LIDAR();
		}
		tiltAngle++; // increments the "tiltAngle" in steps of "tiltAngle" (seems superfluous, imo)
		tilt.write(tiltAngle); // calls the function "write" (writes a value of "tiltAngle" passed in from the for loop to the step servo) to the variable (instance) "tilt"
		for (int panAngle = 180; panAngle >= 0; panAngle--) { // pans the lidar from 180 degrees to 0 in steps of "panAngle"
			pan.write(panAngle); // calls the function "write" (writes a value of "panAngle" passed in from the for loop to the step servo) to the variable (instance) of "pan"
		//	LIDAR();
		}

	}

	//reset to flat, 36 degrees, facing forward
	tilt.write(minTilt); // calls the function "write" (writes a value of "minTilt" to the step servo) to the variable (instance) of "tilt"
	pan.write(90); // calls the function "write" (writes a value of '90' to the step servo) to the variable (instance) of "pan"
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
