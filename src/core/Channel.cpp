#include "core/Channel.h"

template <typename T>
Channel<T>::Channel(T* imgBuffer, int width, int height, int channel_num): Matrix<T>(height, width) { 
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            size_t idx = (i * width + j) * 3 + channel_num;
            (*this)(j, i) = imgBuffer[idx];
        }
    }
}

template <typename T>
Channel<T>::Channel(T* imgBuffer, int width, int height): Matrix<T>(height, width) { 
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            (*this)(j, i) = imgBuffer[i * width + j]; 
        }
    }
}

template <typename T>
T Channel<T>::getMin() const {
    unsigned char min = std::numeric_limits<unsigned char>::max();
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            if((*this)(j, i) < min) {
                min = (*this)(j, i);
            }
        }
    }
    return min;
};
    
template <typename T>
T Channel<T>::getMax() const {
    unsigned char max = std::numeric_limits<unsigned char>::min();
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            if((*this)(j, i) > max) {
                max = (*this)(j, i);
            }
        }
    }
    return max;
};

template <typename T>
double Channel<T>::getMean() const {
    double sum = 0;
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            sum += (double)(*this)(j, i);
        }
    }
    return sum / (this->getRows() * this->getCols());
};

template <typename T>
void Channel<T>::threshold(unsigned char threshold, unsigned char lowValue, unsigned char highValue) {
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            if((*this)(j, i) < threshold) {
                (*this)(j, i) = lowValue;
            } else {
                (*this)(j, i) = highValue;
            }
        }
    }
};

//Explicit instantiation
template class Channel<unsigned char>;
template class Channel<double>;