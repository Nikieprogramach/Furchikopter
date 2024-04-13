/*********
  Modified from the examples of the Arduino LoRa library by nuttyengieer.com 
  for more information write to nuttyengineeronline@gmail.com or info@nuttyengineer.com
*********/

#include <SPI.h>
#include <LoRa.h>
#define ss 10
#define rst 9
#define dio0 2

#define joyLR A0
#define joyUD A1
#define joyTwist A2

int counter = 0;

void setup() {
  pinMode(joyLR, INPUT);
  pinMode(joyUD, INPUT);
  pinMode(joyTwist, INPUT);

  //initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender Tested by SME Dehradun ");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
 if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(analogRead(joyLR));
    LoRa.print(",");
  LoRa.print(analogRead(joyUD));
    LoRa.print(",");
  LoRa.print(analogRead(joyTwist));
  LoRa.endPacket();

  counter++;

  // delay(1000);
}