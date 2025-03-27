#include "utils/Convolution_Engine.h"
#include <stdexcept>
#include <cmath>
#include <limits>
#include <vector>

template<typename T>
void ConvolutionEngine<T>::convolve(Image<T>& image, const Matrix<T>& kernel) {
    if (!isValidKernel(kernel)) {
        throw std::invalid_argument("Kernel must be square with odd dimensions");
    }
    
    // Apply to each channel
    for (int c = 0; c < image.getNumChannels(); ++c) {
        Matrix<T>* channel = image.getChannel(c);
        applyKernel(*channel, kernel);
    }
}

template<typename T>
void ConvolutionEngine<T>::applyKernel(Matrix<T> channel, const Matrix<T>& kernel) {
    int kernelSize = kernel.getRows();
    int kernelRadius = kernelSize / 2;
    
    Matrix<T> output(channel.getRows(), channel.getCols());
    std::vector<std::vector<double>> tempOutput(
        channel.getRows(), 
        std::vector<double>(channel.getCols(), 0.0)
    );
    
    // First pass: compute convolution
    double minVal = std::numeric_limits<double>::max();
    double maxVal = std::numeric_limits<double>::lowest();  // Changed from min()
    
    // Copy border pixels
    for(int i = 0; i < channel.getRows(); ++i) {
        for(int j = 0; j < channel.getCols(); ++j) {
            output(i, j) = channel(i, j);
        }
    }
    
    // Process inner pixels
    for(int i = kernelRadius; i < channel.getRows() - kernelRadius; ++i) {
        for(int j = kernelRadius; j < channel.getCols() - kernelRadius; ++j) {
            double sum = 0.0;
            
            // Apply kernel
            for(int ki = -kernelRadius; ki <= kernelRadius; ++ki) {
                for(int kj = -kernelRadius; kj <= kernelRadius; ++kj) {
                    sum += static_cast<double>(channel(i + ki, j + kj)) * 
                          kernel(ki + kernelRadius, kj + kernelRadius);
                }
            }
            
            tempOutput[i][j] = sum;
            minVal = std::min(minVal, sum);
            maxVal = std::max(maxVal, sum);
        }
    }
    
    // Second pass: normalize and convert back to T
    if (maxVal > minVal) {  // Avoid division by zero
        normalizeChannel(output, minVal, maxVal);
    }
    
    channel = std::move(output);
}

// Example kernel creation method
template<typename T>
Matrix<T> ConvolutionEngine<T>::createGaussianKernel(int size, double sigma) {
    if (size % 2 == 0) {
        throw std::invalid_argument("Kernel size must be odd");
    }
    
    Matrix<T> kernel(size, size);
    double sum = 0.0;
    int radius = size / 2;
    
    // Compute Gaussian values
    for(int i = -radius; i <= radius; ++i) {
        for(int j = -radius; j <= radius; ++j) {
            double exponent = -(i*i + j*j)/(2*sigma*sigma);
            double value = std::exp(exponent)/(2*M_PI*sigma*sigma);
            kernel(i + radius, j + radius) = value;
            sum += value;
        }
    }
    
    // Normalize
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            kernel(i, j) /= sum;
        }
    }
    
    return kernel;
}

template<typename T>
void ConvolutionEngine<T>::normalizeChannel(Matrix<T>& channel, double minVal, double maxVal) {
    double range = maxVal - minVal;
    for(int i = 0; i < channel.getRows(); ++i) {
        for(int j = 0; j < channel.getCols(); ++j) {
            double normalized = (channel(i, j) - minVal) / range * 255.0;
            channel(i, j) = static_cast<T>(std::clamp(std::round(normalized), 0.0, 255.0));
        }
    }
}

template<typename T>
Matrix<T> ConvolutionEngine<T>::createSharpenKernel() {
    Matrix<T> kernel(3, 3);
    kernel(0, 0) = 0; kernel(0, 1) = -1; kernel(0, 2) = 0;
    kernel(1, 0) = -1; kernel(1, 1) = 5; kernel(1, 2) = -1;
    kernel(2, 0) = 0; kernel(2, 1) = -1; kernel(2, 2) = 0;
    return kernel;
}

template<typename T>
Matrix<T> ConvolutionEngine<T>::createEdgeDetectionKernel() {
    Matrix<T> kernel(3, 3);
    kernel(0, 0) = 0; kernel(0, 1) = 1; kernel(0, 2) = 0;
    kernel(1, 0) = 1; kernel(1, 1) = -4; kernel(1, 2) = 1;
    kernel(2, 0) = 0; kernel(2, 1) = 1; kernel(2, 2) = 0;
    return kernel;
}



// Add explicit instantiations
template class ConvolutionEngine<unsigned char>;