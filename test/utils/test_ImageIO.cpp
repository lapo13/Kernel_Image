#include <gtest/gtest.h>
#include "utils/ImageIO.h"

class ImageIOTest : public ::testing::Test {
protected:
    ImageHeader header;
    ImageHeader header2;
    unsigned char* imgBuffer;
    MultiChannelImage<unsigned char>* image;
    SingleChannelImage<unsigned char>* image2;

    void SetUp() {
        // Initialize the header for a 2x2 RGB image
        header.magicNumber = "P6";
        header.width = 2;
        header.height = 2;
        header.maxVal = 255;
        header.numChannels = 3;
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
        delete[] imgBuffer;
        imgBuffer = nullptr;

        // Initialize the header for a 2x2 grayscale image
        header2.magicNumber = "P5";
        header2.width = 2;
        header2.height = 2;
        header2.maxVal = 255;
        header2.numChannels = 1;
        imgBuffer = new unsigned char[header2.width * header2.height * header2.numChannels];
        for (int i = 0; i < header2.width * header2.height * header2.numChannels; ++i) {
            imgBuffer[i] = static_cast<unsigned char>(i);
        }
        // Create a SingleChannelImage object
        std::unique_ptr<Matrix<unsigned char>> channel = std::make_unique<Matrix<unsigned char>>(header2.height, header2.width);
        for (int y = 0; y < header2.height; ++y) {
            for (int x = 0; x < header2.width; ++x) {
                (*channel)(x, y) = imgBuffer[y * header2.width + x];
            }
        }
        image2 = new GrayscaleImage<unsigned char>(std::move(channel), header2);
        delete[] imgBuffer;
        imgBuffer = nullptr;        
    }

    void TearDown() {
        // Clean up the image objects
        delete image;
        image = nullptr;
        delete image2;
        image2 = nullptr;
    }
};

TEST_F(ImageIOTest, Load_and_Save_Image) {
    //save the image 
    ImageIO::saveImage("test_output.ppm", *image);
    ImageIO::saveImage("test_output.pgm", *image2);

    // Load the image back
    MultiChannelImage<unsigned char>* loadedImage = ImageIO::loadRGBImage<unsigned char>("test_output.ppm");
    SingleChannelImage<unsigned char>* loadedImage2 = ImageIO::loadGrayImage<unsigned char>("test_output.pgm");

    // Check if the loaded RGB image matches the original
    EXPECT_EQ(loadedImage->getWidth(), image->getWidth());
    EXPECT_EQ(loadedImage->getHeight(), image->getHeight());
    EXPECT_EQ(loadedImage->getNumChannels(), image->getNumChannels());
    EXPECT_EQ(loadedImage->getHeader().magicNumber, image->getHeader().magicNumber);
    EXPECT_EQ(loadedImage->getHeader().maxVal, image->getHeader().maxVal);
    for (int row = 0; row < image->getHeight(); ++row) {
        for (int col = 0; col < image->getWidth(); ++col) {
            for (int ch = 0; ch < image->getNumChannels(); ++ch) {
                EXPECT_EQ(loadedImage->getChannel(ch)(col, row), image->getChannel(ch)(col, row));
            }
        }
    }

    // Check if the loaded grayscale image matches the original
    EXPECT_EQ(loadedImage2->getWidth(), image2->getWidth());
    EXPECT_EQ(loadedImage2->getHeight(), image2->getHeight());
    EXPECT_EQ(loadedImage2->getNumChannels(), image2->getNumChannels());
    EXPECT_EQ(loadedImage2->getHeader().magicNumber, image2->getHeader().magicNumber);
    EXPECT_EQ(loadedImage2->getHeader().maxVal, image2->getHeader().maxVal);
    for (int row = 0; row < image2->getHeight(); ++row) {
        for (int col = 0; col < image2->getWidth(); ++col) {
            EXPECT_EQ(loadedImage2->getChannel()(col, row), image2->getChannel()(col, row));
        }
    }
}