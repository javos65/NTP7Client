#include <NTP7Client.h> 

#include <WiFi.h> // for WiFi shield
#include <WiFiUdp.h>

const char *ssid     = "SSID;
const char *password = "Pass";

WiFiUDP ntpUDP;
NTP7Client timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 114400000); // ntp RTC client, UTC+1hr, 4-hourly update

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

if (WiFi.status() == WL_CONNECTED)
 {
  timeClient.begin();
  timeClient.update();
 }
 else Serial.print( "\n No Connection \n" );
 
}

void loop() {
  Serial.println(timeClient.getEpochTime());
  Serial.println(timeClient.getFormattedTime());
  Serial.println(timeClient.getFormattedTimeDay());
  
  delay(1000);
}
