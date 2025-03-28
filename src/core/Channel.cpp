#include "core/Channel.h"

template <typename T>
Channel<T>::Channel(T* imgBuffer, int width, int height, int channel_num): Matrix<T>(height, width) {  // Nota: height e width invertiti
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            size_t idx = (i * width + j) * 3 + channel_num;
            (*this)(j, i) = imgBuffer[idx];
        }
    }
}

template <typename T>
Channel<T>::Channel(T* imgBuffer, int width, int height): Matrix<T>(height, width) {  // Nota: height e width invertiti
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
            if((*this)(i, j) < min) {
                min = (*this)(i, j);
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
            if((*this)(i, j) > max) {
                max = (*this)(i, j);
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
            sum += (double)(*this)(i, j);
        }
    }
    return sum / (this->getRows() * this->getCols());
};

/*template <typename T>
void Channel<T>::normalize(unsigned char newMin, unsigned char newMax) {
    T min = getMin();
    T max = getMax();
    double range = max - min;
    double newRange = newMax - newMin;
    
    // Avoid division by zero
    if (range == 0) {
        return;
    }
    
    for(int i = 0; i < this->getRows(); ++i) {
        for(int j = 0; j < this->getCols(); ++j) {
            // First scale to [0,1], then scale to new range and offset
            double normalized = (static_cast<double>((*this)(i, j)) - min) / range;
            (*this)(i, j) = static_cast<T>(normalized * newRange + newMin);
        }
    }
}*/

template <typename T>
void Channel<T>::threshold(unsigned char threshold, unsigned char lowValue, unsigned char highValue) {
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

//Explicit instantiation
template class Channel<unsigned char>;
template class Channel<double>;