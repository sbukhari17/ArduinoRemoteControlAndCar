#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 2); // RX, TX    **NOTE**: For our Bluetooth module, RX & TX were switched
#define LEFT 0 //left joystick
#define RIGHT 1 //right joystick


void setup() {
  // Open serial communications:
  Serial.begin(9600);
  Serial.println("Type AT commands!");
  
  // The HC-06 defaults to 9600 according to the datasheet.
  mySerial.begin(9600);
}

void loop() {
    int lVal = analogRead(LEFT);
    int rVal = analogRead(RIGHT);
    String mystr = "";
    
    //Concatenate comma-separated command string//
    mystr += lVal;
    mystr += ",";
    mystr += rVal;
    mystr += "\n";
    
    int len = mystr.length()+1;
    char arr [len];
    mystr.toCharArray(arr,len); //Convert string to Chars - will be converted to bytes when sent over via write
    for(int i=0; i < len; i++){
      mySerial.write(arr[i]);
    }
    
    delay(100);
  }
