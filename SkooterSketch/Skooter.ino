#include <Math.h>
#include "Skooter.h" 

Skooter::Skooter() : m_state(SkooterState::AWAKE) {}

void Skooter::setup()
{
    m_pan.attach(PAN_PIN);
    m_tilt.attach(TILT_PIN);
    m_pan.write(PAN_CENTER);
    m_tilt.write(START_TILT);
    delay(50);
    m_state = SkooterState::SEEKING_NEAREST_NEIGHBOR;
    m_lidar.begin(0, true);
}

void Skooter::loop()
{
    // sprintf to msgBuffer to format logs
    static char lineBuffer[80];
    m_current.timestamp = millis();
    m_current.distance = m_lidar.distance();
    m_current.pan = m_pan.read();
    m_current.tilt = m_tilt.read();

    // record latest nearest neighbor
    if (m_current.distance < m_closest.distance)
    {
        m_closest = m_current;

        sprintf(lineBuffer,
            "new closest! timestamp: %lu, distance: %d, pan: %d, tilt: %d",
            m_closest.timestamp, m_closest.distance, m_closest.tilt , m_closest.tilt);
        Serial.println(lineBuffer);

        sprintf(lineBuffer,
            "m_current.timestamp: %lu, distance: %d, pan: %d, tilt: %d",
            m_current.timestamp, m_current.distance, m_current.pan, m_current.tilt);
        Serial.println(lineBuffer);

        sprintf(lineBuffer,
            "m_last.timestamp: %lu, distance: %d, pan: %d, tilt: %d",
            m_last.timestamp, m_last.distance, m_last.pan, m_last.tilt);
        Serial.println(lineBuffer);

        // Skooter is now mesmerized by the closest object 
        // 
        // use the heuristic that since
        // larger objects near Skooter, such as a hand or face,
        // tend have distances ~100 away from anything else
        // 
        // spiral out while the abs(delta) < 100

    }

    int delta = m_last.distance - m_current.distance;
    sprintf(lineBuffer, "delta: %d, %s", delta,
        (delta > 0 ? "getting closer!" : "whoops, farther away!"));
    Serial.println(lineBuffer);

    m_last = m_current;
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
    
    // done with loop for this round, decrement delay
    m_panTiltDelay--;
    if (m_panTiltDelay < 0) m_panTiltDelay = 0;
*/
