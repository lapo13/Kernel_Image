#ifndef CHANNEL_H
#define CHANNEL_H

#include "Matrix.h"

template <typename T>
class Channel : public Matrix<T> {
     private:
         unsigned char min, max;   
 
     public:
        Channel(T *imgBuffer, int width, int height, int channel_num);
        Channel(T *imgBuffer, int width, int height);

        T getMin() const;
        T getMax() const;
        void setMin(T min){
            this->min = min;
        };
        void setMax(T max){
            this->max = max;
        };
 
        double getMean() const;
 
        //void normalize(unsigned char newMin, unsigned char newMax);
        void threshold(unsigned char threshold, unsigned char lowValue, unsigned char highValue);
 
        ~Channel() = default;
     };

#endif //CHANNEL_H