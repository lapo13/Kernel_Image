#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

class Matrix {

private:
    std::vector<unsigned char> data;
    int rows, cols;

public:
    Matrix(int rows, int cols);

    unsigned char& operator()(int i, int j) {
        return data[i * cols + j];
    }
    const unsigned char& operator()(int i, int j) const {
        return data[i * cols + j];
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    void MatFill(unsigned char* buffer);
    void MatResize(int rows, int cols);

    ~Matrix() {
        data.clear();
    }
};

#endif //MATRIX_H