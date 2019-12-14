#ifndef _ESPY_SERIAL_H_
#define _ESPY_SERIAL_H_

#include "EspyFileSystem.h"
#include "ResponseHandler.h"

// Espy's Serial buffer appears to have a 270 character maximum
// We keep to n < 256 chars to be on the safe side

typedef enum SerialState
{
    INIT,
	WAITING_FOR_DIRECTORY_CONTENTS,
	READING_DIRECTORY_CONTENTS,
	WAITING_FOR_FILE_CONTENTS,
	READING_FILE_CONTENTS,
    IDLE
} EspySerialState;

class EspySerial
{
public:
//	static const int MAX_BUFFER_SIZE = 251;

	static void begin()
	{
		Serial.begin(74880);
		
		// wait half a second
		delay(500);

		// clear the buffer
		while (Serial.available()) {
			Serial.read();
		}

		// tell Skooter we need directory contents
		m_state = SerialState::WAITING_FOR_DIRECTORY_CONTENTS;
	}

	static void checkBuffer()
	{
		char buf[256];
		int len;

		// if there is anything on the Serial buffer
		if (Serial.available() > 0) 
		{
			// if the signal for a message ('m') has been given 
			// we should read the byte from the buffer
			if (SerialState::WAITING_FOR_DIRECTORY_CONTENTS)
			{
				m_state = SerialState::READING_DIRECTORY_CONTENTS;
			}
			else if (m_state == SerialState::READING_DIRECTORY_CONTENTS)
			{
				//Serial.println("Checking if i: " + String(i + 1) + " ==  s.length(): " + String(s.length()));

				//// the first byte matches the length of the message, 
				//// so we should process it      
				//if (Serial.available() == (i + 3)) { 
				//    // +3 since +1 for message length, +1 \r, +1 \n
				//	len = Serial.available();
				//	Serial.read(); // we've already inspected the message length
    //                int j = 0;
    //                while (j < len) 
    //                { 
    //                    if (Serial.available()) 
    //                    { 
    //                        buf[j++] = Serial.read();
    //                    }
    //                }
				//	if (j != len) {
				//		Serial.println("FAIL");
				//	}
				//	buf[len] = '\0';
				//	m_currentMessage += buf;
		//			if (len < MAX_BUFFER_SIZE + 3) {
						// currentMessage must be complete, save to file

				m_currentMessage += Serial.readStringUntil('\n');

//						Serial.println("got this: " + m_currentMessage);
						//EspyFileSystem::saveFileContents(ResponseHandler::directoryFileName(), m_currentMessage);
						//ResponseHandler::setWelcomeMessage();

				m_state = SerialState::IDLE;
			}
			else if (m_state == SerialState::IDLE) 
			{
				Serial.println("Idle consuming: " + (char)Serial.peek());
				// this is not addressed to us consume it to free up the buffer
				while (Serial.available()) Serial.read();
			}
		}
	}

private:
	static EspySerialState m_state;
	static String m_currentMessage;
};

EspySerialState EspySerial::m_state = SerialState::INIT;
String EspySerial::m_currentMessage = "";

#endif
