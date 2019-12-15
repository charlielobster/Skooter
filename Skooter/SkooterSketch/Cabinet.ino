#include "Cabinet.h" 

Cabinet::Cabinet() : 
    m_softwareSerial(ESP_TX_PIN, ESP_RX_PIN), 
    m_fileCount(0), 
    m_currentFileName(""),
    m_requestedFileName(""),
    m_state(SerialState::NO_ACTIVITY) {}

void Cabinet::setup() 
{
	if (!SD.begin(CHIP_SELECT)) {
		Serial.println("Cabinet - initialization failed");
	}
   
    //clearDirectory();
    m_softwareSerial.begin(38400);   

    m_fileCount = writeDirectoryContents() + 1;
    m_currentFileName = getNextFileName();
    writeNextFileName(m_currentFileName);
}

void Cabinet::clearDirectory()
{
    String fileName = "";
    File root = SD.open("/");
    if (root) { 
        File f = root.openNextFile();
        while (f) 
        {   
            fileName = String(f.name());
            Serial.println("removing file " + fileName);
            f.close();
            SD.remove(fileName);
            f = root.openNextFile();            
        }
        root.close();
    }    
}

void Cabinet::checkForFileName()
{
    char c;
    while (m_softwareSerial.available() > 0) 
    { 
        c = (char)m_softwareSerial.read();
        Serial.print(c);
        if (c != '~') 
        { 
           m_requestedFileName.concat(c);
        }
        else 
        {
            m_state = SerialState::NO_ACTIVITY;            
            writeFileContents(m_requestedFileName);
            m_requestedFileName = "";
        }
    }         
}

void Cabinet::checkBuffer()
{    
    switch (m_state) 
    { 
    case SerialState::NO_ACTIVITY:
        if (m_softwareSerial.available() > 0) 
        {
            m_state = SerialState::GETTING_FILE_NAME; 
            checkForFileName();
        }
        break;

    case SerialState::GETTING_FILE_NAME:
        checkForFileName();
        break;

    default:
        while (m_softwareSerial.available() > 0) { 
            Serial.print((char)m_softwareSerial.read());
        }
        break;
    }
}

void Cabinet::openCurrentFile()
{
    m_dataFile = SD.open(m_currentFileName, FILE_WRITE);
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
    Serial.println("writing file " + fileName);
    File f = SD.open(fileName, FILE_READ);
    
    if (f) {
        m_softwareSerial.print('f');
        int sz = f.size();
        for (int i = 0; i < sz; i++) {
            char c = (char)f.read();
            m_softwareSerial.print(c);
        }
        m_softwareSerial.print('~');
        f.close();
        Serial.println("done writing file " + fileName);
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
    String fullMessage = String('d') + fileName + String('~');
    Serial.println(fullMessage);
    m_softwareSerial.print(fullMessage);
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
}
