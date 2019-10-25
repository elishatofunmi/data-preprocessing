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
RF24 radio(8,10);  // CE, CSN

//address through which two modules communicate.
const byte addresses[][6] = {"1Node", "2Node"};



void setup()
{
  pinMode(7, OUTPUT);
  Serial.begin(115200);
  Serial.println("program started");
  delay(2000);
  //lcd.clear();
  
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);

  radio.setChannel(115);
  //set the address
  Serial.println("Reading from address 1");
  radio.openReadingPipe(1,addresses[1]);
  

  Serial.println("opened reading address");
  
  
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  //Read the data if available in buffer


  if (role == 1){

    radio.startListening();
    unsigned char data;

  
    Serial.println("Now Listening");
    if (radio.available()){
      
      radio.read( &data, sizeof(char));
      Serial.println("Here");
      if (data == 1.22){
      Serial.print(", Got response ");
      Serial.println("Motion Detected");
      digitalWrite(7,HIGH);
      Serial.println(data);
      }
      else{
        digitalWrite(7, LOW);
        Serial.println("Motion not Detected");
      }
      
    }
   
  else{
    Serial.println("Transmitter not found");
    digitalWrite(7, LOW);
  }
  }
  
}
