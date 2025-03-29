#include "core/Image.h"
#include <stdexcept>

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
const std::vector<T> Image<T>::getPixel(int x, int y) {
    // Check bounds
    if (x >= header.width || y >= header.height) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }

    std::vector<T> pixel(header.numChannels);
    for (int i = 0; i < header.numChannels; ++i) {
        pixel[i] = channels[i]->operator()(x, y);  // Note: Channel uses (row,col) order
    }
    return pixel;
}

template <typename T>
void Image<T>::setPixel(int x, int y, const T* pixel) {
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
