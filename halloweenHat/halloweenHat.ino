#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int LED_PIN = 3;
const int pixelsPerStrand = 37;
const int hatFrontPixel = 19;
const int onBrightness = 75;
const int delayBetweenFades = 500 / 10;
const int delayForSolidColor = 10000 / 10;
Adafruit_NeoPixel strand;

void setup() {
  strand = Adafruit_NeoPixel(pixelsPerStrand, LED_PIN, NEO_GRB + NEO_KHZ800);
  strand.begin();
}

void loop() {
  rainbow();
  orangeWhiteMarquee();
  orange();
  orangeBlackMarquee();
}

void orangeBlackMarquee() {
  marquee(onBrightness, onBrightness / 3, 0, 0, 0, 0);
}

void orangeWhiteMarquee() {
  marquee(onBrightness, onBrightness / 3, 0, onBrightness, onBrightness, onBrightness);
}

void marquee(int red, int green, int blue, int redOff, int greenOff, int blueOff){
  for (int step = 0; step < pixelsPerStrand * 2; ++step) {
    for (int i = 0; i < pixelsPerStrand; ++i) {
      if((i + step) % 2 == 0) {
        strand.setPixelColor(i, red, green, blue);
      } else {
        strand.setPixelColor(i, redOff, greenOff, blueOff);      
      }
    }
    strand.show();
    delay(delayBetweenFades * 3);
  }
  delay(delayForSolidColor / 4);
}

void orange() {
  for(int i = 0; i < 5; ++i) {
   circleColor(onBrightness, onBrightness / 3, 0, onBrightness, onBrightness, onBrightness);
   circleColor(onBrightness, onBrightness, onBrightness, onBrightness, onBrightness / 3, 0);
  }
}

void circleColor(int red, int green, int blue, int redOff, int greenOff, int blueOff){
  for (int step = 0; step < pixelsPerStrand/2; ++step) {
    for (int i = 0; i < pixelsPerStrand; ++i) {
      if(i >= hatFrontPixel - step && i <= hatFrontPixel + step) {
        strand.setPixelColor(i, red, green, blue);
      } else {
        strand.setPixelColor(i, redOff, greenOff, blueOff);      
      }
    }
    strand.show();
    delay(delayBetweenFades / 2);
  }
  delay(delayForSolidColor / 4);
}

void rainbow() {
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


