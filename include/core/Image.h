#ifndef IMAGE_H
#define IMAGE_H
#include "Channel.h"
#include "ImageHeader.h"
#include <vector>


template <typename T>
class Image {

private:
    ImageHeader header;
    std::vector<Channel<T>*> channels;

public:
    Image(T* imgBuffer, ImageHeader header): header(header) {
        if (header.numChannels == 1) {
            channels.push_back(new Channel(imgBuffer, header.width , header.height));
        } else {
            for (int i = 0; i < header.numChannels; ++i) {
                channels.push_back(new Channel(imgBuffer, header.width , header.height, i));
            }
        }
    }

    Channel<T>& getChannel(int channel){
        return *channels[channel];
    }

    void setChannel(int channel, const Channel<T>& data){
        *channels[channel] = data;
    }

    void setPixel(int x, int y, std::vector<T> pixel){
        // Check bounds
        if (((x >= header.width )||(y >= header.height)) && (static_cast<int>(pixel.size()) != header.numChannels)) {
            throw std::out_of_range("Pixel coordinates out of bounds or pixel size mismatch");
        }

        for (int i = 0; i < header.numChannels; ++i) {
            channels[i]->operator()(x, y) = pixel[i];
        }
    }
    const std::vector<T> getPixel(int x, int y){
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

    void resize(unsigned int width, unsigned int height){
        for (int i = 0; i < header.numChannels; ++i) {
            channels[i]->MatResize(height, width);
        }
        this->header.width = width;
        this->header.height = height;
    }

    int getWidth() const {
        return this->header.width;
    }
    int getHeight() const {
        return this->header.height;
    }
    int getNumChannels() const {
        return this->header.numChannels;
    }

    const ImageHeader& getHeader() const {
        return this->header;
    }

    ~Image() {
        for (int i = 0; i < header.numChannels; ++i) {
            delete channels[i];
        }
    }
};

#endif //IMAGE_H