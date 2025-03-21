#include "core/Image.h"

const std::vector<unsigned char> Image::getPixel(unsigned int x, unsigned int y) {
    std::vector<unsigned char> pixel(NumChannels);
    for (int i = 0; i < NumChannels; ++i) {
        pixel[i] = Image::getChannel(i)->operator()(y, x);
    }
    return pixel;
}

void Image::setPixel(unsigned int x, unsigned int y, const unsigned char* pixel) {
    for (int i = 0; i < NumChannels; ++i) {
        Image::getChannel(i) -> operator()(x, y) = pixel[i];
    }
}

void Image::resize(unsigned int width, unsigned int height) {
    for (int i = 0; i < NumChannels; ++i) {
        channels[i]->MatResize(height, width);
    }
}

