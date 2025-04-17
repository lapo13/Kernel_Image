#ifndef CONVOLUTION_ENGINE_H
#define CONVOLUTION_ENGINE_H

#include "core/Image.h"
#include "core/Matrix.h"
#include <vector>

template<typename ImageType, typename KernelType>
class ConvolutionEngine { //usare namespace ConvolutionEngine
protected:
    ConvolutionEngine() = delete;  // Static class only
    
    // Helper method to apply kernel to a single channel
    static void applyKernel(Channel<ImageType>& channel, const Matrix<KernelType>& kernel, int kernelRadius, KernelType* outputBuffer);
    // Helper to normalize results
    static void normalizeResults(KernelType* outputBuffer, const Channel<ImageType>& channel, int kernelRadius);
    //helper fo checking kernel validity
    static bool isValid(Matrix<KernelType> kernel);

public:
    // Basic convolution operation
    static void convolve(Image<ImageType>& image, const Matrix<KernelType>& kernel);
    //usare un factory method per i kernel
    
    // Predefined kernels that return KernelType matrices
    static Matrix<KernelType> createGaussianKernel(int size, double sigma);
    static Matrix<KernelType> createSharpenKernel(); 
    static Matrix<KernelType> createEmbossKernel();
    static Matrix<KernelType> createBlurringKernel();
    static Matrix<KernelType> createEdgeDetectionKernel();
    
};

#endif // CONVOLUTION_ENGINE_H