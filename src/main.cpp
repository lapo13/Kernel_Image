#include "core/Image.h"
#include "utils/ImageIO.h"
#include "utils/Convolution_Engine.h"
#include <iostream>

int main() {
    Image<unsigned char>* img = ImageIO<unsigned char>::loadImage(R"(/Users/lapotinacci/Documents/images/sample_5184×3456.ppm)");

    if (img == NULL) {
        std::cerr << "Error: Could not load image" << std::endl;
        return 1;
    }

    Matrix<unsigned char> KS = ConvolutionEngine<unsigned char, unsigned char>::createSharpenKernel();
    Matrix<unsigned char> KE = ConvolutionEngine<unsigned char, unsigned char>::createEmbossKernel();

    ConvolutionEngine <unsigned char, unsigned char>::convolve(*img, KE);

    //img->getChannel(0)->normalize(0,255);

    /*std::cout<<(int)img->getChannel(0)->getMin()<<std::endl;
    std::cout<<(int)img->getChannel(0)->getMax()<<std::endl;
    std::cout<<img->getChannel(0)->getMean()<<std::endl;
    img->getChannel(0)->threshold(128,0,255);*/

    ImageIO<unsigned char>::saveImage(R"(/Users/lapotinacci/Documents/images/sample_5184×3456_out.ppm)", *img);

    delete img;
    return 0;
};