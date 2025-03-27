#ifndef CONVOLUTION_ENGINE_H
#define CONVOLUTION_ENGINE_H

#include <vector> 
#include "core/Image.h"
#include "core/Matrix.h"

template <typename T>
class ConvolutionEngine {
private:
    ConvolutionEngine() = delete;
             
public:
    // Basic convolution operation
    static void convolve(Image<T>& image, const Matrix<T>& kernel);

    // Create some basic kernels
    static Matrix<T> createGaussianKernel(int size, double sigma);
    static Matrix<T> createSharpenKernel();
    static Matrix<T> createEdgeDetectionKernel();
    
private:
    // Helper method to apply kernel to a single channel
    static void applyKernel(Matrix<T> channel, const Matrix<T>& kernel);
    static void normalizeChannel(Matrix<T>& channel, double minVal, double maxVal); 
    
    // Helper to validate kernel dimensions
    static bool isValidKernel(const Matrix<T>& kernel) {
        return (kernel.getRows() == kernel.getCols()) && 
               (kernel.getRows() % 2 == 1);  // Must be odd-sized
    }
};

#endif // CONVOLUTION_ENGINE_H