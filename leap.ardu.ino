#include <SoftwareSerial.h>
#include <Servo.h>
#include "Lixie.h"
#define DATA_PIN   5
#define NUM_LIXIES 1
Lixie lix(DATA_PIN, NUM_LIXIES);
Servo myservo0;
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;
Servo myservo9;
Servo myservo10;
Servo myservo11;



SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {

  Serial.begin(9600);
  lix.begin(); // Initialize LEDs
  lix.color(0,0,0);
  lix.color_off(34, 0, 255);
  lix.brightness(255);
  myservo0.attach(2);     //deget mare
  myservo1.attach(3);     //deget aratator
  myservo2.attach(4);     //deget mijlociu
  myservo3.attach(5);     //deget inelar
  myservo4.attach(6);     //deget mic
  myservo5.attach(7);     //cot
  myservo6.attach(8);     // umar fata/spate
  myservo7.attach(9);     //umar stanga/dreapta
  myservo8.attach(10);    //shold stanga
  myservo9.attach(11);    //shold dreapta
  myservo10.attach(12);   //
  myservo11.attach(13);   //
      myservo0.write(0);   
      myservo1.write(180);
      myservo2.write(0);  
      myservo3.write(0);  
      myservo4.write(0);  
      myservo5.write(90); 


}

void loop() {
lix.write(1);
  if (Serial.available() > 0) {

    int inByte = Serial.read();
    

  Serial.write(inByte);



 switch (inByte) {

      case '0':
      {
        myservo0.write(180);             
        delay(20);  
        break;                    
      }
        

      case '1':

        {
            myservo1.write(0);              
            delay(20);   
            break;// waits 15ms for the servo to reach the position
        }

        

      case '2':
     {
             myservo2.write(180);             
        delay(20);  
        break;                    
      }
        

      case '3':
{
             myservo3.write(180);             
        delay(20);  
        break;                    
      }
        break;

      case '4':

        {
             myservo4.write(180);             
        delay(20);  
        break;                    
      }

        break;

      case '5':
    {
      myservo0.write(0);
      myservo1.write(180);
      myservo2.write(0);
      myservo3.write(0);
      myservo4.write(0);
    break;
    }

    default: {break;}
 }
inByte=5;
  }
  }
