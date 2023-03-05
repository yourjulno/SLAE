//
// Created by julia on 05.03.23.
//
#include <gtest/gtest.h>
#include <ostream>
#include "../src/sparse/sparse.hpp"
#include "../src/solve/GZ.hpp"
#include "../src/solve/Jacobi.hpp"
#include "../src/solve/MPI.hpp"

int main(){

    std::set<Tri<double>> a = {{0, 0, 12}, {0, 1, 17}, {0, 2, 3},
                               {1, 0, 17}, {1, 1, 15825}, {1, 2, 28},
                               {2, 0, 3}, {2, 1, 28}, {2, 2, 238}};

    std::vector<double> b = {1, 2, 3};
    std::vector<double> x = {1, 1, 1};
    auto first = CSR<double>(a, 3, 3);

    //auto k = Jacobi(first, x, b, pow(10, -5));
//    auto l = GZ(first, x, b, pow(10, -5));
    auto p = MPI(first, x, b, pow(10, -3), pow(10, -6));
//    std::cout << k.second << " ";
//    for (auto i : k.first){
//        std::cout << i;
//    }
}