#include "core/Image.h"

Image::Channel::Channel(unsigned char* imgBuffer, int width, int height, int channel_num): 
Matrix(height, width) {  // Nota: height e width invertiti
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            size_t idx = (i * width + j) * 3 + channel_num;
            (*this)(j, i) = imgBuffer[idx];  // Nota: j e i invertiti
        }
    }
}

Image::Channel::Channel(unsigned char* imgBuffer, int width, int height): 
Matrix(height, width) {  // Nota: height e width invertiti
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            (*this)(j, i) = imgBuffer[i * width + j];  // Nota: j e i invertiti
        }
    }
}

unsigned char Image::Channel::getMin() const {
    unsigned char min = std::numeric_limits<unsigned char>::max();
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            if((*this)(i, j) < min) {
                min = (*this)(i, j);
            }
        }
    }
    return min;
};
    

unsigned char Image::Channel::getMax() const {
    unsigned char max = std::numeric_limits<unsigned char>::min();
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            if((*this)(i, j) > max) {
                max = (*this)(i, j);
            }
        }
    }
    return max;
};


double Image::Channel::getMean() const {
    double sum = 0;
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            sum += (double)(*this)(i, j);
        }
    }
    return sum / (this->getRows() * this->getCols());
};


void Image::Channel::normalize(unsigned char newMin, unsigned char newMax) {
    unsigned char min = getMin();
    unsigned char max = getMax();
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            (*this)(i, j) = (newMax - newMin) * ((*this)(i, j) - min) / (max - min) + newMin;
        }
    }
    this->setMin(newMin);
    this->setMax(newMax);
};


void Image::Channel::threshold(unsigned char threshold, unsigned char lowValue, unsigned char highValue) {
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