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

    Matrix(const T* imgBuffer, int width, int height): rows(height), cols(width) { 
        data = std::vector<T>(imgBuffer, imgBuffer + width * height);
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

    T getMax() const {
    T max = (*this)(0, 0);
        for(int i = 0; i < this->rows; ++i) {
            for(int j = 0; j < this->cols; ++j) {
                if((*this)(j, i) > max) {
                    max = (*this)(j, i);
                }
            }
        }
        return max;
    };

    T getMin() const {
        T min = (*this)(0, 0);
        for(int i = 0; i < this->rows; ++i) {
            for(int j = 0; j < this->cols; ++j) {
                if((*this)(j, i) < min) {
                    min = (*this)(j, i);
                }
            }
        }
        return min;
    };

    double getMean() const {
        double sum = 0;
        for(int i = 0; i < this->getRows(); ++i) {
            for(int j = 0; j < this->getCols(); ++j) {
                sum += (double)((*this)(j, i));
            }
        }
        return (sum / (this->getRows() * this->getCols()));
    };

    int getRows() const {
        return rows;
    }
    int getCols() const {
        return cols;
    }

    ~Matrix() {
        data.clear();
    }
};

#endif //MATRIX_H