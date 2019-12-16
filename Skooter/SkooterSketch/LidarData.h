#ifndef _LIDARDATA_H_
#define _LIDARDATA_H_

struct LidarData
{
	int x; 
	int y; 
	int heading; 
	int theta; 
	int phi; 
	int d;

	LidarData() {}

	LidarData(int x, int y, int heading, int theta, int phi, int d) 
		: x(x), y(y), heading(heading), theta(theta), phi(phi), d(d) {}

	String toString() const
	{
		char data[40];
		sprintf(data, "%d,%d,%d,%d,%d,%d", x, y, heading, theta, phi, d);
		return String(data);
	}
};

#endif
