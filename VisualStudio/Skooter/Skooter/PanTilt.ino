#include "PanTilt.h"

void PanTilt::attach(int p, int t)
{
	pan.attach(p);
	tilt.attach(t);
}

void PanTilt::setTiltRange(int min, int max)
{
	minTilt = min;
	maxTilt = max;
}

void PanTilt::lookPan() 
{
	// sweeps the full 180 degree angle in 1 degree steps
	pan.write(0);
	delay(500);

	for (int panAngle = 0; panAngle <= 180; panAngle++) {
		pan.write(panAngle);
		delay(15);
	}

	pan.write(90);
}

void PanTilt::lookTilt() 
{
	for (int tiltAngle = minTilt; tiltAngle <= maxTilt; tiltAngle++) {
		tilt.write(tiltAngle);
		delay(15);
	}

	tilt.write(minTilt);
	delay(15);
}

void PanTilt::lookScan() 
{
	// scooter first pans to lower left corner
	pan.write(0);
	tilt.write(0);

	for (int tiltAngle = minTilt; tiltAngle <= maxTilt; tiltAngle++) {
		for (int panAngle = 0; panAngle <= 180; panAngle++) {
			pan.write(panAngle);
		//	LIDAR();
		}
		tiltAngle++;
		tilt.write(tiltAngle);
		for (int panAngle = 180; panAngle >= 0; panAngle--) {
			pan.write(panAngle);
		//	LIDAR();
		}
	}

	//reset to flat, 36 degrees, facing forward
	tilt.write(minTilt);
	pan.write(90);
}
