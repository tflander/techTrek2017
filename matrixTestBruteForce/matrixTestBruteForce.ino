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

// this fails
//  for (int strand=0; strand <= numStrands; ++strand) {
//    matrix[strand] = &Adafruit_NeoPixel(pixelsPerStrand, strand, NEO_GRB + NEO_KHZ800);
//    matrix[strand]->begin();
//  }

// also fails.
//  for (int strand=0; strand <= numStrands; ++strand) {
//    Adafruit_NeoPixel* pixels = &Adafruit_NeoPixel(pixelsPerStrand, strand + pinForRowZero, NEO_GRB + NEO_KHZ800);
//    pixels->begin();
//    matrix[strand] = pixels;
//  }

// also fails
//  for (int strand=0; strand <= numStrands; ++strand) {
//    Adafruit_NeoPixel* pixels = new Adafruit_NeoPixel(pixelsPerStrand, strand + pinForRowZero, NEO_GRB + NEO_KHZ800);
//    pixels->begin();
//    matrix[strand] = pixels;
//  }

// this works
    Adafruit_NeoPixel* row0 = &Adafruit_NeoPixel(pixelsPerStrand, 0 + pinForRowZero, NEO_GRB + NEO_KHZ800);
    row0->begin();
    matrix[0] = row0;
    
    Adafruit_NeoPixel* row1 = &Adafruit_NeoPixel(pixelsPerStrand, 1 + pinForRowZero, NEO_GRB + NEO_KHZ800);
    row1->begin();
    matrix[1] = row1;
    
    Adafruit_NeoPixel* row2 = &Adafruit_NeoPixel(pixelsPerStrand, 4, NEO_GRB + NEO_KHZ800);
    row2->begin();
    matrix[2] = row2;
    
    Adafruit_NeoPixel* row3 = &Adafruit_NeoPixel(pixelsPerStrand, 5, NEO_GRB + NEO_KHZ800);
    row3->begin();
    matrix[3] = row3;
    
    Adafruit_NeoPixel* row4 = &Adafruit_NeoPixel(pixelsPerStrand, 6, NEO_GRB + NEO_KHZ800);
    row4->begin();
    matrix[4] = row4;
    
    Adafruit_NeoPixel* row5 = &Adafruit_NeoPixel(pixelsPerStrand, 7, NEO_GRB + NEO_KHZ800);
    row5->begin();
    matrix[5] = row5;
    
    Adafruit_NeoPixel* row6 = &Adafruit_NeoPixel(pixelsPerStrand, 8, NEO_GRB + NEO_KHZ800);
    row6->begin();
    matrix[6] = row6;
    
    Adafruit_NeoPixel* row7 = &Adafruit_NeoPixel(pixelsPerStrand, 9, NEO_GRB + NEO_KHZ800);
    row7->begin();
    matrix[7] = row7;
}

void randomizeStrand(int row) {
      Adafruit_NeoPixel* pixels = matrix[row];
      for(int pixel=0; pixel < pixelsPerStrand; ++ pixel) {
          pixels->setPixelColor( pixel, onBrightness/2, 0, random(onBrightness));
      }
      pixels->show();
}

void cycleDotForStrand(int row) {
      Adafruit_NeoPixel* pixels = matrix[row];
      for(int pixel=0; pixel < pixelsPerStrand; ++ pixel) {
          pixels->setPixelColor( pixel, onBrightness, 0, 0);
          pixels->show();
          delay(50);
          pixels->setPixelColor( pixel, 0, 0, 0);
      }
      pixels->show();
}

void randomizeMatrix() {
  for(int i = 0; i < numStrands; ++i) {
    randomizeStrand(i);
  }
}

void cycleDot() {
  for(int i = 0; i < numStrands; ++i) {
    cycleDotForStrand(i);
  }
}

void loop() {
  // randomizeMatrix();
  cycleDot();
}

