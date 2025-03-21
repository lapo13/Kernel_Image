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
        return data[i* rows + j]; 
    }
    const unsigned char& operator()(int i, int j) const {
        return data[i* rows + j]; 
    }

    int getRows() const {
        return rows;
    }
    int getCols() const {
        return cols;
    }

    void MatResize(int rows, int cols);

    ~Matrix() {
        data.clear();
    }
};

#endif //MATRIX_H