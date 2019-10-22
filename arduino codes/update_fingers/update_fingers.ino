void setup() {
   // put your setup code here, to run once:
  //#include <SPI.h>
  //#include <Wire.h>
  #include <WiFiClient.h>
  //#include <ESP8266WiFi.h>
  #include <SoftwareSerial.h>
  //#include <ESP8266WebServer.h>
  //#include <Adafruit_GFX.h>
  #include <Adafruit_Fingerprint.h>
  #include <Keypad.h>
  #include <ArduinoJson.h>
  //#include <ESP8266HTTPClient.h>


  // set these to run examples
  #define FIREBASE_HOST "https://fingerprintmatching-4a8bf.firebaseio.com/";
  #define FIREBASE_AUTH "Dqj1O90X4PwbJrCBe3tTAh5xKlsjrZ4xV0N60OLg";
  #define WIFI_SSID "Snares"
  #define WIFI_PASSWORD "@Tofunmi2"



  String myStrings; //complete message from arduino, which consists of sensor data
  char rdata; // recieved characters

  int firstVal;

  pinMode(16, OUTPUT);

  //Firebase.setString('images: ', image);

  //KEYPAD DESCRIPTION
  const byte ROWS = 4; //FOUR ROWS
  const byte COLS = 4; //FOUR COLUMNS

  char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };

  byte rowPins[ROWS] = {0,2,4,5}; //CONNECT TO THE ROW PINOUTS OF THE KEYPAD
  byte colPins[COLS] = {12,13,14,15}; //CONNECT TO THE COLUMN PINOUTS OF THE KEYPAD

  Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS,COLS);

  int col_scan; //variable to identiy a key press
  char temp_press; //variable to hold value of key press
  

  #define Password_length 5

 char Data[Password_length];
 char password_var;

 char Master[Password_length]= "1234";

 //Fingerprint scanner pins
  #define FingerRX 1
  #define FingerTX 3

  SoftwareSerial mySerial(FingerRX,FingerTX);
  Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

  uint8_t id;

  String postData;

}

void loop() {
  // put your main code here, to run repeatedly:

  //first connect to Wifi
  Serial.begin(9600);
  // connect to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print('connecting');

  while (WIFI.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());




  // Keep getting finger print ID
  
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      digitalWrite(16, HIGH);
      delay(5000);
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!
}
