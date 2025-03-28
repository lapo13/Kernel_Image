#include "core/Image.h"
#include "utils/ImageIO.h"
//#include "utils/Convolution_Engine.h"
#include <iostream>

int main() {
    Image<unsigned char>* img = ImageIO<unsigned char>::loadImage(R"(/Users/lapotinacci/Documents/images/sample_640×426.pgm)");

    if (img == NULL) {
        std::cerr << "Error: Could not load image" << std::endl;
        return 1;
    }

    /*Matrix<unsigned char> KS = ConvolutionEngine<unsigned char, unsigned char>::createSharpenKernel();
    Matrix<double> KG = ConvolutionEngine<unsigned char, double>::createGaussianKernel(3, 1.0);
    Matrix<unsigned char> KE = ConvolutionEngine<unsigned char, unsigned char>::createEdgeDetectionKernel();

    ConvolutionEngine <unsigned char, double>::convolve(*img, KG);*/


    //img->getChannel(0)->normalize(0,255);

    /*std::cout<<(int)img->getChannel(0)->getMin()<<std::endl;
    std::cout<<(int)img->getChannel(0)->getMax()<<std::endl;
    std::cout<<img->getChannel(0)->getMean()<<std::endl;
    img->getChannel(0)->threshold(128,0,255);*/

    ImageIO<unsigned char>::saveImage(R"(/Users/lapotinacci/Documents/images/sample_640×426_out.pgm)", *img);

    delete img;
    return 0;
};