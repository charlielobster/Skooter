#ifndef _SKOOTER_H_
#define _SKOOTER_H_

#include "Lidar.h" 
#include "PanTilt.h"

typedef enum SkooterState
{
  AWAKE,
  SCAN_PANNING,
  SCAN_TILTING,
  SCAN_GETTING_AVERAGE,
  SCAN_TAKING_MEASUREMENT,
  SCAN_WRITING_TO_FILE,
  TAKING_MEASUREMENT,
  DONE
} skooterState;

class Skooter
{
public:  
  constexpr static int DELAY = 30;
  constexpr static int SHORT_DELAY = 5;
  constexpr static double DELTA = 0.75;
  constexpr static double MINIMUM_AVERAGES = 4;
  constexpr static int MOTION_SCAN_RATE = 4;
  constexpr static int SCAN_INCREMENT = 2;
  constexpr static int MIN_DISTANCE = 150;
  Skooter();
	void setup();
	void loop(); 
    
private: 
	Lidar lidar;
	PanTilt panTilt;

  skooterState m_state;
  int m_delay;
  int m_scanTiltAngle;
  int m_scanPanAngle;
  double m_avgReading; 
  int m_currentReading;   
  int m_numReadings;
  bool m_scanningLeft;
  bool m_scanningUp;
};

#endif
