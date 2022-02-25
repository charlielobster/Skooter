#ifndef _SKOOTER_H_
#define _SKOOTER_H_

#include "Lidar.h" 
#include "PanTilt.h"

typedef struct LidarPanTilt
{
  LidarPanTilt() : distance(9999) {}
  int distance;
  int theta; // pan
  int phi;  // tilt
} lidarPanTilt;

typedef enum SkooterState
{
  AWAKE,
  WAKE_UP_SPIRALING_OUT,
  WAKE_UP_SPIRALING_IN,
  FIND_THE_FINGER,
  MESMERIZED,
  MESMERIZED_SPIRALING_OUT,
  MESMERIZED_SPIRALING_IN
} skooterState;

class Skooter
{
public:  
  constexpr static int SPIRAL_DELAY = 20;
  constexpr static int BEE_LINE_DELAY = 15;
  constexpr static int MINIMUM_DISTANCE = 10;
  Skooter();
	void setup();
	void loop(); 
    
private: 
	Lidar lidar;
	PanTilt panTilt;

  skooterState m_state;
  lidarPanTilt m_closest;
  int m_delay;
  double m_spiralRadius;
  double m_theta;
};

#endif
