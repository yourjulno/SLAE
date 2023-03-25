//
// Created by julia on 22.03.23.
//
#include <gtest/gtest.h>
#include "../src/sparse/sparse.hpp"
#include "../src/solve/SOR.hpp"

TEST(FIRST, SOR) {
    std::set<Tri<double>> example = {{0, 0, 10},
                                     {0, 1, 1},
                                     {1, 0, 1},
                                     {1, 1, 7},
                                     {1, 2, 0.1},
                                     {2, 2, 1}};
    std::vector<double> free = {20, 30, 1};
    std::vector<double> x = {0, 0, 0};
    CSR<double> first(example, 3, 3);
    auto res_from_sor = SOR(first, x, free, 1e-12);
    std::cout << res_from_sor.second;
}