#include <Servo.h>
#include "LIDARLite.h" 

constexpr static int MAX_DISTANCE = 32767;
constexpr static int PAN_PIN = 6;
constexpr static int TILT_PIN = 9;
constexpr static int MIN_TILT = 30;
constexpr static int LEVEL_TILT = 35;
constexpr static int START_TILT = 55;
constexpr static int UP_TILT = 125;
constexpr static int MAX_TILT = 180;
constexpr static int MIN_PAN = 30;
constexpr static int PAN_CENTER = 90;
constexpr static int MAX_PAN = 150; 
constexpr static int MIN_DELTA = 50;
constexpr static int SMALL_MOVE_DELAY = 20;
constexpr static int LARGE_MOVE_DELAY = 1000;

typedef struct LidarEvent
{
    LidarEvent() : distance(MAX_DISTANCE), pan(0) {}
    int distance;
    int pan;
} lidarEvent;

LIDARLite lidar;
Servo pan;
Servo tilt;

lidarEvent current;	    // current reading
lidarEvent last;		// last reading 
lidarEvent leftEdge;	// right edge pan angle < left edge pan angle, 
lidarEvent rightEdge;	// since the angles are from Skooter's point of view


void setup()
{
    lidar.begin(0, true);
    pan.attach(PAN_PIN);
    tilt.attach(TILT_PIN);
    current.pan = MIN_PAN - 1;
    pan.write(MIN_PAN);
    tilt.write(START_TILT);
    delay(LARGE_MOVE_DELAY);
}

void tryPanningRight()
{
    if (current.pan < MAX_PAN)
    {
        pan.write(current.pan + 1);
    }
    else
    {
        rightEdge.pan = current.pan;
        pan.write(current.pan - 1);
    }
}

void tryPanningLeft()
{
    if (current.pan > MIN_PAN)
    {
        pan.write(current.pan - 1);
    }
    else
    {
        leftEdge.pan = current.pan;
        pan.write(current.pan + 1);
    }
}

void loop()
{
    last = current;

    current.distance = lidar.distance();
    current.pan = pan.read();

    int delta = abs(last.distance - current.distance);
    bool movingRight = (current.pan - last.pan > 0 ? true : false);
    bool hitObject = (delta < MIN_DELTA);
    bool currentIsCloser = (current.distance < last.distance);

    if (movingRight)
    {
        if (hitObject) tryPanningRight(); else
        {
            if (currentIsCloser)
            {
                leftEdge = current;
                tryPanningRight();
            }
            else
            {
                rightEdge = last;
                tryPanningLeft();
            }
        }
    }
    else
    {
        if (hitObject) tryPanningLeft(); else
        {
            if (currentIsCloser)
            {
                rightEdge = current;
                tryPanningLeft();
            }
            else
            {
                leftEdge = last;
                tryPanningRight();
            }
        }
    }
    delay(SMALL_MOVE_DELAY);
}