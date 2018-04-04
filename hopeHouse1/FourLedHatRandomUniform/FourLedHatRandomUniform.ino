
int pins[] = {LED_BUILTIN, 6, 7, A2, A3};
int numPins = sizeof(pins) / sizeof(pins[0]);
int minOnInMillis = 20;
int maxOnInMillis = 1000;
int maxAllOffInMillis = 300;

void setup() {
  for (int i = 0; i < numPins; ++i) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  int pin = random(0, numPins);
  digitalWrite(pin, HIGH);
  delay(random(minOnInMillis, maxOnInMillis));
  digitalWrite(pin, LOW);
  delay(random(0, maxAllOffInMillis));
}




