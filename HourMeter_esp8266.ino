/*
    This is an example sketch to publish MQTT data to your
    Antares IoT Platform project device via ESP8266.

    MQTT server & port:
    platform.antares.id, port 1338

    MQTT topic:
    /oneM2M/req/your-access-key/antares-cse/json

    This sketch will deploy data to your Antares device
    and publish to the MQTT topic simultaneously.

    For more information, please visit https://antares.id/id/docs.html
*/


#include <AntaresESP8266MQTT.h>

#define ACCESSKEY "b8e8472fa3d2ea23:0a285c5fea62c8a7"
#define WIFISSID "Rumah"
#define PASSWORD "sugengimam"

#define projectName "KPC"
#define deviceName "AlternatorCurrent"

AntaresESP8266MQTT antares(ACCESSKEY);



void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
  
}

void loop() {
  //ambil dari arduino
  if(Serial.available()){
     String msg = "";
    while (Serial.available()){
      msg += char(Serial.read());
      delay(50);
    }
    //kirim lagi ke arduino
//    Serial.print(msg);
    
  antares.checkMqttConnection();
  antares.add("hour_meter", msg);
  antares.publish(projectName, deviceName);
  delay(1000);
 
   
  }
}
