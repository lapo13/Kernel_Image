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
    
    Image* img = new Image(imgBuffer, width, NumChannels, height);
    
    return img;
}

void ImageIO::saveImage(const std::string& filename, const Image& image) {
    // Open file
};