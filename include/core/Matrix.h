#include <vector>

class Matrix {

private:
     std::vector<uint8_t> data;
     int rows, cols;

public:
     Matrix(int rows, int cols);

     uint8_t& operator()(int i, int j) {
          return data[i * cols + j];
     }
     const uint8_t& operator()(int i, int j) const {
          return data[i * cols + j];
     }

     int getRows() const {
          return rows;
     }

     int getCols() const {
          return cols;
     }

     void MatFill(uint8_t* buffer);
     void MatResize(int rows, int cols);

     ~Matrix() {
          data.clear();
     }
};