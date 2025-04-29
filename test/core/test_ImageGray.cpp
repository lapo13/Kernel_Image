#include <gtest/gtest.h>
#include "core/Image.h"

class ImageGrayTest : public ::testing::Test {
protected:
    ImageHeader header;
    unsigned char* imgBuffer;
    SingleChannelImage<unsigned char>* image;

    void SetUp() {
        header.width = 4;
        header.height = 4;
        header.numChannels = 1;
        header.maxVal = 255;
        header.magicNumber = "P5";

        imgBuffer = new unsigned char[header.width * header.height * header.numChannels];
        for (int i = 0; i < header.width * header.height * header.numChannels; ++i) {
            imgBuffer[i] = static_cast<unsigned char>(i);
        }
        image = new GrayscaleImage<unsigned char>(new Matrix<unsigned char>(imgBuffer, header.width, header.height), header);
    }

     void TearDown() {
          delete[] imgBuffer;
          imgBuffer = nullptr;
          delete image;
          image = nullptr;
     }
};

TEST_F(ImageGrayTest, Constructor) {
    EXPECT_EQ(image->getWidth(), 4);
    EXPECT_EQ(image->getHeight(), 4);
    EXPECT_EQ(image->getNumChannels(), 1);
    EXPECT_EQ(image->getHeader().maxVal, 255);
    EXPECT_EQ(image->getHeader().magicNumber, "P5");
}

TEST_F(ImageGrayTest, GetPixel) {
    unsigned char pixel = image->getPixel(1, 1);
    EXPECT_EQ(static_cast<int>(pixel), 5); // Expected value at (1, 1)
}

TEST_F(ImageGrayTest, SetPixel) {
    unsigned char newPixel = 100;
    image->setPixel(1, 1, newPixel);
    unsigned char pixel = image->getPixel(1, 1);
    EXPECT_EQ(pixel, 100);
}

TEST_F(ImageGrayTest, OutOfBounds) {
    EXPECT_THROW(image->setPixel(5, 5, 100), std::out_of_range);
    EXPECT_THROW(image->getPixel(5, 5), std::out_of_range);
}
