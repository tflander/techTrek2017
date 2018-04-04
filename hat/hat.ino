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
  greenToRed();
  delay(delayForSolidColor);
  redToBlue();
  delay(delayForSolidColor);
  blueToGreen();
  delay(delayForSolidColor);
}

void greenToRed() {
  showColor(0, onBrightness, 0);
  for(int i = 0; i < onBrightness; ++i) {
    showColor(i, onBrightness - i, 0);
  }  
}

void blueToGreen() {
  showColor(0, 0, onBrightness);
  for(int i = 0; i < onBrightness; ++i) {
    showColor(0, i, onBrightness - i);
  }  
}

void redToBlue() {
  showColor(onBrightness, 0, 0);
  for(int i = 0; i < onBrightness; ++i) {
    showColor(onBrightness - i, 0, i);
  }  
}

void showColor(int red, int green, int blue){
  for (int i = 0; i < pixelsPerStrand; ++i) {
    strand.setPixelColor(i, red, green, blue);
  }
  strand.show();
  delay(delayBetweenFades);
}


