#ifndef IMAGE_H
#define IMAGE_H
#include "Matrix.h"
#include <vector>
#include <string>
#include <iostream>

template <typename T>
class Image {

protected:

    class Channel : public Matrix<T> {
    private:
        unsigned char min, max;   

    public:
        Channel(T *imgBuffer, int width, int height, int channel_num);
        Channel(T *imgBuffer, int width, int height);

        T getMin() const;
        T getMax() const;

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
    T max;
    std::string MagicNumber;
    std::vector<Channel*> channels;

public:
    Image(T* imgBuffer, int width, int height, int NumChannels, std::string magicnumber, T max);


    Channel* getChannel(int channel) {
        return channels[channel];
    }
    const Channel* getChannel(T channel) const {
        return channels[channel];
    }

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