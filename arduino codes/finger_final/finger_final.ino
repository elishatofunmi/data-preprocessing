/*************************************************** 
  This is an example sketch for our optical Fingerprint sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> http://www.adafruit.com/products/751

  These displays use TTL Serial to communicate, 2 pins are required to 
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

//#include <ESP8266WiFi.h">
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <Adafruit_Fingerprint.h>
#include <Keypad.h>
#include <password.h>
//#iclude <ESP8266HTTPClient.h>
#define Password_Length 5
char Data[Password_Length];
int count_id;
int check_id;
int id;
int password_status; 

char Master[Password_Length] = "1234";
byte data_count = 0, master_count = 0;
char keyVal;

//KEYPAD DESCRIPTION
  const byte ROWS = 4; //FOUR ROWS
  const byte COLS = 4; //FOUR COLUMNS

  Password password = Password("1234");

  char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };

  byte rowPins[ROWS] = {7,6,5,4}; //CONNECT TO THE ROW PINOUTS OF THE KEYPAD
  byte colPins[COLS] = {12,11,10,9}; //CONNECT TO THE COLUMN PINOUTS OF THE KEYPAD


  Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS,COLS);



// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
// #define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial
SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


 #define FIREBASE_HOST "https://fingerprintmatching-4a8bf.firebaseio.com/";
 #define FIREBASE_AUTH "Dqj1O90X4PwbJrCBe3tTAh5xKlsjrZ4xV0N60OLg";
 #define WIFI_SSID "Snares"
 #define WIFI_PASSWORD "@Tofunmi2"

void setup()  
{
  Serial.begin(9600);

  //connect to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print('connecting');
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);

  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

// get number of existing finger templates
  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
  count_id = finger.templateCount;
}



void clearData()
{
  while (data_count != 0)
  {
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}


int get_password(){
    keyVal = keypad.getKey();

  if (keyVal) // makes sure a key is actually pressed, equal to (customKey!= NO_KEY)
  {
    Data[data_count] = keyVal;
    data_count++;
  }

  if (data_count == Password_Length - 1) // if the array is equal to the number of expected chars, compare data to master
  {
    if (!strcmp(Data, Master)) //equal to (strmcmp(Data, Master) == 0)
    {
      Serial.println("password match");
      
      clearData();
      digitalWrite(8, HIGH);
      return 1;
      delay(1000);
      digitalWrite(8, LOW);
      delay(1000);
      
    }
    else{
      Serial.println("Password mismatch");
      clearData();
      return 0;
      digitalWrite(8, LOW);
      delay(1000);
     
    }
    }
  }



uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
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
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}



// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  digitalWrite(13,HIGH);
  delay(5000);
  digitalWrite(13, LOW);
  return finger.fingerID; 
}


int enroll(){
  int id = 0;
  count_id = finger.templateCount;
  id = count_id+ 1;
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      if (Firebase.failed()){
        Serial.print("Setting/number failed: ");
        Serial.println(Firebase.error());
        return;
    }

    //upload new ID
    char val;
    val = finger.image2Tz(1);
    Firebase.setInt("Access granted to ID: ", val);
    
    
    
    delay(1000);
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
  delay(2000);
  

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
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    digitalWrite(13,HIGH);
    delay(5000);
    digitalWrite(13, LOW);
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
   
 


void loop()                     // run over and over again
{ 
  id = -1;
  uint8_t k = finger.getImage();
  if (k == FINGERPRINT_OK){
    //getFingerprintIDez();

    
    digitalWrite(13, HIGH);
    digitalWrite(8, HIGH);
    delay(5000);
    digitalWrite(13, LOW);
    digitalWrite(8, LOW);

    //get fingerprint ID
    id = getFingerprintID();
    //Serial.print("ID is #"); Serial.print(finger.fingerID);
    if (id == FINGERPRINT_NOTFOUND){
      //finger.fingerID
      Serial.println("Enter password: ");
      int call = 0;
      int vor = 0;
      int threshold = 1;
      while(1){
        get_password();
        vor = get_password();
        if (vor == threshold){
          delay(4000);
          break;
      }
      else{
        continue;
      }
      
    }
    delay(4000);
    
    
    //handle error
    
    enroll();
//    exit();
 }
 else{
  getFingerprintIDez();
 }}}  

  
