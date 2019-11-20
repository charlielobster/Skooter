#ifndef _PANTILT_
#define _PANTILT_

class PanTilt 
{
public:
	void attach(int p, int t);
	void setTiltRange(int min, int max);
	void lookPan();
	void lookTilt();
	void lookScan();

private:
	Servo pan;	
	Servo tilt;
	int minTilt;
	int maxTilt;
};

#endif