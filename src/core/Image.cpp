#include "core/Image.h"

unsigned char* Image::getPixel(unsigned int x, unsigned int y) {
    unsigned char* pixel = new unsigned char[NumChannels];
    for (unsigned int i = 0; i < NumChannels; ++i) {
        pixel[i] = (*channels[i])(y, x);
    }
    return pixel;
}

void Image::setPixel(unsigned int x, unsigned int y, const unsigned char* pixel) {
    for (unsigned int i = 0; i < NumChannels; ++i) {
        (*channels[i])(y, x) = pixel[i];
    }
}

void Image::resize(unsigned int width, unsigned int height) {
    for (unsigned int i = 0; i < NumChannels; ++i) {
        channels[i]->MatResize(height, width);
    }
}

