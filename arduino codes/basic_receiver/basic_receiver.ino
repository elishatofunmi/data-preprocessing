#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(8,10);  // CE, CSN

const byte addresses[][6] = {"1Node", "2Node"};

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  Serial.begin(115200);
  Serial.println("program started");
  delay(2000);

  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);

  radio.setChannel(120);
  //set the address
  Serial.println("Reading from address 1");
  radio.openReadingPipe(1,addresses[1]);
  radio.startListening();

}

void loop() {
  // put your main code here, to run repeatedly:
  radio.startListening();
  unsigned int data;


  if (radio.available()){
    radio.read( &data, sizeof(unsigned int));
    Serial.println(data);
    delay(2000);

    if (data == 1.22){
      Serial.print(", Got response ");
      Serial.println("Receiving information");
      Serial.println(data);
      digitalWrite(7, HIGH);
      delay(3000);
      digitalWrite(7, LOW);
      delay(3000);
    }
    else{
      digitalWrite(7, LOW);
      Serial.println("Motion not detected");
      delay(3000);
      
    }
  }
  else{
    Serial.println("Signal not available");
  }

}
