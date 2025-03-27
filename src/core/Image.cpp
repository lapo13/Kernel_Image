#include "core/Image.h"

template <typename T>
Image<T>::Image(T* imgBuffer, int width, int height, int NumChannels, std::string magicnumber, T max): 
width(width), height(height), NumChannels(NumChannels), max(max), MagicNumber(magicnumber) {
    if (NumChannels == 1) {
        channels.push_back(new Channel(imgBuffer, width, height));
    } else {
        for (int i = 0; i < NumChannels; ++i) {
            channels.push_back(new Channel(imgBuffer, width, height, i));
        }
    }
}

template <typename T>
const std::vector<T> Image<T>::getPixel(unsigned int x, unsigned int y) {
    std::vector<T> pixel(NumChannels);
    for (int i = 0; i < NumChannels; ++i) {
        pixel[i] = Image::getChannel(i)->operator()(x, y);
    }
    return pixel;
}

template <typename T>
void Image<T>::setPixel(unsigned int x, unsigned int y, const T* pixel) {
    for (int i = 0; i < NumChannels; ++i) {
        Image::getChannel(i) -> operator()(x, y) = pixel[i];
    }
}

template <typename T>
void Image<T>::resize(unsigned int width, unsigned int height) {
    for (int i = 0; i < NumChannels; ++i) {
        channels[i]->MatResize(height, width);
    }
}

//Explicit instantiation
template class Image<unsigned char>;
