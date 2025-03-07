#include "Image.h"

uint8_t* Image::getPixel(unsigned int x, unsigned int y) {
    uint8_t* pixel = new uint8_t[NumChannels];
    for (unsigned int i = 0; i < NumChannels; ++i) {
        pixel[i] = (*channels[i])(y, x);
    }
    return pixel;
}

void Image::setPixel(unsigned int x, unsigned int y, const uint8_t* pixel) {
    for (unsigned int i = 0; i < NumChannels; ++i) {
        (*channels[i])(y, x) = pixel[i];
    }
}

void Image::resize(unsigned int width, unsigned int height) {
    for (unsigned int i = 0; i < NumChannels; ++i) {
        channels[i]->MatResize(height, width);
    }
}

