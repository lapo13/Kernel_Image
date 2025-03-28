#include "core/Image.h"

template <typename T>
Image<T>::Image(T* imgBuffer, ImageHeader header): header(header) {
    if (header.numChannels == 1) {
        channels.push_back(new Channel(imgBuffer, header.width , header.height));
    } else {
        for (int i = 0; i < header.numChannels; ++i) {
            channels.push_back(new Channel(imgBuffer, header.width , header.height, i));
        }
    }
}

template <typename T>
Channel<T>& Image<T>::getChannel(int channel) {
    return *channels[channel];
}

template <typename T>
void Image<T>::setChannel(int channel, const Channel<T>& data) {
    *channels[channel] = data;
}

template <typename T>
const std::vector<T> Image<T>::getPixel(unsigned int x, unsigned int y) {
    std::vector<T> pixel(header.numChannels);
    for (int i = 0; i < header.numChannels; ++i) {
        pixel[i] = channels[i]->operator()(x, y);
    }
    return pixel;
}

template <typename T>
void Image<T>::setPixel(unsigned int x, unsigned int y, const T* pixel) {
    for (int i = 0; i < header.numChannels; ++i) {
        channels[i]->operator()(x, y) = pixel[i];
    }
}

template <typename T>
void Image<T>::resize(unsigned int width, unsigned int height) {
    for (int i = 0; i < header.numChannels; ++i) {
        channels[i]->MatResize(height, width);
    }
}

//Explicit instantiation
template class Image<unsigned char>;
