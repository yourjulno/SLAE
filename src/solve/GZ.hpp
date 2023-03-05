//
// Created by julia on 04.03.23.
//

#ifndef SLAE_GZ_HPP
#define SLAE_GZ_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
template <class T>
std::pair<std::vector<T>,int> GZ(const CSR<T> &A, const std::vector<T> &x, const std::vector<T> b,T tolerance){
    std::vector<T> solve = A * x - b;
    std::vector<T> x_ = x;
    std::ofstream outfile;
    outfile.open("/home/julia/CLionProjects/SLAE/src/solve/GZ.txt", std::ofstream::out | std::ofstream::app);


    int count = 0;
    T res;
    while (lenght(solve) > tolerance){
        outfile << log(lenght(solve)) << " ";
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
        count++;
        outfile << count << std::endl;
    }
    outfile.close();

    std::pair<std::vector<double>, int> k = {solve, count};
    return k;
}
#endif //SLAE_GZ_HPP
