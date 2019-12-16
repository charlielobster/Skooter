#include "Cabinet.h" 

Cabinet::Cabinet() : 
    m_softwareSerial(ESP_TX_PIN, ESP_RX_PIN), 
    m_fileCount(0), 
    m_state(CabinetState::NO_ACTIVITY),
    m_requestedFileNameIndex(0),
    m_currentLineIndex(0)
{
    strcpy(m_currentFileName, "");
    strcpy(m_requestedFileName, "");
    strcpy(m_currentLine, "");
}

void Cabinet::setup() 
{
    m_softwareSerial.begin(38400);   
	delay(DELAY);

	SD.begin(CHIP_SELECT);
	delay(DELAY);

	if (CLEAR_DIRECTORY_AT_SETUP) 
	{ 
		clearDirectory();
	} 
	else 
	{
		writeDirectoryContents();
	}

    sprintf(m_currentFileName, "skdat_%d.txt", m_fileCount);
	delay(DELAY);

	openCurrentFile();
	delay(DELAY);
}

// only during setup
void Cabinet::clearDirectory()
{
    File root = SD.open("/");
    delay(DELAY);

    while (!root)
    {
        SD.end();
        SD.begin(CHIP_SELECT);
        root = SD.open("/");                
    }

    root.rewindDirectory();
    delay(DELAY);

    m_currentFile = root.openNextFile();
	delay(DELAY);

    while (m_currentFile) 
    {   
        strcpy(m_currentFileName, m_currentFile.name());
        m_currentFile.close();
		delay(DELAY);

        SD.remove(m_currentFileName);
		delay(DELAY);

        m_currentFile = root.openNextFile();            
		delay(DELAY);
    }

    root.close();
    delay(DELAY);
}

// only during setup
void Cabinet::writeDirectoryContents()
{
    m_fileCount = 0;
	File root = SD.open("/");
	delay(DELAY);

    while (!root)
    {
        SD.end();
        SD.begin(CHIP_SELECT);
        root = SD.open("/");                
    }

	root.rewindDirectory();
	delay(DELAY);

    m_currentFile = root.openNextFile();
    delay(DELAY);

    while (m_currentFile) 
    {
        m_fileCount++;
		strcpy(m_currentFileName, m_currentFile.name());
        writeCurrentFileName();
        delay(DELAY);
        
        m_currentFile.close();
		delay(DELAY);

		m_currentFile = root.openNextFile();
        delay(DELAY);
    }
        
    root.close();
    delay(DELAY);
}

void Cabinet::checkForFileName()
{
    char c;
    while (m_softwareSerial.available() > 0) 
    { 
        c = (char)m_softwareSerial.read();
        if (c != '~') 
        { 
           m_requestedFileName[m_requestedFileNameIndex++] = c;
        }
        else 
        {
            m_requestedFileName[m_requestedFileNameIndex] = '\0';
            m_state = CabinetState::OPENING_REQUESTED_FILE;
           // Serial.println("requested file "); 
           // Serial.println(m_requestedFileName);
        }
    }         
}

void Cabinet::loop()
{    
    checkForFileName();
    switch (m_state) 
    {         
    case CabinetState::OPENING_REQUESTED_FILE:
        checkIfRequestedFileIsOpen();
        break;

    case CabinetState::OPENING_CURRENT_FILE:
        openCurrentFile();       
        break;

	case CabinetState::WRITING_TO_CURRENT_FILE:
		writeToCurrentFile();
        break;

    case CabinetState::NO_ACTIVITY:
    default:
        //while (m_softwareSerial.available() > 0) 
		//{ 
        //    Serial.print((char)m_softwareSerial.read());
        //}
        break;
    }
}

void Cabinet::checkIfRequestedFileIsOpen()
{
   if (m_currentFile) m_currentFile.close();
    m_currentFile = SD.open(m_requestedFileName, FILE_READ);            
    if (!m_currentFile)
    {
        SD.end();
        if (!SD.begin(CHIP_SELECT)) ;
        m_currentFile = SD.open(m_requestedFileName, FILE_READ);
    }                
	if (m_currentFile) 
	{        
        m_softwareSerial.print('f');
        int sz = m_currentFile.size();
        m_currentFile.seek(0);
        for (int i = 0; i < sz; i++) 
		{
            char c = (char)m_currentFile.read();
            m_softwareSerial.print(c);
          //  Serial.print(c);
        }
        m_softwareSerial.print('~');
        m_currentFile.close();
    
        strcpy(m_requestedFileName, "");
        m_requestedFileNameIndex = 0;

        m_state = CabinetState::OPENING_CURRENT_FILE;
        openCurrentFile();
    }
}

void Cabinet::openCurrentFile()
{
    if (m_currentFile)  m_currentFile.close();
    m_currentFile = SD.open(m_currentFileName, FILE_WRITE);            
    if (!m_currentFile)
    {
        SD.end();
        if (!SD.begin(CHIP_SELECT)) ;
        m_currentFile = SD.open(m_currentFileName, FILE_WRITE);
    }                  
    if (m_currentFile)
    {
        if (strlen(m_currentLine) > 0)
        {
            m_state = CabinetState::WRITING_TO_CURRENT_FILE;
            writeToCurrentFile();
        }
        else
        { 
            m_state = CabinetState::NO_ACTIVITY;
        }
    } 
}

void Cabinet::writeCurrentFileName()
{
    m_softwareSerial.print('d');
    m_softwareSerial.print(m_currentFileName);
    m_softwareSerial.print('~');
 }

void Cabinet::writeToCurrentFile()
{
    static int i = 0;
    if (m_currentFile && strlen(m_currentLine) > 0)
    {
        if ((m_currentFile.size() + strlen(m_currentLine) - m_currentLineIndex) > MAX_FILE_SIZE)
        {
            writeCurrentFileName();
            m_currentFile.close();      
            m_fileCount++;      
            sprintf(m_currentFileName, "skdat_%d.txt", m_fileCount);
            m_state = CabinetState::OPENING_CURRENT_FILE;
            openCurrentFile();            
        }
        else 
        {            
            if (m_currentLineIndex < strlen(m_currentLine))
            {                
                if (!m_currentFile.write(m_currentLine[m_currentLineIndex]))                
                {
                    m_state = CabinetState::OPENING_CURRENT_FILE;  
                    openCurrentFile();                  
                } 
                else 
                {
                    m_currentLineIndex++;
                }
            }
            else
            {
            //    Serial.println("finishing line " + String(i++));
                m_currentFile.write('\r');
                m_currentFile.write('\n');
                m_currentFile.flush();
                strcpy(m_currentLine, "");
                m_state = CabinetState::NO_ACTIVITY;
            }
        }
    }
}

void Cabinet::writeLine(String line)
{
	strcpy(m_currentLine, line.c_str());
    m_currentLineIndex = 0;
    m_state = CabinetState::WRITING_TO_CURRENT_FILE;
}
