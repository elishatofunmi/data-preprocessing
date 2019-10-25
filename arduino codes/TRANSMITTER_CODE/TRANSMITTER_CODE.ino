//#include <ArduinoJson.h>
#include <Arduino.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <RF24.h>

//NRF PINS

int pin_ce = 7;
int pin_csn = 8;
bool radioNumber = 1;
bool role = 0; //sending
RF24 radio(pin_ce, pin_csn);// For Leonardo, need explicit SS pin

byte addresses[][6] = {"1Node", "2Node"};

int BUTTON = 3;
int Sensor_one = 4;
int Sensor_two = 5;
int Sensor_three = 6;




boolean sensorState = LOW; 
boolean buttonState = false;
boolean stateAlarm = LOW;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON, OUTPUT);
  pinMode(Sensor_one, INPUT);
  pinMode(Sensor_two, INPUT);
  pinMode(Sensor_three, INPUT);

  Serial.begin(9600);
  //indicate program has started
  digitalWrite(LED_BUILTIN, HIGH);

  radio.begin();
  
  

  //set the address
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(124);
  //radio.openWritingPipe(address[1]);

  Serial.println("Writing to address 1");
  radio.openWritingPipe(addresses[1]);
  Serial.println("Writing to address 0");
  
  // start the radio listening for data
  radio.stopListening();
  
  

  //set module as transmitter
  //radio.stopListening();

}


void loop() {
  if (role == 0){
    radio.stopListening();
    Serial.println(F("Now Sending"));

    int one = digitalRead(Sensor_one);
    int two = digitalRead(Sensor_two);
    int three = digitalRead(Sensor_three);


    if (one == HIGH or two == HIGH or three == HIGH) {
      buttonState = HIGH;
      Serial.println("Alarm on!");
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(BUTTON, HIGH);
      stateAlarm = HIGH;
      // SEND MESSAGE TO RECEIVER
      Serial.println("Detected Movements/Humans"); 
      bool slt;


      unsigned char myData = 1.22;
      slt = radio.write( &myData, sizeof(unsigned char) );
      Serial.print(slt);
      if (!slt){
        Serial.println(F("Failed"));
        }
        else{
          Serial.println("Writing to address");
          radio.write( &myData, sizeof(unsigned char) );
          Serial.println(F("Data re-sent"));
          }
      
    }else{
      buttonState = LOW;
      digitalWrite(BUTTON, LOW);
      digitalWrite(LED_BUILTIN, LOW);
    }
      
      
   } 
    
 }
