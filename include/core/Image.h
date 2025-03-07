#include "Matrix.h"

class Image {

protected:
     class Channel : public Matrix {
          private:
               Matrix* data = nullptr;

          public:
               Channel(uint8_t* imgBuffer, int width, unsigned int height);

               uint8_t getMin() const;
               uint8_t getMax() const;
               double getMean() const;

               void normalize(uint8_t newMin, uint8_t newMax);
               void threshold(uint8_t threshold, uint8_t lowValue, uint8_t highValue);

               ~Channel() {
                    delete data;
               }

     };

private:
     int width, height, NumChannels;
     std::vector<Channel*> channels;

public:

     Image(uint8_t* imgBuffer, int width, int NumChannels, int height) : width(width), height(height), NumChannels(NumChannels) {
          for (unsigned int i = 0; i < NumChannels; ++i) {
               channels.push_back(new Channel(imgBuffer, width, height));
          }
     }

     Channel* getChannel(unsigned int channel) {
          return channels[channel];
     }

     const Channel* getChannel(unsigned int channel) const {
          return channels[channel];
     }

     uint8_t* getPixel(unsigned int x, unsigned int y);

     void setPixel(unsigned int x, unsigned int y, const uint8_t* pixel);

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

     ~Image() {
          for (unsigned int i = 0; i < NumChannels; ++i) {
               delete channels[i];
          }
     }
};