

//#include <Adafruit_Fingerprint.h>
#include <Keypad.h>
#include <Password.h>
#define Password_Length 5
char Data[Password_Length]; 

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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  keyVal = keypad.getKey();
  //delay(2000);

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
      
    }
    else{
      Serial.println("Password mismatch");
     
    }
    }
  }


void clearData()
{
  while (data_count != 0)
  {
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}
