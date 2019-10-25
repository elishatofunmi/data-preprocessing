
// SimpleTx - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN   7
#define CSN_PIN 8

int BUTTON = 3;
int Sensor_one = 4;
int Sensor_two = 5;
int Sensor_three = 6;



const byte slaveAddress[5] = {'R','x','A','A','A'};


RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend[10] = "Message 0";
char txNum = '0';


unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second



void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON, OUTPUT);
  pinMode(Sensor_one, INPUT);
  pinMode(Sensor_two, INPUT);
  pinMode(Sensor_three, INPUT);
  Serial.begin(9600);

    Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(slaveAddress);

}

void loop() {
  // put your main code here, to run repeatedly:
  int one = digitalRead(Sensor_one);
  int two = digitalRead(Sensor_two);
  int three = digitalRead(Sensor_three);
  if (one == HIGH or two == HIGH or three == HIGH){
    send();
    digitalWrite(BUTTON, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    Serial.println("failed");
    digitalWrite(BUTTON, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }

}


//=======================

void send(){
  bool rslt;
  rslt = radio.write( &dataToSend, sizeof(dataToSend) );

  Serial.print("Data Sent ");
  Serial.print(dataToSend);

  if (rslt){
    Serial.println(" Acknowledge recieved");
    updateMessage();
  }
  else{
    Serial.println(" Tx failed");
    updateMessage();
  }
}

void updateMessage(){
  radio.write( &dataToSend, sizeof(dataToSend) );
}
