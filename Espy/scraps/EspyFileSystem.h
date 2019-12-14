#ifndef _ESPY_FILE_SYSTEM_H_
#define _ESPY_FILE_SYSTEM_H_

#include <FS.h>

class EspyFileSystem
{
public:
	static String directoryFileName;
	static String logFileName;

	static void streamFile(String fileName, ESP8266WebServer &server)
	{
		File f = SPIFFS.open(fileName, "r");
		size_t sent = server.streamFile(f, "text/plain");
		// if (f.size() != sent) EspyFileSystem::log("problem sending file"); 
		f.close();
	}

	static bool foundFile(String fileName)
	{
		bool found = false;

		Dir dir = SPIFFS.openDir("/"); 
		while (!found && dir.next()) 
		{
			String nextFile = dir.fileName();
			Serial.println("checking " + fileName + " and " + nextFile);
			if (fileName == nextFile) {
				Serial.println("found file " + fileName);
				found = true;
			}
		}
		return found;
	}

	static String getFileContents(String fileName)
	{
		String contents = "";
		char buf[1024];
		size_t len = 0;

		File file = SPIFFS.open(fileName, "r");
		if (file) 
		{
			int fsize = file.size();
			while (fsize > 0) {
				len = std::min((int)(sizeof(buf) - 1), fsize);
				file.read((uint8_t *)buf, len);
				buf[len] = '\0';
				contents += buf;
				fsize -= len;
			}
		}
		return contents;
	}

	static void saveFileContents(String fileName, String contents)
	{
		File f = SPIFFS.open(fileName, "w");
		if (f) 
		{
			f.print(contents);
			f.flush();
			f.close();
		}
	}

	static void log(String msg)
	{
		File f = SPIFFS.open(logFileName, "w");
		f.println(msg);
		f.flush();
		f.close();
	}

private:
	static String m_currentFileName;
	static File m_currentFile;
};

String EspyFileSystem::directoryFileName = "/Skooter.txt";
String EspyFileSystem::logFileName = "/EspyLog.txt";
String EspyFileSystem::m_currentFileName = "";
File EspyFileSystem::m_currentFile = SPIFFS.open("/dummy.txt", "r");


#endif
