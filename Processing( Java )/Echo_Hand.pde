import com.onformative.leap.LeapMotionP5;
import com.leapmotion.leap.Finger;
import processing.serial.*;
Serial port;
LeapMotionP5 leap;

public void setup() {
  size(500, 500);
  port = new Serial(this, "COM4", 57600);
  leap = new LeapMotionP5(this);
}

public void draw() {
  background(0);
  fill(255);
  for (Finger finger : leap.getFingerList()) {
    int fingerid=finger.id()%10;
    PVector fingerPos = leap.getTip(finger);
    ellipse(fingerPos.x, fingerPos.y, 10, 10);
    System.out.println(fingerid);
    if(fingerid==0)
       {port.write('0');delay(10); }
    else 
      if(fingerid==1)
        { port.write('1');
          delay(10);  
      }
     else
        if(fingerid==2)
           {port.write('2');
           delay(10); }
         else  
           if(fingerid==3)
               {port.write('3');delay(10); }
            else
              if(fingerid==4)
                 {port.write('4');delay(10);}
              

}
    port.write('5');
}

public void stop() {
  leap.stop();
}
