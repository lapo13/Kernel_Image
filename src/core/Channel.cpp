#include <Image.h>

Image::Channel::Channel(uint8_t* imgBuffer, int width, unsigned int height) : Matrix(height, width) {
    MatFill(imgBuffer);
};

uint8_t Image::Channel::getMin() const {
    uint8_t min = std::numeric_limits<uint8_t>::max();
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            if((*this)(i, j) < min) {
                min = (*this)(i, j);
            }
        }
    }
};
    

uint8_t Image::Channel::getMax() const {
    uint8_t max = std::numeric_limits<uint8_t>::min();
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            if((*this)(i, j) > max) {
                max = (*this)(i, j);
            }
        }
    }
};


double Image::Channel::getMean() const {
    double sum = 0;
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            sum += (*this)(i, j);
        }
    }
    return sum / (this->getRows() * this->getCols());
};


void Image::Channel::normalize(uint8_t newMin, uint8_t newMax) {
    uint8_t min = getMin();
    uint8_t max = getMax();
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            (*this)(i, j) = (newMax - newMin) * ((*this)(i, j) - min) / (max - min) + newMin;
        }
    }
    this->setMin(newMin);
    this->setMax(newMax);
};


void Image::Channel::threshold(uint8_t threshold, uint8_t lowValue, uint8_t highValue) {
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            if((*this)(i, j) < threshold) {
                (*this)(i, j) = lowValue;
            } else {
                (*this)(i, j) = highValue;
            }
        }
    }
};