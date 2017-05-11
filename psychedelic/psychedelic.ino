#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int numStrands = 8;
const int pixelsPerStrand = 24;
const int onBrightness = 16;
const int pinForRowZero = 2;
const int isRGBW = 0;
const int cycleDelay = 400;

Adafruit_NeoPixel *matrix[numStrands];

unsigned long cells[pixelsPerStrand][numStrands];


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

int getRedFromLong(unsigned long value) {
  return (value >> 16) & 255;
}

int getGreenFromLong(unsigned long value) {
  return (value >> 8) & 255;
}

int getBlueFromLong(unsigned long value) {
  return value & 255;
}

int getData(unsigned long value) {
  return (value >> 24) & 255;
}

unsigned long toLong(int data, int red, int green, int blue) {
  return (unsigned long)blue | ((unsigned long)green << 8) | ((unsigned long)red << 16) | ((unsigned long)data << 24);
}

void showCells() {

  for (int y = 0; y < numStrands; ++y) {
    for(int x = 0; x < pixelsPerStrand; ++x) {
        long cellAsLong = cells[x][y];
        matrix[y]->setPixelColor(x, getRedFromLong(cellAsLong), getGreenFromLong(cellAsLong), getBlueFromLong(cellAsLong));
    }
    matrix[y]->show();
  }
  
  delay(cycleDelay);  
}


//void randomizeStrand(int row, colorFunction redFunction, colorFunction greenFunction, colorFunction blueFunction, colorFunction whiteFunction) {
//      Adafruit_NeoPixel* pixels = matrix[row];
//      for(int pixel=0; pixel < pixelsPerStrand; ++ pixel) {
//          if(isRGBW) {
//            // TODO:
//          } else {
//            pixels->setPixelColor(pixel, redFunction(), greenFunction(), blueFunction());            
//          }
//      }
//      pixels->show();
//}

//void randomizeMatrix(colorFunction redFunction, colorFunction greenFunction, colorFunction blueFunction, colorFunction whiteFunction) {
//  for (int c = 0; c < cyclesPerColor; ++c) {
//    for(int i = 0; i < numStrands; ++i) {
//      randomizeStrand(i, redFunction, greenFunction, blueFunction, whiteFunction);
//    }
//    delay(cycleDelay);
//  }
//}

void setHline(color, int x1, int x2, int y) {
  for(x = x1; x <= x2; ++x) {
    cells[x][y] = color;
  }
}

void setVline(color, int y1, int y2, int x) {
  for(y = y1; y <= y2; ++y) {
    cells[x][y] = color;
  }  
}

void paintRing(unsigned long color, int x1, int y1, int x2, int y2) {
  setHline(color, x1, x2, y1);
  setHline(color, x1, x2, y2);
  setVline(color, y1, y2, x1);
  setVline(color, y1, y2, x2);
}

void loop() {
  int centerX1 = 3;
  int centerX2 = 20;
  int centerY1 = 3;
  int centerY2 = 4;

  unsigned long red =     toLong(0, onBrightness, 0, 0);
  unsigned long green =   toLong(0, 0, onBrightness, 0);
  unsigned long blue =    toLong(0, 0, 0, onBrightness);
  unsigned long cyan =    toLong(0, 0, onBrightness, onBrightness);
  unsigned long magenta = toLong(0, onBrightness, 0, onBrightness);
  unsigned long yellow =  toLong(0, onBrightness, onBrightness , 0);

  paintRing(red, centerX1, centerY1, centerX2, centerY2);
  paintRing(green, centerX1-1, centerY1-1, centerX2+1, centerY2+1);
  paintRing(blue, centerX1-2, centerY1-2, centerX2+2, centerY2+2);
  paintRing(yellow, centerX1-3, centerY1-3, centerX2+3, centerY2+3);
  
}

