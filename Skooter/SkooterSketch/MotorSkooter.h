#ifndef _MOTOR_SKOOTER_H_
#define _MOTOR_SKOOTER_H_

//#include "Cabinet.h"
#include "Lidar.h" 
#include "PanTilt.h"
#include "Tracks.h"
#include "NoiseMaker.h"
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
	//	cabinet.setup();
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
	//	cabinet.loop();

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

			/*
			 case SkooterState::AWAKE:
				 if (m_delay == 0)
				 {
					 m_state = SCAN_TILTING;
					 m_scanningLeft = false;
					 m_scanningUp = true;
					 m_avgReading = 0;
					 m_scanPanAngle = PanTilt::PAN_CENTER;
					 m_scanTiltAngle = PanTilt::LEVEL_TILT;
					 panTilt.tiltWrite(m_scanTiltAngle);
					 m_delay = DELAY;
					 m_state = SkooterState::SCAN_TILTING;
				 }
				 break;

			 case SkooterState::SCAN_TILTING:
				 if (m_delay == 0)
				 {
					 m_numReadings = 0;
					 m_avgReading = 0;
					 m_state = SkooterState::SCAN_GETTING_AVERAGE;
					 m_delay = SHORT_DELAY;
				 }
				 break;

			 case SkooterState::SCAN_GETTING_AVERAGE:
				 if (m_delay == 0)
				 {
					 if (m_numReadings < MINIMUM_AVERAGES)
					 {
						 m_avgReading += lidar.distance();
						 m_numReadings++;
						 m_delay = SHORT_DELAY;

						 if (m_numReadings == MINIMUM_AVERAGES)
						 {
							 m_numReadings = 0;
							 m_avgReading /= MINIMUM_AVERAGES;
							 m_state = SkooterState::SCAN_TAKING_MEASUREMENT;
						 }
					 }
				 }
				 break;

			 case SkooterState::SCAN_TAKING_MEASUREMENT:
				 if (m_delay == 0)
				 {
					 if (m_numReadings < MOTION_SCAN_RATE)
					 {
						 m_currentReading = lidar.distance();
						 m_delay = SHORT_DELAY;

						 if (m_currentReading < MIN_DISTANCE &&
							 abs(m_avgReading - m_currentReading) >(DELTA * m_avgReading))
						 {
							 noiseMaker.makeFoundYouNoise();
						 }
						 else
						 {
							 m_avgReading *= (MINIMUM_AVERAGES + m_numReadings);
							 m_avgReading += m_currentReading;
							 m_avgReading /= (MINIMUM_AVERAGES + m_numReadings + 1.0);
						 }

						 m_numReadings++;
						 if (m_numReadings == MOTION_SCAN_RATE)
						 {
							 m_state = SkooterState::SCAN_WRITING_TO_FILE;
						 }
					 }
				 }
				 break;

			 case SkooterState::SCAN_PANNING:
				 if (m_delay == 0)
				 {
					 m_numReadings = 0;
					 m_avgReading = 0;
					 m_state = SkooterState::SCAN_GETTING_AVERAGE;
					 m_delay = SHORT_DELAY;
				 }
				 break;

			 case SkooterState::SCAN_WRITING_TO_FILE:
				 if (cabinet.state() == CabinetState::NO_ACTIVITY)
				 {
					 LidarData ld(tracks.x(), tracks.y(), tracks.heading(),
						 panTilt.tiltAngle(), panTilt.panAngle(), m_avgReading);
					 cabinet.writeLine(ld.toString());
					 m_state = SkooterState::SCAN_PANNING;
					 m_delay = DELAY;
					 m_scanPanAngle += (m_scanningLeft ? -SCAN_INCREMENT : SCAN_INCREMENT);
					 if (m_scanPanAngle - SCAN_INCREMENT < 40)
					 {
						 m_scanningLeft = false;
					 }
					 if (m_scanPanAngle + SCAN_INCREMENT > 140)
					 {
						 m_scanningLeft = true;
					 }
					 if (m_scanPanAngle == PanTilt::PAN_CENTER)
					 {
						 if ((m_scanTiltAngle + SCAN_INCREMENT) < 60)
						 {
							 m_scanTiltAngle += SCAN_INCREMENT;
							 panTilt.tiltWrite(m_scanTiltAngle);
							 m_delay = DELAY;
							 m_state = SkooterState::SCAN_TILTING;
						 }
						 else
						 {
							 panTilt.panWrite(PanTilt::PAN_CENTER);
							 panTilt.tiltWrite(PanTilt::LEVEL_TILT);
							 m_state = SkooterState::AWAKE;
							 m_delay = DELAY;
						 }
					 }
					 panTilt.panWrite(m_scanPanAngle);
				 }
				 break;

			 case SkooterState::TAKING_MEASUREMENT:
				 if (cabinet.state() == CabinetState::NO_ACTIVITY)
				 {
					 LidarData ld(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
					 cabinet.writeLine(ld.toString());
					 //if (j == 2000) { 
					  //   m_state = SkooterState::AWAKE;
						// Serial.println("done");
					// }
				 }
				 break;


				 */









        }

		//LidarData ld(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), m_currentReading);
		//cabinet.writeLine(ld.toString());

        m_delay--;
        if (m_delay <= 0) m_delay = 0;        
	}

private:
	Lidar lidar;
	PanTilt panTilt;
	Tracks tracks;
	NoiseMaker noiseMaker;
	//Cabinet cabinet;

	motorSkooterState m_state;

	int m_delay;
	int m_currentReading;
  
    tracksState m_tracksState;
};

#endif
