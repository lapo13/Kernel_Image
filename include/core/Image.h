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
    Image(T* imgBuffer, ImageHeader header);

    Channel<T>& getChannel(int channel);
    void setChannel(int channel, const Channel<T>& data);

    void setPixel(int x, int y, const T* pixel);
    const std::vector<T> getPixel(int x, int y);

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

    void resize(unsigned int width, unsigned int height);

    ~Image() {
        for (int i = 0; i < header.numChannels; ++i) {
            delete channels[i];
        }
    }
};

#endif //IMAGE_H