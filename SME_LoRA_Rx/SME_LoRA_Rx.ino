/*********
  Modified from the examples of the Arduino LoRa library by nuttyengieer.com 
  for more information write to nuttyengineeronline@gmail.com or info@nuttyengineer.com
*********/
#include<LiquidCrystal.h>
#include <SPI.h>
#include <LoRa.h>
#include <Servo.h>
#define ss 10
#define rst 9
#define dio0 2


Servo elevator;
Servo rudder;
Servo l_aileron;
Servo r_aileron;

Servo ESC;

void setup() {
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

  elevator.attach(7);
  rudder.attach(6);
  l_aileron.attach(5);
  r_aileron.attach(4);

  ESC.attach(3,1000,2000);
}

int joyLR;
int joyUD;
int joyTwist;
int motorSpeed;

char values[3];
int lora_msg = 0;
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

        joyTwist = LoRaData.substring(LoRaData.indexOf(",", LoRaData.indexOf(",") + 1) + 1, LoRaData.lastIndexOf(",")).toInt();
        Serial.println(joyTwist);

        motorSpeed = LoRaData.substring(LoRaData.lastIndexOf(",") + 1).toInt();
        Serial.println(motorSpeed);


        elevator.write(map(joyUD, 0, 1023, 0, 160));
        rudder.write(map(joyTwist, 0, 1023, 140, 50));
        l_aileron.write((map(joyLR, 0, 1023, 40, 140)));
        r_aileron.write((map(joyLR, 0, 1023, 140, 40)));

        ESC.write(map(motorSpeed, 0, 1023, 0, 180));
        lora_msg++;
        Serial.println(lora_msg);

        delay(15);

  // print RSSI of packet
  // Serial.print("' with RSSI ");
  // Serial.println(LoRa.packetRssi());
    }
  }
}
