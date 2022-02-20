#include "Skooter.h" 
#include "LidarData.h"

Skooter::Skooter() : m_state(SkooterState::AWAKE), m_scanningLeft(true), m_scanningUp(true) {}

void Skooter::setup()
{
    lidar.setup();
}

void Skooter::loop()
{
    switch (m_state)
    {
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
        }
        break;

    case SkooterState::SCAN_TAKING_MEASUREMENT:
        if (m_delay == 0)
        {
            if (m_numReadings < MOTION_SCAN_RATE) 
            {
                m_currentReading = lidar.distance();
                m_delay = SHORT_DELAY;

                

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

    case SkooterState::TAKING_MEASUREMENT:
        //LidarData ld(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
        break;
    }
    
    m_delay--;
    if (m_delay <= 0) m_delay = 0;
    
}
