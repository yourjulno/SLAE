//
// Created by julia on 04.03.23.
//

#ifndef SLAE_JACOBI_HPP
#define SLAE_JACOBI_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
template <class T>
std::vector<T> Jacobi(const CSR<T> &A, const std::vector<T> &x, const std::vector<T> &b, T tolerance){

    std::vector<T> solve = A * x - b;
    std::vector<T> x_ = x;
    std::vector<T> x_initial;
    int count = 0;
    std::ofstream outfile;
    outfile.open("/home/julia/CLionProjects/SLAE/src/solve/Jacobi.txt",
                 std::ofstream::out | std::ofstream::app);
    T res;

    while (lenght(solve) > tolerance){

        x_initial = x_;
            for (int i = 0; i < A.getCol(); i++){
                res = 0;
                for (int j = A.getMatrRows(i); j < A.getMatrRows(i + 1); j++) {

                    if (i != A.getColns(j)) {
                        res = res + A.getValues(j)*x_initial[A.getColns(j)];
                    }
                    else
                        continue;
                }
            x_[i] = (b[i] - res)/A(i, i);
        }
            solve =  A * x_ - b;
            count++;
        outfile << log(lenght(solve)) << " ";
        outfile << count << std::endl;
        }

    return solve;
}
#endif //SLAE_JACOBI_HPP
