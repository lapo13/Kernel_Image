#include "utils/ImageIO.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <typeinfo>

template<typename T>
Image<T>* ImageIO<T>::loadImage(const std::string& filename) {
    int width, height, maxVal, NumChannels;
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        std::cerr << "Error code: " << strerror(errno) << std::endl;
        exit(1);
    }
    printf("File opened\n");

    std::string magicNumber;
    file >> magicNumber;
    if (magicNumber != "P6" && magicNumber != "P5") {
        std::cerr << "Error: Invalid magic number " << magicNumber << std::endl;
        file.close();
        return nullptr;
    }

    NumChannels = magicNumber == "P6" ? 3 : 1;
    file >> width >> height >> maxVal;

    
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    
    const size_t bufferSize = width * height * NumChannels;
    T* imgBuffer = new T[bufferSize];
    
    if(imgBuffer == nullptr) {
        std::cerr << "Error: Could not allocate memory for buffer of type: " 
                  << typeid(T).name() << std::endl;
        file.close();
        exit(1);
    }

    // Read file data into buffer
    file.read(reinterpret_cast<char*>(imgBuffer), bufferSize * sizeof(T));
    
    if (file.gcount() != (long)(bufferSize * sizeof(T))) {
        std::cerr << "Error: Could not read complete image data of type: " 
                  << typeid(T).name() << ". Expected " 
                  << bufferSize * sizeof(T) << " bytes but got " 
                  << file.gcount() << std::endl;
        delete[] imgBuffer;
        file.close();
        return nullptr;
    }

    file.close();
    
    // Create image with proper type
    Image<T>* img = new Image<T>(imgBuffer, width, height, NumChannels, magicNumber, maxVal);
    delete[] imgBuffer;  
    
    return img;
}

template<typename T>
void ImageIO<T>::saveImage(const std::string &filename, Image<T>& image) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        std::cerr << "Error code: " << strerror(errno) << std::endl;
        return;
    }

    // Write header
    file << image.getMagicNumber() << "\n"; 
    file << image.getWidth() << " " << image.getHeight() << "\n";
    file << image.getMax() << "\n";

    // allocate buffer
    const size_t bufferSize = image.getWidth() * image.getHeight() * image.getNumChannels();
    T* buffer = new T[bufferSize];  // Changed to T* from unsigned char*

    if(image.getMagicNumber() == "P5") {
        size_t idx = 0;
        if (image.getNumChannels() != 1) {
            std::cerr << "Error: P5 format requires 1 channel" << std::endl;
            delete[] buffer;
            file.close();
            return;
        }
        for (int y = 0; y < image.getHeight(); ++y) {
            for (int x = 0; x < image.getWidth(); ++x) {
                std::vector<T> pixel = image.getPixel(x, y);  // Changed to vector<T>
                if (pixel.size() != 1) {
                    std::cerr << "Error: Invalid pixel data at (" << x << "," << y << ")" << std::endl;
                    delete[] buffer;
                    file.close();
                    return;
                }
                buffer[idx++] = pixel[0];
            }
        }
    } 
    else if(image.getMagicNumber() == "P6") {
        size_t idx = 0;
        if (image.getNumChannels() != 3) {
            std::cerr << "Error: P6 format requires 3 channels" << std::endl;
            delete[] buffer;
            file.close();
            return;
        }
        for (int y = 0; y < image.getHeight(); ++y) {
            for (int x = 0; x < image.getWidth(); ++x) {
                std::vector<T> pixel = image.getPixel(x, y);  // Changed to vector<T>
                if (pixel.size() != 3) {
                    std::cerr << "Error: Invalid pixel data at (" << x << "," << y << ")" << std::endl;
                    delete[] buffer;
                    file.close();
                    return;
                }
                buffer[idx++] = pixel[0];
                buffer[idx++] = pixel[1];
                buffer[idx++] = pixel[2];
            }
        }
    } else {
        std::cerr << "Error: Invalid magic number " << image.getMagicNumber() << std::endl;
        delete[] buffer;
        file.close();
        return;
    }

    // Write exactly bufferSize bytes
    file.write(reinterpret_cast<const char*>(buffer), bufferSize * sizeof(T));  // Added sizeof(T)
    delete[] buffer;
    file.close();
}

// Explicit instantiation of template class
template class ImageIO<unsigned char>;