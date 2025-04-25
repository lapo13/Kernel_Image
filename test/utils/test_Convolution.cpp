#include <gtest/gtest.h>
#include "utils/Convolution.h"
#include "utils/ImageIO.h"
#include "core/Image.h"

class ConvolutionEngineTest : public ::testing::Test {  //rifere i test considerando delle immagini precalcolate 
protected:
    Image<unsigned char>* preCalculatedImage;
    Image<unsigned char>* preCalculatedImage_2;
    Image<unsigned char>* testImage;
    Image<unsigned char>* testImage_2;
    Matrix<float> kernel;

    void SetUp() {
        preCalculatedImage = ImageIO::loadImage<unsigned char>(R"(/Users/lapotinacci/Documents/Kernel_Image/images/output/sample_1280×853_out.ppm)");
        preCalculatedImage_2 = ImageIO::loadImage<unsigned char>(R"(/Users/lapotinacci/Documents/Kernel_Image/images/output/sample_1280×853_out.pgm)");
        testImage = ImageIO::loadImage<unsigned char>(R"(/Users/lapotinacci/Documents/Kernel_Image/images/input/sample_1280×853.ppm)");
        testImage_2 = ImageIO::loadImage<unsigned char>(R"(/Users/lapotinacci/Documents/Kernel_Image/images/input/sample_1280×853.pgm)");
        kernel = Convolution::createKernel<float>(Convolution::KernelType::Emboss);
    }
    void TearDown() {
        delete testImage;
        testImage = nullptr;
        delete testImage_2;
        testImage_2 = nullptr;
        delete preCalculatedImage;
        preCalculatedImage = nullptr;
        delete preCalculatedImage_2;
        preCalculatedImage_2 = nullptr;
    }
};

TEST_F(ConvolutionEngineTest, Convolve) {
    // convolution testing RGB image
    Convolution::convolve(*testImage, kernel);
    // Check if the convolution result matches the pre-calculated image
    for (int row = 0; row < preCalculatedImage->getHeight(); ++row) {
        for (int col = 0; col < preCalculatedImage->getWidth(); ++col) {
            for (int ch = 0; ch < preCalculatedImage->getNumChannels(); ++ch) {
                EXPECT_EQ(testImage->getChannel(ch)(col, row), preCalculatedImage->getChannel(ch)(col, row));
            }
        }
    }

    // convolution testing grayscale image
    Convolution::convolve(*testImage_2, kernel);
    // Check if the convolution result matches the pre-calculated image
    for (int row = 0; row < preCalculatedImage_2->getHeight(); ++row) {
        for (int col = 0; col < preCalculatedImage_2->getWidth(); ++col) {
            EXPECT_EQ(testImage_2->getChannel(0)(col, row), preCalculatedImage_2->getChannel(0)(col, row));
        }
    }
}

TEST_F(ConvolutionEngineTest, CreateSharpenKernel) {
    Matrix<float> sharpenKernel = Convolution::createKernel<float>(Convolution::KernelType::Sharpen);
    EXPECT_EQ(sharpenKernel.getRows(), 3);
    EXPECT_EQ(sharpenKernel.getCols(), 3);
    EXPECT_EQ(sharpenKernel(1, 1), 9);
    EXPECT_EQ(sharpenKernel(0, 0), -1);
    EXPECT_EQ(sharpenKernel(0, 1), -1);
    EXPECT_EQ(sharpenKernel(0, 2), -1);
    EXPECT_EQ(sharpenKernel(1, 0), -1);
    EXPECT_EQ(sharpenKernel(1, 2), -1);
    EXPECT_EQ(sharpenKernel(2, 0), -1);
    EXPECT_EQ(sharpenKernel(2, 1), -1);
    EXPECT_EQ(sharpenKernel(2, 2), -1);
}

TEST_F(ConvolutionEngineTest, CreateEmbossKernel) {
    Matrix<float> embossKernel = Convolution::createKernel<float>(Convolution::KernelType::Emboss);
    EXPECT_EQ(embossKernel.getRows(), 3);
    EXPECT_EQ(embossKernel.getCols(), 3);
    EXPECT_EQ(embossKernel(1, 1), 1);
    EXPECT_EQ(embossKernel(0, 0), -2);
    EXPECT_EQ(embossKernel(0, 1), -1);
    EXPECT_EQ(embossKernel(0, 2), 0);
    EXPECT_EQ(embossKernel(1, 0), -1);
    EXPECT_EQ(embossKernel(1, 2), 1);
    EXPECT_EQ(embossKernel(2, 0), 0);
    EXPECT_EQ(embossKernel(2, 1), 1);
    EXPECT_EQ(embossKernel(2, 2), 2);
}

TEST_F(ConvolutionEngineTest, CreateBlurringKernel) {
    Matrix<float> blurringKernel = Convolution::createKernel<float>(Convolution::KernelType::Blur);
    EXPECT_EQ(blurringKernel.getRows(), 3);
    EXPECT_EQ(blurringKernel.getCols(), 3);
    EXPECT_EQ(blurringKernel(1, 1), 1.0f / 9.0f);
    EXPECT_EQ(blurringKernel(0, 0), 1.0f / 9.0f);
    EXPECT_EQ(blurringKernel(0, 1), 1.0f / 9.0f);
    EXPECT_EQ(blurringKernel(0, 2), 1.0f / 9.0f);
    EXPECT_EQ(blurringKernel(1, 0), 1.0f / 9.0f);
    EXPECT_EQ(blurringKernel(1, 2), 1.0f / 9.0f);
    EXPECT_EQ(blurringKernel(2, 0), 1.0f / 9.0f);
    EXPECT_EQ(blurringKernel(2, 1), 1.0f / 9.0f);
    EXPECT_EQ(blurringKernel(2, 2), 1.0f / 9.0f);
}

TEST_F(ConvolutionEngineTest, CreateEdgeDetectionKernel) {
    Matrix<float> edgeDetectionKernel = Convolution::createKernel<float>(Convolution::KernelType::EdgeDetection);
    EXPECT_EQ(edgeDetectionKernel.getRows(), 3);
    EXPECT_EQ(edgeDetectionKernel.getCols(), 3);
    EXPECT_EQ(edgeDetectionKernel(1, 1), -4);
    EXPECT_EQ(edgeDetectionKernel(0, 0), 0);
    EXPECT_EQ(edgeDetectionKernel(0, 1), 1);
    EXPECT_EQ(edgeDetectionKernel(0, 2), 0);
    EXPECT_EQ(edgeDetectionKernel(1, 0), 1);
    EXPECT_EQ(edgeDetectionKernel(1, 2), 1);
    EXPECT_EQ(edgeDetectionKernel(2, 0), 0);
    EXPECT_EQ(edgeDetectionKernel(2, 1), 1);
    EXPECT_EQ(edgeDetectionKernel(2, 2), 0);
}