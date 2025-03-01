#include <stdlib.h>

template <typename T>
class Matrix {

private:
     std::vector<T> data;
     int rows, cols;

public:
     Matrix(int rows, int cols) : rows(rows), cols(cols) {
          data.resize(rows * cols);
     }

     T& operator()(int i, int j) {
          return data[i * cols + j];
     }

     const T& operator()(int i, int j) const {
          return data[i * cols + j];
     }

     int getRows() const {
          return rows;
     }

     int getCols() const {
          return cols;
     }

     typename std::vector<T>::iterator begin() {
          return data.begin();
     }

     typename std::vector<T>::iterator end() {
          return data.end();
     }

     typename std::vector<T>::const_iterator begin() const {
          return data.begin();
     }

     typename std::vector<T>::const_iterator end() const {
          return data.end();
     }

     void MatFill(T value);
     void MatResize(int rows, int cols);

};