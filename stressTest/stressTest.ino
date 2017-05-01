#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int numStrands = 8;
const int pixelsPerStrand = 24;
const int onBrightness = 8;
const int pinForRowZero = 2;
const int isRGBW = 0;
const int PAUSE_BETWEEN_COLORS = 1000;
const int PAUSE_FOR_FULL_BLAST = 10000;

Adafruit_NeoPixel *matrix[numStrands];

void setup() {

  neoPixelType pixelType = NEO_GRB + NEO_KHZ800;
  if(isRGBW) {
    pixelType = NEO_GRBW + NEO_KHZ800;
  }
  for (int strand=0; strand < numStrands; ++strand) {
    Adafruit_NeoPixel* pixels = new Adafruit_NeoPixel(pixelsPerStrand, strand + pinForRowZero, NEO_GRB + NEO_KHZ800);
    pixels->begin();
    matrix[strand] = pixels;
  }

}

void setStrandRGBW(int row, int red, int green, int blue, int white) {
      Adafruit_NeoPixel* pixels = matrix[row];
      for(int pixel=0; pixel < pixelsPerStrand; ++ pixel) {
          if(isRGBW) {
            // TODO:
          } else {
            pixels->setPixelColor( pixel, red, green, blue);
          }
      }
      pixels->show();
}

void setPixelsRGBW(int red, int green, int blue, int white) {
  for(int i = 0; i < numStrands; ++i) {
    setStrandRGBW(i, red, green, blue, white);
  }
}

void loop() {
  setPixelsRGBW(onBrightness, onBrightness, onBrightness, onBrightness);
  delay(PAUSE_FOR_FULL_BLAST);
  
  setPixelsRGBW(onBrightness, 0, 0, 0);
  delay(PAUSE_BETWEEN_COLORS);
  setPixelsRGBW(0, onBrightness, 0, 0);
  delay(PAUSE_BETWEEN_COLORS);
  setPixelsRGBW(0, 0, onBrightness, 0);
  delay(PAUSE_BETWEEN_COLORS);
  setPixelsRGBW(0, 0, 0, onBrightness);
  delay(PAUSE_BETWEEN_COLORS);
}

