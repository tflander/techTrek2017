#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int LED_PIN = 3;
const int pixelsPerStrand = 37;
const int onBrightness = 75;
const int delayBetweenFades = 500;
const int delayForSolidColor = 10000;
Adafruit_NeoPixel strand;

void setup() {
  strand = Adafruit_NeoPixel(pixelsPerStrand, LED_PIN, NEO_GRB + NEO_KHZ800);
  strand.begin();
}

void loop() {
  greenToYellow();
  yellowToRed();
  redToPurple();
  purpleToBlue();
  blueToCyan();
  cyanToGreen();
}

void greenToYellow() {
  fade(0, onBrightness, 0, onBrightness, onBrightness, 0);  
}

void yellowToRed() {
  fade(onBrightness, onBrightness, 0, onBrightness, 0, 0);  
}

void redToPurple() {
  fade(onBrightness, 0, 0, onBrightness, 0, onBrightness);  
}

void purpleToBlue() {
  fade(onBrightness, 0, onBrightness, 0, 0, onBrightness);  
}

void blueToCyan() {
  fade(0, 0, onBrightness, 0, onBrightness, onBrightness);  
}

void cyanToGreen() {
  fade(0, onBrightness, onBrightness, 0, onBrightness, 0);  
}

void redToBlue() {
  fade(onBrightness, 0, 0, 0, 0, onBrightness);  
}

void fade(int startRed, int startGreen, int startBlue, int endRed, int endGreen, int endBlue) {
  showColor(startRed, startGreen, startBlue);
  int currentRed = startRed;
  int currentGreen = startGreen;
  int currentBlue = startBlue;
  for(int i = 0; i < onBrightness; ++i) {
    currentRed = fadeSingleColor(currentRed, endRed);
    currentGreen = fadeSingleColor(currentGreen, endGreen);
    currentBlue = fadeSingleColor(currentBlue, endBlue);
    showColor(currentRed, currentGreen, currentBlue);
  }  
  delay(delayForSolidColor);
}

int fadeSingleColor(int currentColor, int endColor) {
  if(currentColor < endColor)
    return currentColor + 1;
  if(currentColor > endColor) {
    return currentColor - 1;
  }
  return currentColor;
}

void showColor(int red, int green, int blue){
  for (int i = 0; i < pixelsPerStrand; ++i) {
    strand.setPixelColor(i, red, green, blue);
  }
  strand.show();
  delay(delayBetweenFades);
}


