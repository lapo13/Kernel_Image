#ifndef IMAGE_H
#define IMAGE_H
#include "Matrix.h"
#include "ImageHeader.h"
#include <vector>


template <typename T>
class Image { // da fare refactor con image interface e factory per creare immagini a 1 o 3 canali

private:
    ImageHeader header;
    std::vector<Matrix<T>*> channels;

public:
    Image(const T* imgBuffer, ImageHeader header): header(header) {
        channels.reserve(header.numChannels);
        if (header.numChannels == 1) {
            channels.push_back(new Matrix(imgBuffer, header.width , header.height));
        } else {
            T* rBuffer = new T[header.width * header.height];
            T* gBuffer = new T[header.width * header.height];
            T* bBuffer = new T[header.width * header.height];
            for (int i = 0; i < header.height*header.width; ++i) {
                rBuffer[i] = imgBuffer[i*header.numChannels];
                gBuffer[i] = imgBuffer[i*header.numChannels + 1];
                bBuffer[i] = imgBuffer[i*header.numChannels + 2];
            }
            channels.insert(channels.begin(), new Matrix(rBuffer, header.width, header.height));
            channels.insert(channels.begin() + 1, new Matrix(gBuffer, header.width, header.height));
            channels.insert(channels.begin() + 2, new Matrix(bBuffer, header.width, header.height));
            delete[] rBuffer;
            delete[] gBuffer;
            delete[] bBuffer;
        }
    }

    Matrix<T>& getChannel(int channel){
        return *channels[channel];
    }

    void setChannel(int channel, const Matrix<T>& data){
        channels[channel] = data;
    }

    void setPixel(int x, int y, std::vector<T> pixel){
        // Check bounds
        if (((x >= header.width )||(y >= header.height)) && (static_cast<int>(pixel.size()) != header.numChannels)) {
            throw std::out_of_range("Pixel coordinates out of bounds or pixel size mismatch");
        }

        for (int i = 0; i < header.numChannels; ++i) {
            channels.at(i)->operator()(x, y) = pixel[i];
        }
    }
    const std::vector<T> getPixel(int x, int y){
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