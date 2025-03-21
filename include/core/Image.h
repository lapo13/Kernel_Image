#ifndef IMAGE_H
#define IMAGE_H
#include "Matrix.h"
#include <vector>
#include <string>
#include <iostream>

class Image {

protected:
    class Channel : public Matrix {
    private:
        unsigned char min, max;
        int channel_num;   

    public:
        Channel(unsigned char *imgBuffer, int width, int height, int channel_num);
        Channel(unsigned char *imgBuffer, int width, int height);

        unsigned char getMin() const;
        unsigned char getMax() const;
        void setMin(unsigned char Min) {
            this->min = Min;
        }
        void setMax(unsigned char Max) {
            this->max = Max;
        }

        double getMean() const;

        void normalize(unsigned char newMin, unsigned char newMax);
        void threshold(unsigned char threshold, unsigned char lowValue, unsigned char highValue);

        ~Channel() = default;
    };

private:
    int width, height, NumChannels;
    unsigned char max;
    std::string MagicNumber;
    std::vector<Channel*> channels;

public:
    Image(unsigned char* imgBuffer, int width, int height, int NumChannels, std::string magicnumber, unsigned char max);

    Channel* getChannel(int channel) {
        return channels[channel];
    }

    const Channel* getChannel(unsigned int channel) const {
        return channels[channel];
    }

    const std::vector<unsigned char> getPixel(unsigned int x, unsigned int y);

    void setPixel(unsigned int x, unsigned int y, const unsigned char* pixel);

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    int getNumChannels() const {
        return NumChannels;
    }

    std::string getMagicNumber() const {
        return MagicNumber;
    }

    int getMax() const {
        return (int)max;
    }

    void resize(unsigned int width, unsigned int height);

    ~Image() {
        for (int i = 0; i < NumChannels; ++i) {
            delete channels[i];
        }
    }
};

#endif //IMAGE_H