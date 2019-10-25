
//#include <ArduinoJson.h>
#include <Arduino.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <RF24.h>

int pin_ce = 7;
int pin_csn = 8;
RF24 radio(pin_ce, pin_csn);// For Leonardo, need explicit SS pin

byte addresses[][6] = {"1Node", "2Node"};

int button = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();

  //set the address
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(120);

  radio.openWritingPipe(addresses[1]);
  Serial.println("Written address");
  
  // start the radio listening for data
  radio.stopListening();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int myData = 1.22;

  radio.stopListening();
  bool slt;
  Serial.println(slt);
  slt = radio.write( &myData, sizeof(unsigned int) );
  Serial.println(slt);
  Serial.println(myData);
  digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);
  delay(3000);
  

}
