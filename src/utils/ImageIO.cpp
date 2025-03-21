#include "utils/ImageIO.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

Image* ImageIO::loadImage(const std::string& filename) {
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
    unsigned char* imgBuffer = new unsigned char[bufferSize];
    if(imgBuffer == nullptr) {
        std::cerr << "Error: Could not allocate memory for image buffer" << std::endl;
        file.close();
        exit(1);
    }

    
    file.read(reinterpret_cast<char*>(imgBuffer), bufferSize);
    if (file.gcount() != bufferSize) {
        std::cerr << "Error: Could not read complete image data. Expected " 
                  << bufferSize << " bytes but got " << file.gcount() << std::endl;
        delete[] imgBuffer;
        file.close();
        return nullptr;
    }

    file.close();
    
    Image* img = new Image(imgBuffer, width, height, NumChannels, magicNumber, maxVal);
    delete[] imgBuffer;  
    
    return img;
}

void ImageIO::saveImage(const std::string &filename, Image& image) {
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
    unsigned char* buffer = new unsigned char[bufferSize];
    size_t idx = 0;

    if(image.getMagicNumber() == "P5") {
        for (int i = 0; i < image.getHeight(); ++i) {
            for (int j = 0; j < image.getWidth(); ++j) {
                std::vector<unsigned char> pixel = image.getPixel(j, i);
                buffer[idx++] = pixel[0];
            }
        }
    } 
    
    else if(image.getMagicNumber() == "P6") {
        for (int i = 0; i < image.getHeight(); ++i) {
            for (int j = 0; j < image.getWidth(); ++j) {
                std::vector<unsigned char> pixel = image.getPixel(j, i);
                for (int k = 0; k < image.getNumChannels(); ++k) {
                    buffer[idx++] = pixel[k];
                }
            }
        }

    } else {
        std::cerr << "Error: Invalid magic number " << image.getMagicNumber() << std::endl;
        delete[] buffer;
        file.close();
        return;
    }

    // Write exactly bufferSize bytes
    file.write(reinterpret_cast<const char*>(buffer), bufferSize);
    delete[] buffer;
    file.close();
}