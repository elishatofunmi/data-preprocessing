#include <ArduinoJson.h>
#include <Arduino.h>
#include <RH_NRF24.h>
#include <SPI.h>

//NRF PINS

int pin_ce = 14;
int pin_csn = 12;
RH_NRF24 nrf24(pin_ce, pin_csn);// For Leonardo, need explicit SS pin

//SENSOR IS AN LED TO SIGNIFY INPUT SIGNAL COMING IN
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

  //RECEIVER point
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

  //nrf24.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (nrf24.waitAvailableTimeout(500))
  { 
    // Should be a reply message for us now   
    if (nrf24.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      if ((char*)buf == 'MOTION DETECTED'){
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(BUTTON, HIGH);
        digitalWrite(SENSOR, HIGH);
    }
    else
    {
      Serial.println("recv failed");
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(BUTTON, LOW);
      digitalWrite(SENSOR, LOW);
    }
  }
  else
  {
    Serial.println("No reply, is nrf24_server running?");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(BUTTON, LOW);
    digitalWrite(SENSOR, LOW);
  }
  delay(400);

  }
  
}
