#include "utils/Convolution_Engine.h"
#include <iostream>
#include <thread>

template<typename ImageType, typename KernelType>
void ConvolutionEngine<ImageType, KernelType>::convolve(Image<ImageType>& image, const Matrix<KernelType>& kernel) {
    int numChannels = image.getNumChannels();
    std::vector<std::thread> threads;
    threads.resize(numChannels);

    for (int c = 0; c < numChannels; ++c) {
        threads[c] = std::thread([&image, &kernel, c]() {
            applyKernel(image.getChannel(c), kernel);
        });
    }

    for (int i = 0; i < numChannels; ++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
}

template<typename ImageType, typename KernelType>
void ConvolutionEngine<ImageType, KernelType>::applyKernel(Channel<ImageType>& channel, const Matrix<KernelType>& kernel) {
    int kernelSize = kernel.getRows();
    int kernelRadius = kernelSize / 2;

    int chRows = channel.getRows();
    int chCols = channel.getCols();

    // Create buffer for output
    KernelType* outputBuffer = new KernelType[chRows * chCols];
    for (int i = 0; i < chRows * chCols; ++i) {
        outputBuffer[i] = 0;
    }

    // Initialize min and max values for normalization
    KernelType minVal = 0.0;
    KernelType maxVal = 0.0;

    // Process inner pixels - using row-major order
    for(int row = kernelRadius; row < chRows - kernelRadius; ++row) {
        for(int col = kernelRadius; col < chCols - kernelRadius; ++col) {

            // Apply kernel - match image orientation
            for(int krow = -kernelRadius; krow <= kernelRadius; ++krow) {
                for(int kcol = -kernelRadius; kcol <= kernelRadius; ++kcol) {
                    std::cout << (static_cast<KernelType>(channel( col + kcol, row + krow))) << " * "
                        << (kernel( kcol + kernelRadius, krow + kernelRadius)) << std::endl;
                    outputBuffer[row *chCols + col] += 
                        (static_cast<KernelType>(channel( col + kcol, row + krow))) *
                        (kernel( kcol + kernelRadius, krow + kernelRadius));
                    
                }
            }
            std::cout << "outputBuffer[" << row << "][" << col << "] = " 
                        << outputBuffer[row *chCols + col] << std::endl;
            std::cout << "-------------------------------"<< std::endl;
            minVal = (outputBuffer[row *chCols + col] < minVal) ? outputBuffer[row *chCols + col] : minVal;
            maxVal = (outputBuffer[row *chCols + col] > maxVal) ? outputBuffer[row *chCols + col] : maxVal;
        }
    }

    // Process border pixels
    for(int row = 0; row < chRows; ++row) {
        for(int col = 0; col < chCols; ++col) {
            if (row < kernelRadius || row >= chRows - kernelRadius || col < kernelRadius || col >= chCols - kernelRadius) {
                outputBuffer[row *chCols + col] = 0; // Set border pixels to zero
            }
        }
    }

    // Normalize the results
    normalizeResults(outputBuffer, minVal, maxVal, channel, kernelRadius);

    // Update the channel with the new values
    for(int row = kernelRadius; row < chRows - kernelRadius; ++row) {
        for(int col = kernelRadius; col < chCols - kernelRadius; ++col) {
            channel(col, row) = static_cast<ImageType>(outputBuffer[row * chCols + col]);
        }
    }

    // Clean up
    delete[] outputBuffer;
    outputBuffer = nullptr;

}

template<typename ImageType, typename KernelType>
void ConvolutionEngine<ImageType, KernelType>::normalizeResults(KernelType* outputBuffer, KernelType minVal, KernelType maxVal, const Channel<ImageType>& channel, int kernelRadius) {
    double range = static_cast<double>(maxVal - minVal);
    if (range == 0) {
        range = 1; // Avoid division by zero
    }
    int chCols = channel.getCols();
    int chRows = channel.getRows();
    double max = static_cast<double>(channel.getMax()); 

    // Normalize the output buffer
    for (int row = kernelRadius; row < chRows - kernelRadius; ++row) {
        for (int col = kernelRadius; col < chCols - kernelRadius; ++col) {
            double normalizedValue = ((static_cast<double>(outputBuffer[row * chCols + col] - minVal)) / range) * max;
            outputBuffer[row * chCols + col] = static_cast<KernelType>(normalizedValue);
        }
    }
}

template<typename ImageType, typename KernelType>
bool ConvolutionEngine<ImageType, KernelType>::isValid(Matrix<KernelType> kernel){
    int isOdd = kernel.getCols()%2;
    if (isOdd == 1){
        return true;
    }else {
        return false;
    }
}

//Kernel definitions funcions 

template<typename ImageType, typename KernelType>
Matrix<KernelType> ConvolutionEngine<ImageType, KernelType>::createSharpenKernel() {
    Matrix<KernelType> kernel(3, 3);
    kernel(0, 0) = -1; kernel(0, 1) = -1; kernel(0, 2) = -1;
    kernel(1, 0) = -1; kernel(1, 1) = 9; kernel(1, 2) = -1;
    kernel(2, 0) = -1; kernel(2, 1) = -1; kernel(2, 2) = -1;
    if(isValid(kernel)){
        return kernel;
    }else {
        throw std::runtime_error("Invalid kernel dimensions: kernel size must be odd");
    }
} 

template<typename ImageType, typename KernelType>
Matrix<KernelType> ConvolutionEngine<ImageType, KernelType>::createEmbossKernel() {
    Matrix<KernelType> kernel(3, 3);
    kernel(0, 0) = -2; kernel(0, 1) = -1; kernel(0, 2) = 0;
    kernel(1, 0) = -1; kernel(1, 1) = 1; kernel(1, 2) = 1;
    kernel(2, 0) = 0; kernel(2, 1) = 1; kernel(2, 2) = 2;
    if(isValid(kernel)){
        return kernel;
    }else {
        throw std::runtime_error("Invalid kernel dimensions: kernel size must be odd");
    }
}

template<typename ImageType, typename KernelType>
Matrix<KernelType> ConvolutionEngine<ImageType, KernelType>::createBlurringKernel(){
    Matrix<KernelType> kernel(3, 3);
    kernel(0, 0) = (1.0f / 9.0f); kernel(0, 1) = (1.0f / 9.0f); kernel(0, 2) = (1.0f / 9.0f);
    kernel(1, 0) = (1.0f / 9.0f); kernel(1, 1) = (1.0f / 9.0f); kernel(1, 2) = (1.0f / 9.0f);
    kernel(2, 0) = (1.0f / 9.0f); kernel(2, 1) = (1.0f / 9.0f); kernel(2, 2) = (1.0f / 9.0f);

    if(isValid(kernel)){
        return kernel;
    }else {
        throw std::runtime_error("Invalid kernel dimensions: kernel size must be odd");
    }
}

template<typename ImageType, typename KernelType>
Matrix<KernelType> ConvolutionEngine<ImageType, KernelType>::createEdgeDetectionKernel(){
    Matrix<KernelType> kernel(3, 3);
    kernel(0, 0) = 0; kernel(0, 1) = 1; kernel(0, 2) = 0;
    kernel(1, 0) = 1; kernel(1, 1) = -4; kernel(1, 2) = 1;
    kernel(2, 0) = 0; kernel(2, 1) = 1; kernel(2, 2) = 0;

    if(isValid(kernel)){
        return kernel;
    }else {
        throw std::runtime_error("Invalid kernel dimensions: kernel size must be odd");
    }
}
// Add explicit instantiations for common type combinations
template class ConvolutionEngine<unsigned char, double>;
template class ConvolutionEngine<unsigned char, float>;
template class ConvolutionEngine<unsigned char, int>;
template class ConvolutionEngine<int, int>;
//template class ConvolutionEngine<float, float>;


