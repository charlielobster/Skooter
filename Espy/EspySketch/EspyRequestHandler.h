#ifndef _ESPY_REQUEST_HANDLER_H_
#define _ESPY_REQUEST_HANDLER_H_

#include <ESP8266WebServer.h>
#include <FS.h>

#include "SkooterFiles.h"

class EspyRequestHandler
{
public:
	static String welcomeMessage;
	static String processingRequestMessage;

	static String getFileNotFoundMessage(const ESP8266WebServer &server)
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

	static void streamFile(ESP8266WebServer &server, String fileName)
	{
		File f = SPIFFS.open(fileName, "r");
		size_t sent = server.streamFile(f, "text/plain");
		f.close();
	}

	static void createWelcomeMessage()
	{
		String message = "";
		message = 
			(message +
				"<html><body><p>" +
				"Welcome to <b>ESPY'S TOTALLY AWESOME</b> website!" +
				"</p><br>" +
				"I talk to <b>Skooter</b> all the time! We are BFFs!<br>&nbsp;<br>" +
				"Psst!...<br>" +
				"I have some of <b>Skooter\'s TOP-SECRET data files!</b><br>Wanna see 'em?" +
				"<br>&nbsp;<br>" +
				(SkooterFiles::asTags.length() > 0 ? 
					SkooterFiles::asTags : "DRAT! Skooter must be asleep!!") +
				"<br>&nbsp;<br>" +
				"</body></html>"
			);
		welcomeMessage = message;
	}
};

String EspyRequestHandler::welcomeMessage =
"<html><body><p>Welcome to ESPY'S website!</p><br>Under construction!</body></html>";

String EspyRequestHandler::processingRequestMessage =
"<html><body>File is being saved to the cache.<br>Please try again in a moment!</body></html>";

#endif
