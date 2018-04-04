
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if(millis() > 10000) {
    enterLowPower();
  } else {
    halfSecondFlash();    
  }
}
void halfSecondFlash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);                     
  digitalWrite(LED_BUILTIN, LOW); 
  delay(500);                     
  
}

void heartBeat() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);                     
  digitalWrite(LED_BUILTIN, LOW); 
  delay(100);                     
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);                     
  digitalWrite(LED_BUILTIN, LOW); 
  delay(5000);                     
  
}

void enterLowPower()
{
  while(true) {
    heartBeat();
  }
}


