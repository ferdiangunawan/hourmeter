

/*
 * Project        : Hour Meter Engine.
 */




//LiquidCrystal_I2C lcd(0x27,16,2);

#include <EEPROM.h>
//LiquidCrystal lcd (12, 11, 5, 4, 3, 2);
String statusRunning = "Running";
String statusStop = "Stop";
int addr_detik = 0;
int addr_menit = 1;
int addr_jam1 = 2;
int addr_jam2 = 3;
int addr_jam3 = 4;
int addr_jam4 = 5;
int addr_jam5 = 6;
int addr_jam6 = 7;

int detik = 0;
int menit = 0; 
int jam1 = 0; 
int jam2 = 0; 
int jam3 = 0; 
int jam4 = 0; 
int jam5 = 0;
int jam6 = 0;

int value_detik;
int value_menit;
int value_jam1;
int value_jam2;
int value_jam3;
int value_jam4;
int value_jam5;
int value_jam6;

int print_display;

//INPUT
int alternator = 52;
bool engineRunning = true;

String kirim = "";

void setup() {
  Serial3.begin(115200);
  // put your setup code here, to run once:
//   lcd.backlight();
//    lcd.init();
  Serial.begin(9600);
//  lcd.begin (16, 2);
//  lcd.print("Service Meter");
//  lcd.setCursor(0,1);
//  lcd.print("KPC");
//  delay(2000);
//  lcd.clear();
//  lcd.setCursor(0,0);

  
  value_detik = EEPROM.read(addr_detik);
  value_menit = EEPROM.read(addr_menit);
  value_jam1 = EEPROM.read(addr_jam1);
  value_jam2 = EEPROM.read(addr_jam2);
  value_jam3 = EEPROM.read(addr_jam3);
  value_jam4 = EEPROM.read(addr_jam4);
  value_jam5 = EEPROM.read(addr_jam5);
  value_jam6 = EEPROM.read(addr_jam6);
  
  Serial.println("=======================================================");
  Serial.print("Detik :");
  Serial.println(value_detik);
  Serial.print("Menit :");
  Serial.println(value_menit);
  Serial.print("Jam 1 :");
  Serial.println(value_jam1);
  Serial.print("Jam 2 :");
  Serial.println(value_jam2);
  Serial.print("Jam 3 :");
  Serial.println(value_jam3);
  Serial.print("Jam 4 :");
  Serial.println(value_jam4);
  Serial.print("Jam 5 :");
  Serial.println(value_jam5);
  Serial.print("Jam 6 :");
  Serial.println(value_jam6);
  Serial.println("=======================================================");

  pinMode(alternator, INPUT);
  digitalWrite(alternator,LOW);

}

void loop() {
  engineRunning = digitalRead(alternator)==HIGH;
  if (engineRunning){
    engineStart();
    
  }else if(!engineRunning){
    engineStop();
  }
}
  void engineStart(){
  // put your main code here, to run repeatedly:
  value_detik = value_detik + 1;
  EEPROM.update(addr_detik, value_detik);
  
  if(value_detik == 60){
    detik = 0;
    EEPROM.update(addr_detik,detik);

    value_menit = value_menit + 1;
    EEPROM.update(addr_menit, value_menit);
  }
  
  value_detik = EEPROM.read(addr_detik);
 
  
  if(value_menit == 60){
    menit = 0;
    EEPROM.update(addr_menit, menit);

    value_jam1 = value_jam1 + 1;
    EEPROM.update(addr_jam1, value_jam1);
  }
  value_menit = EEPROM.read(addr_menit);


  if(value_jam1 == 10){
    jam1 = 0;
    EEPROM.update(addr_jam1, jam1);
    
    value_jam2 = value_jam2 + 1;
    EEPROM.update(addr_jam2, value_jam2);
  }
  value_jam1 = EEPROM.read(addr_jam1);
 

  if(value_jam2 == 10){
    jam2 = 0;
    EEPROM.update(addr_jam2, jam2);

    
    value_jam3 = value_jam3 + 1;
    EEPROM.update(addr_jam3, value_jam3);
  }
  value_jam2 = EEPROM.read(addr_jam2);
 

  if(value_jam3 == 10){
    jam3 = 0;
    EEPROM.update(addr_jam3, jam3);
    
    value_jam4 = value_jam4 + 1;
    EEPROM.update(addr_jam4, value_jam4);
  }
  value_jam3 = EEPROM.read(addr_jam3);
 

  if(value_jam4 == 10){
    jam4 = 0;
    EEPROM.update(addr_jam4, jam4);
    
    value_jam5 = value_jam5 + 1;
    EEPROM.update(addr_jam5, value_jam5);
  }
  value_jam4 = EEPROM.read(addr_jam4);
 
  
  if(value_jam5 == 10){
    jam5 = 0;
    EEPROM.update(addr_jam5, jam5);
    
    value_jam6 = value_jam6 + 1;
    EEPROM.update(addr_jam6, value_jam6);
  }
  value_jam5 = EEPROM.read(addr_jam5);

  
   if(value_jam6 == 255){
    jam6 = 0;
    EEPROM.update(addr_jam6, jam6);
   }
  value_jam6 = EEPROM.read(addr_jam6);

    kirim = "";
    kirim += value_jam6;
    kirim += value_jam5;
    kirim += value_jam4;
    kirim += value_jam3;
    kirim += value_jam2;
    kirim += value_jam1;
    kirim += ",";
    kirim += value_menit/6;
    kirim += ":";
    kirim += value_detik;

    Serial3.print(kirim);

    if(Serial3.available()){
    String msg = "";
    while (Serial3.available()){
      msg += char(Serial3.read());
      delay(50);
    }
    //kirim lagi ke arduino
    Serial.println(msg);
  }
  delay(1000);
  
  }
  void engineStop(){
      Serial.print(statusStop);

    delay(1000);
      
  }
