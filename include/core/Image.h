#ifndef IMAGE_H
#define IMAGE_H
#include "Matrix.h"
#include "ImageHeader.h"
#include <vector>
template <typename T>
class MultiChannelImage{
public:
    virtual ~MultiChannelImage() = default;
    virtual Matrix<T>& getChannel(int chNum) = 0;
    virtual void setChannel(int chNum, const Matrix<T>& data) = 0;
    virtual void setPixel(int x, int y, std::vector<T> pixel) = 0;
    virtual const std::vector<T> getPixel(int x, int y) = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual int getNumChannels() const = 0;
    virtual const ImageHeader& getHeader() const = 0;
};

template <typename T>
class SingleChannelImage{
public:
    virtual ~SingleChannelImage() = default;
    virtual Matrix<T>& getChannel() = 0;
    virtual void setChannel(const Matrix<T>& data) = 0;
    virtual void setPixel(int x, int y, T pixel) = 0;
    virtual const T getPixel(int x, int y) = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual int getNumChannels() const = 0;
    virtual const ImageHeader& getHeader() const = 0;
};

template <typename T>
class GrayscaleImage : public SingleChannelImage<T> {
private:
    ImageHeader header;
    Matrix<T>* channel;

public:
    GrayscaleImage(Matrix<T>* ch, ImageHeader header): header(header), channel(ch) {};
    
    Matrix<T>& getChannel() override{
        return *channel;
    }
    void setChannel(const Matrix<T>& data) override{
        *channel = data;
    }

    void setPixel(int x, int y, T pixel) override{
        // Check bounds
        if (((x >= header.width )||(y >= header.height))) {
            throw std::out_of_range("Pixel coordinates out of bounds or pixel size mismatch");
        }
        channel->operator()(x, y) = pixel;
    }
    const T getPixel(int x, int y) override{
        // Check bounds
        if (x >= header.width || y >= header.height) {
            throw std::out_of_range("Pixel coordinates out of bounds");
        }
        return channel->operator()(x, y);
    }

    int getWidth() const override{
        return this->header.width;
    }
    int getHeight() const override{
        return this->header.height;
    }
    int getNumChannels() const override{
        return this->header.numChannels;
    }
    const ImageHeader& getHeader() const override{
        return this->header;
    }

    ~GrayscaleImage(){
        delete channel;
    }
};

template <typename T>
class ImageRGB : public MultiChannelImage<T> {
private:
    ImageHeader header;
    std::vector<Matrix<T>*> channels;
public:
    ImageRGB(std::vector<Matrix<T>*> ch, ImageHeader header): header(header), channels(ch) {}
        
    Matrix<T>& getChannel(int chNum) override{
        return *channels[chNum];
    }

    void setChannel(int chNum, const Matrix<T>& data) override{
        if(chNum < 0 || chNum >= header.numChannels) {
            throw std::out_of_range("Channel index out of bounds");
        }
        *channels[chNum] = data;
    }

    void setPixel(int x, int y, std::vector<T> pixel) override{
        // Check bounds
        if ((x >= header.width || y >= header.height) || (static_cast<int>(pixel.size()) != header.numChannels)) {
            throw std::out_of_range("Pixel coordinates out of bounds or pixel size mismatch");
        }

        for (int i = 0; i < header.numChannels; ++i) {
            channels.at(i)->operator()(x, y) = pixel.at(i);
        }
    }

    const std::vector<T> getPixel(int x, int y) override{
        // Check bounds
        if (x >= header.width || y >= header.height) {
            throw std::out_of_range("Pixel coordinates out of bounds");
        }

        std::vector<T> pixel(header.numChannels);
        for (int i = 0; i < header.numChannels; ++i) {
            pixel[i] = channels.at(i)->operator()(x, y);
        }
        return pixel;
    }

    int getWidth() const override{
        return this->header.width;
    }
    int getHeight() const override{
        return this->header.height;
    }
    int getNumChannels() const override{
        return this->header.numChannels;
    }

    const ImageHeader& getHeader() const override{
        return this->header;
    }

    ~ImageRGB(){
        for(Matrix<T>* channel : channels) {
            delete channel;
        }
    }
};

#endif //IMAGE_H