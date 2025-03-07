#include <Image.h>

template <typename PixelType, unsigned int NumChannels>
PixelType Image<PixelType, NumChannels>::Channel::getMin() const {
    PixelType min = std::numeric_limits<PixelType>::max();
    for (auto it = begin(); it != end(); ++it) {
        if (*it < min) {
            min = *it;
        }
    }
    return min;
};

template <typename PixelType, unsigned int NumChannels>
PixelType Image<PixelType, NumChannels>::Channel::getMax() const {
    PixelType max = std::numeric_limits<PixelType>::min();
    for (auto it = begin(); it != end(); ++it) {
        if (*it > max) {
            max = *it;
        }
    }
    return max;
};

template <typename PixelType, unsigned int NumChannels>
double Image<PixelType, NumChannels>::Channel::getMean() const {
    double sum = 0;
    for (auto it = begin(); it != end(); ++it) {
        sum += *it;
    }
    return sum / (data.getRows() * data.getCols());
};

template <typename PixelType, unsigned int NumChannels>
void Image<PixelType, NumChannels>::Channel::normalize(PixelType newMin, PixelType newMax) {
    PixelType min = getMin();
    PixelType max = getMax();
    for (auto it = begin(); it != end(); ++it) {
        *it = newMin + (*it - min) * (newMax - newMin) / (max - min);
    }
};

template <typename PixelType, unsigned int NumChannels>
void Image<PixelType, NumChannels>::Channel::threshold(PixelType threshold, PixelType lowValue, PixelType highValue) {
    for (auto it = begin(); it != end(); ++it) {
        *it = (*it > threshold) ? highValue : lowValue;
    }
};