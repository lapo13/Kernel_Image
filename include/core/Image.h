#include "Matrix.h"
#include <array>


template <typename PixelType, unsigned int NumChannels>
class Image {

private:
     std::array<Channel> channels;
     unsigned int width, height;

protected:
     class Channel : public Matrix<PixelType> {
          private:
               unsigned int width, height;
               Matrix<PixelType> data;

          public:
               Channel(PixelType ImageChannel, int width, unsigned int height) : width(width), height(height), data(width, height) {
                    for (unsigned int i = 0; i < width; ++i) {
                         for (unsigned int j = 0; j < height; ++j) {
                              data(i, j) = ImageChannel;
                         }
                    }
               };
               PixelType getMin() const;
               PixelType getMax() const;
               double getMean() const;

               void normalize(PixelType newMin, PixelType newMax);
               void threshold(PixelType threshold, PixelType lowValue, PixelType highValue);

               iterator begin() {
                    return data.begin();
               }
               iterator end() {
                    return data.end();
               }
     };

public:

     Image(const Image<PixelType, NumChannels>& img) : width(img.width), height(img.height) {
          for (unsigned int i = 0; i < NumChannels; ++i) {
               channels[i] = new Channel(img.channel, img.width, img.height);
          }
     }

     Channel& getChannel(unsigned int channel) {
          return channels[channel];
     }
     const Channel& getChannel(unsigned int channel) const {
          return channels[channel];
     }

     std::array<Channel, NumChannels>& getPixel(unsigned int x, unsigned int y);

     void setPixel(unsigned int x, unsigned int y, const std::array<PixelType, NumChannels>& pixel);

     unsigned int getWidth() const {
          return width;
     }

     unsigned int getHeight() const {
          return height;
     }

     unsigned int getNumChannels() const {
          return NumChannels;
     }

     void resize(unsigned int width, unsigned int height);
     void fill(const std::array<PixelType, NumChannels>& pixel);

};