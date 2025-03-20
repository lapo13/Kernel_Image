#include "core/Image.h"

const unsigned char* Image::getPixel(unsigned int x, unsigned int y) {
    unsigned char* pixel = new unsigned char[NumChannels];
    for (int i = 0; i < NumChannels; ++i) {
        pixel[i] = (*channels[i])(x, y);
    }
    return pixel;
}

void Image::setPixel(unsigned int x, unsigned int y, const unsigned char* pixel) {
    for (int i = 0; i < NumChannels; ++i) {
        (*channels[i])(y, x) = pixel[i];
    }
}

void Image::resize(unsigned int width, unsigned int height) {
    for (int i = 0; i < NumChannels; ++i) {
        channels[i]->MatResize(height, width);
    }
}

