#include <Matrix.h>

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows * cols);
}

void Matrix::MatFill(uint8_t* buffer) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i * cols + j] = buffer[i * cols + j];
        }
        //no need for dimension check becouse the matrix has been resized like the buffer
    }
}


void Matrix::MatResize(int rows, int cols) {
    data.resize(rows * cols);
    this->rows = rows;
    this->cols = cols;
}