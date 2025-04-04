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
    T min = (*this)(0, 0);
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
    T max = (*this)(0, 0);
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

//Explicit instantiation
template class Channel<unsigned char>;
template class Channel<double>;
template class Channel<int>;
template class Channel<float>;