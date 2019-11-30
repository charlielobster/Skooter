#ifndef _LIDAR_H_
// prevent duplicate declaration of types, enums and static variables if this header file is included more than once
// https://en.wikipedia.org/wiki/Include_guard
#define _LIDAR_H_

#include <LIDARLite.h> 
// include Lidarlite header files, 
// (thereby making its declarations, types, enums, and static variables available to whatever is being declared in this header file, "Lidar.h")

class Lidar // declare the class Lidar
{
public: // accessible outside of the class Lidar
	void setup(); // declaration of function setup
	int distance(); // declaration of function distance with return type int
	
private: // inaccessible outside of the class Lidar
	LIDARLite eye; // declare LIDARLite private member named "eye" (note: compile-time error if no #include <LIDARLite.h>)
};

#endif
