void setup() {
   // put your setup code here, to run once:
  #include <SoftwareSerial.h>
  #include <Adafruit_Fingerprint.h>
  #include <Keypad.h>

  
  // set these to run examples
  #define FIREBASE_HOST "https://fingerprintmatching-4a8bf.firebaseio.com/";
  #define FIREBASE_AUTH "Dqj1O90X4PwbJrCBe3tTAh5xKlsjrZ4xV0N60OLg";
  #define WIFI_SSID "Snares"
  #define WIFI_PASSWORD "@Tofunmi2"

  
 //Fingerprint scanner pins
  SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

 

}

void loop() {
  // put your main code here, to run repeatedly:

}
