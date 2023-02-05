//
// Created by julia on 05.02.23.
//
#include <vector>
#include <iostream>
#include <string>
#ifndef SLAE_THIRD_DIAGONAL_H
#define SLAE_THIRD_DIAGONAL_H



class ThirdDiagonalMatrix {
private:
    struct line{
        int first;
        int second;
        int third;
    };
    std::vector<line> data_;

public:
    explicit ThirdDiagonalMatrix(unsigned int N);
    /* N - size of matix */
    double & operator()(int i, int j) const;
   /* returns (i, j) of matrix
    * i -- row, j - {0, 1, 2} */
    [[nodiscard]] unsigned int rows() const;

};

#endif //SLAE_THIRD_DIAGONAL_H
