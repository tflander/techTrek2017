
#include <Servo.h>

Servo servoA;
Servo servoB;
int currentPosA, currentPosB, delayForTriggerRead, delayForServoTurn;
int servoPinA = 3;
int servoPinB = 7;
int triggerPin = 9;
int isTriggered = 0;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, INPUT);
  servoA.attach(servoPinA, 575, 2460); 
  servoB.attach(servoPinB, 575, 2460); 
  currentPosA = 0;  
  currentPosB = 90; 
  delayForTriggerRead = 20;
  delayForServoTurn = 10;

  servoA.write(currentPosA);     
  servoB.write(currentPosB);
     
}

void loop() {
   Serial.print("waiting for trigger\n");      
   waitForTrigger();  
   trigger();
   chew();
   waitThenReset();
}

void chew() {
  int chews = random(10, 32);
  for(int i = 0; i < chews; ++i) {
   Serial.print("chew\n");
    rotateAtSpeedTo(45, 45);
    rotateAtSpeedTo(90, 0);
    delay(random(200,500));
    if(random(1,10) < 2) {
      delay (random(500, 1500));
    }
  }
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
  rotateAtSpeedTo(90, 0);
  Serial.print("gotcha!\n");  
};

void waitThenReset() {
  Serial.print("digesting...\n");
  delay(10000);
  Serial.print("digestion complete\n");
  rotateAtSpeedTo(0, 90);
}

void rotateAtSpeedTo(int destPosA, int destPosB) {
  int stepAmtA = getStepAmt(currentPosA, destPosA);
  int stepAmtB = getStepAmt(currentPosB, destPosB);

  // TODO: fail if number of steps for A and B are different
  
  while(currentPosA != destPosA) {
    currentPosA += stepAmtA;
    currentPosB += stepAmtB;
    servoA.write(currentPosA);
    servoB.write(currentPosB);
    delay(delayForServoTurn);
  }
}

int getStepAmt(int currentPos, int destPos) {
  int stepAmt = 1;
  if(currentPos > destPos) {
    stepAmt = -1;
  }
  return stepAmt;
}


