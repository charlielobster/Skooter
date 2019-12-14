#include <SoftwareSerial.h> 
SoftwareSerial mySerial(3, 2);  //RX,TX 
 
//  Arduino pin 2 (RX) to ESP8266 TX 
//  Arduino pin 3 to voltage divider then to ESP8266 RX 
//  Connect GND from the Arduiono to GND on the ESP8266 
//  Pull ESP8266 CH_PD HIGH 
  
void setup()  
{     
    pinMode(LED_BUILTIN, OUTPUT); 
    Serial.begin(9600);     // communication with the host computer 
    // Start the software serial for communication with the ESP8266 
    mySerial.begin(115200);   
    Serial.println("EspyHandler.setup");
} 
  
void loop()  
{ 
    // listen for communication from the ESP8266 and then write it to the serial monitor 
    if (mySerial.available())   
    {  
      String s = mySerial.readStringUntil('\n');
      s = s.substring(0, s.length() - 1); // strip off the \r
      Serial.println(s);      
      if (s == "getDirectory") { 
        mySerial.println("file1.txt");          
        mySerial.println("file2.txt");          
        mySerial.println("file3.txt");          
      } else if (s == "getFile") { 
        mySerial.println("line 1");
        mySerial.println("line 2");
      }
    }    
}
