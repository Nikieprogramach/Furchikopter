/*********
  Modified from the examples of the Arduino LoRa library by nuttyengieer.com 
  for more information write to nuttyengineeronline@gmail.com or info@nuttyengineer.com
*********/
#include<LiquidCrystal.h>
#include <SPI.h>
#include <LoRa.h>
#define ss 10
#define rst 9
#define dio0 2

#define servoRudder 3
int counter = 0;



void setup() {
  pinMode(servoRudder, OUTPUT);
  //initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);
 Serial.println("LoRa Receiver Tested by SME Dehradun  ");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
 if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
  delay(3000);
}

int joyLR;
int joyUD;
int joyTwist;

char values[3];

void loop() {

  // try to parse packet
  int packetSize = LoRa.parsePacket();
  delay(10);
  if (packetSize) {
    // received a packet
    // Serial.print("Received packet '");
    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.println(LoRaData); 
      //LoRaData.indexOf(",")
      joyLR = LoRaData.substring(0,LoRaData.indexOf(",")).toInt();
      Serial.println(joyLR);

      joyUD = LoRaData.substring(LoRaData.indexOf(",") + 1,LoRaData.indexOf(",", LoRaData.indexOf(",") + 1)).toInt();
      Serial.println(joyUD);

      joyTwist = LoRaData.substring(LoRaData.lastIndexOf(",") + 1).toInt();
      Serial.println(joyTwist);

      analogWrite(servoRudder, map(joyLR, 0, 1023, 0, 180));


    

  // print RSSI of packet
  // Serial.print("' with RSSI ");
  // Serial.println(LoRa.packetRssi());
    }
  }
}
