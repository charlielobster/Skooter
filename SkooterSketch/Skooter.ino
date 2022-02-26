#include <Math.h>
#include "Skooter.h" 

Skooter::Skooter() : m_state(SkooterState::AWAKE) {}

void Skooter::setup()
{
    lidar.setup();
    panTilt.setup();
    panTilt.setTheta(PanTilt::PAN_CENTER);
    panTilt.setPhi(PanTilt::START_TILT);
    delay(30);
    m_state = SkooterState::SEEKING_NEAREST_NEIGHBOR;
}

void Skooter::loop()
{
    // sprintf to msgBuffer to format logs
    char msgBuffer[200];

    int distance = lidar.distance();
    sprintf(msgBuffer,
        "new time: %lu, distance: %d, theta: %d, phi: %d",
        millis(), distance, panTilt.theta(), panTilt.phi());
    Serial.println(msgBuffer);

}

/*
    constexpr static double ct = PanTilt::LEVEL_TILT + 48.0;
    constexpr static double cp = PanTilt::PAN_CENTER;

    switch (m_state)
    {
    case SkooterState::AWAKE:
        m_panTiltDelay = 0;
        m_spiralRadius = 2;                     
        m_theta = 0;
        m_closest.distance = 999;
        m_state = SkooterState::SEEKING_SPIRALING_OUT;   
        break;

    case SkooterState::SEEKING_SPIRALING_OUT:
        if (m_panTiltDelay == 0) 
        {
            if (m_spiralRadius < 32.0) 
            { 
                m_spiralRadius+=0.5;
                m_theta += M_PI / m_spiralRadius;
                panTilt.panWrite(cp + m_spiralRadius * cos(m_theta));
                panTilt.tiltWrite(ct + m_spiralRadius * sin(m_theta));
                m_panTiltDelay = SPIRAL_DELAY;            
            }
            else
            {
                m_state = SkooterState::SEEKING_NEAREST_NEIGHBOR;
                panTilt.panWrite(m_closest.theta);
                panTilt.tiltWrite(m_closest.phi);
                m_panTiltDelay = BEE_LINE_DELAY;
            }
        }
        break;

    case SkooterState::SEEKING_SPIRALING_IN:   
        if (m_panTiltDelay == 0) 
        {  
            if (m_spiralRadius > 4.0) 
            { 
                m_spiralRadius-=0.5;
                m_theta -= M_PI / m_spiralRadius;
                panTilt.panWrite(cp + m_spiralRadius * cos(m_theta));
                panTilt.tiltWrite(ct + m_spiralRadius * sin(m_theta));
                m_panTiltDelay = SPIRAL_DELAY;      
            }
            else 
            {
                m_spiralRadius = 2;
                m_state = SkooterState::SEEKING_NEAREST_NEIGHBOR;
                panTilt.panWrite(m_closest.theta);
                panTilt.tiltWrite(m_closest.phi);
                m_panTiltDelay = BEE_LINE_DELAY;
            }
        }
        break;

    case SkooterState::SEEKING_NEAREST_NEIGHBOR:
        if (m_panTiltDelay == 0) 
        { 
            if ((distance - m_closest.distance) < DELTA) 
            { 
                Serial.println("MESMERIZED!");
                m_state = SkooterState::MESMERIZED_SPIRALING_OUT;
                m_panTiltDelay = 0;
            } 
            else 
            {
            Serial.println("No finger found!");  
            m_state = SkooterState::SEEKING_SPIRALING_OUT;
            m_panTiltDelay = 0;
            //m_spiralRadius = 2;
            m_theta = 0;
            }
        }
        break;

    case SkooterState::MESMERIZED_SPIRALING_OUT:
        if (m_panTiltDelay == 0) 
        { 
            if (distance - m_closest.distance < DELTA) 
            {       
            if (m_spiralRadius < 32.0) 
            { 
                m_spiralRadius+=0.5;
                m_theta += M_PI / m_spiralRadius;
                panTilt.panWrite(m_closest.theta + m_spiralRadius * cos(m_theta));
                panTilt.tiltWrite(m_closest.phi + m_spiralRadius * sin(m_theta));
            }
            else
            {
                m_state = SkooterState::MESMERIZED_SPIRALING_IN;
                panTilt.panWrite(m_closest.theta);
                panTilt.tiltWrite(m_closest.phi);
            }
            m_panTiltDelay = SPIRAL_DELAY;
            }
            else 
            {
                Serial.println("Oh no! We lost the finger!");
                m_state = SkooterState::SEEKING_NEAREST_NEIGHBOR;
                panTilt.panWrite(m_closest.theta);
                panTilt.tiltWrite(m_closest.phi);
                m_panTiltDelay = BEE_LINE_DELAY;
            }
        }
        break;
    
    default:
        break;
    }
    
    // record latest nearest neighbor
    if (distance < m_closest.distance) 
    {    
        sprintf(msgBuffer, 
            "new best distance: %d, theta: %d, phi: %d", 
            distance, panTilt.panAngle(), panTilt.tiltAngle());
        Serial.println(msgBuffer);

        m_closest.distance = distance;
        m_closest.theta = panTilt.panAngle();
        m_closest.phi = panTilt.tiltAngle();    
    }

    // done with loop for this round, decrement delay
    m_panTiltDelay--;
    if (m_panTiltDelay < 0) m_panTiltDelay = 0;
*/
