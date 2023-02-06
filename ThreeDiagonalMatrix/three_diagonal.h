//
// Created by julia on 05.02.23.
//
#include <vector>
#include <iostream>
#include <string>
#include <array>
#ifndef SLAE_THIRD_DIAGONAL_H
#define SLAE_THIRD_DIAGONAL_H
struct line{
    double first;
    double second;
    double third;
};


class ThirdDiagonalMatrix {
private:

//    double num = 0;
    std::vector<line> data_;

public:
    explicit ThirdDiagonalMatrix(const std::vector<line> &matrix);
    /* N - size of matix */
    double & operator()(unsigned int i, unsigned int j) const;
   /* returns (i, j) of matrix
    * i -- row, j - {0, 1, 2} */
    [[nodiscard]] unsigned int rows() const;
    /* returns size of matrix */

};

#endif //SLAE_THIRD_DIAGONAL_H
