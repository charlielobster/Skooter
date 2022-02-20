#ifndef _MOTOR_SKOOTER_H_
#define _MOTOR_SKOOTER_H_

#include "Lidar.h" 
#include "PanTilt.h"
#include "LidarData.h"

typedef enum MotorSkooterState
{
	WAKE = 0,
	FORWARD = 1,
	LEFT = 2,
	RIGHT = 3,
	NOISE,
} motorSkooterState;

class MotorSkooter
{
public:
	static const int DELAY = 100;
	static const int SHORT_DELAY = 5;
	static const int MOTION_SCAN_RATE = 4;
	static const int SCAN_INCREMENT = 3;
	static const int MIN_DISTANCE = 150;
  static const int ANGLE = 180;
  static const int UNIT = 5;
    
	MotorSkooter() : 
	    m_delay(0), 
	    m_currentReading(0), 
	    m_state(MotorSkooterState::WAKE) {}
   
  void setup()
	{
		lidar.setup();
		panTilt.setup();
	}

  bool testDistance()
  {
      return (m_currentReading / 20) > 1;
  }

	void loop()
	{
    m_currentReading = lidar.distance();
    printf("%d\n", m_currentReading);
    panTilt.loop();

    if (m_delay == 0)  
    {
        switch (m_state)
        {
        case MotorSkooterState::WAKE:
            // go to FORWARD state
            m_state = MotorSkooterState::FORWARD;           
            m_delay = 0;
            break;

        case MotorSkooterState::FORWARD:    
            if (testDistance())
            {
              m_state = MotorSkooterState::FORWARD;
            }
            else
            {
              m_state = MotorSkooterState::LEFT;
            }
            m_delay = DELAY;
            break;
            
        case MotorSkooterState::LEFT:    
            if (testDistance())
            {
              m_state = MotorSkooterState::FORWARD;
            }
            else
            {
              m_state = MotorSkooterState::LEFT;                    
            }
            m_delay = 2 * DELAY;                
            break;
        }
    }
    
    //LidarData ld(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), m_currentReading);
    //cabinet.writeLine(ld.toString());

    m_delay--;
    if (m_delay <= 0) m_delay = 0;        
	}

private:
  Lidar lidar;
  PanTilt panTilt;
  
  motorSkooterState m_state;
  
  int m_delay;
  int m_currentReading;  
};

#endif
