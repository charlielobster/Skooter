#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <FS.h>

#include "EspyRequestHandler.h"
#include "SkooterFiles.h"
#include "EspySerial.h"

typedef enum RequestState
{
    AVAILABLE,
    PROCESSING_REQUEST
} EspyRequestState;

EspyRequestState requestState = RequestState::AVAILABLE;
String localFiles = "";

ESP8266WebServer server;

void wifiLogin()
{
    int i = 0;

    WiFi.mode(WIFI_STA);
    WiFi.begin("CCNYPhysicsClub_2.4", "SuperSecurePassword@Physics421");

    while (WiFi.status() != WL_CONNECTED && i < 5000)
    {
        delay(500);
        i += 500;
    }
}

void onRoot()
{
    digitalWrite(LED_BUILTIN, 1);
    server.send(200, "text/html", EspyRequestHandler::welcomeMessage);
    digitalWrite(LED_BUILTIN, 0);
}

void checkFileName()
{
    digitalWrite(LED_BUILTIN, 1);

    String fileName = server.uri();
    String withoutSlash = fileName.substring(1);

    if (localFiles.indexOf(fileName) >= 0) 
    {
        EspyRequestHandler::streamFile(server, fileName);
    }
    else if (SkooterFiles::asList.indexOf(withoutSlash) >= 0)
    {
        // ask Skooter for the file contents
        Serial.print(withoutSlash + '~');      

        // set the file EspySerial will write to
        EspySerial::setFile(fileName);   

        // append the file name to the local files
        if (localFiles.length() > 0) localFiles.concat(',');
	    localFiles += fileName; 	

        server.send(200, "text/html", "Your request is being processed");
        
        // enter processing state
        //requestState = RequestState::PROCESSING_REQUEST;
    }
    else 
    {
        server.send(404, "text/plain", 
        EspyRequestHandler::getFileNotFoundMessage(server));
    }
       
    digitalWrite(LED_BUILTIN, 0);
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, 1);

    Serial.begin(38400);    
    SPIFFS.begin();
    SPIFFS.format();

    wifiLogin();

    MDNS.begin("esp8266");

    server.on("/", onRoot);
    server.onNotFound(checkFileName);
    server.begin();

    digitalWrite(LED_BUILTIN, 0);
}

void handleRequests()
{
    switch (requestState)
    {
        case RequestState::AVAILABLE:
            server.handleClient();
            break;

	case RequestState::PROCESSING_REQUEST:
	    if (EspySerial::state == SerialState::NO_TRANSACTION) 
	    {
	        EspyRequestHandler::streamFile(server, EspySerial::lastFileName());
	        requestState = RequestState::AVAILABLE;
	    }
	    break;

	default:
	    break;
    }
}

void loop()
{
	EspySerial::checkBuffer();
	handleRequests();
	MDNS.update();
}
