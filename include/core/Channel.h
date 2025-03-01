#include "Matrix.h"

template <typename PixelType>
class Channel : public Matrix<PixelType> {
     
public:
     Channel(int rows, int cols) : Matrix<PixelType>(rows, cols) {}

     PixelType getMin() const;
     PixelType getMax() const;
     double getMean() const;

     void normalize(PixelType newMin, PixelType newMax);
     void threshold(PixelType threshold, PixelType lowValue, PixelType highValue);
};
