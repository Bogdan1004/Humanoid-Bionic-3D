#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo; 
Servo myservo1;
Servo myservo2;
Servo myservo3; 
Servo myservo4; 


SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {

  Serial.begin(9600);
  myservo.attach(4); 
  myservo1.attach(5); 
  myservo2.attach(6); 
  myservo3.attach(7);
  myservo4.attach(8);
      myservo.write(0);
      myservo1.write(180);
      myservo2.write(0);
      myservo3.write(180);
      myservo4.write(0);


}

void loop() {

  if (Serial.available() > 0) {

    int inByte = Serial.read();
    int c=inByte;

  Serial.write(inByte);



 switch (inByte) {

      case '0':
      {
        myservo3.write(180);             
        delay(15);  
        break;                    
      }
        

      case '1':

        {
            myservo1.write(0);              
            delay(15);   
            break;
        }

        

      case '2':
     {
             myservo4.write(180);             
        delay(15);  
        break;                    
      }
        

      case '3':
{
             myservo2.write(180);             
        delay(15);  
        break;                    
      }
        break;

      case '4':

        {
             myservo.write(180);             
        delay(15);  
        break;                    
      }

        break;

      case '5':
    {
      myservo.write(0);   //mic
      myservo1.write(180);//aratator
      myservo2.write(0);  //inelar
      myservo3.write(0);   //mare
      myservo4.write(0);  //mijlociu
    break;
    }
    default: {break;}
 }
inByte=5;
  }
  }
