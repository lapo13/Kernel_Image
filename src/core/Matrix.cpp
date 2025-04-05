#include "core/Matrix.h"
#include <iostream>

template <typename T>
void Matrix<T>::MatResize(int rows, int cols) {
    std::vector<T> newData(rows * cols);
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            if (i < this->rows && j < this->cols) {
                newData[i * cols + j] = data[i * this->cols + j];
            } else {
                newData[i * cols + j] = 0;
            }
        }
    }
    this->rows = rows;
    this->cols = cols;
    data = newData;
}

// Explicit instantiation
template class Matrix<unsigned char>;
template class Matrix<double>;
template class Matrix<int>;
template class Matrix<float>;