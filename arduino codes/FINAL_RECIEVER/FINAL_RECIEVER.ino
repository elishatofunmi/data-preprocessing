//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <RH_NRF24.h>
#include <LiquidCrystal.h>


const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
RH_NRF24 nrf24(7,8);// For Leonardo, need explicit SS pin


void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  // display welcome on LCD
  lcd.begin(16, 2);
  lcd.print("Motion Not Detected");
  Serial.println("Motion Not Detected");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::ReceivePower0dBm))
    Serial.println("setRF failed");


}

void loop() {
  // put your main code here, to run repeatedly:
  //  nrf24.waitPacketSent();
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
      lcd.setCursor(0,0);
      lcd.print("Motion Detected !!!");
      Serial.println("Motion Detected");
      digitalWrite(4, HIGH);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is nrf24_server running?");
  }
  delay(400);

}
