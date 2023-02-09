//
// Created by julia on 05.02.23.
//
#include <vector>
#include <iostream>
#include <string>
#include <array>
#ifndef SLAE_THIRD_DIAGONAL_H
#define SLAE_THIRD_DIAGONAL_H

template<class T>
struct line{
    T first;
    T second;
    T third;
};

template<class T>
class ThirdDiagonalMatrix {
private:

//    double num = 0;
    std::vector<line<T>> data_;

public:
    explicit ThirdDiagonalMatrix(const std::vector<line<T>> &matrix);
    /* N - size of matix */
    std::array<T, 3> & operator[](unsigned int i) const;
   /* returns (i, j) of matrix
    * i -- row, j - {0, 1, 2} */
    [[nodiscard]] unsigned int rows() const;
    /* returns size of matrix */

};

#endif //SLAE_THIRD_DIAGONAL_H
