#ifndef CHANNEL_H
#define CHANNEL_H

#include "Matrix.h"

template <typename T>
class Channel : public Matrix<T> { // fondere la classe Channel in Matrix
     private:
         unsigned char min, max;   
 
     public:
        Channel(T *imgBuffer, int width, int height, int channel_num);
        Channel(T *imgBuffer, int width, int height);

        T getMin() const;
        T getMax() const;
        double getMean() const;
 
        ~Channel() = default;
     };

#endif //CHANNEL_H