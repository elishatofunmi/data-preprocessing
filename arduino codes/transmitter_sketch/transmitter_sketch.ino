//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9,10);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(115);
  
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{
  //Send message to receiver
  const char text[] = "Hello World";
  Serial.print("Sending: ");
  Serial.println(text);
  radio.write(&text, sizeof(text));
  Serial.println("Sent");
  digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);
  delay(3000);
  
  delay(1000);
}
