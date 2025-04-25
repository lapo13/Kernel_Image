#include <gtest/gtest.h>
#include "core/Matrix.h"
#include <iostream>


class MatrixTest : public ::testing::Test {
protected:
    void SetUp() {
        // Setup code that runs before each test
        int c = 1;
        matrix = Matrix<int>(3, 4);
        for (int i = 0; i < 3; ++i){
          for (int j = 0; j < 4; ++j){
               matrix(j, i) = c; 
               c++;
          }
        }
    }
    Matrix<int> matrix;
};

TEST_F(MatrixTest, BasicProperties) {
    EXPECT_EQ(matrix.getRows(), 3);
    EXPECT_EQ(matrix.getCols(), 4);
}

TEST_F(MatrixTest, AccessElements) {
     EXPECT_EQ(matrix(0, 0), 1);
     EXPECT_EQ(matrix(1, 0), 2);
     EXPECT_EQ(matrix(2, 0), 3);
     EXPECT_EQ(matrix(3, 0), 4);
     EXPECT_EQ(matrix(0, 1), 5);
     EXPECT_EQ(matrix(1, 1), 6);
     EXPECT_EQ(matrix(2, 1), 7);
     EXPECT_EQ(matrix(3, 1), 8);
     EXPECT_EQ(matrix(0, 2), 9);
     EXPECT_EQ(matrix(1, 2), 10);
     EXPECT_EQ(matrix(2, 2), 11);
     EXPECT_EQ(matrix(3, 2), 12);
}

TEST_F(MatrixTest, GetMax) {
    EXPECT_EQ(matrix.getMax(), 12);
}

TEST_F(MatrixTest, GetMin) {
    EXPECT_EQ(matrix.getMin(), 1);
}

TEST_F(MatrixTest, GetMean) {
    EXPECT_DOUBLE_EQ(matrix.getMean(), 6.5);
}

TEST_F(MatrixTest, OutOfBoundsAccess) {
    EXPECT_THROW(matrix(5, 7), std::out_of_range);
    EXPECT_THROW(matrix(0, 5), std::out_of_range);
    EXPECT_THROW(matrix(-1, 0), std::out_of_range);
    EXPECT_THROW(matrix(0, -1), std::out_of_range);
}