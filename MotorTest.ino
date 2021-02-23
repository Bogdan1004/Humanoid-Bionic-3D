// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
int command;             //Int to store app command state.
int speedCar = 255;     // 50 - 255.
int speed_Coeff = 4;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
 
  motor1.run(RELEASE);
   motor2.run(RELEASE);
    motor3.run(RELEASE);
     motor4.run(RELEASE);
     
}
void goAhead()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.setSpeed(speedCar); 
  motor2.setSpeed(speedCar); 
  motor3.setSpeed(speedCar); 
  motor4.setSpeed(speedCar); 
  
}
void goBack()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(speedCar); 
  motor2.setSpeed(speedCar); 
  motor3.setSpeed(speedCar); 
  motor4.setSpeed(speedCar); 
}
void goRight(){ 
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(speedCar); 
  motor2.setSpeed(speedCar); 
  motor3.setSpeed(speedCar); 
  motor4.setSpeed(speedCar); 
}
void goLeft(){
  motor4.run(FORWARD);
  motor3.run(FORWARD);
  motor2.run(BACKWARD);
  motor1.run(BACKWARD);
  motor1.setSpeed(speedCar); 
  motor2.setSpeed(speedCar); 
  motor3.setSpeed(speedCar); 
  motor4.setSpeed(speedCar); 
}

void stopRobot(){
  motor4.run(RELEASE);
  motor3.run(RELEASE);
  motor2.run(RELEASE);
  motor1.run(RELEASE);
  motor1.setSpeed(speedCar); 
  motor2.setSpeed(speedCar); 
  motor3.setSpeed(speedCar); 
  motor4.setSpeed(speedCar); 
}
void loop(){
  
if (Serial.available() > 0) {
  command = Serial.read();
  stopRobot();      //Initialize with motors stopped.


switch (command) {
case 'F':goAhead();break;
case 'B':goBack();break;
case 'L':goLeft();break;
case 'R':goRight();break;
case '0':speedCar = 100;break;
case '1':speedCar = 115;break;
case '2':speedCar = 130;break;
case '3':speedCar = 145;break;
case '4':speedCar = 160;break;
case '5':speedCar = 175;break;
case '6':speedCar = 190;break;
case '7':speedCar = 205;break;
case '8':speedCar = 220;break;
case '9':speedCar = 235;break;
case 'q':speedCar = 255;break;
}
}
}
