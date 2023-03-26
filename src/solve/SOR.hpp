//
// Created by julia on 22.03.23.
//

#ifndef SLAE_SOR_HPP
#define SLAE_SOR_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"
#include <iostream>
#include "MPI.hpp"
template <class T>
std::pair<std::vector<T>,int> SOR(const CSR<T> &A, const std::vector<T> &x,
                                  const std::vector<T> b, const T tolerance, const T omega){
    std::vector<T> solve = A * x - b;
    std::vector<T> x_ = x;
    const T maxl = max_lambda(A);

    int count = 0;
    T res;
    while (lenght(solve) > tolerance){

        for (int i = 0; i < A.getCol(); i++){
            res = 0;
            T d;
            for (int j = A.getMatrRows(i); j < A.getMatrRows(i + 1); j++) {

                if (i != A.getColns(j)) {
                    res = res + omega * A.getValues(j)*x_[A.getColns(j)];
                }
                else
                    d = A.getValues(j);
            }

            x_[i] = (b[i] * omega / d - res / d ) - (omega - 1) * x_[i];
        }
        solve =  A * x_ - b;
        count++;
    }
    std::pair<std::vector<double>, int> k = {solve, count};
    return k;
}

template <class T>
std::pair<std::vector<T>,int> SSOR(const CSR<T> &A, const std::vector<T> &x,
                                   const std::vector<T> b, const T tolerance, const T omega ){

}
#endif //SLAE_SOR_HPP
