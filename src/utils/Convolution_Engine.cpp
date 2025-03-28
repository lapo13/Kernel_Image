#include "utils/Convolution_Engine.h"
#include <cmath>
#include <algorithm>
#include <utility> 

template<typename ImageType, typename KernelType>
void ConvolutionEngine<ImageType, KernelType>::convolve(Image<ImageType>& image, const Matrix<KernelType>& kernel) {
    for (int c = 0; c < image.getNumChannels(); ++c) {
        applyKernel(image.getChannel(c), kernel);
    }
}

template<typename ImageType, typename KernelType>
void ConvolutionEngine<ImageType, KernelType>::applyKernel(Channel<ImageType>& channel, const Matrix<KernelType>& kernel) {
    int kernelSize = kernel.getRows();
    int kernelRadius = kernelSize / 2;

    ImageType* kernelData = new ImageType[channel.getCols() * channel.getRows()];
    Channel<ImageType> output(kernelData, channel.getCols(), channel.getRows());

    // Initialize min and max values for normalization
    double minVal = 0.0;
    double maxVal = 0.0;
    
    // Process inner pixels - using row-major order
    for(int row = kernelRadius; row < channel.getRows() - kernelRadius; ++row) {
        for(int col = kernelRadius; col < channel.getCols() - kernelRadius; ++col) {
            double sum = 0.0;
            
            // Apply kernel - match image orientation
            for(int krow = -kernelRadius; krow <= kernelRadius; ++krow) {
                for(int kcol = -kernelRadius; kcol <= kernelRadius; ++kcol) {
                    sum += static_cast<double>(channel(row + krow, col + kcol)) * 
                          static_cast<double>(kernel(krow + kernelRadius, kcol + kernelRadius));
                    minVal = (sum < minVal) ? sum : minVal;
                    maxVal = (sum > maxVal) ? sum : maxVal;
                }
            }
            
            // Store result in output using same row-major order
            output(col, row) = static_cast<ImageType>(
                std::clamp(std::round(sum), 0.0, 255.0)
            );
        }
    }
    
    channel = std::move(output);
}

template<typename ImageType, typename KernelType>
Matrix<KernelType> ConvolutionEngine<ImageType, KernelType>::createSharpenKernel() {
    Matrix<KernelType> kernel(3, 3);
    kernel(0, 0) = 0; kernel(0, 1) = -1; kernel(0, 2) = 0;
    kernel(1, 0) = -1; kernel(1, 1) = 5; kernel(1, 2) = -1;
    kernel(2, 0) = 0; kernel(2, 1) = -1; kernel(2, 2) = 0;
    return kernel;
}

// Add explicit instantiations for common type combinations
template class ConvolutionEngine<unsigned char, double>;
//template class ConvolutionEngine<unsigned char, float>;
template class ConvolutionEngine<unsigned char, unsigned char>;
//template class ConvolutionEngine<float, float>;


