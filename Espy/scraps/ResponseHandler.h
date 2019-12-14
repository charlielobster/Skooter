#ifndef _RESPONSE_HANDLER_H_
#define _RESPONSE_HANDLER_H_

#include <ESP8266WebServer.h>

#include "EspyFileSystem.h"

class ResponseHandler
{
public:
	static String welcomeMessage;

	static void setWelcomeMessage()
	{
		welcomeMessage = createWelcomeMessage();
	}

	static String getFileNotFoundMessage(ESP8266WebServer &server)
	{
		String message = "File Not Found\n\n";
		message += "URI: ";
		message += server.uri();
		message += "\nMethod: ";
		message += (server.method() == HTTP_GET) ? "GET" : "POST";
		message += "\nArguments: ";
		message += server.args();
		message += "\n";
		for (uint8_t i = 0; i < server.args(); i++)
		{
			message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
		}
		return message;
	}

private:
	static String getFileTags()
	{
		int len = 0;
		String contents = "";
		String fileName = "";
		String fileContents = EspyFileSystem::getFileContents(EspyFileSystem::directoryFileName);

		if (fileContents.length() > 0)
		{
			while (fileContents.length() > 0)
			{
				len = fileContents.indexOf(',');
				if (len > -1)
				{
					fileName = fileContents.substring(0, len);
					fileContents = fileContents.substring(len + 1);
				}
				else
				{
					fileName = fileContents;
					fileContents = "";
				}
				contents += ("<a href=\"" + fileName + "\">" + fileName + "</a><br>");
			}	// end while
		}
		else
		{
			contents = "DRAT! Skooter must be sleeping at the moment...that JERK-FACE!!";
		}
		return contents;
	}

	static String createWelcomeMessage()
	{
		String fileTags = getFileTags();
		String message = "";
		message =
			(message +
				"<html><body><p>" +
				"Welcome to ESPY'S TOTALLY AWESOME website!" +
				"</p><br>" +
				"I talk to Skooter all the time! We are like BFFs!<br>&nbsp;<br>" +
				"Psst...I have some of Skooter\'s TOP-SECRET data files! Wanna see?" +
				"<br>&nbsp;<br>" +
				    fileTags +
				"<br>&nbsp;<br>" +
//				"You can always look at my log file too! " +
//				"<a href=\"" + EspyFileSystem::logFileName + "\">" +
//				EspyFileSystem::logFileName +
//				"</a>" +
				"</body></html>"
			);
		return message;
	}
};

String ResponseHandler::welcomeMessage = 
	"<html><body><p>Welcome to ESPY'S website!</p><br>Under construction!</body></html>";

#endif
