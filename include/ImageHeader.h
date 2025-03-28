#ifndef IMAGE_HEADER_H
#define IMAGE_HEADER_H

#include <string>

struct ImageHeader {
    int width;
    int height;
    int numChannels;
    int maxVal;
    std::string magicNumber;
    
    ImageHeader() = default;
    
    ImageHeader(int w, int h, int nc, int max, std::string magic) 
        : width(w), height(h), numChannels(nc), maxVal(max), magicNumber(magic) {}
};

#endif //IMAGE_HEADER_H