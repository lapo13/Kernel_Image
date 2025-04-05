#include <gtest/gtest.h>
#include "utils/Convolution_Engine.h"
#include "utils/ImageIO.h"

class ConvolutionEngineTest : public ::testing::Test {
protected:
    Image<int>* image;
    Matrix<int> kernel;

    void SetUp() override {
        // Create a simple 5x5 image
        int imgData[25] = { 
            0, 0, 0, 0, 0,
            0, 25, 25, 25, 0,
            0, 25, 25, 25, 0,
            0, 25, 25, 25, 0,
            0, 0, 0, 0, 0
        };
        ImageHeader header = { 5, 5, 1, 255, "P5" };
        image = new Image<int>(imgData, header);

        // Create a simple kernel
        kernel = Matrix<int>(3, 3);
        kernel(0, 0) = -1; kernel(0, 1) = -1; kernel(0, 2) = -1;
        kernel(1, 0) = -1; kernel(1, 1) = 8; kernel(1, 2) = -1;
        kernel(2, 0) = -1; kernel(2, 1) = -1; kernel(2, 2) = -1;
    }
     void TearDown() override {
          delete image;
     }
};

TEST_F(ConvolutionEngineTest, Convolve) {
    // Print input image
    std::cout << "Input image:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << (int)image->getPixel(i, j)[0] << " ";
        }
        std::cout << std::endl;
    }

    // Apply convolution
    ConvolutionEngine<int, int>::convolve(*image, kernel);

    // Print output image
    std::cout << "Output image:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << (int)image->getPixel(i, j)[0] << " ";
        }
        std::cout << std::endl;
    }

    // Check the output
    unsigned char expectedData[25] = { 
        0, 0, 0, 0, 0,
        0, 25, 15, 25, 0,
        0, 15, 0, 15, 0,
        0, 25, 15, 25, 0,
        0, 0, 0, 0, 0
    };
    for (int i = 0; i < 5; ++i) {
          for (int j = 0; j < 5; ++j) {
               EXPECT_EQ(((int)image->getPixel(i, j)[0]), ((int)expectedData[i * 5 + j]));
          }
        
    }
}

TEST_F(ConvolutionEngineTest, CreateSharpenKernel) {
    Matrix<float> sharpenKernel = ConvolutionEngine<unsigned char, float>::createSharpenKernel();
    EXPECT_EQ(sharpenKernel.getRows(), 3);
    EXPECT_EQ(sharpenKernel.getCols(), 3);
    EXPECT_EQ(sharpenKernel(1, 1), 9);
}

TEST_F(ConvolutionEngineTest, CreateEmbossKernel) {
    Matrix<float> embossKernel = ConvolutionEngine<unsigned char, float>::createEmbossKernel();
    EXPECT_EQ(embossKernel.getRows(), 3);
    EXPECT_EQ(embossKernel.getCols(), 3);
    EXPECT_EQ(embossKernel(1, 1), 1);
}

TEST_F(ConvolutionEngineTest, CreateBlurringKernel) {
    Matrix<float> blurringKernel = ConvolutionEngine<unsigned char, float>::createBlurringKernel();
    EXPECT_EQ(blurringKernel.getRows(), 3);
    EXPECT_EQ(blurringKernel.getCols(), 3);
    EXPECT_FLOAT_EQ(blurringKernel(1, 1), 1.0f / 9.0f);
}

TEST_F(ConvolutionEngineTest, CreateEdgeDetectionKernel) {
    Matrix<float> edgeDetectionKernel = ConvolutionEngine<unsigned char, float>::createEdgeDetectionKernel();
    EXPECT_EQ(edgeDetectionKernel.getRows(), 3);
    EXPECT_EQ(edgeDetectionKernel.getCols(), 3);
    EXPECT_EQ(edgeDetectionKernel(1, 1), -4);
}