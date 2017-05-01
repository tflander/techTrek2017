#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int numStrands = 8;
const int pixelsPerStrand = 24;
const int onBrightness = 16;
const int pinForRowZero = 2;
const int isRGBW = 0;
const int cyclesPerColor = 20;
const int cycleDelay = 400;

typedef int (*colorFunction)();

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

int fullBlast() {
  return onBrightness;
}

int halfIntensity() {
  return onBrightness / 2;
}

int randomFullRange() {
  return random(onBrightness);
}

int off() {
  return 0;
}

void randomizeStrand(int row, colorFunction redFunction, colorFunction greenFunction, colorFunction blueFunction, colorFunction whiteFunction) {
      Adafruit_NeoPixel* pixels = matrix[row];
      for(int pixel=0; pixel < pixelsPerStrand; ++ pixel) {
          if(isRGBW) {
            // TODO:
          } else {
            pixels->setPixelColor(pixel, redFunction(), greenFunction(), blueFunction());            
          }
      }
      pixels->show();
}

void randomizeMatrix(colorFunction redFunction, colorFunction greenFunction, colorFunction blueFunction, colorFunction whiteFunction) {
  for (int c = 0; c < cyclesPerColor; ++c) {
    for(int i = 0; i < numStrands; ++i) {
      randomizeStrand(i, redFunction, greenFunction, blueFunction, whiteFunction);
    }
    delay(cycleDelay);
  }
}

void loop() {
  randomizeMatrix(off, randomFullRange, halfIntensity, off);
  randomizeMatrix(randomFullRange, halfIntensity, off, off);
  randomizeMatrix(halfIntensity, off, randomFullRange, off);
  randomizeMatrix(randomFullRange, off, halfIntensity, off);
  randomizeMatrix(off, halfIntensity, randomFullRange, off);
  randomizeMatrix(halfIntensity, randomFullRange, off, off);
}

