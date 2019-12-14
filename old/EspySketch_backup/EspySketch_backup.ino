#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#ifndef STASSID
#define STASSID "CCNYPhysicsClub_2.4"
#define STAPSK  "SuperSecurePassword@Physics421"
#define LOG_FILE "/log.txt"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const char* LOG_FILE_NAME = LOG_FILE;



ESP8266WebServer server(80);

const int COMMAND_TIME = 500;
const int DELAY_TIME = 50;

typedef enum SERIAL_STATE 
{
  NONE = 0,
  REQUESTING_DIRECTORY_CONTENTS,
  RECEIVING_DIRECTORY_CONTENTS,
  REQUESTING_FILE_CONTENTS,
  RECEIVING_FILE_CONTENTS
} states;

//typedef enum {  NONE, GOT_R, GOT_S, GOT_G } states;

// current state-machine state
states state = NONE;
// current partial number
unsigned int currentValue;

void setup ()
{
  Serial.begin (115200);
  state = NONE;
}  // end of setup

void processRPM (const unsigned int value)
{
  // do something with RPM 
  Serial.print ("RPM = ");
  Serial.println (value);
} // end of processRPM

void processSpeed (const unsigned int value)
{
  // do something with speed 
  Serial.print ("Speed = ");
  Serial.println (value);
} // end of processSpeed

void processGear (const unsigned int value)
{
  // do something with gear 
  Serial.print ("Gear = ");
  Serial.println (value);  
} // end of processGear

void handlePreviousState ()
{
  switch (state)
  {
  case GOT_R:
    processRPM (currentValue);
    break;
  case GOT_S:
    processSpeed (currentValue);
    break;
  case GOT_G:
    processGear (currentValue);
    break;
  }  // end of switch  

  currentValue = 0; 
}  // end of handlePreviousState

void processIncomingByte (const byte c)
{
  if (isdigit (c))
  {
    currentValue *= 10;
    currentValue += c - '0';
  }  // end of digit
  else 
  {

    // The end of the number signals a state change
    handlePreviousState ();

    // set the new state, if we recognize it
    switch (c)
    {
    case 'R':
      state = GOT_R;
      break;
    case 'S':
      state = GOT_S;
      break;
    case 'G':
      state = GOT_G;
      break;
    default:
      state = NONE;
      break;
    }  // end of switch on incoming byte
  } // end of not digit  
  
} // end of processIncomingByte

void loop ()
{


  // do other stuff in loop as required
  
}  // end of lo




























void checkSerial()
{
  
}

void handleRoot() 
{
  String response = "";
  String fileNames = "";
  String contents = "";
  String fileName = "";
  int len = 0;

  digitalWrite(LED_BUILTIN, 1);
  
  // communicate with Skooter via the Serial port 
  Serial.print("12-getDirectory");
  Serial.flush();
  delay(COMMAND_TIME);
  
  while (Serial.available()) {
    len = Serial.parseInt();
    Serial.read();
    for (int i = 0; i < len; i++) { 
      while (!Serial.available()) ;
      fileNames.concat((char)Serial.read());
    }
  }

  while (fileNames.length() > 0) {    
    len = fileNames.indexOf(',');
    if (len > -1) { 
      fileName = fileNames.substring(0, len); // strip off ','
      fileNames = fileNames.substring(len + 1);    
    } else {
      fileName = fileNames;
      fileNames = "";
    }
    contents += ("<a href=\"" + fileName + "\">" + fileName + "</a><br>");
  }

  response = String("<html><body>") + 
    String("<p>Welcome to Skooter's TOTALLY AWESOME website!</p><br>") +
    String("Browse Skooter's TOP SECRET data files!<br>") + 
      contents + 
    String("</body></html>");
  server.send(200, "text/html", response);   
  
  digitalWrite(LED_BUILTIN, 0);
}

void handleFileRequest() 
{  
  File logFile = SPIFFS.open(LOG_FILE_NAME, "r");                 // Open it
  size_t sent = server.streamFile(logFile, "text/plain");
  
  Serial.println("sent " + String(sent) + " bytes");
/*  
  char buf[1024];
  int siz = logFile.size();
  while(siz > 0) {
    size_t len = std::min((int)(sizeof(buf) - 1), siz);
    logFile.read((uint8_t *)buf, len);
    server.client().write((const char*)buf, len);
    siz -= len;
  }
  */
  logFile.close(); 
}

void setup(void) 
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  Serial.begin(9600);

  bool r = SPIFFS.begin();  
  if (r) Serial.println("Beginning SPIFF"); 
  File logFile = SPIFFS.open(LOG_FILE_NAME, "w");                 // Open it
  Serial.println("logFile.size(): " + String(logFile.size()));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  logFile.print("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    logFile.print(".");
  }
  logFile.println("");
  logFile.print("Connected to ");
  logFile.println(ssid);
  logFile.print("IP address: ");
  logFile.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    logFile.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleFileRequest);
  
  server.begin();
  logFile.println("HTTP server started");
  logFile.close(); 
}

SerialState getCurrentRequestState()
{
  return NONE;
}

void loop(void) {
  // first check if Skooter is sending us some data
  while (Serial.available())
    processIncomingByte (Serial.read());
  // now see if there is some requests to ask Skooter's help for
  // if (we need to make or are currently making a request to Skooter)
  //  check that we have some room to write out the rest of the request
  
  server.handleClient();
  MDNS.update();
}
