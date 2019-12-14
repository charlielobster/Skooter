#ifndef _ESPY_WIFI_H_
#define _ESPY_WIFI_H_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class EspyWifi
{
public:
	static const int MAX_WAIT_TIME = 5000;

	static bool login()
	{
		bool result = false;
		int i = 0;

		WiFi.mode(WIFI_STA);
		WiFi.begin(m_ssid, m_password);

		while (WiFi.status() != WL_CONNECTED && i < MAX_WAIT_TIME) 
		{
			delay(500);
			i += 500;
		}
		if (i < MAX_WAIT_TIME) result = true;
		return result;
	}

	static String ssid() 
	{ 
		return m_ssid; 
	}

private:
	static String m_ssid;
	static String m_password;
};

//String EspyWifi::m_ssid = "brunnhilde";
//String EspyWifi::m_password = "glColor5f";  // typically 192.168.0.10
 String EspyWifi::m_ssid = "CCNYPhysicsClub_2.4";
 String EspyWifi::m_password = "SuperSecurePassword@Physics421"; // typically 192.168.110.101

#endif 
