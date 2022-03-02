#include <Servo.h>
#include "LIDARLite.h" 

constexpr static int MAX_DISTANCE = 32767;
constexpr static int PAN_PIN = 6;
constexpr static int TILT_PIN = 9;
constexpr static int MIN_TILT = 30;
constexpr static int LEVEL_TILT = 35;
constexpr static int START_TILT = 55;
constexpr static int UP_TILT = 125;
constexpr static int MAX_TILT = 150;
constexpr static int MIN_PAN = 30;
constexpr static int PAN_CENTER = 90;
constexpr static int MAX_PAN = 150; 
constexpr static int MIN_DELTA = 50;
constexpr static int SMALL_MOVE_DELAY = 25;
constexpr static int LARGE_MOVE_DELAY = 1000;

typedef struct LidarEvent
{
    LidarEvent() : distance(MAX_DISTANCE), pan(0) {}
    int distance;
    int pan;
    int tilt;
} lidarEvent;

LIDARLite lidar;
Servo pan;
Servo tilt;

lidarEvent current; // current reading
lidarEvent last;	// last reading 
lidarEvent minEdge;	// right edge pan angle < left edge pan angle, 
lidarEvent maxEdge;	// since the angles are from Skooter's point of view

void setup()
{
    lidar.begin(0, true);
    pan.attach(PAN_PIN);
    tilt.attach(TILT_PIN);
    current.pan = MIN_PAN - 1;
    current.tilt = MIN_TILT - 1;
    pan.write(MIN_PAN);
    tilt.write(START_TILT);
    delay(LARGE_MOVE_DELAY);
}

void tryTiltingUp()
{
    if (current.tilt < MAX_TILT)
    {
        tilt.write(current.tilt + 1);
    }
    else
    {
        maxEdge.tilt = current.tilt;
        tilt.write(current.tilt - 1);
    }
}

void tryPanningRight()
{
    if (current.pan < MAX_PAN)
    {
        pan.write(current.pan + 1);
    }
    else
    {
        maxEdge.pan = current.pan;
        pan.write(current.pan - 1);
    }
}

void tryTiltingDown()
{
    if (current.tilt > MIN_TILT)
    {
        tilt.write(current.tilt - 1);
    }
    else
    {
        minEdge.tilt = current.tilt;
        tilt.write(current.tilt + 1);
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
        minEdge.pan = current.pan;
        pan.write(current.pan + 1);
    }
}

void loop()
{
    last = current;

    current.distance = lidar.distance();
    current.pan = pan.read();
    current.tilt = tilt.read();

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
                minEdge.pan = current.pan;
                tryPanningRight();
            }
            else
            {
                maxEdge.pan = last.pan;
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
                maxEdge.pan = current.pan;
                tryPanningLeft();
            }
            else
            {
                minEdge.pan = last.pan;
                tryPanningRight();
            }
        }
    }
    delay(SMALL_MOVE_DELAY);
}