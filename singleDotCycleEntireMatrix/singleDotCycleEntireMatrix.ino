#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int numStrands = 8;
const int pixelsPerStrand = 24;
const int onBrightness = 8;
const int pinForRowZero = 2;

Adafruit_NeoPixel *matrix[numStrands];

void setup() {

  for (int strand=0; strand < numStrands; ++strand) {
    Adafruit_NeoPixel* pixels = new Adafruit_NeoPixel(pixelsPerStrand, strand + pinForRowZero, NEO_GRB + NEO_KHZ800);
    pixels->begin();
    matrix[strand] = pixels;
  }

}

void cycleDotForStrand(int row) {
      Adafruit_NeoPixel* pixels = matrix[row];
      for(int pixel=0; pixel < pixelsPerStrand; ++ pixel) {
          pixels->setPixelColor( pixel, 0, onBrightness, 0);
          pixels->show();
          delay(50);
          pixels->setPixelColor( pixel, 0, 0, 0);
      }
      pixels->show();
}

void cycleDot() {
  for(int i = 0; i < numStrands; ++i) {
    cycleDotForStrand(i);
  }
}

void loop() {
  cycleDot();
}

