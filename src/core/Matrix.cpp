#include <Matrix.h>

template <typename T>
void Matrix<T>::MatFill(T value) {
    for (auto it = begin(); it != end(); ++it) {
        *it = value;
    }
}

template <typename T>
void Matrix<T>::MatResize(int rows, int cols) {
    data.resize(rows * cols);
    this->rows = rows;
    this->cols = cols;
}