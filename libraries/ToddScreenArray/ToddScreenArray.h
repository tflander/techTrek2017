
#ifndef TODD_SCREEN_ARRAY_H
#define TODD_SCREEN_ARRAY_H

#include <Adafruit_NeoPixel.h>

class ScreenArray {
    public:
        ScreenArray(const neoPixelType&, const int& pixelsPerStrand, const int& numStrands);

        // Temp for now
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
        // end temp for now
      

};

#endif TODD_SCREEN_ARRAY_H