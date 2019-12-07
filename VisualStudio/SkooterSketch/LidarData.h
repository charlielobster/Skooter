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

	LidarData() {}

	LidarData(int x, int y, int heading, int theta, int phi, int d) : x(x), y(y), heading(heading), theta(theta), phi(phi), d(d) {}

	String toString() const
	{
		char data[100];
		// use sprintf to create a formatted string of data comprising one line of 6 comma-separated values
		sprintf(data, "%d,%d,%d,%d,%d,%d", x, y, heading, theta, phi, d);
		return String(data);
	}
};

#endif
