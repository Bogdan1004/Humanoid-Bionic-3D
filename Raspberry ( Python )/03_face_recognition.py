import cv2
import numpy as np
import os
import sys
import time
import RPi.GPIO as gpio

gpio.setmode(gpio.BOARD)
gpio.setup(11,gpio.OUT)
gpio.setup(13,gpio.OUT)
servo = gpio.PWM(11,50)
servo.start(7.5)
servo.ChangeDutyCycle(0)
servo1 = gpio.PWM(13,50)
servo1.start(7.5)
servo1.ChangeDutyCycle(0)

incrementServo = .1
incrementServo1 = 1

currentPos = 7.5
currentPos1 = 40
CFace = 0
max_right_pos = False
max_left_pos = True
minPos = 3 
maxPos = 11.5
minPos1 =0
maxPos1=180
rangeRight = 230 
rangeLeft = 140  

recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read('trainer/trainer.yml')
cascadePath = "haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascadePath);

font = cv2.FONT_HERSHEY_SIMPLEX

id = 0

names = ['Bogdan', 'Vlad', 'Unknown','RandomGuy', 'etc'] 


cam = cv2.VideoCapture(0)
cam.set(3, 640) # set video widht
cam.set(4, 480) # set video height


minW = 0.1*cam.get(3)
minH = 0.1*cam.get(4)

# Functions

def scan():
    global currentPos
    global max_right_pos
    global max_left_pos
    
    if not max_right_pos: 
        servo_right()
        if currentPos >= maxPos:
            max_right_pos = True
            max_left_pos = False
            servo1_left()
    if not max_left_pos:
        servo_left()
        if currentPos <= minPos:
            max_right_pos = False
            max_left_pos = True
            servo1_right()
def servo1_left():
    global currentPos1
   
    if currentPos1 > minPos1:
        currentPos1 = currentPos1 - incrementServo1
        servo1.ChangeDutyCycle(currentPos1)
    time.sleep(.02) 
    servo1.ChangeDutyCycle(0)

def servo1_right():
    global currentPos1

    if currentPos1 < maxPos1:
        currentPos1 = currentPos1 + incrementServo1
        servo.ChangeDutyCycle(currentPos1)
    time.sleep(.02)
    
    servo1.ChangeDutyCycle(0) 


def servo_left():
    global currentPos
   
    if currentPos > minPos:
        currentPos = currentPos - incrementServo
        servo.ChangeDutyCycle(currentPos)
    time.sleep(.02) 
    servo.ChangeDutyCycle(0)

def servo_right():
    global currentPos

    if currentPos < maxPos:
        currentPos = currentPos + incrementServo
        servo.ChangeDutyCycle(currentPos)
    time.sleep(.02)
    
    servo.ChangeDutyCycle(0) 

    

def track_face(face_position):

    if face_position < rangeRight:
        servo_left()
    else:
        servo1_left()
    
    if face_position > rangeLeft:
        servo_right()
    else:
        servo1_right()
    time.sleep(.01)
    servo.ChangeDutyCycle(0)
    servo1.ChangeDutyCycle(0)


while True:
    ret, img =cam.read()
    #img = cv2.flip(img, -1) # Flip vertically
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    
    faces = faceCascade.detectMultiScale( 
        gray,
        scaleFactor = 1.2,
        minNeighbors = 5,
        minSize = (int(minW), int(minH)),
       )

    for(x,y,w,h) in faces:
        cv2.rectangle(img, (x,y), (x+w,y+h), (0,255,0), 2)
        CFace = (w/2+x)
        id, confidence = recognizer.predict(gray[y:y+h,x:x+w])


        if (confidence < 100):
            id = names[id]
            confidence = "  {0}%".format(round(100 - confidence))
        else:
            id = "unknown"
            confidence = "  {}%".format(round(100 - confidence))
        
        cv2.putText(img, str(id), (x+5,y-5), font, 1, (255,255,255), 2)
        cv2.putText(img, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)
        
    
    cv2.imshow('camera',img) 

    if CFace != 0:
        track_face(CFace)
    else:
        scan()
        
    CFace = 0
    
    k = cv2.waitKey(10) & 0xff 
    if k == 27:
        break
    

#cleanup
print("\n [INFO] Exiting Program and cleanup stuff")
gpio.cleanup()
cam.release()
cv2.destroyAllWindows()