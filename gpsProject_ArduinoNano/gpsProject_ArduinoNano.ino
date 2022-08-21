// Note: TX on GPS device goes to pin 4 on Arduino Nano
// Note: RX on GPS device goes to pin 3 on Arduino Nano

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

String jsonLocation ="";
String a = "";

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop(){
  
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      //Serial.print("LAT= ");
      double _lat = gps.location.lat();
      //Serial.print(_lat, 6);
      //Serial.print(" LON= ");
      double _lon = gps.location.lng(); 
      //Serial.println(_lon, 6);
      delay(2000);

      jsonLocation = "{\"latitude\":" + String(_lat) + ", \"longitude\":" + String(_lon) + "}";

      a = Serial.readString();
      a.trim();
      String command = "jsonData";
      // Serial.println(a);
      if (a == command)
      {
        Serial.println(jsonLocation);
      }
 
      
    }
  }
}
