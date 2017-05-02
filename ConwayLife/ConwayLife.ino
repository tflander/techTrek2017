#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int numStrands = 8;
const int pixelsPerStrand = 24;
const int onBrightness = 16;
const int pinForRowZero = 2;
const int LIVE = 1;
const int DEAD = -1;
const int NEUTRAL = 0;
const int RED = LIVE;
const int GREEN = NEUTRAL;
const int BLUE = DEAD;
const int isRGBW = 0;

unsigned long cells[pixelsPerStrand][numStrands];

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

    for(int pixel = 0; pixel < pixelsPerStrand; ++pixel) {
      setCell(random(2), strand, pixel);
    }
  }
}

int getRandomValueForColor(int isLive, int color) {
  if(color == DEAD) {
    if(isLive) return 0;
    return onBrightness;
  }
    
  if(color == LIVE) {
    if(isLive) return onBrightness;
    return 0;
  }
  return random(onBrightness);
}

// TODO: will need these later.
//void setDead(int row, int col) {
//  setCell(0, row, col);
//}
//
//void setAlive(int row, int col) {
//  setCell(1, row, col);
//}

void setCell(int isLive, int row, int col) {
  int red = getRandomValueForColor(isLive, RED);
  int green = getRandomValueForColor(isLive, GREEN);
  int blue = getRandomValueForColor(isLive, BLUE);
  cells[col][row] = toLong(isLive, red, green, blue);
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

unsigned long toLong(int isAlive, int red, int green, int blue) {
  return (unsigned long)blue | ((unsigned long)green << 8) | ((unsigned long)red << 16) | ((unsigned long)isAlive << 24);
}


void loop() {
  for (int row = 0; row < numStrands; ++row) {
    for(int pixel = 0; pixel < pixelsPerStrand; ++pixel) {
        long cellAsLong = cells[pixel][row];
        matrix[row]->setPixelColor(pixel, getRedFromLong(cellAsLong), getGreenFromLong(cellAsLong), getBlueFromLong(cellAsLong));
    }
    matrix[row]->show();
  }
  
  delay(10000);
}
