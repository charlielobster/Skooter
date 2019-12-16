#ifndef _MOTOR_SKOOTER_H_
#define _MOTOR_SKOOTER_H_

#include "Lidar.h" 
#include "PanTilt.h"
#include "Tracks.h"
#include "NoiseMaker.h"

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
	static const double DELTA = .5;
	static const double MINIMUM_AVERAGES = 4;
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
		tracks.setup();
		noiseMaker.setup();
	}

    bool testDistance()
    {
        return (m_currentReading / 20) > 1;
    }

	void loop()
	{
        m_currentReading = lidar.distance();
		noiseMaker.loop();
		tracks.loop();
        panTilt.loop();
        tracks.loop();

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
                    tracks.goForward(UNIT);
                }
                else
                {
                    m_state = MotorSkooterState::LEFT;
                    tracks.turnToAngle(ANGLE);
                }
                m_delay = DELAY;
                break;
                
            case MotorSkooterState::LEFT:    
                if (testDistance())
                {
                    m_state = MotorSkooterState::FORWARD;
                    tracks.goForward(UNIT);
                }
                else
                {
                    m_state = MotorSkooterState::LEFT;                    
                    tracks.turnToAngle(ANGLE);
                }
                m_delay = 2 * DELAY;                
                break;
            }
        }

        m_delay--;
        if (m_delay <= 0) m_delay = 0;        
	}

private:
	Lidar lidar;
	PanTilt panTilt;
	Tracks tracks;
	NoiseMaker noiseMaker;

	motorSkooterState m_state;

	int m_delay;
	int m_currentReading;
  
    tracksState m_tracksState;
};

#endif
