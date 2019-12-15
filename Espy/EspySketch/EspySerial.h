#ifndef _ESPY_SERIAL_H_
#define _ESPY_SERIAL_H_

#include <FS.h>

typedef enum SerialState
{
	NO_TRANSACTION,
	WAITING_FOR_FILE,
	GETTING_FILE_NAME,
	GETTING_FILE_CONTENTS
} EspySerialState;

class EspySerial
{
public:
	static EspySerialState state;

	static void setFile(String fileName)
	{
		m_fileName = fileName;
		m_file = SPIFFS.open(m_fileName, "w");
		state = SerialState::WAITING_FOR_FILE;
	}

	static String lastFileName() { return m_fileName; }

	static void checkBuffer()
	{
		switch (state)
		{
		case SerialState::NO_TRANSACTION:
			if (Serial.peek() == 'd')
			{
				Serial.read();
				if (SkooterFiles::asList.length() > 0) SkooterFiles::asList.concat(',');
				state = SerialState::GETTING_FILE_NAME;
				getFileNameData();
			}
			break;

		case SerialState::WAITING_FOR_FILE:
			if (Serial.peek() == 'f')
			{
				Serial.read();
				state = SerialState::GETTING_FILE_CONTENTS;
				getFileData();
			}
			break;

		case SerialState::GETTING_FILE_NAME:
			getFileNameData();
			break;

		case SerialState::GETTING_FILE_CONTENTS:
			getFileData();
			break;

		default:
			break;
		}
	}

	static void getFileNameData()
	{
		char c;
		while (Serial.available() > 0)
		{
			c = (char)Serial.read();
			if (c != '~')
			{
				SkooterFiles::asList.concat(c);
			}
			else
			{
				SkooterFiles::appendTag();
				EspyRequestHandler::createWelcomeMessage();
				state = SerialState::NO_TRANSACTION;
			}
		}
	}

	static void getFileData()
	{
		char c;
		while (m_file && Serial.available() > 0)
		{
			c = (char)Serial.read();
			if (c != '~')
			{
				m_file.write(c);
			}
			else
			{
				m_file.close();
				state = SerialState::NO_TRANSACTION;
			}
		}
	}

private:
	static File m_file;
	static String m_fileName;
};

EspySerialState EspySerial::state = SerialState::NO_TRANSACTION;
String EspySerial::m_fileName = "dummy.txt";
File EspySerial::m_file = SPIFFS.open("dummy.txt", "r");

#endif
