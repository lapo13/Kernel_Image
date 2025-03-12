#ifndef IMAGE_H
#define IMAGE_H
#include "Matrix.h"

class Image {

protected:
    class Channel : public Matrix {
    private:
        unsigned char min, max;

    public:
        Channel(unsigned char *imgBuffer, int width, int height);

        unsigned char getMin() const;
        unsigned char getMax() const;
        void setMin(unsigned char min) {
            this->min = min;
        }
        void setMax(unsigned char max) {
            this->max = max;
        }

        double getMean() const;

        void normalize(unsigned char newMin, unsigned char newMax);
        void threshold(unsigned char threshold, unsigned char lowValue, unsigned char highValue);

        ~Channel();
    };

private:
    int width, height, NumChannels;
    std::vector<Channel*> channels;

public:
    Image(unsigned char* imgBuffer, int width, int NumChannels, int height) : width(width), height(height), NumChannels(NumChannels) {
        for (int i = 0; i < NumChannels; ++i) {
            channels.push_back(new Channel(imgBuffer, width, height));
        }
    }

    Channel* getChannel(int channel) {
        return channels[channel];
    }

    const Channel* getChannel(unsigned int channel) const {
        return channels[channel];
    }

    unsigned char* getPixel(unsigned int x, unsigned int y);

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

    void resize(unsigned int width, unsigned int height);

    ~Image() {
        for (int i = 0; i < NumChannels; ++i) {
            delete channels[i];
        }
    }
};

#endif //IMAGE_H