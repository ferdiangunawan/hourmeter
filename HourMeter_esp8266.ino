// coded by Ferdian Gunawan
// date : 04/16/2021
#include "AntaresESP8266HTTP.h"

#define ACCESSKEY "b8e8472fa3d2ea23:0a285c5fea62c8a7"
#define WIFISSID "Rumah"
#define PASSWORD "sugengimam"
//lupasandy

#define projectName "KPC"
#define deviceName "AlternatorCurrent"

AntaresESP8266HTTP antares(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  antares.setDebug(false);
  antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
  antares.get(projectName, deviceName); // Store latest value in buffer
  // Variables
  /*
    Uncomment the line below to use HTTP instead of HTTPS.
    Will be faster, but less secure
  */
  // antares.sendNonSecure(projectName, deviceName); 

  if(Serial.available()){
    String msg = "";
    while (Serial.available()){
      msg += char(Serial.read());
      delay(50);
    }
    if(antares.getSuccess()) {
  String hmSekarang = antares.getString("hm_update");
   if (hmSekarang.length() > 5){
    
   Serial.print(hmSekarang);
   }
 else{
     Serial.print("11");
   }
    }
  antares.add("hour_meter", msg);
  antares.add("hm_update","111");
     
  antares.send(projectName, deviceName);
  
  }
  delay(10000);
}
