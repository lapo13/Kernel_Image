#include "core/Image.h"
#include "utils/ImageIO.h"
#include "utils/Convolution_Engine.h"
#include <iostream>

int main() {
    Image<unsigned char>* img = ImageIO<unsigned char>::loadImage(R"(/Users/lapotinacci/Documents/Kernel_Image/images/input/sample_1280×853.ppm)");
    Image<unsigned char>* img_2= ImageIO<unsigned char>::loadImage(R"(/Users/lapotinacci/Documents/Kernel_Image/images/input/sample_1280×853.pgm)");

    if (img == NULL) {
        std::cerr << "Error: Could not load image" << std::endl;
        return 1;
    }

    Matrix<int> KS = ConvolutionEngine<unsigned char, int>::createSharpenKernel();
    Matrix<int> KE = ConvolutionEngine<unsigned char, int>::createEmbossKernel();
    Matrix<float> KB = ConvolutionEngine<unsigned char, float>::createBlurringKernel();
    Matrix<int> KE2 = ConvolutionEngine<unsigned char, int>::createEdgeDetectionKernel();

    ConvolutionEngine <unsigned char, float>::convolve(*img, KB);
    ConvolutionEngine <unsigned char, float>::convolve(*img_2, KB);

    //img->getChannel(0)->normalize(0,255);

    /*std::cout<<(int)img->getChannel(0)->getMin()<<std::endl;
    std::cout<<(int)img->getChannel(0)->getMax()<<std::endl;
    std::cout<<img->getChannel(0)->getMean()<<std::endl;
    img->getChannel(0)->threshold(128,0,255);*/

    ImageIO<unsigned char>::saveImage(R"(/Users/lapotinacci/Documents/Kernel_Image/images/output/sample_1280×853_out.ppm)", *img);
    ImageIO<unsigned char>::saveImage(R"(/Users/lapotinacci/Documents/Kernel_Image/images/output/sample_1280×853_out.pgm)", *img_2);


    delete img;
    return 0;
};