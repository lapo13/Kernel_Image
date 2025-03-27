#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

template <typename T>
class Matrix {

private:
    std::vector<T> data;
    int rows, cols;

public:
    Matrix(int rows, int cols);

    T& operator()(int i, int j) {
        return data[i* rows + j]; 
    }
    const T& operator()(int i, int j) const {
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