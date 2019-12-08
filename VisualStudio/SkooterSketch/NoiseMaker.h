#ifndef _NOISEMAKER_H_
#define _NOISEMAKER_H_

class NoiseMaker
{
public:
	static const int BUZZER_PIN = 8; 
	long i = 0;

	void setup() 
	{
		pinMode(BUZZER_PIN, OUTPUT); 
		makeStartupNoise();
	}

	void makeStartupNoise() 
	{
		for (int i = 0; i < 3; i++) {
			tone(BUZZER_PIN, 1000);
			delay(100);
			noTone(BUZZER_PIN);
			delay(100);
		}
	}
};


#endif