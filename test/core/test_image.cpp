#include <gtest/gtest.h>
#include "core/Image.h"


class ImageTest : public ::testing::Test {
protected:
    ImageHeader header;
    unsigned char* imgBuffer;
    Image<unsigned char>* image;

    void SetUp() override {
          header.width = 4;
          header.height = 4;
          header.numChannels = 3;
          header.maxVal = 255;
          header.magicNumber = "P6";
          imgBuffer = new unsigned char[header.width * header.height * header.numChannels];
          for (int i = 0; i < header.width * header.height * header.numChannels; ++i) {
               imgBuffer[i] = static_cast<unsigned char>(i);
          }
          image = new Image<unsigned char>(imgBuffer, header);
     }
     void TearDown() override {
          delete[] imgBuffer;
          delete image;
     }
};

TEST_F(ImageTest, Constructor) {
     EXPECT_EQ(image->getWidth(), 4);
     EXPECT_EQ(image->getHeight(), 4);
     EXPECT_EQ(image->getNumChannels(), 3);
     EXPECT_EQ(image->getHeader().width, 4);
     EXPECT_EQ(image->getHeader().height, 4);
     EXPECT_EQ(image->getHeader().numChannels, 3);
     EXPECT_EQ(image->getHeader().maxVal, 255);
     EXPECT_EQ(image->getHeader().magicNumber, "P6");
}

TEST_F(ImageTest, GetPixel) {
    std::vector<unsigned char> pixel = image->getPixel(1, 1);
    EXPECT_EQ(pixel[0], 15); // Channel 0
    EXPECT_EQ(pixel[1], 16); // Channel 1
    EXPECT_EQ(pixel[2], 17); // Channel 2
}

TEST_F(ImageTest, SetPixel) {
    unsigned char newPixel[3] = {100, 101, 102};
    image->setPixel(1, 1, newPixel);
    std::vector<unsigned char> pixel = image->getPixel(1, 1);
    EXPECT_EQ(pixel[0], 100);
    EXPECT_EQ(pixel[1], 101);
    EXPECT_EQ(pixel[2], 102);
}

TEST_F(ImageTest, Resize) {
    image->resize(2, 2);
    EXPECT_EQ(image->getWidth(), 2);
    EXPECT_EQ(image->getHeight(), 2);
    EXPECT_THROW(image->getPixel(3, 3), std::out_of_range);
}

