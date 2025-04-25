#include <gtest/gtest.h>
#include "utils/ImageIO.h"

class ImageIOTest : public ::testing::Test {
protected:
    ImageHeader header;
    unsigned char* imgBuffer;
    Image<unsigned char>* image;

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
        imageFactory<unsigned char> factory;
        image = factory.createImage(imgBuffer, header);
    }

    void TearDown() {
        delete[] imgBuffer;
        delete image;
    }
};

TEST_F(ImageIOTest, Load_and_Save_Image) {
     // Save the image to a file
     ImageIO::saveImage<unsigned char>("test.ppm", *image);

     // Load the image from the file
     Image<unsigned char>* loadedImage = ImageIO::loadImage<unsigned char>("test.ppm");

     // Check if the loaded image is not null
     ASSERT_NE(loadedImage, nullptr);

     // Check if the loaded image has the same properties as the original
     EXPECT_EQ(loadedImage->getWidth(), header.width);
     EXPECT_EQ(loadedImage->getHeight(), header.height);
     EXPECT_EQ(loadedImage->getNumChannels(), header.numChannels);
     EXPECT_EQ(loadedImage->getHeader().magicNumber, header.magicNumber);
     EXPECT_EQ(loadedImage->getHeader().maxVal, header.maxVal);

     // Check if the pixel data is the same
     for (int y = 0; y < header.height; ++y) {
          for (int x = 0; x < header.width; ++x) {
               std::vector<unsigned char> pixel = loadedImage->getPixel(x, y);
               EXPECT_EQ(pixel[0], imgBuffer[(y * header.width + x) * header.numChannels]);
               EXPECT_EQ(pixel[1], imgBuffer[(y * header.width + x) * header.numChannels + 1]);
               EXPECT_EQ(pixel[2], imgBuffer[(y * header.width + x) * header.numChannels + 2]);
          }
     }

     // Clean up the loaded image
     delete loadedImage;
     std::remove("test.ppm");
}