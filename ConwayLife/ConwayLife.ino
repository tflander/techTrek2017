#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//#define DEBUG 0

const int numStrands = 8;
const int pixelsPerStrand = 24;
const int onBrightness = 8;
const int pinForRowZero = 2;
const int LIVE = 1;
const int DEAD = -1;
const int NEUTRAL = 0;
const int RED = LIVE;
const int GREEN = NEUTRAL;
const int BLUE = DEAD;
const int isRGBW = 0;
const int delayBetweenCycles = 1000;

unsigned long cells[pixelsPerStrand][numStrands];

Adafruit_NeoPixel *matrix[numStrands];

void setup() {

#ifdef DEBUG
Serial.begin(9600);
#endif

  #ifdef DEBUG
    Serial.println("+setup()");
  #endif

 neoPixelType pixelType = NEO_GRB + NEO_KHZ800;
  if(isRGBW) {
    pixelType = NEO_GRBW + NEO_KHZ800;
  }
  for (int y=0; y < numStrands; ++y) {
    Adafruit_NeoPixel* pixels = new Adafruit_NeoPixel(pixelsPerStrand, y + pinForRowZero, NEO_GRB + NEO_KHZ800);
    pixels->begin();
    matrix[y] = pixels;

    for(int x = 0; x < pixelsPerStrand; ++x) {
      setCell(random(2), x, y);
    }
  }

  #ifdef DEBUG
    Serial.println("-setup()");
  #endif
  
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
  return random(onBrightness/2);
}

void setDead(int x, int y) {
  setCell(0, x, y);
}

void setAlive(int x, int y) {
  setCell(1, x, y);
}

void setCell(int isLive, int x, int y) {
  int red = getRandomValueForColor(isLive, RED);
  int green = getRandomValueForColor(isLive, GREEN);
  int blue = getRandomValueForColor(isLive, BLUE);
  cells[x][y] = toLong(isLive, red, green, blue);
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

  // determine cells that transitioned
  int newCells[pixelsPerStrand][numStrands];
  for( int y = 0; y < numStrands; ++y) {
    for (int x = 0; x < pixelsPerStrand; ++x) {
      int neighbors = countNeighbors(x, y);
        int isLive = isAlive(cells[x][y]);
        int newVal = 0;  // assume fewer than two neighbors or more than three neighbors
        if(neighbors == 3) {
          newVal = 1;
        } else if (neighbors == 2) {
          newVal = isLive;
        }

        int shouldFlip = 0;
        if(newVal != isLive) {
          shouldFlip = 1;
        }
        newCells[x][y] = shouldFlip;
      }
    }

  #ifdef DEBUG
    Serial.println("Cells to Flip");
  for( int y = 0; y < numStrands; ++y) {
    for (int x = 0; x < pixelsPerStrand; ++x) {
      Serial.print(newCells[x][y]);
    }
    Serial.println("");
  }    
  Serial.println("==========");
  #endif
    

  // update cells that transitioned
  for( int y = 0; y < numStrands; ++y) {
    for (int x = 0; x < pixelsPerStrand; ++x) {
      if(newCells[x][y]) {
        int isLive = isAlive(cells[x][y]);
        if(isLive) {
          setDead(x, y);
        } else {
          setAlive(x, y);
        }
        
      }
    }
  }
      
}


int countNeighbors(int x, int y) {
  int neighbors = 0;
        
   for (int x1 = x - 1; x1 <= x + 1; ++x1) {
     for(int y1 = y - 1; y1 <= y + 1; ++y1) {
       if(x1 != x || y1 != y) {
         int xpos = x1;
         int ypos = y1;
         if(ypos < 0) ypos = numStrands - 1;
         if(xpos >= pixelsPerStrand) xpos = 0;
         if(xpos < 0) xpos =  pixelsPerStrand - 1;
         if(ypos >= numStrands) ypos = 0;
         if(isAlive(cells[xpos][ypos])) {
             neighbors = neighbors + 1;
         }
       }
      }
    }
    return neighbors;
  }


void showCells() {

  #ifdef DEBUG
    Serial.println("showCells");
  for( int y = 0; y < numStrands; ++y) {
    for (int x = 0; x < pixelsPerStrand; ++x) {
        long cellAsLong = cells[x][y];
        Serial.print("r=");
        Serial.print(getRedFromLong(cellAsLong));
        Serial.print(";g=");
        Serial.print(getGreenFromLong(cellAsLong));
        Serial.print(";b=");
        Serial.print(getBlueFromLong(cellAsLong));
        Serial.print("|");
    }
    Serial.println("");
  }    
  Serial.println("==========");
  #endif
  
  for (int y = 0; y < numStrands; ++y) {
    for(int x = 0; x < pixelsPerStrand; ++x) {
        long cellAsLong = cells[x][y];
        matrix[y]->setPixelColor(x, getRedFromLong(cellAsLong), getGreenFromLong(cellAsLong), getBlueFromLong(cellAsLong));
    }
    matrix[y]->show();
  }
  
  delay(delayBetweenCycles);  
}

void loop() {
  showCells();
  mutateGrid();
}
