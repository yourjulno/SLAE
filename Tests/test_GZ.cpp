//
// Created by julia on 04.03.23.
//

#include <gtest/gtest.h>
#include "../src/sparse/sparse.hpp"
#include "../src/solve/GZ.hpp"
int main(){
    std::set<Tri<double>> example = {{0,0,100},{0,1,0.2},
                                     {1,0,0.2},{1,1,100}};
    std::vector<double> free = {1000, 999};
    std::vector<double> x = {0,0};


    CSR<double> first(example, 2, 2);
    auto res = GZ(first, x,free, pow(10,-12));

}