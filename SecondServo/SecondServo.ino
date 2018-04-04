
#include <Servo.h>

Servo servo;
int currentPos, delayAmt;

void setup() {
  servo.attach(9); 
  currentPos = 0; 
  delayAmt = 20;
  servo.write(currentPos);     
}

void loop() {  
   secondDemo();
}

void secondDemo() {
   rotateAtSpeedTo(90);
   delay(1000);         
   rotateAtSpeedTo(0);
   delay(2000);    
}

void rotateAtSpeedTo(int destPos) {
  int stepAmt = getStepAmt(destPos);

  while(currentPos != destPos) {
    currentPos += stepAmt;
    servo.write(currentPos);
    delay(delayAmt);
  }

}

int getStepAmt(int destPos) {
  int stepAmt = 1;
  if(currentPos > destPos) {
    stepAmt = -1;
  }
  return stepAmt;
}


