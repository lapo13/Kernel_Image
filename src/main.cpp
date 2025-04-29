#include "core/Image.h"
#include "utils/ImageIO.h"
#include "utils/Convolution.h"
#include <iostream>

int main() {

    MultiChannelImage<unsigned char>* img = ImageIO::loadRGBImage<unsigned char>(R"(/Users/lapotinacci/Documents/Kernel_Image/images/input/sample_1280×853.ppm)");
    SingleChannelImage<unsigned char>* img_2 = ImageIO::loadGrayImage<unsigned char>(R"(/Users/lapotinacci/Documents/Kernel_Image/images/input/sample_1280×853.pgm)");
    std::cout<<"Image loaded"<<std::endl;

    Matrix<float> kernel = Convolution::createKernel<float>(Convolution::KernelType::Sharpen);
    Matrix<float> kernel_2 = Convolution::createKernel<float>(Convolution::KernelType::Emboss);
    Matrix<float> kernel_3 = Convolution::createKernel<float>(Convolution::KernelType::EdgeDetection);
    Matrix<float> kernel_4 = Convolution::createKernel<float>(Convolution::KernelType::Blur);

    std::cout<<"Kernel created"<<std::endl;

    Convolution::convolve(*img, kernel_4);
    Convolution::convolve(*img_2, kernel_4);
    std::cout<<"Convolution done"<<std::endl;

    ImageIO::saveImage(R"(/Users/lapotinacci/Documents/Kernel_Image/images/output/sample_1280×853_out.ppm)", *img);
    ImageIO::saveImage(R"(/Users/lapotinacci/Documents/Kernel_Image/images/output/sample_1280×853_out.pgm)", *img_2);
    std::cout<<"Image saved"<<std::endl;

    delete img;
    img = nullptr;
    delete img_2;
    img_2 = nullptr;
    return 0;
}