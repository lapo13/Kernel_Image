#include "core/Matrix.h"
#include <iostream>

template <typename T>
Matrix<T>::Matrix(int rows, int cols): rows(rows), cols(cols) {
    data.resize(rows * cols);
}

template <typename T>
void Matrix<T>::MatResize(int rows, int cols) {
    data.resize(rows * cols);
    this->rows = rows;
    this->cols = cols;
}

// Explicit instantiation
template class Matrix<unsigned char>;