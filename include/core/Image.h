#include "Channel.h"

template <typename PixelType, unsigned int NumChannels>
class Image {

private:
     std::array<Channel<PixelType>, NumChannels> channels;
     unsigned int width, height;

public:

     Image(const Image<PixelType, NumChannels>& img) : width(img.width), height(img.height);

     Channel <PixelType>& getChannel(unsigned int channel) {
          return channels[channel];
     }
     const Channel <PixelType>& getChannel(unsigned int channel) const {
          return channels[channel];
     }

     std::array<Channel<PixelType>, NumChannels>& getPixel(unsigned int x, unsigned int y);

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