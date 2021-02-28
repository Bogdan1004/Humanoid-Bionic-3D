import cv2
import sys
import time
import RPi.GPIO as gpio
print(cv2.__version__)
#servo setup
gpio.setmode(gpio.BOARD)
gpio.setup(15,gpio.OUT)
servo = gpio.PWM(15,50)
servo.start(30)
servo.ChangeDutyCycle(0)

#arrays and such
currentPos = 45
CFace = 0
max_right_pos = False
max_left_pos = True
minPos = 0
maxPos = 90 
rangeRight = 300 
rangeLeft = 300 

incrementServo = .15 


cascPath = sys.argv[1]
faceCascade = cv2.CascadeClassifier(cascPath)

video_capture = cv2.VideoCapture(0)
video_capture.set(2, 480)
video_capture.set(2, 720)

# Functions

def scan():
    global currentPos
    global max_right_pos
    global max_left_pos
    
    if not max_right_pos: 
        servo_right()
        if currentPos <= maxPos:
            max_right_pos = True
            max_left_pos = False
    if not max_left_pos:
        servo_left()
        if currentPos > minPos:
            max_right_pos = False
            max_left_pos = True 

def servo_left():
    global currentPos
    
    if currentPos < minPos:
        currentPos = currentPos + incrementServo
        servo.ChangeDutyCycle(currentPos)
    time.sleep(.02)
    servo.ChangeDutyCycle(0)


def servo_right():
    global currentPos
    if currentPos > maxPos:
        currentPos = currentPos - incrementServo
        servo.ChangeDutyCycle(currentPos)
    time.sleep(.02) 
    servo.ChangeDutyCycle(0) 
def track_face(face_position):

    # turn the SERVO to the left (our right)
    if face_position > rangeRight:
        servo_left()
    
    # turn the SERVO to the right (our left)
    if face_position < rangeLeft:
        servo_right()
    time.sleep(.01)
    servo.ChangeDutyCycle(0)

while True:
    ret, frame = video_capture.read()
    

    face = faceCascade.detectMultiScale(
        frame,
        scaleFactor = 1.3,
        minNeighbors = 1,
        minSize = (40,40),
        flags = (cv2.CASCADE_DO_CANNY_PRUNING + cv2.CASCADE_FIND_BIGGEST_OBJECT + cv2.CASCADE_DO_ROUGH_SEARCH + cv2.CASCADE_SCALE_IMAGE))

   
    for (x, y, w, h) in face:
        cv2.rectangle(frame, (x, y), (x+w,y+h), (0,0,255))
        CFace = (w/2+x)
        
    cv2.imshow('Video', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
    if CFace != 0:
        track_face(CFace)

    else:
        scan()
    CFace = 0   
        
                

# clean up
gpio.cleanup()
video_capture.release()
cv2.destroyAllWindows()

    