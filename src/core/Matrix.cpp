#include "core/Matrix.h"
#include <iostream>

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows * cols);
}

void Matrix::MatResize(int rows, int cols) {
    data.resize(rows * cols);
    this->rows = rows;
    this->cols = cols;
}