//
// Created by julia on 07.04.23.
//

#ifndef SLAE_DESCENT_HPP
#define SLAE_DESCENT_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
//наискорейший градиентный спуск
template <class T>
std::pair<std::vector<T>, std::pair<std::vector<T>, int>> Descent_method(const CSR<T> &A, const std::vector<T> &x, const std::vector<T> &b, T tolerance){
    std::vector<T> x_ = x;
    std::vector<T> r = A * x - b;
    std::vector<T> Ar;
    Ar.reserve(x.size());
    std::ofstream outfile;
    outfile.open("/home/julia/CLionProjects/SLAE/src/solve/Descent.txt",
                 std::ofstream::out | std::ofstream::app);
    outfile << x_[0] << " " << x_.back() << std::endl;
    double alpha;
    int count = 0;
    while (lenght(r) > tolerance){

        Ar = A * r;

        // x_k+1 = x_k - alpha(A * x_k - b)
        // r_k = A * x_k - b
        alpha = r * r / (r * Ar);
        x_ = x_ - alpha * r;

        r =  A * x_ - b;

        count++;
        outfile << x_[0] << " " << x_.back() << std::endl;

    }
    std::pair<std::vector<T>,int> k = {r, count};
    return std::make_pair(x_, k);
}
#endif //SLAE_DESCENT_HPP
