
#include <Servo.h>

Servo servo;
int currentPos, delayForTriggerRead, delayForServoTurn;
int servoPin = 5;
int triggerPin = 9;
int isTriggered = 0;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, INPUT);
  servo.attach(servoPin); 
  currentPos = 0; 
  delayForTriggerRead = 20;
  delayForServoTurn = 20;
  servo.write(currentPos);     
}

void loop() {
   Serial.print("waiting for trigger\n");      
   waitForTrigger();  
   trigger();
   waitThenReset();
}

void waitForTrigger() {
  while(true) {
    int pressCount = 0;
    for(int i = 0; i < 3; ++i) {
      pressCount += digitalRead(triggerPin);
      delay(20);
    }
    if(pressCount == 3) {
      Serial.print("triggered\n"); 
      return;     
    }
  }
}

void trigger() {
  Serial.print("closing trap...\n");
//   secondDemo();
  delay(1500); // fake for now
  Serial.print("gotcha!\n");  
};

void waitThenReset() {
  Serial.print("digesting...\n");
  delay(10000);
  Serial.print("digestion complete\n");
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
    delay(delayForServoTurn);
  }

}

int getStepAmt(int destPos) {
  int stepAmt = 1;
  if(currentPos > destPos) {
    stepAmt = -1;
  }
  return stepAmt;
}


