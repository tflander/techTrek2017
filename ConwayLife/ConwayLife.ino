#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int numRows = 8;
const int pixelsPerRow = 24;
// const int onBrightness = 128;
const int LIVE = 1;
const int DEAD = -1;
const int NEUTRAL = 0;
const int RED = LIVE;
const int GREEN = NEUTRAL;
const int BLUE = DEAD;

unsigned long cells[pixelsPerRow][numRows];
Adafruit_NeoPixel pixels[numRows];

void setup() {

  for (int row = 0; row < numRows; ++row) {

    Adafruit_NeoPixel pixels[row] = Adafruit_NeoPixel(pixelsPerRow, row, NEO_GRB + NEO_KHZ800);
    pixels[row].begin();
    
    for (int col = 0; col < pixelsPerRow; ++ col) {
      setCell(random(1), row, col);
    }
  }  
}

int getRandomValueForColor(int isLive, int color) {
  if(color == DEAD) {
    if(isLive) return 0;
    return 255;
  }
    
  if(color == LIVE) {
    if(isLive) return 255;
    return 0;
  }
  return random(255);
}

void setDead(int row, int col) {
  setCell(0, row, col);
}

void setAlive(int row, int col) {
  setCell(1, row, col);
}

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
  return blue | (green << 8) | (red << 16) | (isAlive << 24);
}


void loop() {
  for (int row = 0; row < numRows; ++row) {
    for(int pixel = 0; pixel < pixelsPerRow; ++pixel) {
        long cellAsLong = cells[pixel][row];
      pixels[row].setPixelColor(pixel, getRedFromLong(cellAsLong), getGreenFromLong(cellAsLong), getBlueFromLong(cellAsLong));
      pixels[row].show();
    }
  }
  
  delay(10000);
}
