#ifndef _ESPY_H_
#define _ESPY_H_

#include <ESP8266WebServer.h>

class Espy
{
public: 
  const int COMMAND_TIME = 500;
  const int DELAY_TIME = 50;
  
  Espy() : server(80){}
  ~Espy(){}
  
  void setup()
  {
    server.on("/", std::bind(&Espy::handleRoot, this));    
    server.onNotFound(std::bind(&Espy::checkIfFileExists, this));
    server.begin();
  }
  
  void handleRoot(void) 
  {
    String contents = "";
    String fileName = "";
  
    digitalWrite(LED_BUILTIN, 1);
    
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
    server.send(200, "text/html", "<html><body><p>Welcome to Skooter's TOTALLY AWESOME website!</p><br>Browse Skooter's TOP SECRET data files!<br>" + contents + "</body></html>");   
    digitalWrite(LED_BUILTIN, 0);
  }

  void checkIfFileExists() 
  {
    String contents = "";
    String line = "";
    digitalWrite(LED_BUILTIN, 1);
  
    // ask Skooter for the file contents
    Serial.println("getFile");
    delay(COMMAND_TIME);
    while (Serial.available()) {
      line = Serial.readStringUntil('\n');    
      contents += (line + '\n');
      delay(DELAY_TIME);
    }
    if (contents != "") { 
  
      server.send(200, "text/plain", contents);
    
    } else {
      
      String message = "File Not Found\n\n";
      message += "URI: ";
      message += server.uri();
      message += "\nMethod: ";
      message += (server.method() == HTTP_GET) ? "GET" : "POST";
      message += "\nArguments: ";
      message += server.args();
      message += "\n";
      for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      }
      server.send(404, "text/plain", message);
    }
    digitalWrite(LED_BUILTIN, 0);
  }

  void loop()
  {
      server.handleClient();
  }

private:
  ESP8266WebServer server;
  
};

#endif
