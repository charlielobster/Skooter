#ifndef _NOISEMAKER_H_
#define _NOISEMAKER_H_

typedef enum NoiseMakerState
{
	OFF,
	STARTUP_NOISE_BUZZER_ON,
	STARTUP_NOISE_BUZZER_OFF,
	FOUND_YOU_NOISE_ON,
	FOUND_YOU_NOISE_OFF
} noiseMakerState;

class NoiseMaker
{
public:
	static const int BUZZER_PIN = 8; 

	NoiseMaker() : 
		m_state(NoiseMakerState::OFF),
		m_delay(0) {}

	void setup() 
	{
		pinMode(BUZZER_PIN, OUTPUT); 
		makeStartupNoise();
	}

	void loop()
	{
        m_delay--;
        if (m_delay <= 0) m_delay = 0;

        if (m_delay == 0)
        {
            switch (m_state)
            {
            case NoiseMakerState::FOUND_YOU_NOISE_ON:
                
                break;
            }
        }
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

private:
	noiseMakerState m_state;
	int m_delay;
};


#endif
