
#include <Servo.h>
int soundSensor = 2;
Servo myservo;
void setup() 
{
  Serial.begin(9600);
  pinMode (soundSensor, INPUT);
  myservo.attach(3);
}

void loop()
{
  int statusSensor = digitalRead (soundSensor);
  Serial.write(statusSensor);
  if (statusSensor == 1)
  {
    myservo.write(0);
    delay(25);
  }
  else
  {
    myservo.write(180);
    delay(25);
  }
  
}
