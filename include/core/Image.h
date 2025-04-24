#ifndef IMAGE_H
#define IMAGE_H
#include "Matrix.h"
#include "ImageHeader.h"
#include <vector>

template <typename T>
class Image {
public:
    virtual ~Image() = default;
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
class imageGrayScale : public Image<T> {

private:
    ImageHeader header;
    Matrix<T>* channel;

public:
    imageGrayScale(const T* imgBuffer, ImageHeader header): header(header) {
        if (header.numChannels != 1) {
            throw std::invalid_argument("Image must have 1 channel for grayscale");
        }
        channel = new Matrix<T>(header.height, header.width);
        size_t idx = 0;
        for (int y = 0; y < header.height; ++y) {
            for (int x = 0; x < header.width; ++x) {
                (*channel)(x, y) = imgBuffer[idx++];
            }
        }
    }

    
    Matrix<T>& getChannel(int chNum) override{
        if (chNum != 0) {
            throw std::invalid_argument("Invalid channel index for grayscale image in getChannel");
        }
        return *channel;
    }

    void setChannel(int chNum, const Matrix<T>& data) override{
        if (chNum != 1) {
            throw std::invalid_argument("Invalid channel index for grayscale image in setChannel");
        }
        *channel = data;
    }

    void setPixel(int x, int y, std::vector<T> pixel) override{
        // Check bounds
        if (((x >= header.width )||(y >= header.height)) && (static_cast<int>(pixel.size()) != header.numChannels)) {
            throw std::out_of_range("Pixel coordinates out of bounds or pixel size mismatch");
        }
        channel->operator()(x, y) = pixel[0];
    }
    const std::vector<T> getPixel(int x, int y) override{
        // Check bounds
        if (x >= header.width || y >= header.height) {
            throw std::out_of_range("Pixel coordinates out of bounds");
        }
        std::vector<T> pixel(header.numChannels);
        pixel[0] = channel->operator()(x, y);
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

    ~imageGrayScale(){
        delete channel;
    }
};

template <typename T>
class imageRGB : public Image<T> {
private:
    ImageHeader header;
    std::vector<Matrix<T>*> channels;
public:
    imageRGB(const T* imgBuffer, ImageHeader header): header(header) {
        if (header.numChannels != 3) {
            throw std::invalid_argument("Image must have 3 channels for RGB");
        }
        for (int i = 0; i < header.numChannels; ++i) {
            channels.push_back(new Matrix<T>(header.height, header.width));
        }
        size_t idx = 0;
        for (int y = 0; y < header.height; ++y) {
            for (int x = 0; x < header.width; ++x) {
                for (int c = 0; c < header.numChannels; ++c) {
                    if(static_cast<int>(idx) >= header.width * header.height * header.numChannels) {
                        throw std::out_of_range("Index out of bounds");
                    }
                    (*channels[c])(x, y) = imgBuffer[idx++];
                }
            }
        }
    }

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
        if ((x >= header.width || y >= header.height) && (static_cast<int>(pixel.size()) != header.numChannels)) {
            throw std::out_of_range("Pixel coordinates out of bounds or pixel size mismatch");
        }

        for (int i = 0; i < header.numChannels; ++i) {
            channels.at(i)->operator()(x, y) = pixel[i];
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

    ~imageRGB(){
        for(auto channel : channels) {
            delete channel;
        }
    }
};

template <typename T>
class imageFactory {
public:
    static Image<T>* createImage(const T* imgBuffer, ImageHeader header) {
        if (header.numChannels == 1) {
            return new imageGrayScale<T>(imgBuffer, header);
        } else if (header.numChannels == 3) {
            return new imageRGB<T>(imgBuffer, header);
        } else {
            throw std::invalid_argument("Unsupported number of channels");
        }
    }

    ~imageFactory() = default;
};

#endif //IMAGE_H