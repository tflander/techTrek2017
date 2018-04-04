
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

int ledPin = 3;
int pixelsPerStrand = 1;

Adafruit_NeoPixel pixels;

// the setup function runs once when you press reset or power the board
void setup() {
    pixels = Adafruit_NeoPixel(pixelsPerStrand, ledPin, NEO_GRB + NEO_KHZ800);
    pixels.begin();
}

// the loop function runs over and over again forever
void loop() {
  for(int i = 0; i < pixelsPerStrand; ++i) {
    pixels.setPixelColor(i, 0, 64, 0);
  }
  pixels.show();
  delay(1000);
 }
