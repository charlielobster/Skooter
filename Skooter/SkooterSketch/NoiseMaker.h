#ifndef _NOISEMAKER_H_
#define _NOISEMAKER_H_

class NoiseMaker
{
public:
	static const int BUZZER_PIN = 8; 

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

   void makeFoundYouNoise()
   {
        for (int j = 4; j > 0; j--) { 
            tone(BUZZER_PIN, j * 256 - 1);
            delay(50);
            noTone(BUZZER_PIN);
            delay(50);
        }
   }
};


#endif
