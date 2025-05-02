#include <gtest/gtest.h>
#include "core/Image.h"


class ImageRGBTest : public ::testing::Test {
protected:
    ImageHeader header;
    unsigned char* imgBuffer;
    MultiChannelImage<unsigned char>* image;

     void SetUp() {
          header.width = 4;
          header.height = 4;
          header.numChannels = 3;
          header.maxVal = 255;
          header.magicNumber = "P6";

          imgBuffer = new unsigned char[header.width * header.height * header.numChannels];
          for (int i = 0; i < header.width * header.height * header.numChannels; ++i) {
               imgBuffer[i] = static_cast<unsigned char>(i);
          }
          // Create a MultiChannelImage object
          std::vector<std::unique_ptr<Matrix<unsigned char>>> channels(header.numChannels);
          for (int i = 0; i < header.numChannels; ++i) {
               channels[i] = std::make_unique<Matrix<unsigned char>>(header.height, header.width);
          }
          size_t idx = 0;
          for (int y = 0; y < header.height; ++y) {
               for (int x = 0; x < header.width; ++x) {
                    for (int c = 0; c < header.numChannels; ++c) {
                         (*channels[c])(x, y) = imgBuffer[idx++];
                    }
               }
          }
          image = new ImageRGB<unsigned char>(std::move(channels), header);
      }
     void TearDown() {
          delete[] imgBuffer;
          imgBuffer = nullptr;
          delete image;
          image = nullptr;
     }
};

TEST_F(ImageRGBTest, Constructor) {
     EXPECT_EQ(image->getWidth(), 4);
     EXPECT_EQ(image->getHeight(), 4);
     EXPECT_EQ(image->getNumChannels(), 3);
     EXPECT_EQ(image->getHeader().width, 4);
     EXPECT_EQ(image->getHeader().height, 4);
     EXPECT_EQ(image->getHeader().numChannels, 3);
     EXPECT_EQ(image->getHeader().maxVal, 255);
     EXPECT_EQ(image->getHeader().magicNumber, "P6");
}

TEST_F(ImageRGBTest, GetPixel) {
    std::vector<unsigned char> pixel = image->getPixel(1, 1);
    EXPECT_EQ(pixel[0], 15); // Channel 0
    EXPECT_EQ(pixel[1], 16); // Channel 1
    EXPECT_EQ(pixel[2], 17); // Channel 2
}

TEST_F(ImageRGBTest, SetPixel) {
    std::vector<unsigned char> newPixel = {100, 101, 102};
    image->setPixel(1, 1, newPixel);
    std::vector<unsigned char> pixel = image->getPixel(1, 1);
    EXPECT_EQ(pixel[0], 100);
    EXPECT_EQ(pixel[1], 101);
    EXPECT_EQ(pixel[2], 102);
}

TEST_F(ImageRGBTest, OutOfBounds) {
    std::vector<unsigned char> newPixel = {100, 101, 102};
    EXPECT_THROW(image->setPixel(5, 5, newPixel), std::out_of_range);
    EXPECT_THROW(image->getPixel(5, 5), std::out_of_range);
}

