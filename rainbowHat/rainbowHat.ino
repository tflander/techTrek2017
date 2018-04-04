#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int LED_PIN = 3;
const int pixelsPerStrand = 37;
const int hatFrontPixel = 19;
const int onBrightnessDay = 75;
const int onBrightnessNight = 64;
const int onBrightness = onBrightnessNight;
Adafruit_NeoPixel strand;

void setup() {
  strand = Adafruit_NeoPixel(pixelsPerStrand, LED_PIN, NEO_GRB + NEO_KHZ800);
  strand.begin();
}

void loop() {
  rainbow();
}

void circleFade(int redStart, int greenStart, int blueStart, int redEnd, int greenEnd, int blueEnd){
  showColor(redStart, greenStart, blueStart);

  int step = 0;
  while(true) {
    int changed = 0;
    for (int i = 0; i < pixelsPerStrand; ++i) {
      if(i >= hatFrontPixel - step && i <= hatFrontPixel + step) {
        for(int j = 0; j < 5; ++j) {
          changed += stepFade(i, redEnd, greenEnd, blueEnd);
        }
      }
    }
    if(step <= pixelsPerStrand/2) ++step;
    if(changed == 0) {
      return;
    }

  }
}

int stepFade(int pixel, int redEnd, int greenEnd, int blueEnd) {
        uint32_t currColor= strand.getPixelColor(pixel);
        uint8_t red = (currColor>>16) & 255;
        uint8_t green = (currColor>>8) & 255;
        uint8_t blue = currColor & 255;
        return fadePixel(pixel, red, green, blue, redEnd, greenEnd, blueEnd);  
}

void rainbow() {
  greenToYellow();
  yellowToOrange();
  orangeToRed();
  redToPurple();
  purpleToBlue();
  blueToCyan();
  cyanToGreen();  
}

void greenToYellow() {
  circleFade(0, onBrightness, 0, onBrightness, onBrightness, 0);  
}

void yellowToOrange() {
  circleFade(onBrightness, onBrightness, 0, onBrightness, onBrightness/3, 0);  
}

void orangeToRed() {
  circleFade(onBrightness, onBrightness/3, 0, onBrightness, 0, 0);  
}

void redToPurple() {
  circleFade(onBrightness, 0, 0, onBrightness, 0, onBrightness);  
}

void purpleToBlue() {
  circleFade(onBrightness, 0, onBrightness, 0, 0, onBrightness);  
}

void blueToCyan() {
  circleFade(0, 0, onBrightness, 0, onBrightness, onBrightness);  
}

void cyanToGreen() {
  circleFade(0, onBrightness, onBrightness, 0, onBrightness, 0);  
}

void redToBlue() {
  circleFade(onBrightness, 0, 0, 0, 0, onBrightness);  
}

int fadePixel(int pixel, int startRed, int startGreen, int startBlue, int endRed, int endGreen, int endBlue) {
  int changed = 0;
  int nextRed = fadeSingleColor(startRed, endRed);
  int nextGreen = fadeSingleColor(startGreen, endGreen);
  int nextBlue = fadeSingleColor(startBlue, endBlue);
  if(startRed != nextRed) ++changed;
  if(startGreen != nextGreen) ++changed;
  if(startBlue != nextBlue) ++changed;
  strand.setPixelColor(pixel, nextRed, nextGreen, nextBlue);
  strand.show();
  return changed;
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
}


