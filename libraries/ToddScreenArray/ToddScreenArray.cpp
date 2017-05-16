#include <ToddScreenArray.h>


class Strand {
    public:

        Strand(const int& strandCount) {
            this->strandCount = strandCount;
            pixelData = (unsigned long*) malloc(strandCount);
        }

        ~Strand() {
            free(pixelData);
        }

        unsigned long getRaw(const int& index) {
            // TODO: handle index out of range
            return pixelData[index];
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
        

    private:

        int strandCount;
        unsigned long* pixelData = NULL;
};

ScreenArray::ScreenArray(const neoPixelType& pixelType, const int& pixelsPerStrand, const int& numStrands) {

    unsigned long cells[pixelsPerStrand][numStrands];


}
