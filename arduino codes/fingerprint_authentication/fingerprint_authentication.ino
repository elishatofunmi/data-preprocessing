c
void setup() {
  // put your setup code here, to run once:
  //#include <SPI.h>
  #include <Wire.h>
  //#include <WiFiClient.h>
  //#include <ESP8266WiFi.h>
  #include <SoftwareSerial.h>
  //#include <ESP8266WebServer.h>
  //#include <Adafruit_GFX.h>
  #include <Adafruit_Fingerprint.h>
  #include <Keypad.h>
  #include <ArduinoJson.h>
  #include <ESP8266HTTPClient.h>


  // set these to run examples
  #define FIREBASE_HOST "https://fingerprintmatching-4a8bf.firebaseio.com/";
  #define FIREBASE_AUTH "Dqj1O90X4PwbJrCBe3tTAh5xKlsjrZ4xV0N60OLg";
  #define WIFI_SSID "Snares"
  #define WIFI_PASSWORD "@Tofunmi2"
  

  String myStrings; //complete message from arduino, which consists of sensor data
  char rdata; // recieved characters

  int firstVal;

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


   if input_gotten == "1234"{
    getFingerprintEnroll()
  }


  

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  String path = "/";
  FirebaseObject object = Firebase.get(path); // to retrieve the entire database

  // to extract data with respect to the different keys using which it is stored
  String Name = object.getString('Name');
  char fingerprint = object.getInt('fingerprint');
  
// to send data to the database
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

//START TAKING READINGS AT PIN D4 OF NODEMCU
dht.begin();
float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t){
  Serial.Println(F("Failed to read from DHT sensor!"));
  return;
}

// push humitiy to path
Serial.print("Humidity: "); Serial.print(h);
String firehumid = String(h) + String("%"); // convert integer humidity to string
Serial.print("% Temperature: "); Serial.print(t); Serial.println("C");
String fireTemp = String(t) + string("C");
delay(4000);

Firebase.pushString("/DHT11/Humidity", firehumid);
Firebase.pushString("/DHT11/Temperature", fireTemp);




 

  
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
}



char get_password(){
  //get password from keypad
  while (finger.available()){
    KeypadEvent e = customKeypad.read();
    Serial.print((char)e.bit.KEY);


  }
  delay(10);
}





uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
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

p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  delay(2000);p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");

 while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
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

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}
  

  







  

}
