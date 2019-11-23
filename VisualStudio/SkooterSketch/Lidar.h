#ifndef _LIDAR_ // prevents problems if someone accidentally #include's the library twice
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
