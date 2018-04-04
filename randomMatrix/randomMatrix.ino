#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int numStrands = 8;
const int pixelsPerStrand = 24;
const int onBrightness = 255;
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
    Adafruit_NeoPixel* pixels = new Adafruit_NeoPixel(pixelsPerStrand, strand + pinForRowZero, pixelType);
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

int randomHalfRange() {
  return random(onBrightness/2);
}


int off() {
  return 0;
}

void randomizeStrand(int row, colorFunction redFunction, colorFunction greenFunction, colorFunction blueFunction, colorFunction whiteFunction) {
      Adafruit_NeoPixel* pixels = matrix[row];
      for(int pixel=0; pixel < pixelsPerStrand; ++ pixel) {
          if(isRGBW) {
            pixels->setPixelColor(pixel, pixels->Color(redFunction(), greenFunction(), blueFunction(), whiteFunction()) );
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
  randomizeMatrix(off, randomFullRange, halfIntensity, randomHalfRange);
  randomizeMatrix(randomFullRange, halfIntensity, off, randomHalfRange);
  randomizeMatrix(halfIntensity, off, randomFullRange, randomHalfRange);
  randomizeMatrix(randomFullRange, off, halfIntensity, randomHalfRange);
  randomizeMatrix(off, halfIntensity, randomFullRange, randomHalfRange);
  randomizeMatrix(halfIntensity, randomFullRange, off, randomHalfRange);
}

