#ifndef _ESPY_SERVER_H_
#define _ESPY_SERVER_H_

#include <ESP8266WebServer.h>
#include <FS.h>

#include "EspyFileSystem.h"
#include "ResponseHandler.h"
#include "EspySerial.h"

class EspyServer
{
public:
	static const int HTTP_PORT = 80;

	EspyServer() : m_server(HTTP_PORT) {}
	~EspyServer() {}

	void setup()
	{
		m_server.on("/", std::bind(&EspyServer::onRoot, this));
		m_server.onNotFound(std::bind(&EspyServer::checkFileName, this));
		m_server.begin();
	}

	/*
	// communicate with Skooter via the Serial port
	Serial.println("getDirectory");

	delay(COMMAND_TIME);
	while (Serial.available()) {
		fileName = Serial.readStringUntil('\n');
		fileName = fileName.substring(0, fileName.length() - 1); // strip off the \r
		contents += ("<a href=\"" + fileName + "\">" + fileName + "</a><br>");
		Serial.println(fileName);
		delay(DELAY_TIME);
	}
	*/

	void onRoot()
	{
        digitalWrite(LED_BUILTIN, 1);
		Serial.println("onRoot");
		m_server.send(200, "text/html", "<html><body>here</body></html>");
		digitalWrite(LED_BUILTIN, 0);
	}

	void checkFileName()
	{
		String fileName = m_server.uri();
		Serial.println("checkFileName: " + fileName);

		digitalWrite(LED_BUILTIN, 1);

		if (EspyFileSystem::foundFile(fileName)) 
		{
            Serial.println("found file name: " + fileName);
			EspyFileSystem::streamFile(fileName, m_server);
		}
		else if (ResponseHandler::welcomeMessage.indexOf(fileName) >= 0)
		{
			// ask Skooter for the file contents
			EspySerial::waitForFile(fileName);
			Serial.println("waiting for file contents for " + fileName);

			/*File f = SPIFFS.open(fileName, "w");
			
			while (!Serial.available());

			bool endOfFile = false;

			while (!endOfFile)
			{
				if (Serial.available())
				{
					int bt = Serial.read();
					if (bt != '~') 
					{
						f.write(bt);
					}
					else 
					{
						endOfFile = true;
					}
				}				
			}
			f.close();*/
			m_server.send(200, "text/html", "<html><body>be there in a sec!</body></html>");
		}
		else 
		{
			m_server.send(404, "text/plain", ResponseHandler::getFileNotFoundMessage(m_server));
		}
       
		digitalWrite(LED_BUILTIN, 0);
	}

	void handleClient()
	{
		m_server.handleClient();
	}

private:
	ESP8266WebServer m_server;
};

#endif
