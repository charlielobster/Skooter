#ifndef _LIDAR_ 
// prevent duplicate declaration of types, enums and static variables if this header file is included more than once
// https://en.wikipedia.org/wiki/Include_guard
#define _LIDAR_

#include <LIDARLite.h> 
// include Lidarlite header files, (making its declarations, types, enums, and static variables) 
// available to those declared in this header file, "Lidar.h"

class Lidar // declare the class "Lidar"
{
public: // accessible outside of the class "Lidar"
	void setup(); // declaration of function "setup"
	int measure(); // declaration of function "measure" with return type int
	
private: // inaccessible outside of the class "Lidar"
	LIDARLite eye; // declare Lidarlite instance "eye"
};

#endif
