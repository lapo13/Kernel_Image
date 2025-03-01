#include <array>
#include <Image.h>

template <typename PixelType, unsigned int NumChannels>
std::array<Channel<PixelType>, NumChannels>& Image<PixelType, NumChannels>::getPixel(unsigned int x, unsigned int y) {
    static std::array<Channel<PixelType>, NumChannels> pixel;
    for (unsigned int i = 0; i < NumChannels; ++i) {
        pixel[i](0,0) = channels[i](y,x);
    }
    return pixel; 
}

template <typename PixelType, unsigned int NumChannels>
void Image<PixelType, NumChannels>::setPixel(unsigned int x, unsigned int y, const std::array<PixelType, NumChannels>& pixel) {
    for (unsigned int i = 0; i < NumChannels; ++i) {
        channels[i](y,x) = pixel[i];
    }
}

template <typename PixelType, unsigned int NumChannels>
void Image<PixelType, NumChannels>::resize(unsigned int width, unsigned int height) {
    for (unsigned int i = 0; i < NumChannels; ++i) {
        channels[i].resize(width, height);
    }
    this->width = width;
    this->height = height;
}

template <typename PixelType, unsigned int NumChannels>
void Image<PixelType, NumChannels>::fill(const std::array<PixelType, NumChannels>& pixel) {
    for (unsigned int i = 0; i < NumChannels; ++i) {
        channels[i].fill(pixel[i]);
    }
}
