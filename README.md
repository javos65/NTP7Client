# NTP7Client

Connect to a NTP server, load RTC clock, keep realtime local.
This way there is no need to frequently request NTP time, leave it to daily update by example
here is how:

```cpp
#include <NTPClient.h>
// change next line to use with another board/shield
// #include <ESP8266WiFi.h>
#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid     = "<SSID>";
const char *password = "<PASSWORD>";

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset : NTP7Client rtcClient(ntpUDP);

// You can specify the time server pool and the offset, (in seconds) 
// additionally you can specify the update interval (in milliseconds).
NTP7Client timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 14400000); // +1 hour europe mainland, update every 4 hours

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  rtcClient.begin();
  rtcClient.update();
}

void loop() {
  Serial.println(rtcClient.getEpochTime());
  Serial.println(rtcClient.getFormattedTime());
  Serial.println(rtcClient.getFormattedTimeDay());
  delay(1000);
}
```

## Function documentation
'begin \ update' reads NTP time from Server, syncs RTC clock.
`getEpochTime` returns the Unix epoch from RTC Clock !, which are the seconds elapsed since 00:00:00 UTC on 1 January 1970 (leap seconds are ignored, every day is treated as having 86400 seconds). 
**Attention**: If you have set a time offset this time offset will be added to your epoch timestamp when synced to the RTC.
