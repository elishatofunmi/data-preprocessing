//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

bool radioNumber = 1;
bool role = 1; //receiver
//create an RF24 object
RF24 radio(7,8);  // CE, CSN

//address through which two modules communicate.
const byte address[][6] = {"1Node", "2Node"};

struct dataStruct{
  unsigned long _micros;
  float value;
}myData;

void setup()
{
  pinMode(4, OUTPUT);
  // display welcome on LCD
  //lcd.begin(16, 2);
  //lcd.print("Motion Not Detected");
  Serial.begin(115200);
  Serial.println("program started");
  delay(2000);
  //lcd.clear();
  
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  //radio.setPALevel(RF24_PA_MIN);
  //radio.setDataRate(RF24_2MBPS);
  //set the address
  if(radioNumber){
    //radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,address[1]);
  }else{
    //radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,address[0]);
  }

  //radio.setChannel(124);
  //radio.openReadingPipe(1,address[1]);
  Serial.println("opened reading address");
  
  //Serial.println("PA level has been set");
  
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  //Read the data if available in buffer


  if (role == 1){

    radio.startListening();
    Serial.println(F("Now Listening"));
    if (radio.available()){
      radio.read(&myData, sizeof(myData));
    }
    Serial.println(myData.value);
    if (myData.value == 1.22){
      Serial.println("Motion Detected");
      digitalWrite(4, HIGH);
    }
    else{
      digitalWrite(4, LOW);
    }
  }
  
}
