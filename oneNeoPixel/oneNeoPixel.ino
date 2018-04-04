#include <Adafruit_NeoPixel.h>
 
#define PIN      7
#define N_LEDS 1
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
}
 
void loop() {
  chase(strip.Color(32, 0, 0)); // Red
  chase(strip.Color(0, 32, 0)); // Green
  chase(strip.Color(0, 0, 32)); // Blue
}
 
static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.show();
      delay(25);
  }
}
