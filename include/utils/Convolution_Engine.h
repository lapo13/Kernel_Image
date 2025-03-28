#ifndef CONVOLUTION_ENGINE_H
#define CONVOLUTION_ENGINE_H

#include "core/Image.h"
#include "core/Matrix.h"
#include <vector>

template<typename ImageType, typename KernelType>
class ConvolutionEngine {
private:
    ConvolutionEngine() = delete;  // Static class only
    
    // Helper method to apply kernel to a single channel
    static void applyKernel(Channel<ImageType>& channel, const Matrix<KernelType>& kernel);

public:
    // Basic convolution operation
    static void convolve(Image<ImageType>& image, const Matrix<KernelType>& kernel);
    
    // Predefined kernels that return KernelType matrices
    //static Matrix<KernelType> createGaussianKernel(int size, double sigma);
    static Matrix<KernelType> createSharpenKernel();
    //static Matrix<KernelType> createSobelKernelX();
    //static Matrix<KernelType> createSobelKernelY();
};

#endif