#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <FS.h>

typedef enum EspyState
{
    IDLE,
    GETTING_FILE_NAME,
    GETTING_FILE
} SerialState;

SerialState state = EspyState::IDLE;
File file;
ESP8266WebServer server;
String directoryFileName = "/SkFiles.txt";
String welcomeMessage =
 "<html><body><p>Welcome to ESPY'S website!</p><br>Under construction!</body></html>";

void wifiLogin()
{
	int i = 0;

	WiFi.mode(WIFI_STA);
	WiFi.begin("ssid", "password");

	while (WiFi.status() != WL_CONNECTED && i < 5000)
	{
		delay(500);
		i += 500;
	}
}

String getFileContents(String fileName)
{
	String contents = "";
	char buf[1024];
	size_t len = 0;

	File f = SPIFFS.open(fileName, "r");
	if (f)
	{
		int fsize = f.size();
		while (fsize > 0) {
			len = std::min((int)(sizeof(buf) - 1), fsize);
			f.read((uint8_t *)buf, len);
			buf[len] = '\0';
			contents += buf;
			fsize -= len;
		}
	}
	return contents;
}

String getFileTags()
{
	int len = 0;
	String contents = "";
	String fileName = "";
	String fileContents = getFileContents(directoryFileName);
	
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
		contents += ("<a href=\"/" + fileName + "\">/" + fileName + "</a><br>");
	}		
	return contents;
}

String createWelcomeMessage()
{
	String fileTags = getFileTags();
	String message = "";
	message =
		(message +
			"<html><body><p>" +
			"Welcome to ESPY'S TOTALLY AWESOME website!" +
			"</p><br>" +
			"I talk to Skooter all the time! We are like BFFs!<br>&nbsp;<br>" +
			"Psst!...I have some of Skooter\'s TOP-SECRET data files! Wanna see?" +
			"<br>&nbsp;<br>" +
			(fileTags.length() > 0 ? fileTags : 
			    "DRAT! Skooter must be sleeping at the moment...that JERK-FACE!!") +
			"<br>&nbsp;<br>" +
			"</body></html>"
			);
	return message;
}

void getData()
{
    int bt;
    while (Serial.available() > 0)
    {
        bt = Serial.read();
        if (bt != '~') 
        {            
            file.write(bt);
        }
        else 
        {
            file.close();
            state = EspyState::IDLE;
        }
    }    
}

void checkBuffer()
{
    switch (state)
    {
    case EspyState::IDLE:
        if (Serial.peek() == 'd') 
        { 
            Serial.read();
            file = SPIFFS.open(directoryFileName, "a");
            file.seek(file.size(), SeekSet);
            if (file.size() > 0) file.write(',');
            state = EspyState::GETTING_FILE_NAME;            
            getData();
            if (state == EspyState::IDLE) 
            { 
                welcomeMessage = createWelcomeMessage();
            }
        } 
        else if (Serial.peek() == 'f') 
        { 
            Serial.read();
            state = EspyState::GETTING_FILE;
            getData();
        }
        break;
    
    case EspyState::GETTING_FILE_NAME:
        getData();
        if (state == EspyState::IDLE) 
        { 
            welcomeMessage = createWelcomeMessage();
        }
        break;

    case EspyState::GETTING_FILE:
        getData();
        break;

    default:
        break;
    }
}

bool foundFile(String fileName)
{
	Dir dir = SPIFFS.openDir("/");
    
	while (dir.next())
	{
		String nextFile = dir.fileName();
		if (fileName == nextFile) {
			return true;
		}
	}
	return false;
}


String getFileNotFoundMessage()
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

void onRoot()
{
    digitalWrite(LED_BUILTIN, 1);
    server.send(200, "text/html", welcomeMessage);
    digitalWrite(LED_BUILTIN, 0);
}

void checkFileName()
{
    digitalWrite(LED_BUILTIN, 1);

	String fileName = server.uri();

    if (foundFile(fileName)) 
    {
		File f = SPIFFS.open(fileName, "r");
		size_t sent = server.streamFile(f, "text/plain");
		f.close();
    }
    else if (welcomeMessage.indexOf(fileName) >= 0)
    {
        // ask Skooter for the file contents
		Serial.print(fileName.substring(1));        
        file = SPIFFS.open(fileName, "w");
        server.send(200, "text/html", "<html><body>File is being saved to the cache.<br>Please try again in a moment!</body></html>");
    }
    else 
    {
        server.send(404, "text/plain", getFileNotFoundMessage());
    }
       
    digitalWrite(LED_BUILTIN, 0);
}

void setup()
{
    Serial.begin(74880);
    SPIFFS.begin();
	SPIFFS.format();

    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, 1);

	file = SPIFFS.open(directoryFileName, "w");

	wifiLogin();

	MDNS.begin("esp8266");

    server.on("/", onRoot);
    server.onNotFound(checkFileName);
    server.begin();

    digitalWrite(LED_BUILTIN, 0);
}

void loop()
{
	checkBuffer();
	server.handleClient();
	MDNS.update();
}
