#include <Image.h>

Image::Channel::Channel(uint8_t* imgBuffer, int width, unsigned int height) : Matrix(height, width) {
    MatFill(imgBuffer);
};

uint8_t Image::Channel::getMin() const {
    uint8_t min = std::numeric_limits<uint8_t>::max();
    for(int i = 0; i < data->getRows(); ++i) {
        for(int j = 0; j < data->getCols(); ++j) {
            if((*data)(i, j) < min) {
                min = (*data)(i, j);
            }
        }
    }
};
    

uint8_t Image::Channel::getMax() const {
    uint8_t max = std::numeric_limits<uint8_t>::min();
    for(int i = 0; i < data->getRows(); ++i) {
        for(int j = 0; j < data->getCols(); ++j) {
            if((*data)(i, j) > max) {
                max = (*data)(i, j);
            }
        }
    }
};


double Image::Channel::getMean() const {
    double sum = 0;
    for(int i = 0; i < data->getRows(); ++i) {
        for(int j = 0; j < data->getCols(); ++j) {
            sum += (*data)(i, j);
        }
    }
    return sum / (data->getRows() * data->getCols());
};


void Image::Channel::normalize(uint8_t newMin, uint8_t newMax) {
    uint8_t min = getMin();
    uint8_t max = getMax();
    for(int i = 0; i < data->getRows(); ++i) {
        for(int j = 0; j < data->getCols(); ++j) {
            (*data)(i, j) = (newMax - newMin) * ((*data)(i, j) - min) / (max - min) + newMin;
        }
    }
};


void Image::Channel::threshold(uint8_t threshold, uint8_t lowValue, uint8_t highValue) {
    for(int i = 0; i < data->getRows(); ++i) {
        for(int j = 0; j < data->getCols(); ++j) {
            if((*data)(i, j) < threshold) {
                (*data)(i, j) = lowValue;
            } else {
                (*data)(i, j) = highValue;
            }
        }
    }
};