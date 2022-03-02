#include <Math.h>
#include "Skooter.h" 

Skooter::Skooter() : m_state(AWAKE) {}

void Skooter::setup()
{
    m_lidar.begin(0, true);
    m_pan.attach(PAN_PIN);
    m_tilt.attach(TILT_PIN);
 //   Serial.begin(38400);
}

void Skooter::getLidarEvent()
{
    m_current.distance = m_lidar.distance();
    m_current.pan = m_pan.read();
    m_closest = (m_current.distance < m_closest.distance ? m_current : m_closest);
}

void Skooter::moveToClosest()
{
    m_state = MOVING_TO_CLOSEST;
    m_lastHit = m_closest;
    m_pan.write(m_closest.pan);
    delay(LARGE_MOVE_DELAY);
}

void Skooter::tryPanningRight()
{
    if (m_current.pan < MAX_PAN)
    {
        m_pan.write(m_current.pan + 1);
        delay(SMALL_MOVE_DELAY);
    }
    else
    {
        moveToClosest();
    }
}

void Skooter::tryPanningLeft()
{
    if (m_current.pan > MIN_PAN)
    {
        m_pan.write(m_current.pan - 1);
        delay(SMALL_MOVE_DELAY);
    }
    else
    {
        moveToClosest();
    }
}

void Skooter::loop()
{  
    getLidarEvent();

    //sprintf(m_lineBuffer, "state: %d", m_state);
    //Serial.println(m_lineBuffer);

    //sprintf(m_lineBuffer, "current distance: %d, pan: %d", m_current.distance, m_current.pan);
    //Serial.println(m_lineBuffer);

    //sprintf(m_lineBuffer, "last distance: %d, pan: %d", m_lastHit.distance, m_lastHit.pan);
    //Serial.println(m_lineBuffer);

    switch (m_state)
    {
    case AWAKE:
        m_pan.write(MIN_PAN);
        m_tilt.write(START_TILT); 
        m_closest.distance = MAX_DISTANCE;
        m_state = FINDING_CLOSEST;
        delay(LARGE_MOVE_DELAY);
        break;

    case FINDING_CLOSEST:
        if (m_current.pan < MAX_PAN - 1)
        {
            m_pan.write(m_current.pan + 1);
            delay(SMALL_MOVE_DELAY);
        }
        else
        {
            moveToClosest();
        }
        break;

    // awkward ... but there it is
    case MOVING_TO_CLOSEST:
    case FINDING_LEFT_EDGE:
    case FINDING_RIGHT_EDGE:
    case CORRECTING_LEFT:
    case CORRECTING_RIGHT:

        int delta = abs(m_lastHit.distance - m_current.distance);

        // if delta < MIN_EDGE_DELTA, 
        // there is an object implied by closest, last, and current
        if (delta < MIN_EDGE_DELTA)
        {
            switch (m_state)
            {
            case MOVING_TO_CLOSEST:
                // Serial.println("found object!");

            case CORRECTING_LEFT:
                m_state = FINDING_LEFT_EDGE;

            case FINDING_LEFT_EDGE:
                tryPanningRight();
                break;

            case CORRECTING_RIGHT:
                m_state = FINDING_RIGHT_EDGE;

            case FINDING_RIGHT_EDGE:
                tryPanningLeft();
                break;
            }
            m_lastHit = m_current;
        }
        else
        // delta >= MIN_EDGE_DELTA, a new object
        {
            switch (m_state)
            {
            case MOVING_TO_CLOSEST:
                //  Serial.println("object not found!");
                m_closest.distance = MAX_DISTANCE;
                m_state = FINDING_CLOSEST;
                m_pan.write(MIN_PAN);
                delay(LARGE_MOVE_DELAY);
                break;

            case FINDING_LEFT_EDGE:
                // if the current distance is closer than the last hit, 
                // then current object must be the new closest object
                if (m_current.distance == m_closest.distance) 
                {
                    // m_current must be the m_closest
                    m_closest = m_rightEdge = m_current;
                    tryPanningRight();
                }
                else 
                // otherwise, the last hit must be the left edge of the closest object
                {
                    //   Serial.println("setting left edge");
                    m_state = CORRECTING_RIGHT;
                    m_leftEdge = m_current = m_lastHit; // reset everything to the last hit
                    tryPanningLeft();
                }
                break;

            case CORRECTING_RIGHT:
                tryPanningLeft();
                break;

            case FINDING_RIGHT_EDGE:
                if (m_current.distance < m_lastHit.distance)
                {
                    // m_current must be the m_closest
                    m_closest = m_leftEdge = m_current;
                    tryPanningLeft();
                }
                else
                {
                    //  Serial.println("setting right edge");
                    m_state = CORRECTING_LEFT;
                    m_rightEdge = m_current = m_lastHit;
                    tryPanningRight();
                }
                break;

            case CORRECTING_LEFT:
                tryPanningRight();
                break;
            }

            m_closest.pan = (m_rightEdge.pan + m_leftEdge.pan) / 2;

            //sprintf(m_lineBuffer, "left edge distance: %d, pan: %d", m_leftEdge.distance, m_leftEdge.pan);
            //Serial.println(m_lineBuffer);

            //sprintf(m_lineBuffer, "right edge distance: %d, pan: %d", m_rightEdge.distance, m_rightEdge.pan);
            //Serial.println(m_lineBuffer);

            //sprintf(m_lineBuffer, "delta: %d", m_state, delta);
            //Serial.println(m_lineBuffer);
        }
        break;
    }
}
