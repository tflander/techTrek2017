#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int numStrands = 8;
const int pixelsPerStrand = 24;
const int onBrightness = 16;
const int pinForRowZero = 2;
const int isRGBW = 0;
//const int cycleDelay = 400;
const int fadeDelay = 40;

Adafruit_NeoPixel *matrix[numStrands];

unsigned long cells[pixelsPerStrand][numStrands];

unsigned long toLong(int data, int red, int green, int blue) {
  return (unsigned long)blue | ((unsigned long)green << 8) | ((unsigned long)red << 16) | ((unsigned long)data << 24);
}

const int TO_RED = 1;
const int TO_GREEN = 2;
const int TO_BLUE = 4;
const int TO_CYAN = TO_GREEN | TO_BLUE;
const int TO_MAGENTA = TO_RED | TO_BLUE;
const int TO_YELLOW = TO_RED | TO_GREEN;

unsigned long red =     toLong(TO_CYAN, onBrightness, 0, 0);
unsigned long green =   toLong(TO_MAGENTA, 0, onBrightness, 0);
unsigned long blue =    toLong(TO_GREEN, 0, 0, onBrightness);
unsigned long cyan =    toLong(TO_YELLOW, 0, onBrightness, onBrightness);
unsigned long magenta = toLong(TO_RED, onBrightness, 0, onBrightness);
unsigned long yellow =  toLong(TO_BLUE, onBrightness, onBrightness , 0);

unsigned long colors[] = {magenta, green, blue, yellow, cyan, red};

int numColors = 6;

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

int getDataFromLong(unsigned long value) {
  return (value >> 24) & 255;
}

void fadeToNextColor() {
  for(int i = 0; i < onBrightness; ++i) {
    stepFade();
  }
}

int adjustColor(int currentColor, const int toColor) {
  
        if(toColor) {
          if(currentColor < onBrightness) return currentColor + 1;
        } else {
          if (currentColor > 0) return currentColor - 1;
        }

        return currentColor;
}

void stepFade() {

  for (int y = 0; y < numStrands; ++y) {
    for(int x = 0; x < pixelsPerStrand; ++x) {
        long cellAsLong = cells[x][y];
        int red = getRedFromLong(cellAsLong);
        int green = getGreenFromLong(cellAsLong);
        int blue = getBlueFromLong(cellAsLong);
        int data = getDataFromLong(cellAsLong);

        red = adjustColor(red, data & TO_RED);
        green = adjustColor(green, data & TO_GREEN);
        blue = adjustColor(blue, data & TO_BLUE);

        cells[x][y] = toLong(data, red, green, blue);
        matrix[y]->setPixelColor(x, red, green, blue);
    }
    matrix[y]->show();
  }
  
  delay(fadeDelay);  
}

void showCells() {

  for (int y = 0; y < numStrands; ++y) {
    for(int x = 0; x < pixelsPerStrand; ++x) {
        long cellAsLong = cells[x][y];
        matrix[y]->setPixelColor(x, getRedFromLong(cellAsLong), getGreenFromLong(cellAsLong), getBlueFromLong(cellAsLong));
    }
    matrix[y]->show();
  }
  
  fadeToNextColor();
}

void setHline(unsigned long color, int x1, int x2, int y) {
  for(int x = x1; x <= x2; ++x) {
    cells[x][y] = color;
  }
}

void setVline(unsigned long color, int y1, int y2, int x) {
  for(int y = y1; y <= y2; ++y) {
    cells[x][y] = color;
  }  
}

void paintRing(unsigned long color, int x1, int y1, int x2, int y2) {
  setHline(color, x1, x2, y1);
  setHline(color, x1, x2, y2);
  setVline(color, y1, y2, x1);
  setVline(color, y1, y2, x2);
}

unsigned long getColorWithOffset(int offset) {
  if(offset >= numColors) offset -= numColors;
  return colors[offset];
}

void paintRings(int offset) {

  int centerX1 = 3;
  int centerX2 = 20;
  int centerY1 = 3;
  int centerY2 = 4;

  paintRing(getColorWithOffset(offset), centerX1, centerY1, centerX2, centerY2);
  paintRing(getColorWithOffset(offset+1), centerX1-1, centerY1-1, centerX2+1, centerY2+1);
  paintRing(getColorWithOffset(offset+2), centerX1-2, centerY1-2, centerX2+2, centerY2+2);
  paintRing(getColorWithOffset(offset+3), centerX1-3, centerY1-3, centerX2+3, centerY2+3);  
  showCells();
}

void loop() {

  for (int i=numColors-1; i>=0; --i) {
    paintRings(i);
  }
  
}

