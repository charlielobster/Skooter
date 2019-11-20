#ifndef _LIDAR_
#define _LIDAR_

#include <LIDARLite.h>

class Lidar {

public:
	void setup();
	int measure();
	
private:
	LIDARLite eye;
};

#endif
