#ifndef IMAGE_H
#define IMAGE_H
#include "Channel.h"
#include <vector>
#include <string>
#include <iostream>

template <typename T>
class Image {

private:
    int width, height, NumChannels;
    std::string MagicNumber;
    std::vector<Channel<T>*> channels;

public:
    Image(T* imgBuffer, int width, int height, int NumChannels, std::string magicnumber);

    Channel<T>& getChannel(int channel);
    void setChannel(int channel, const Channel<T>& data);

    void setPixel(unsigned int x, unsigned int y, const T* pixel);
    const std::vector<T> getPixel(unsigned int x, unsigned int y);

    int getWidth() const {
        return width;
    }
    int getHeight() const {
        return height;
    }
    int getNumChannels() const {
        return NumChannels;
    }
    const std::string getMagicNumber() const {
        return MagicNumber;
    }

    void resize(unsigned int width, unsigned int height);

    ~Image() {
        for (int i = 0; i < NumChannels; ++i) {
            delete channels[i];
        }
    }
};

#endif //IMAGE_H