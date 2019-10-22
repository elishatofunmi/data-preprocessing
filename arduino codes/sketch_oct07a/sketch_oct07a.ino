#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ArduinoHttpClient.h>
#include <Arduino.h>
#include <RH_NRF24.h>
#include <SPI.h>

//NRF PINS

int pin_ce = 14;
int pin_csn = 12;
RH_NRF24 nrf24(pin_ce, pin_csn);// For Leonardo, need explicit SS pin


int BUTTON = 0;
int SENSOR = 13;
boolean sensorState = LOW; 
boolean buttonState = false;
boolean stateAlarm = LOW;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON, OUTPUT);
  pinMode(SENSOR, INPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  //tranmitter point
  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");

}
// Thing function runs continiously
void loop() {
  sensorState = digitalRead(SENSOR);
  if (sensorState == HIGH) {
      buttonState = HIGH;
      Serial.println("Alarm on!");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(BUTTON, HIGH);
      stateAlarm = HIGH;
      transmit(stateAlarm);
      delay(750);
  }
  else {
      buttonState = LOW;
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(BUTTON, LOW);
      Serial.println("Alarm off!");
      stateAlarm = LOW;
      transmit(stateAlarm);
      delay(750);
  }  
}

void Transmit(boolean& state) {
  if (state == HIGH){
    Serial.println("Sending to info");
  // Send a message to nrf24_server
  uint8_t data[] = "MOTION DETECTED";
  nrf24.send(data, sizeof(data));
  }
  else{
    Serial.println("Sending no info");
  // Send a message to nrf24_server
  uint8_t data[] = "MOTION NOT DETECTED";
  nrf24.send(data, sizeof(data));
  }

}
