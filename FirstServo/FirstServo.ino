
#include <Servo.h>

Servo servo; 
void setup() {
  servo.attach(9); 
}

void loop() {  
   firstDemo();
   secondDemo();
}

void firstDemo() {
   servo.write(0);     
   delay(1000);         
   servo.write(90);    
   delay(2000);    
}

void secondDemo() {
   rotateAtSpeed(90, 0, 10);
   servo.write(0);     
   delay(1000);         
   rotateAtSpeed(0, 90, 10);
   delay(2000);    
}

void rotateAtSpeed(int currentPos, int destPos, int delayAmt) {
  int stepAmt = 1;
  if(currentPos > destPos) {
    stepAmt = -1;
  }

  while(currentPos != destPos) {
    currentPos += stepAmt;
    servo.write(currentPos);
    delay(delayAmt);
  }

}

