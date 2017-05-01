#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int pixelsPerStrand = 24;
const int onBrightness = 32;
const int pin = 2;
const int isRGBW = -1;
const int PAUSE_BETWEEN_COLORS = 1000;

Adafruit_NeoPixel* pixels;

void setup() {

  neoPixelType pixelType = NEO_GRB + NEO_KHZ800;
  if(isRGBW) {
    pixelType = NEO_GRBW + NEO_KHZ800;
  }
  pixels = new Adafruit_NeoPixel(pixelsPerStrand, pin, pixelType);
  pixels->begin();

}

void setStrandRGBW(int red, int green, int blue, int white) {
      for(int pixel=0; pixel < pixelsPerStrand; ++ pixel) {
          if(isRGBW) {
            pixels->setPixelColor(pixel, pixels->Color(red,green,blue,white) );
          } else {
            pixels->setPixelColor( pixel, red, green, blue);
          }
      }
      pixels->show();
}


void loop() {
  setStrandRGBW(onBrightness, 0, 0, 0);
  delay(PAUSE_BETWEEN_COLORS);
  setStrandRGBW(0, onBrightness, 0, 0);
  delay(PAUSE_BETWEEN_COLORS);
  setStrandRGBW(0, 0, onBrightness, 0);
  delay(PAUSE_BETWEEN_COLORS);
  setStrandRGBW(0, 0, 0, onBrightness);
  delay(PAUSE_BETWEEN_COLORS);
}

