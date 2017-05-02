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

int isAlive(unsigned long value) {
  return (value >> 24) & 255;
}

unsigned long toLong(int isAlive, int red, int green, int blue) {
  return (unsigned long)blue | ((unsigned long)green << 8) | ((unsigned long)red << 16) | ((unsigned long)isAlive << 24);
}

  /*
xAny live cell with fewer than two live neighbours dies, as if caused by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
xAny live cell with more than three live neighbours dies, as if by overpopulation.
xAny dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
   */
void mutateGrid() {

  int newCells[pixelsPerStrand][numStrands];
  for( int r = 0; r < numStrands; ++r) {
    for (int c = 0; c < pixelsPerStrand; ++c) {
      int neighbors = countNeighbors(r, c);
        int isLive = isAlive(cells[c][r]);
        int newVal = 0;  // assume fewer than two neighbors or more than three neighbors
        if(neighbors == 3) {
          newVal = 1;
        } else if (neighbors == 2) {
          newVal = isLive;
        }
        newCells[c][r] = newVal;
      }
    }

    // TODO: update cells that transitioned
    
}


int countNeighbors(int col, int row) {
  int neighbors = 0;
        
   for (int r = row - 1; r <= row + 1; ++r) {
     for(int c = col - 1; c <= col + 1; ++c) {
       if(r != row || c != col) {
         int rpos = r;
         int cpos = c;
         if(rpos < 0) rpos = numStrands - 1;
         if(rpos >= pixelsPerStrand) rpos = 0;
         if(cpos < 0) cpos =  pixelsPerStrand - 1;
         if(cpos >= numStrands) cpos = 0;
         if(isAlive(cells[cpos][rpos])) {
             neighbors = neighbors + 1;
         }
       }
      }
    }
    return neighbors;
  }


void showCells() {
  for (int row = 0; row < numStrands; ++row) {
    for(int pixel = 0; pixel < pixelsPerStrand; ++pixel) {
        long cellAsLong = cells[pixel][row];
        matrix[row]->setPixelColor(pixel, getRedFromLong(cellAsLong), getGreenFromLong(cellAsLong), getBlueFromLong(cellAsLong));
    }
    matrix[row]->show();
  }
  
  delay(1000);  
}

void loop() {
  showCells();
  mutateGrid();
}
