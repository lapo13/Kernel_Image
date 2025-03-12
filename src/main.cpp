#include "core/Image.h"
#include "utils/ImageIO.h"
#include <iostream>

int main() {
    Image* img = ImageIO::loadImage("/Users/lapotinacci/Downloads/sample_640×426.ppm");
    if (img == nullptr) {
        std::cerr << "Error: Could not load image" << std::endl;
        return 1;
    }
     std::cout<<img->getChannel(0)->getMin()<<std::endl;
     std::cout<<img->getChannel(0)->getMax()<<std::endl;
     std::cout<<img->getChannel(0)->getMean()<<std::endl;
     img->getChannel(0)->normalize(0,255);
     std::cout<<img->getChannel(0)->getMin()<<std::endl;
     std::cout<<img->getChannel(0)->getMax()<<std::endl;
     std::cout<<img->getChannel(0)->getMean()<<std::endl;
     img->getChannel(0)->threshold(128,0,255);

     return 0;
};