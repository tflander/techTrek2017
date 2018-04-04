#include <ToddScreenArray.h>



        Strand::Strand(const int& strandCount) {
            this->strandCount = strandCount;
            pixelData = (unsigned long*) malloc(strandCount);
        }

        Strand::~Strand() {
            free(pixelData);
        }

        unsigned long Strand::getRaw(const int& index) {
            // TODO: handle index out of range
            return pixelData[index];
        }

        int Strand::getRedFromLong(unsigned long value) {
        return (value >> 16) & 255;
        }

        int Strand::getGreenFromLong(unsigned long value) {
        return (value >> 8) & 255;
        }

        int Strand::getBlueFromLong(unsigned long value) {
        return value & 255;
        }

        int Strand::getDataFromLong(unsigned long value) {
        return (value >> 24) & 255;
        }
        
ScreenArray::ScreenArray(const neoPixelType& pixelType, const int& pixelsPerStrand, const int& numStrands) {

    unsigned long cells[pixelsPerStrand][numStrands];


}
