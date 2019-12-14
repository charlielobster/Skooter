
typedef enum {  NONE, GOT_R, GOT_S, GOT_G } states;

// current state-machine state
states state = NONE;
// current partial number
unsigned int currentValue;

void setup()
{
	Serial.begin(115200);
	state = NONE;
}  // end of setup

void processRPM(const unsigned int value)
{
	// do something with RPM 
	Serial.print("RPM = ");
	Serial.println(value);
} // end of processRPM

void processSpeed(const unsigned int value)
{
	// do something with speed 
	Serial.print("Speed = ");
	Serial.println(value);
} // end of processSpeed

void processGear(const unsigned int value)
{
	// do something with gear 
	Serial.print("Gear = ");
	Serial.println(value);
} // end of processGear

void handlePreviousState()
{
	switch (state)
	{
	case GOT_R:
		processRPM(currentValue);
		break;
	case GOT_S:
		processSpeed(currentValue);
		break;
	case GOT_G:
		processGear(currentValue);
		break;
	}  // end of switch  

	currentValue = 0;
}  // end of handlePreviousState

void processIncomingByte(const byte c)
{
	if (isdigit(c))
	{
		currentValue *= 10;
		currentValue += c - '0';
	}  // end of digit
	else
	{

		// The end of the number signals a state change
		handlePreviousState();

		// set the new state, if we recognize it
		switch (c)
		{
		case 'R':
			state = GOT_R;
			break;
		case 'S':
			state = GOT_S;
			break;
		case 'G':
			state = GOT_G;
			break;
		default:
			state = NONE;
			break;
		}  // end of switch on incoming byte
	} // end of not digit  

} // end of processIncomingByte

void loop()
{


	// do other stuff in loop as required

}  // end of lo






