//
// Created by julia on 04.03.23.
//

#ifndef SLAE_MPI_HPP
#define SLAE_MPI_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
//x - начальное приближение
template <class T>
std::pair<std::vector<T>, int> MPI(const CSR<T> &A, const std::vector<T> &x, const std::vector<T> &b, T tolerance, T tau){
    std::vector<T> x_ = x;
    std::ofstream outfile;
    outfile.open("/home/julia/CLionProjects/SLAE/src/solve/mpi.txt", std::ofstream::out | std::ofstream::app);
//    outfile << std::fixed;

    std::vector<T> solve = A * x - b;
    int count = 0;
    while (lenght(solve) > tolerance){

        x_ = x_ - tau * solve;
        solve =  A * x_ - b;
        outfile << lenght(solve) << " ";
        count++;
        outfile << count << std::endl;
    }
    outfile.close();
    std::pair<std::vector<T>,int> k = {solve, count};
    return k;
}
#endif //SLAE_MPI_HPP
