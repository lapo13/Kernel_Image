#ifndef CONVOLUTION_ENGINE_H
#define CONVOLUTION_ENGINE_H

#include "core/Image.h"
#include <vector>
#include <thread>

namespace Convolution {

    enum class KernelType {
        Sharpen,
        Emboss,
        Blur,
        EdgeDetection
    };

    namespace detail {
        // Helper function to check if the kernel is valid
        template<typename KernelType>
        bool isValid(const Matrix<KernelType>& kernel) {
            return kernel.getCols() % 2 == 1;
        }

        // Helper method to apply kernel to a single channel
        template<typename ImageType, typename KernelType>
        void applyKernel(Matrix<ImageType>& channel, const Matrix<KernelType>& kernel, int kernelRadius, KernelType* outputBuffer) {
            int chRows = channel.getRows();
            int chCols = channel.getCols();

            // Process inner pixels - using row-major order
            for(int row = kernelRadius; row < chRows - kernelRadius; ++row) {
                for(int col = kernelRadius; col < chCols - kernelRadius; ++col) {

                    // Apply kernel - match image orientation
                    for(int krow = -kernelRadius; krow <= kernelRadius; ++krow) {
                        for(int kcol = -kernelRadius; kcol <= kernelRadius; ++kcol) {
                            outputBuffer[row *chCols + col] += 
                                (static_cast<KernelType>(channel( col + kcol, row + krow))) *
                                (kernel( kcol + kernelRadius, krow + kernelRadius));
                            
                        }
                    }
                }
            }
        }

        // helper method to normalize the results of the output buffer after applying the kernel
        template<typename ImageType, typename KernelType>
        void normalizeResults(KernelType* outputBuffer, const Matrix<ImageType>& channel, int kernelRadius) {
            int chCols = channel.getCols();
            int chRows = channel.getRows();
            double max = static_cast<double>(channel.getMax()); 
            
            KernelType minVal = outputBuffer[0];
            KernelType maxVal = outputBuffer[0];
            // Find min and max values in the output buffer
            for(int row = kernelRadius; row < chRows - kernelRadius; ++row) {
                for(int col = kernelRadius; col < chCols - kernelRadius; ++col) {
                    minVal = outputBuffer[row * chCols + col] < minVal ? outputBuffer[row * chCols + col] : minVal;
                    maxVal = outputBuffer[row * chCols + col] > maxVal ? outputBuffer[row * chCols + col] : maxVal;
                }
            }
            // Calculate the range
            double range = static_cast<double>(maxVal - minVal);
            if (range == 0) {
                range = 1; // Avoid division by zero
            }

            // Normalize the output buffer
            for (int row = kernelRadius; row < chRows - kernelRadius; ++row) {
                for (int col = kernelRadius; col < chCols - kernelRadius; ++col) {
                    double normalizedValue = ((static_cast<double>(outputBuffer[row * chCols + col] - minVal)) / range) * max;
                    outputBuffer[row * chCols + col] = static_cast<KernelType>(normalizedValue);
                }
            }
        }

        // Predefined kernels
        template<typename KernelType>
        Matrix<KernelType> createSharpenKernel() {
            Matrix<KernelType> kernel(3, 3);
            kernel(0, 0) = -1; kernel(0, 1) = -1; kernel(0, 2) = -1;
            kernel(1, 0) = -1; kernel(1, 1) = 9; kernel(1, 2) = -1;
            kernel(2, 0) = -1; kernel(2, 1) = -1; kernel(2, 2) = -1;
            if(detail::isValid(kernel)){
                return kernel;
            }else {
                throw std::runtime_error("Invalid kernel dimensions: kernel size must be odd");
            }
        } 

        template<typename KernelType>
        Matrix<KernelType> createEmbossKernel(){
            Matrix<KernelType> kernel(3, 3);
            kernel(0, 0) = -2; kernel(0, 1) = -1; kernel(0, 2) = 0;
            kernel(1, 0) = -1; kernel(1, 1) = 1; kernel(1, 2) = 1;
            kernel(2, 0) = 0; kernel(2, 1) = 1; kernel(2, 2) = 2;
            if(detail::isValid(kernel)){
                return kernel;
            }else {
                throw std::runtime_error("Invalid kernel dimensions: kernel size must be odd");
            }
        }

        template<typename KernelType>
        Matrix<KernelType> createBlurringKernel(){
            Matrix<KernelType> kernel(3, 3);
            kernel(0, 0) = (1.0f / 9.0f); kernel(0, 1) = (1.0f / 9.0f); kernel(0, 2) = (1.0f / 9.0f);
            kernel(1, 0) = (1.0f / 9.0f); kernel(1, 1) = (1.0f / 9.0f); kernel(1, 2) = (1.0f / 9.0f);
            kernel(2, 0) = (1.0f / 9.0f); kernel(2, 1) = (1.0f / 9.0f); kernel(2, 2) = (1.0f / 9.0f);

            if(detail::isValid(kernel)){
                return kernel;
            }else {
                throw std::runtime_error("Invalid kernel dimensions: kernel size must be odd");
            }
        }

        template<typename KernelType>
        Matrix<KernelType> createEdgeDetectionKernel(){
            Matrix<KernelType> kernel(3, 3);
            kernel(0, 0) = 0; kernel(0, 1) = 1; kernel(0, 2) = 0;
            kernel(1, 0) = 1; kernel(1, 1) = -4; kernel(1, 2) = 1;
            kernel(2, 0) = 0; kernel(2, 1) = 1; kernel(2, 2) = 0;

            if(detail::isValid(kernel)){
                return kernel;
            }else {
                throw std::runtime_error("Invalid kernel dimensions: kernel size must be odd");
            }
        }

    }

    // Basic convolution operation
    template<typename ImageType, typename KernelType>
    void convolve(Image<ImageType>& image, const Matrix<KernelType>& kernel) {
        int numChannels = image.getNumChannels();
        std::vector<std::thread> threads;
        threads.resize(numChannels);

        int kernelSize = kernel.getRows();
        int kernelRadius = kernelSize / 2;

        for (int c = 0; c < numChannels; ++c) {
            threads[c] = std::thread([&image, &kernel, c, kernelRadius]() {

                int chRows = image.getChannel(c).getRows();
                int chCols = image.getChannel(c).getCols();

                KernelType* outputBuffer = new KernelType[chRows * chCols];
                for (int i = 0; i < chRows * chCols; ++i) {
                    outputBuffer[i] = 0;
                }

                // Apply the kernel to the channel
                detail::applyKernel(image.getChannel(c), kernel, kernelRadius, outputBuffer);

                // Normalize the results
                detail::normalizeResults(outputBuffer, image.getChannel(c), kernelRadius);

                // Update the channel with the new values
                for(int row = kernelRadius; row < chRows - kernelRadius; ++row) {
                    for(int col = kernelRadius; col < chCols - kernelRadius; ++col) {
                        (image.getChannel(c))(col, row) = static_cast<ImageType>(outputBuffer[row * chCols + col]);
                    }
                }

                // Clean up
                delete[] outputBuffer;
                outputBuffer = nullptr;
            });
        }

        for (int i = 0; i < numChannels; ++i) {
            if (threads[i].joinable()) {
                threads[i].join();
            }
        }
        threads.clear();
    }

    template<typename T>
    Matrix<T> createKernel(KernelType type) {
        switch(type) {
            case KernelType::Sharpen:
                return detail::createSharpenKernel<T>();
            case KernelType::Emboss:
                return detail::createEmbossKernel<T>();
            case KernelType::Blur:
                return detail::createBlurringKernel<T>();
            case KernelType::EdgeDetection:
                return detail::createEdgeDetectionKernel<T>();
            default:
                throw std::invalid_argument("Unknown kernel type");
        }
    }

} // namespace ConvolutionEngine

#endif // CONVOLUTION_ENGINE_H