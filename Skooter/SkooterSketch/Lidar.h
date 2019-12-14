#ifndef _LIDAR_H_
#define _LIDAR_H_

#include <LIDARLite.h> 

class Lidar 
{
public:
	void setup() 
	{
		lidarLite.begin(0, true);
	}
	
	int distance()
	{
		return lidarLite.distance();
	}
	
private: 
	LIDARLite lidarLite; 
};

#endif
