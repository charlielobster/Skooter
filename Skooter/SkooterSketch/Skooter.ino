#include "Skooter.h" 
#include "LidarData.h"

Skooter::Skooter() : m_state(SkooterState::AWAKE), m_scanningLeft(true), m_scanningUp(true) {}

void Skooter::setup()
{
    lidar.setup();
	panTilt.setup();
	tracks.setup();
    cabinet.setup();
	noiseMaker.setup();
}

void Skooter::loop()
{
    cabinet.loop();
	noiseMaker.loop();
	tracks.loop();
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
            if (m_scanPanAngle - SCAN_INCREMENT < 0)
            { 
                m_scanningLeft = false;
            }
            if (m_scanPanAngle + SCAN_INCREMENT > 180)
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
    }
    
    m_delay--;
    if (m_delay <= 0) m_delay = 0;
    
}
/*
void Skooter::doMotionScan()
{
    int current;
    double avg = lidar.distance();
    for (int i = 1; i < MINIMUM_AVERAGES; i++) 
    { 
        delay(SHORT_DELAY);
        avg += lidar.distance();
    }   
    avg /= MINIMUM_AVERAGES;

    for (int i = 0; i < MOTION_SCAN_RATE; i++) 
    { 
        delay(SHORT_DELAY);
        current = lidar.distance();             

        if (current < MIN_DISTANCE && abs(avg - current) > (DELTA * avg)) 
        { 
            noiseMaker.makeFoundYouNoise();
        }
        else 
        {        
            avg *= (MINIMUM_AVERAGES + i);
            avg += current;
            avg /= (MINIMUM_AVERAGES + i + 1.0);
        }
    }   
}

void Skooter::scan(int increment)
{
     for (int a = PanTilt::LEVEL_TILT; a <= 60; a+=increment) 
     {
        panTilt.tiltWrite(a);
        m_state = SkooterState::SCAN_TILTING;
        delay(DELAY); // delays for 25 ms

        for (int p = 0; p <= 180; p+=increment) 
        { 
            panTilt.panWrite(p);
            delay(DELAY);

            doMotionScan();
        
            LidarData ld(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
      //      cabinet.writeLine(ld.toString());
        }

        a += increment;
        panTilt.tiltWrite(a);
        delay(DELAY);

        for (int p = 180; p >= 0; p-=increment) 
        { 
            panTilt.panWrite(p);
            delay(DELAY);
        
            doMotionScan();
        
            LidarData ld(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
      //      cabinet.writeLine(ld.toString());
        }
    }
    panTilt.tiltWrite(45);
}

void Skooter::pan(int increment)
{
	// for loop: for (initialization; condition; increment) {}
	for (int a = 0; a <= 180; a+=increment) {
		panTilt.panWrite(a);
		delay(25);
        LidarData ld(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
      //  cabinet.writeLine(ld.toString());
	} 
    panTilt.panWrite(90);
}

void Skooter::tilt(int increment)
{
	// lidar tilts (rotates about its azimuthal angle) from the angle minTilt to the angle maxTilt in steps of 1
	for (int a = PanTilt::MIN_TILT; a <= PanTilt::MAX_TILT; a+=increment) {
		// call the PanTilt instance panTilt's function tiltWrite, with the value of a 
		panTilt.tiltWrite(a);
		delay(25); // delays for 25 ms
		LidarData ld(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
	//	cabinet.writeLine(ld.toString());
	}
    panTilt.tiltWrite(45);
}
//
// the function lookScan belongs to the class Skooter
//void Skooter::lookScan()
//{
//	// panTilt goes to its zeroes
//	panTilt.calibrate();
//	delay(250);
//
//	for (int t = PanTilt::MIN_TILT; t <= PanTilt::MAX_TILT; t++) {
//
//		panTilt.tiltWrite(t);
//
//		// pan the lidar along a plane which deviates from a plane parallel with the floor by the angle (tiltAngle - calibratedAngle)
//		// collect 181 readings between 0 and 180 degrees, in steps of 1
//		for (int p = 0; p <= 180; p++) {
//
//			// call the PanTilt instance panTilt's function panWrite, with the value of p
//			panTilt.panWrite(p);
//			// write the lidar distance, tracks, and panTilt related data to the cabinet...
//			LidarData ld(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
//			cabinet.writeLine(ld.toString());
//		}
//
//		t++; // increment t again
//
//		// call the PanTilt instance panTilt's function tiltWrite, with the value of t 
//		panTilt.tiltWrite(t);
//
//		// pan the lidar along a plane which deviates from a plane parallel with the floor by the angle (tiltAngle - calibratedAngle)
//		// collect 181 readings between 180 degrees and 0 degrees, in steps of 1
//		for (int p = 180; p >= 0; p--) {
//			// call PanTilt instance panTilt's function panWrite, with the value of p 
//			panTilt.panWrite(p);
//			// write the lidar distance, tracks, and panTilt related data to the cabinet...
//			LidarData ld(tracks.x(), tracks.y(), tracks.heading(), panTilt.tiltAngle(), panTilt.panAngle(), lidar.distance());
//			cabinet.writeLine(ld.toString());
//		}
//	}
//	panTilt.calibrate();
//}
//
//FIXME ONLY RUN IF IN FRONT OF WALL
//int Skooter::calibrateTilt() 
//{
//	/*int calibratedTilt = -1;
//	float minDistance = 9999.9;
//
//	panTilt.calibrate();
//	delay(250);
//
//	for (int tiltAngle = PanTilt::MIN_TILT; tiltAngle <= PanTilt::MAX_TILT; tiltAngle++) {
//
//		panTilt.tiltWrite(tiltAngle);
//		delay(50);
//
//		int sum = lidar.distance();
//		for (int i = 0; i < 9; i++) {
//			sum += lidar.distance();
//		}
//		float avgDistance = sum / 10.0;
//
//		if (avgDistance < minDistance) 
//		{
//			minDistance = avgDistance;
//			calibratedTilt = tiltAngle;
//		}
//	}
//
//	panTilt.setCalibratedTilt(calibratedTilt);
//  
//	return calibratedTilt;
//	
//}
//
//int Skooter::calingPan() 
//{
//	int calibratedPan = -1;
//	float minDistance = 9999.9;
//
//	panTilt.calibrate();
//	delay(50);
//
//	for (int a = 0; a <= 180; a++) {
//
//		panTilt.panWrite(a);
//		delay(15);
//
//		int sum = lidar.distance();
//		for (int i = 0; i < 9; i++) {
//			sum += lidar.distance();
//		}
//		float avgDistance = sum / 10.0;
//
//		if (avgDistance < minDistance) 
//		{
//			minDistance = avgDistance;
//			calibratedPan = a;
//		}
//	}
//	
//	panTilt.setCalibratedPan(calibratedPan);
//  
//	return calibratedPan;
//}
//
//int Skooter::calPan() 
//{
//  calingPan();
//  while (calibratedPan < 85 || calibratedPan > 95) {
//    if (calibratedPan < 85) {
//      tracks.turnLeft(90-//calibratedPan//); 
//  	FIXME turnRight has to be able to take in a degree and turn long enough to reach that degree then stop
//    }
//    else if (calibratedPan > 95) {
//      tracks.turnRight(180-//calibratedPan//); 
//  	FIXME as above and also check which direction each one is
//    }
//    calingPan();
//  }
//  
//  return calibratedPan;
//}*/
