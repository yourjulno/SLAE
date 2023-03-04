//
// Created by julia on 04.03.23.
//

#ifndef SLAE_GZ_HPP
#define SLAE_GZ_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"

template <class T>
std::vector<T> GZ(const CSR<T> &A, const std::vector<T> &x, const std::vector<T> b,T tolerance){
    std::vector<T> solve = A * x - b;
    std::vector<T> x_ = x;
    T res;
    while (lenght(solve) > tolerance){
        for (int i = 0; i < A.getCol(); i++){
            res = 0;
            for (int j = A.getMatrRows(i); j < A.getMatrRows(i + 1); j++) {

                if (i != A.getColns(j)) {
                    res = res + A.getValues(j)*x_[A.getColns(j)];
                }
                else
                    continue;
            }
            x_[i] = (b[i] - res)/A(i, i);
        }
        solve =  A * x_ - b;
    }
    return solve;
}
#endif //SLAE_GZ_HPP
