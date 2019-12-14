#include "Cabinet.h" 

Cabinet::Cabinet() : m_softwareSerial(ESP_TX_PIN, ESP_RX_PIN), m_fileCount(0) {}

void Cabinet::setup() 
{
	if (!SD.begin(CHIP_SELECT)) {
		Serial.println("Cabinet - initialization failed");
	}
   
    clearDirectory();
    m_softwareSerial.begin(74880);   

    m_fileCount = writeDirectoryContents();
    m_currentFileName = getNextFileName();
    writeNextFileName(m_currentFileName);
}

void Cabinet::clearDirectory()
{
    File root = SD.open("/");
    delay(DELAY);
    if (root) { 
        File f = root.openNextFile();
        while (f) 
        {
            SD.remove(String(f.name()));
            f.close();
            delay(DELAY);
            
            f = root.openNextFile();
            delay(DELAY);
        }
        root.close();
        delay(DELAY);
    }    
}

void Cabinet::checkBuffer()
{    
    if (m_softwareSerial.available() > 0)
    {
        String fileName = "";
        while (m_softwareSerial.available() > 0) { 
            fileName.concat((char)m_softwareSerial.read());
            delay(10);
        }
        writeFileContents(fileName);
    }
}

void Cabinet::openCurrentFile()
{
    m_dataFile = SD.open(m_currentFileName, FILE_WRITE);
    delay(DELAY);
    if (!m_dataFile) 
    {        
        Serial.println("openCurrentFile - error opening " + m_currentFileName);
    }
}

String Cabinet::getNextFileName()
{
    return String(_NAME_PREFIX_) + String(m_fileCount) + String(_EXTENSION_);
}

void Cabinet::writeFileContents(String fileName)
{    
    File f = SD.open(fileName, FILE_READ);
    delay(DELAY);
    
    if (f) {
        m_softwareSerial.print('f');
        int sz = f.size();
        for (int i = 0; i < sz; i++) {
            char c = (char)f.read();
            m_softwareSerial.print(c);
        }
        m_softwareSerial.print('~');
        m_softwareSerial.flush();            
        f.close();
    }
}

int Cabinet::writeDirectoryContents()
{
    int fileCount = 1;
    File root = SD.open("/");
    delay(DELAY);
    if (root) { 
        File f = root.openNextFile();
        delay(DELAY);
        while (f) 
        {
            fileCount++;
            writeNextFileName(f.name());
            delay(DELAY);
            
            f.close();
            f = root.openNextFile();
            delay(DELAY);
        }
        root.close();
    }
    return fileCount;
}

void Cabinet::writeNextFileName(String fileName)
{
    int len = fileName.length();
    m_softwareSerial.print('d');
    for (int i = 0; i < len; i++) { 
        m_softwareSerial.print(fileName.charAt(i));
    }        
    m_softwareSerial.print('~');
    m_softwareSerial.flush();    
}

void Cabinet::writeLine(String s)
{
	if (m_dataFile) 
	{		
        if ((m_dataFile.size() + s.length()) > MAX_FILE_SIZE) 
        {   
            closeCurrentFile();
            m_fileCount++;
            m_currentFileName = getNextFileName();
            writeNextFileName(m_currentFileName);
            openCurrentFile();
        }
		m_dataFile.println(s);
	}
}

void Cabinet::closeCurrentFile()
{
    m_dataFile.close();
    delay(DELAY);
}
