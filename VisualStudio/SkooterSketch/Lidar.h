#ifndef _LIDAR_ 
// prevent duplicate declaration of types, enums and static variables if this header file is included more than once
// https://en.wikipedia.org/wiki/Include_guard
#define _LIDAR_

#include <LIDARLite.h> //includes Lidarlite library making it available to the header file "Lidar.h"

class Lidar // creates the class "Lidar"
{
public: // functions and variables are accessible outside of the class "Lidar"
	void setup(); // declaration of function "setup"
	int measure(); // declaration of variable "measure" of data type "int"
	
private: // class and instance are NOT accessible outside of the class "Lidar"
	LIDARLite eye; // creation of the class "Lidarlite" and the instance "eye"
};

#endif
