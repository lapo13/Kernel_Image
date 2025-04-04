#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

template <typename T>
class Matrix {

private:
    std::vector<T> data;
    int rows, cols;

public:
    Matrix(int rows = 2, int cols = 2) : rows(rows), cols(cols) {
        data.resize(rows * cols);
    }  

    T& operator()(int x, int y) {
        if (x < 0 || x >= cols || y < 0 || y >= rows) {
            throw std::out_of_range("Matrix index out of range");
        }
        return data[y* cols + x]; 
    }
    const T& operator()(int x, int y) const {
        if (x < 0 || x >= cols || y < 0 || y >= rows) {
            throw std::out_of_range("Matrix index out of range");
        }
        return data[y* cols + x]; 
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