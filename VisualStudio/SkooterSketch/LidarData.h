#ifndef _LIDARDATA_H_
#define _LIDARDATA_H_

// struct LidarData, a container for data associated with a lidar reading
struct LidarData
{
	int x; 
	int y; 
	int heading; 
	int theta; 
	int phi; 
	int d;
};

#endif
