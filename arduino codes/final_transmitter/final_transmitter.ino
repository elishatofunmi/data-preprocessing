// nrf24_client

#include <SPI.h>
#include <RH_NRF24.h>

int BUTTON = 3;
int Sensor_one = 6;
int Sensor_two = 4;
int Sensor_three = 5;



boolean sensorState = LOW; 
boolean buttonState = false;
boolean stateAlarm = LOW;


// Singleton instance of the radio driver
//RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
RH_NRF24 nrf24(7,8);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

void setup() 
{

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON, OUTPUT);
  pinMode(Sensor_one, INPUT);
  pinMode(Sensor_two, INPUT);
  pinMode(Sensor_three, INPUT);


  //indicate program has started
  digitalWrite(LED_BUILTIN, HIGH);

  //nrf24.begin();

  //nrf24.stopListening();

  
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


void loop()
{
  int one = digitalRead(Sensor_one);
  int two = digitalRead(Sensor_two);
  int three = digitalRead(Sensor_three);

  if (one == HIGH or two == HIGH or three == HIGH){
    buttonState = HIGH;
    Serial.println("Sending to nrf24_server");
    digitalWrite(3,HIGH);
    // Send a message to nrf24_server
    uint8_t data[] = "Hello World!";
    nrf24.send(data, sizeof(data));
    delay(1000);
  }
  else{
    buttonState = LOW;
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(BUTTON, LOW);
    Serial.println("Alarm off!");
    stateAlarm = LOW;
    delay(1000);
  }
  
  
//  nrf24.waitPacketSent();
//  // Now wait for a reply
//  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
//  uint8_t len = sizeof(buf);
//
//  if (nrf24.waitAvailableTimeout(500))
//  { 
//    // Should be a reply message for us now   
//    if (nrf24.recv(buf, &len))
//    {
//      Serial.print("got reply: ");
//      Serial.println((char*)buf);
//    }
//    else
//    {
//      Serial.println("recv failed");
//    }
//  }
//  else
//  {
//    Serial.println("No reply, is nrf24_server running?");
//  }
//  delay(400);
}
