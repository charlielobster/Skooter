#include "Skooter.h" 

Skooter::Skooter() : m_state(SkooterState::AWAKE), m_scanningLeft(true), m_scanningUp(true) {}

void Skooter::setup()
{
  lidar.setup();
  panTilt.setup();
}

void Skooter::loop()
{
  panTilt.loop();
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
                    abs(m_avgReading - m_currentReading) > (DELTA * m_avgReading)) 
                { 
//                    noiseMaker.makeFoundYouNoise();
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
        // if (cabinet.state() == CabinetState::NO_ACTIVITY) 
//        {
//            LidarData ld(0, 0, 0, 
//                panTilt.tiltAngle(), panTilt.panAngle(), m_avgReading);
//            cabinet.writeLine(ld.toString());
            m_state = SkooterState::SCAN_PANNING;
            m_delay = DELAY;
            m_scanPanAngle += (m_scanningLeft ? -SCAN_INCREMENT : SCAN_INCREMENT);
            if (m_scanPanAngle - SCAN_INCREMENT < 30)
            { 
                m_scanningLeft = false;
            }
            if (m_scanPanAngle + SCAN_INCREMENT > 150)
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
//        }
        break;

    case SkooterState::TAKING_MEASUREMENT:
      // if cabinet ...
      break;
    }
    
    m_delay--;
    if (m_delay <= 0) m_delay = 0;
}
