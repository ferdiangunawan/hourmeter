/*
   Code by        : Ferdian Gunawan
   Project        : Hour Meter Engine.
   Date           : 15/04/2021
*/


#include <EEPROM.h>

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

bool engineRunning = true;
int alternator = 8;
String kirim = "";


void setup() {
  Serial3.begin(115200);
  Serial.begin(9600);
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
}
void updateEprom() {
  if (Serial3.available()) {
    String msg = "";
    while (Serial3.available()) {
      msg += char(Serial3.read());
      delay(50);
    }

//        String msg = "4444444";
    if (msg.length() >5 && msg.length() != NULL) {

      Serial.println("eprom = " + msg);

      String m1 = String(msg[7]);
      int value_menitx = m1.toInt();

      String a1 = String(msg[5]);
      int  value_jam1x = a1.toInt();

      String a2 = String(msg[4]);
      int value_jam2x = a2.toInt();

      String a3 = String(msg[3]);
      int value_jam3x = a3.toInt();

      String a4 = String(msg[2]);
      int value_jam4x = a4.toInt();

      String a5 = String(msg[1]);
      int  value_jam5x = a5.toInt();

      String a6 = String(msg[0]);
      int  value_jam6x = a6.toInt();

      if (value_jam2x != NULL) {
        EEPROM.update(addr_menit, value_menitx);
        EEPROM.update(addr_jam1, value_jam1x);
        EEPROM.update(addr_jam2, value_jam2x);
        EEPROM.update(addr_jam3, value_jam3x);
        EEPROM.update(addr_jam4, value_jam4x);
        EEPROM.update(addr_jam5, value_jam5x);
        EEPROM.update(addr_jam6, value_jam6x);
          delay(50);
      }
    } else {
      Serial.println("Tidak ada Update");
    }
  }
}

void loop() {

  engineRunning = digitalRead(alternator) == HIGH;


  if (engineRunning) {
    hmCounter();
    kirimHM();
    //  updateEprom();
  }
  else if (!engineRunning) {
    updateEprom();
    delay(5000);
  }
}
void kirimHM() {
  kirim = "";
  kirim += value_jam6;
  kirim += value_jam5;
  kirim += value_jam4;
  kirim += value_jam3;
  kirim += value_jam2;
  kirim += value_jam1;
  kirim += ",";
  kirim += value_menit / 6;
  kirim += ":";
  kirim += value_detik;

  Serial3.print(kirim);
}
void hmCounter() {
  // put your main code here, to run repeatedly:
  value_detik = value_detik + 1;
  EEPROM.update(addr_detik, value_detik);

  if (value_detik == 60) {
    detik = 0;
    EEPROM.update(addr_detik, detik);

    value_menit = value_menit + 1;
    EEPROM.update(addr_menit, value_menit);
  }

  value_detik = EEPROM.read(addr_detik);
  Serial.print("Detik :");
  Serial.print(value_detik);
  Serial.print("\t");

  if (value_menit == 60) {
    menit = 0;
    EEPROM.update(addr_menit, menit);

    value_jam1 = value_jam1 + 1;
    EEPROM.update(addr_jam1, value_jam1);
  }
  value_menit = EEPROM.read(addr_menit);
  Serial.print("Menit :");
  Serial.print(value_menit);
  Serial.print("\t");

  if (value_jam1 == 10) {
    jam1 = 0;
    EEPROM.update(addr_jam1, jam1);

    value_jam2 = value_jam2 + 1;
    EEPROM.update(addr_jam2, value_jam2);
  }
  value_jam1 = EEPROM.read(addr_jam1);
  Serial.print("Jam (1) :");
  Serial.print(value_jam1);
  Serial.print("\t");

  if (value_jam2 == 10) {
    jam2 = 0;
    EEPROM.update(addr_jam2, jam2);


    value_jam3 = value_jam3 + 1;
    EEPROM.update(addr_jam3, value_jam3);
  }
  value_jam2 = EEPROM.read(addr_jam2);
  Serial.print("Jam (2) :");
  Serial.print(value_jam2);
  Serial.print("\t");

  if (value_jam3 == 10) {
    jam3 = 0;
    EEPROM.update(addr_jam3, jam3);

    value_jam4 = value_jam4 + 1;
    EEPROM.update(addr_jam4, value_jam4);
  }
  value_jam3 = EEPROM.read(addr_jam3);
  Serial.print("Jam (3) :");
  Serial.print(value_jam3);
  Serial.print("\t");

  if (value_jam4 == 10) {
    jam4 = 0;
    EEPROM.update(addr_jam4, jam4);

    value_jam5 = value_jam5 + 1;
    EEPROM.update(addr_jam5, value_jam5);
  }
  value_jam4 = EEPROM.read(addr_jam4);
  Serial.print("Jam (4) :");
  Serial.print(value_jam4);
  Serial.print("\t");

  if (value_jam5 == 10) {
    jam5 = 0;
    EEPROM.update(addr_jam5, jam5);

    value_jam6 = value_jam6 + 1;
    EEPROM.update(addr_jam6, value_jam6);
  }
  value_jam5 = EEPROM.read(addr_jam5);
  Serial.print("Jam (5) :");
  Serial.print(value_jam5);
  Serial.print("\t");
  if (value_jam6 == 255) {
    jam6 = 0;
    EEPROM.update(addr_jam6, jam6);
  }
  value_jam6 = EEPROM.read(addr_jam6);
  Serial.print("Jam (6) :");
  Serial.print(value_jam6);
  Serial.print("\t");


  //print_display = value_jam6,value_jam5,value_jam4,value_jam3,value_jam2,value_jam1,value_menit,value_detik;

  Serial.print("HM :");
  Serial.print(value_jam6);
  Serial.print(value_jam5);
  Serial.print(value_jam4);
  Serial.print(value_jam3);
  Serial.print(value_jam2);
  Serial.print(value_jam1);
  Serial.print(",");
  Serial.print(value_menit);
  Serial.print(":");
  Serial.print(value_detik);
  Serial.println();


  delay(1000);
}
