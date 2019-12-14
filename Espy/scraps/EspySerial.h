#ifndef _ESPY_SERIAL_H_
#define _ESPY_SERIAL_H_

#include <FS.h>

#include "ResponseHandler.h"

typedef enum EspyState
{
    WAITING_FOR_DIRECTORY,
    WAITING_FOR_FILE,
    IDLE
} SerialState;

class EspySerial
{
public:
	static void begin()
	{
	    m_file = SPIFFS.open(EspyFileSystem::directoryFileName, "w");
	}

    static void waitForFile(String fileName)
    {
        m_file = SPIFFS.open(fileName, "w");
        m_state = EspyState::WAITING_FOR_FILE;
    }

	static void checkBuffer()
	{
        if (m_state != EspyState::IDLE) 
		{ 
        	while (Serial.available() > 0)
        	{
        		m_byte = Serial.read();
        		if (m_byte != '~') 
        		{
    				m_file.write(m_byte);
        		}
        		else 
        		{
                    m_file.close();
                    if (m_state == EspyState::WAITING_FOR_DIRECTORY) 
                    { 
                        ResponseHandler::setWelcomeMessage();
						Serial.println(ResponseHandler::welcomeMessage);
                    }
					m_state = EspyState::IDLE;
				}
        	}
        }
	}

private:
	static int m_byte;
	static File m_file;
    static SerialState m_state;

};

File EspySerial::m_file = SPIFFS.open("dummy.txt", "r");
int EspySerial::m_byte = 0;
SerialState EspySerial::m_state = EspyState::WAITING_FOR_DIRECTORY;

#endif
