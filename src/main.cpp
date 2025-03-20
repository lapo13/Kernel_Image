#include "core/Image.h"
#include "utils/ImageIO.h"
#include <iostream>

int main() {
    Image* img = ImageIO::loadImage(R"(/Users/lapotinacci/Documents/images/sample_640×426.ppm)");

    if (img == NULL) {
        std::cerr << "Error: Could not load image" << std::endl;
        return 1;
    }

    std::cout<<(int)img->getChannel(0)->getMin()<<std::endl;
    std::cout<<(int)img->getChannel(0)->getMax()<<std::endl;
    std::cout<<img->getChannel(0)->getMean()<<std::endl;
    //img->getChannel(0)->normalize(0,200);

    std::cout<<(int)img->getChannel(0)->getMin()<<std::endl;
    std::cout<<(int)img->getChannel(0)->getMax()<<std::endl;
    std::cout<<img->getChannel(0)->getMean()<<std::endl;
    //img->getChannel(0)->threshold(128,0,255);

    ImageIO::saveImage(R"(/Users/lapotinacci/Documents/images/sample_640×426_out.ppm)", *img);

    delete img;
    return 0;
};