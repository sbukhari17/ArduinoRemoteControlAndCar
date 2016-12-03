#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 5); // RX, TX
AF_DCMotor left_motor(1, MOTOR12_64KHZ); // define motor on channel 1 with 64KHz PWM
AF_DCMotor right_motor(2, MOTOR12_64KHZ);
String recv = "";
int leftdir = RELEASE;
int rightdir = RELEASE;

void setup() 
{
  Serial.begin(9600);
  left_motor.setSpeed(255); // Set motor 1 to maximum speed
  right_motor.setSpeed(255);
  mySerial.begin(9600);  
}

void loop() 
{
  if(mySerial.available()) {
    delay(75);
    while(mySerial.available()) {
      recv += (char)mySerial.read();
    } 
  }
  if(recv.indexOf('\n') != -1) {
    int commaIndex = recv.indexOf(',');
    if(commaIndex != -1) {
      int leftVal = recv.substring(0,commaIndex).toInt();
      int rightVal = recv.substring(commaIndex+1).toInt();
      leftdir = valToDir(leftVal);
      rightdir = valToDir(rightVal);
    }
    recv = "";
  }
  if(rightdir == FORWARD) {
    Serial.println("FORWARD");
  } else if(rightdir == BACKWARD) {
    Serial.println("BACKWARD");
  } else if(rightdir == RELEASE) {
    Serial.println("RELEASE");
  }
  left_motor.run(leftdir);
  right_motor.run(rightdir);
}

int valToDir(int val) {
      if(val < 450) {
        return FORWARD;
      } else if(val>600) {
        return BACKWARD;
      } else {
        return RELEASE;
      }
}

