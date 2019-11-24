#include "Lidar.h" // allows the source file "Lidar" access to the library "Lidar.h"

void Lidar::setup() { // the function "setup" belongs to the class "Lidar"
	eye.begin(0, true); 
}

int Lidar::distance() // the function "measure" belongs to the class (::) "Lidar"
{
	return eye.distance(); // returns the function "distance" which is called to the variable (instance) "eye"
}
