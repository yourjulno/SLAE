//
// Created by julia on 20.02.23.
//

#ifndef SLAE_HOUSEHOLDER_H
#define SLAE_HOUSEHOLDER_H

#include "../dense_matrix.hpp"

template <class T>
DenseMatrix<T> Householder_alg(const DenseMatrix<T> &start_matrix) {
    int m = start_matrix.getColns(); // кол-во столбцов
    int n = start_matrix.getRows(); // кол-во строк
    std::vector<T> v;
//    T betta;
//    T sigma;
    auto copy_matrix = start_matrix;
    auto copy_matrix2 = start_matrix;
    for (std::size_t i = 0; i != m; i++){
        for (std::size_t j = i; j < n; j++) {
            copy_matrix[j][j] = lenght(copy_matrix[j]);
            v = copy_matrix[j];
            double betta = v * start_matrix[i];
            double sigma = v * v;
            copy_matrix[j] = copy_matrix[j] - 2. * ((betta / sigma) * v);
        }

    }
    return copy_matrix2;


}

#endif //SLAE_HOUSEHOLDER_H
