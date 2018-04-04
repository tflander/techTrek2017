#include <avr/sleep.h>      

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  halfSecondFlash();
  if(minutesRunning() >= 15) {
    powerDown();
  }
}

unsigned long minutesRunning() {
  return millis() / 60000;
}

void halfSecondFlash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);                     
  digitalWrite(LED_BUILTIN, LOW); 
  delay(200);                     
  
}

void powerDown()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
  sleep_enable();                      
  sleep_mode();
}


