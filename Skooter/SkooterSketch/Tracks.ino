#include "Tracks.h" 

Tracks::Tracks() : 
	m_x(0), 
	m_y(0), 
	m_heading(0), 
	m_state(TracksState::STANDING_STILL),
	m_delay(0) {}

void Tracks::setup()
{
	left.attach(TURN_PIN, 1000, 2000);
	right.attach(FORWARD_PIN, 1000, 2000);
}

void Tracks::loop()
{
	switch (m_state)
	{
	case TracksState::STANDING_STILL:
		stop();
		break;
	case TracksState::TURNING_LEFT:
		turnLeft();
		break;
	case TracksState::TURNING_RIGHT:
		turnRight();
		break;
	case TracksState::MOVING_FORWARD:
		forward();
		break;
	case TracksState::MOVING_BACKWARD:
		backward();
		break;
	}
	m_delay--;
	if (m_delay <= 0) 
	{
		m_delay = 0;
		m_state = TracksState::STANDING_STILL;
	}
}

void Tracks::turnRight()
{
	right.write(40);
	left.write(130);
}

void Tracks::turnLeft()
{
	right.write(130);
	left.write(40);
}

void Tracks::forward()
{
	left.write(90 - MOVE_SPEED);
	right.write(90 - MOVE_SPEED); 
}

void Tracks::backward()
{
	left.write(90 + MOVE_SPEED);
	right.write(90 + MOVE_SPEED);
}

void Tracks::stop()
{
	left.write(90);
	right.write(90);
}

// 90 means turn Skooter 90 degrees to the left, 
// -90 means turn Skooter 90 degrees to the right
void Tracks::turnToAngle(int angle)
{
	(angle < 0 ? clockwiseTurn(-angle) : counterClockwiseTurn(angle) );
}

void Tracks::clockwiseTurn(int angle)
{
	m_delay = floor(angle * 10250.0 / 360.0);
	m_state = TracksState::TURNING_RIGHT;
	turnRight();
}

void Tracks::counterClockwiseTurn(int angle)
{
	m_delay = floor(angle * 11000.0 / 360.0);
	m_state = TracksState::TURNING_LEFT;
	turnLeft();
}

void Tracks::clockwiseCircle()
{
	m_delay = 10750;
	m_state = TracksState::TURNING_RIGHT;
	turnRight();
}

void Tracks::counterClockwiseCircle()
{
	m_delay = 11250;
	m_state = TracksState::TURNING_LEFT;
	turnLeft();
}

void Tracks::goForward(int units)
{
	m_state = TracksState::MOVING_FORWARD;
	m_delay = units * MOVE_TIME;
	forward();
}

void Tracks::goBackward(int units)
{
	m_state = TracksState::MOVING_BACKWARD;
	m_delay = units * MOVE_TIME;
	backward();
}
