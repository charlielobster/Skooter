#include "Lidar.h" // include declarations etc from "Lidar.h"

// define the function named setup declared in the class Lidar
void Lidar::setup()
{ 
	eye.begin(0, true); 
}

// define the function named distance declared in the class Lidar
int Lidar::distance()
{
	return eye.distance(); // returns the function distance which is called to the variable (instance) eye
}
