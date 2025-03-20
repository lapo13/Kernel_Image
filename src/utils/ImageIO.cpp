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

    unsigned char* imgBuffer = new unsigned char[width * height * NumChannels];
    if(imgBuffer == nullptr) {
        std::cerr << "Error: Could not allocate memory for image buffer" << std::endl;
        file.close();
        exit(1);
    }

    file.read((char*)imgBuffer, width * height * NumChannels);
    file.close(); 
    
    Image* img = new Image(imgBuffer, width, NumChannels, height, magicNumber, maxVal);
    
    return img;
}

void ImageIO::saveImage(const std::string &filename, Image& image) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        std::cerr << "Error code: " << strerror(errno) << std::endl;
        return;
    }

    // Write PPM header - Note the space after each newline
    file << image.getMagicNumber() << "\n"; 
    file << image.getWidth() << " " << image.getHeight() << "\n";
    file << image.getMax() << "\n";

    // Buffer for pixel data
    unsigned char* buffer = new unsigned char[image.getWidth() * image.getHeight() * image.getNumChannels()];
    int idx = 0;

    // Fill buffer with pixel data
    for(int y = 0; y < image.getHeight(); y++) {
        for(int x = 0; x < image.getWidth(); x++) {
            unsigned char* pixel = image.getPixel(x, y);
            for(int c = 0; c < image.getNumChannels(); c++) {
                buffer[idx++] = pixel[c];
            }
            delete[] pixel;
        }
    }

    // Write entire buffer at once
    file.write(reinterpret_cast<const char*>(buffer), idx);
    
    delete[] buffer;
    file.close();
}