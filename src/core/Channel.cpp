#include <Channel.h>

template <typename PixelType>
PixelType Channel<PixelType>::getMin() const {
     PixelType min = std::numeric_limits<PixelType>::max();
     for (auto it = begin(); it != end(); ++it) {
          if (*it < min) {
               min = *it;
          }
     }
     return min;
}

template <typename PixelType>
PixelType Channel<PixelType>::getMax() const {
     PixelType max = std::numeric_limits<PixelType>::min();
     for (auto it = begin(); it != end(); ++it) {
          if (*it > max) {
               max = *it;
          }
     }
     return max;
}

template <typename PixelType>
double Channel<PixelType>::getMean() const {
     double sum = 0;
     for (auto it = begin(); it != end(); ++it) {
          sum += *it;
     }
     return sum / (getRows() * getCols());
}

template <typename PixelType>
void Channel<PixelType>::normalize(PixelType newMin, PixelType newMax) {
     PixelType min = getMin();
     PixelType max = getMax();
     for (auto it = begin(); it != end(); ++it) {
          *it = newMin + (*it - min) * (newMax - newMin) / (max - min);
     }
}

template <typename PixelType>
void Channel<PixelType>::threshold(PixelType threshold, PixelType lowValue, PixelType highValue) {
     for (auto it = begin(); it != end(); ++it) {
          if (*it < threshold) {
               *it = lowValue;
          } else {
               *it = highValue;
          }
     }
}